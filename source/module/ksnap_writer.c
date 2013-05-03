

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/list.h>
#include <linux/swap.h>
#include <linux/poison.h>
#include <linux/hardirq.h>
#include <asm/tlbflush.h>

#include "conversion.h"
#include "ksnap_writer.h"
#include "ksnap_version_list.h"
#include "cv_stats.h"
#include "cv_meta_data.h"
#include "cv_pte.h"
#include "cv_lock_list.h"

unsigned long tmp_elapsed_time_in_microseconds(struct timeval * old_tv, struct timeval * current_tv){

	unsigned long secs;
	//get current time
	do_gettimeofday(current_tv);
	secs = current_tv->tv_sec - old_tv->tv_sec;

	if (secs){
		return ((secs * 1000000) - old_tv->tv_usec) + current_tv->tv_usec;
	}
	else
		return current_tv->tv_usec - old_tv->tv_usec;
}

void tmp_ksnap_print_dirty(struct vm_area_struct * vma){
  struct snapshot_pte_list * pte_entry;
  struct list_head * pos, * tmp;

  if (ksnap_vma_to_userdata(vma)->dirty_pages_list){
    list_for_each_safe(pos, tmp, &(ksnap_vma_to_userdata(vma)->dirty_pages_list->list)){
      pte_entry = list_entry(pos, struct snapshot_pte_list, list);
      if (pte_entry){
	list_del(pos);
      }
    }
  }
}


void __add_dirty_page_to_lookup(struct vm_area_struct * vma, struct snapshot_pte_list * new_dirty_entry, unsigned long index){

  if (new_dirty_entry){
    int insert_error = radix_tree_insert(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index, new_dirty_entry);
    if (insert_error == -EEXIST){
      radix_tree_delete(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index);
      radix_tree_insert(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index, new_dirty_entry);
    }
  }
}

struct snapshot_pte_list * conv_dirty_search_lookup(struct ksnap_user_data * cv_user_data, unsigned long index){
  return radix_tree_lookup(&cv_user_data->dirty_list_lookup, index);
}


void ksnap_revert_dirty_list(struct vm_area_struct * vma, struct address_space * mapping){

}

struct page * ksnap_get_dirty_ref_page(struct vm_area_struct * vma, unsigned long index){
  struct snapshot_pte_list * pte_entry;

  if (ksnap_vma_to_userdata(vma)->dirty_pages_list){
    pte_entry = conv_dirty_search_lookup(vma, index);
    if (pte_entry)
      return pte_entry->ref_page;
  }
  return NULL;
  }



void ksnap_add_dirty_page_to_list (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address){
  struct snapshot_pte_list * pte_list_entry, * dirty_pages_list;
  struct page * new_page;
  struct ksnap_user_data * cv_user_data;
 
  cv_user_data=ksnap_vma_to_userdata(vma);

  if (!cv_user_data->dirty_pages_list){
    cv_user_data->dirty_pages_list = _snapshot_create_pte_list();
  }
  dirty_pages_list = cv_user_data->dirty_pages_list;
  struct ksnap * ksnap_segment = ksnap_vma_to_ksnap(vma);
  /*grab the new page*/
  new_page=pte_page(*new_pte);
  lock_page(new_page);
  if (new_page!=pte_page(*new_pte)){
    BUG();
  }
  /*create the new pte entry*/
  //pte_list_entry = kmalloc(sizeof(struct snapshot_pte_list), GFP_KERNEL);
  pte_list_entry = kmem_cache_alloc(ksnap_segment->pte_list_mem_cache, GFP_KERNEL);
  __add_dirty_page_to_lookup(vma,pte_list_entry, new_page->index);
  INIT_LIST_HEAD(&pte_list_entry->list);
  pte_list_entry->pte = new_pte;
  pte_list_entry->addr = address;
  pte_list_entry->pfn = pte_pfn(*new_pte);
  pte_list_entry->ref_page = old_page;
  pte_list_entry->page_index = new_page->index;
  pte_list_entry->obsolete_version=~(0x0);
  pte_list_entry->wait_revision = 0;
  /*now we need to add the pte to the list */
  list_add_tail(&pte_list_entry->list, &dirty_pages_list->list);
  #ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL " %d added index %lu pfn %lu", current->pid, pte_list_entry->page_index, pte_list_entry->pfn);
  #endif

  /*add it to the meta data for tracking*/
  if (cv_user_data->use_tracking){
    ksnap_meta_add_dirty_page(vma, pte_list_entry->page_index);
  }
  //cv_lock_list_add_entry(cv_user_data->dirty_lock_list, cv_lock_list_index(address, vma));
  atomic_inc(&cv_user_data->dirty_page_count);
  cv_user_data->dirty_pages_list_count++;
  //add this lock to the list we'll need to acquire
  unlock_page(new_page);

}

