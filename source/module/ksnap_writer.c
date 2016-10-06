

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

void conv_add_dirty_page_to_lookup(struct vm_area_struct * vma, struct snapshot_pte_list * new_dirty_entry,
                                   unsigned long page_index, unsigned long line_index, uint8_t is_page_level){
    unsigned long index = cv_logging_get_index(page_index, line_index, is_page_level);
    if (new_dirty_entry){
        int insert_error = radix_tree_insert(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index, new_dirty_entry);
        if (insert_error == -EEXIST){
            radix_tree_delete(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index);
            radix_tree_insert(&(ksnap_vma_to_userdata(vma))->dirty_list_lookup, index, new_dirty_entry);
        }
    }
}

struct snapshot_pte_list * conv_dirty_search_lookup_line_and_page(struct ksnap_user_data * cv_user_data,
                                                    unsigned long page_index, unsigned long line_index){
    struct snapshot_pte_list * result;
    //start with the line index
    unsigned long index = cv_logging_get_index(page_index, line_index, 0);
    result = radix_tree_lookup(&cv_user_data->dirty_list_lookup, index);
    if (!result){
        //try with pages
        index = cv_logging_get_index(page_index, line_index, 1);
        result = radix_tree_lookup(&cv_user_data->dirty_list_lookup, index);
    }
    return result;
}

struct snapshot_pte_list * conv_dirty_search_lookup(struct ksnap_user_data * cv_user_data,
                                                    unsigned long page_index, unsigned long line_index, uint8_t is_page_level){
    unsigned long index = cv_logging_get_index(page_index, line_index, is_page_level);
    return radix_tree_lookup(&cv_user_data->dirty_list_lookup, index);
}

void conv_dirty_delete_lookup(struct ksnap_user_data * cv_user_data,
                              unsigned long page_index, unsigned long line_index, uint8_t is_page_level){
    unsigned long index = cv_logging_get_index(page_index, line_index, is_page_level);
    radix_tree_delete(&cv_user_data->dirty_list_lookup, index);
}

void ksnap_revert_dirty_list(struct vm_area_struct * vma, struct address_space * mapping){

}

void ksnap_add_dirty_page_to_list (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address){
  struct snapshot_pte_list * pte_list_entry, * dirty_pages_list;
  struct page * new_page, * checkpoint_page;
  struct ksnap_user_data * cv_user;
  struct ksnap * cv_seg;
  struct cv_page_entry * cv_page;
  int counter=0;

  cv_seg = ksnap_vma_to_ksnap(vma);
  cv_user=ksnap_vma_to_userdata(vma);

  if (!cv_user->dirty_pages_list){
    cv_user->dirty_pages_list = _snapshot_create_pte_list();
  }
  dirty_pages_list = cv_user->dirty_pages_list;
  struct ksnap * ksnap_segment = ksnap_vma_to_ksnap(vma);
  /*grab the new page*/
  new_page=pte_page(*new_pte);
  if (new_page!=pte_page(*new_pte)){
    BUG();
  }

  //is this page already in the dirty list? then this is the result of a checkpoint
  if ((pte_list_entry=conv_dirty_search_lookup(cv_user, new_page->index, 0, 1))){
      if (pte_list_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING){
          cv_page=cv_list_entry_get_page_entry(pte_list_entry);
          cv_page->pfn = pte_pfn(*new_pte);
          cv_memory_accounting_inc_pages(ksnap_segment);
          CV_LOG_MESSAGE("ksnap_writer: pid: %d writing to checkpointed page: %d\n", current->pid, new_page->index);
      }
      else{
          BUG();
      }
  }
  else{
        /*create the new pte entry*/
      pte_list_entry = kmem_cache_alloc(ksnap_segment->pte_list_mem_cache, GFP_KERNEL);
      //mark it as a page (and not logging)
      pte_list_entry->type=CV_DIRTY_LIST_ENTRY_TYPE_PAGING;
      pte_list_entry->page_index = new_page->index;
      pte_list_entry->obsolete_version=~(0x0);
      pte_list_entry->mm = current->mm;
      pte_list_entry->checkpoint = 0;
      pte_list_entry->wait_revision = 0;
      //grab the inner entry for paging
      cv_page=cv_list_entry_get_page_entry(pte_list_entry);
      conv_add_dirty_page_to_lookup(vma,pte_list_entry, new_page->index,0,1);
      INIT_LIST_HEAD(&pte_list_entry->list);
      cv_page->pte = new_pte;
      cv_page->addr = address;
      cv_page->pfn = pte_pfn(*new_pte);
      cv_page->ref_page = old_page;
      conv_set_checkpoint_page(cv_page,0);
      /*now we need to add the pte to the list */
      list_add_tail(&pte_list_entry->list, &dirty_pages_list->list);
      CV_LOG_MESSAGE(" %d added index %lu pfn %lu page %p", current->pid, pte_list_entry->page_index, cv_page->pfn, new_page);
      cv_meta_inc_dirty_page_count(vma);
      cv_user->dirty_pages_list_count++;
      cv_page_debugging_clear_flags(new_page,counter);
      cv_memory_accounting_inc_pages(ksnap_segment);


#ifdef CONV_LOGGING_ON
      /*DEBUGGING*/
      if (cv_page->ref_page){
          uint8_t * ref_kaddr = (uint8_t *)kmap_atomic(cv_page->ref_page, KM_USER0);
          CV_LOG_MESSAGE("COW pid: %d ref_page page: %d page %p, new_page %p, version %lu\n",
                 current->pid, pte_list_entry->page_index, cv_page->ref_page, new_page, cv_user->version_num);
          CV_LOGGING_DEBUG_PRINT_LINE(ref_kaddr + (CV_LOGGING_LOG_SIZE * 2), pte_list_entry->page_index, 0, "ksnap_write: COW");
          kunmap_atomic(ref_kaddr, KM_USER0);
      }
      /**************/
#endif
      
  }
  CV_HOOKS_COW(cv_seg, cv_user, new_page->index);
  INC(COUNTER_COW_FAULT);
}
