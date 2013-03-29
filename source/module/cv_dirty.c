
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

#include "ksnap.h"
#include "cv_dirty.h"

//we keep a radix tree to make it easier to lookup entries in our dirty list
void __add_dirty_page_to_lookup(struct vm_area_struct * vma, struct snapshot_pte_list * new_dirty_entry, unsigned long index){
  struct ksnap_user_data * cv_user_data = ksnap_vma_to_userdata(vma);
  if (new_dirty_entry){
    int insert_error = radix_tree_insert(&cv_user_data->dirty_list_lookup, index, new_dirty_entry);
    if (insert_error == -EEXIST){
      radix_tree_delete(&cv_user_data->dirty_list_lookup, index);
      radix_tree_insert(&cv_user_data->dirty_list_lookup, index, new_dirty_entry);
    }
  }
}

//This gets called from the page fault code...adds a new entry to the dirty list. We assume the new page has
//already been allocated.
void cv_dirty_add(struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address){

  struct snapshot_pte_list * pte_list_entry, * dirty_pages_list;
  struct page * new_page;
  struct ksnap * cv_seg;
  struct ksnap_user_data * cv_user_data;
 
  cv_user_data=ksnap_vma_to_userdata(vma);
  cv_seg=ksnap_vma_to_ksnap(vma);

  dirty_pages_list = cv_user_data->dirty_pages_list;
  /*grab the new page*/
  new_page=pte_page(*new_pte);
  lock_page(new_page);
  if (new_page!=pte_page(*new_pte)){
    BUG();
  }
  /*create the new pte entry*/
  pte_list_entry = kmem_cache_alloc(cv_seg->pte_list_mem_cache, GFP_KERNEL);
  __add_dirty_page_to_lookup(vma,pte_list_entry, new_page->index);
  INIT_LIST_HEAD(&pte_list_entry->list);
  pte_list_entry->pte = new_pte;
  pte_list_entry->addr = address;
  pte_list_entry->pfn = pte_pfn(*new_pte);
  pte_list_entry->ref_page = old_page;
  pte_list_entry->page_index = new_page->index;
  pte_list_entry->debug_flags = 0;
  pte_list_entry->obsolete_revision = ~(0);
  /*now we need to add the pte to the list */
  list_add_tail(&pte_list_entry->list, &dirty_pages_list->list);
  cv_user_data->dirty_page_count+=1;
  //add this lock to the list we'll need to acquire
  unlock_page(new_page);
}

struct snapshot_pte_list * cv_dirty_lookup(struct vm_area_struct * vma, unsigned long index){
  return radix_tree_lookup(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index);
}

void cv_dirty_remove(struct ksnap_user_data * cv_user_data, struct snapshot_pte_list * entry){
  radix_tree_delete(&cv_user_data->dirty_list_lookup, entry->page_index);
  list_del(&entry->list);
  cv_user_data->dirty_page_count-=1; 
}
