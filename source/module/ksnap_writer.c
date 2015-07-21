

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
#include "cv_debugging.h"
#include "cv_memory_accounting.h"

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

void conv_dirty_delete_lookup(struct ksnap_user_data * cv_user_data, unsigned long index){
    radix_tree_delete(&cv_user_data->dirty_list_lookup, index);
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
  struct page * new_page, * checkpoint_page;
  struct ksnap_user_data * cv_user_data;
  int counter=0;
 
  cv_user_data=ksnap_vma_to_userdata(vma);

  if (!cv_user_data->dirty_pages_list){
    cv_user_data->dirty_pages_list = _snapshot_create_pte_list();
  }
  dirty_pages_list = cv_user_data->dirty_pages_list;
  struct ksnap * ksnap_segment = ksnap_vma_to_ksnap(vma);
  /*grab the new page*/
  new_page=pte_page(*new_pte);
  if (new_page!=pte_page(*new_pte)){
    BUG();
  }

  //is this page already in the dirty list? then this is the result of a checkpoint
  if ((pte_list_entry=conv_dirty_search_lookup(cv_user_data, new_page->index))){
      //printk(KERN_EMERG "old pfn 1 %llu, new pfn %llu, address %p, pid %d\n", pte_list_entry->pfn, pte_pfn(*new_pte), address, current->pid);
      pte_list_entry->pfn = pte_pfn(*new_pte);
      cv_memory_accounting_inc_pages(ksnap_segment);      
  }
  else{
        /*create the new pte entry*/
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
      pte_list_entry->mm = current->mm;
      pte_list_entry->checkpoint = 0;
      conv_set_checkpoint_page(pte_list_entry,0);
      /*now we need to add the pte to the list */
      list_add_tail(&pte_list_entry->list, &dirty_pages_list->list);
      //printk(KERN_EMERG "new pfn 2 %llu, address %p, pid %d\n", pte_list_entry->pfn, address, current->pid);
      
      #ifdef CONV_LOGGING_ON
          printk(KSNAP_LOG_LEVEL " %d added index %lu pfn %lu page %p", current->pid, pte_list_entry->page_index, pte_list_entry->pfn, new_page);
      #endif


      cv_meta_inc_dirty_page_count(vma);
      cv_user_data->dirty_pages_list_count++;
      cv_page_debugging_clear_flags(new_page,counter);
      cv_memory_accounting_inc_pages(ksnap_segment);
  }
}