/*remove the old page from the page cache, handle its LRU stuff, etc...*/
void ksnap_remove_old_page(struct address_space * mapping, 
			   struct vm_area_struct * vma, unsigned long index, 
			   unsigned long * debug_time, struct page * ref_page){


  struct list_head * old_entry_lh;
  struct snapshot_pte_list * old_entry; 
  struct page * page_test;

  old_entry_lh = radix_tree_lookup(&mapping_to_ksnap(mapping)->snapshot_page_tree, index);
  /*if (index%80==0){
    printk(KSNAP_LOG_LEVEL "PID %d REMOVED FROM LOOKUP index %lu entry %p radix %p\n", current->pid, index, old_entry_lh, &mapping_to_ksnap(mapping)->snapshot_page_tree); 
    }*/
  if (old_entry_lh==NULL){
    return;
  }
  old_entry = list_entry(old_entry_lh, struct snapshot_pte_list, list);
  page_test = pfn_to_page(old_entry->pfn);

  //printk("REMOVE PFN %lu %p\n", old_entry->pfn, page_test);
  BUG_ON(page_test==NULL);

  if (page_test){
    lock_page(page_test);
    BUG_ON(page_count(page_test)==0);
    remove_pte_entry_from_version_list(&mapping_to_ksnap(mapping)->snapshot_page_tree, index, mapping_to_ksnap(mapping)); 
    ClearPageDirty(page_test);
    SetPageSwapBacked(page_test);
    
    unlock_page(page_test);
    put_page(page_test);
    //another for the "reference" we keep around for merging
    if (ref_page){
      put_page(ref_page);
    }
  }
  return;
}

void ksnap_commit_new_page(struct address_space * mapping, struct vm_area_struct * vma, 
			   struct page * page, struct list_head * pte_entry_list_head, unsigned long * debug_time){

  int insert_error;
  lock_page(page);
  //make sure the page wasn't free'd out from under us
  if (!page_count(page)){
    printk("kSnap: page in change set was freed out from under us\n");
    BUG();
  }
  do{
    //lets now add our new pte into the pte radix tree

    insert_error = radix_tree_insert(&mapping_to_ksnap(mapping)->snapshot_page_tree, page->index, pte_entry_list_head);
    //if it wasn't an eexist error, then something is wrong and we have a bug
    if (insert_error == -EEXIST){
      remove_pte_entry_from_version_list(&mapping_to_ksnap(mapping)->snapshot_page_tree, page->index, mapping_to_ksnap(mapping));
    }
    else if(insert_error){
      printk("kSnap: error inserting a page into our version list radix tree");
      BUG();
      return;
    }
  }while(insert_error);
  /*if (page->index%80==0){
    printk(KSNAP_LOG_LEVEL "INSERTED existed %d entry %p into index %lu radix tree %p, lookup %p\n", 
    insert_error, pte_entry_list_head, page->index, &mapping_to_ksnap(mapping)->snapshot_page_tree, radix_tree_lookup(&mapping_to_ksnap(mapping)->snapshot_page_tree, page->index));
    }*/
  

  get_page(page);
  unlock_page(page);
  return;
}
