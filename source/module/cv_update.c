

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
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <linux/kdebug.h>
#include <linux/notifier.h>
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/mman.h>
#include <linux/hardirq.h>

#include "ksnap.h"
#include "cv_init.h"
#include "ksnap_version_list.h"
#include "ksnap_writer.h"
#include "cv_pte.h"
#include "cv_stats.h"
#include "cv_meta_data.h"
#include "cv_merge.h"
#include "cv_tlb.h"
#include "cv_lock_list.h"
#include "cv_update.h"

void __debug_print_dirty_list(struct ksnap_user_data * cv_user){
  struct snapshot_pte_list * pte_entry;
  struct list_head * pos, * tmp_pos; //pointers for iterating
  printk(KSNAP_LOG_LEVEL "DIRTY LIST FOR %d\n", current->pid);
  list_for_each_safe(pos, tmp_pos, &(cv_user->dirty_pages_list->list)){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    printk(KSNAP_LOG_LEVEL "      dirty..... index %lu pfn %lu\n", pte_entry->page_index, pte_entry->pfn);
  }

}

void __cv_update_parallel(struct vm_area_struct * vma, unsigned long flags, uint64_t target_version_input){
  //struct vm_area_struct * master_vma;
  /*for iterating through the list*/
  struct list_head * pos, * pos_outer, * pos_outer_tmp, * ls, * new_list;
  /*for storing pte values from list*/
  struct snapshot_pte_list * tmp_pte_list, * dirty_entry;
  struct snapshot_version_list * latest_version_entry;
  struct address_space * mapping;
  int gotten_pages = 0;
  struct page * ref_page;
  int merge_count=0;
  unsigned int merge=(flags & MS_KSNAP_GET_MERGE);
  unsigned int merge_only=(flags & MS_KSNAP_GET_MERGE) && (flags & MS_KSNAP_DETERM_LAZY);
  unsigned int update_only=(flags & MS_KSNAP_GET) && (flags & MS_KSNAP_DETERM_LAZY);
  int flush_entire_tlb=0;
  struct ksnap * cv_seg;
  struct ksnap_user_data * cv_user;
  uint64_t target_version_number; //what version are we updating to?
  struct snapshot_version_list * version_list, * list_to_stop_at;

  cv_stats_function_init();

  cv_stats_start(mapping_to_ksnap(mapping), 0, update_latency);
  if (vma==NULL || vma->vm_mm == NULL || vma->vm_file==NULL || vma->vm_file->f_mapping==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: vma not setup right\n");
  }

  //printk(KSNAP_LOG_LEVEL "IN UPDATE %d\n", current->pid);

  mapping=vma->vm_file->f_mapping;
  //get the conversion segment data structure
  cv_seg=ksnap_vma_to_ksnap(vma);
  //get the user segment data structure
  cv_user=ksnap_vma_to_userdata(vma);
  //if we aren't merging then revert everything in our dirty page list
  if (!merge){
    ksnap_revert_dirty_list(vma, mapping);
  }

  if (cv_seg==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: segment is null for some reason, vma is %p vm_file %p f_mapping %p seg %p\n", 
	   vma, vma->vm_file, vma->vm_file->f_mapping, vma->vm_file->f_mapping->ksnap_data);
  }

  //if the target was passed in....use that!
  target_version_number=(target_version_input==0) ? atomic64_read(&cv_seg->committed_version_atomic) : target_version_input;
  list_to_stop_at=(struct snapshot_version_list *)atomic64_read(&cv_seg->uncommitted_version_entry_atomic);


  if (target_version_number<=cv_user->version_num){
    return;
  }

  cv_stats_end(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), 0, update_latency);
  //grab the head of the version list
  version_list=(struct snapshot_version_list *)mapping_to_ksnap(mapping)->snapshot_pte_list;
  //we're going to update, so increment the stats
  cv_stats_inc_reader_get_snapshots(&cv_seg->cv_stats);        
  //only go in here if there is an element in the list (prev != next)
  if (version_list && version_list->list.prev != version_list->list.next){
    //if the subscriber's vma has a previous ptr into the list, use that. If not, just use the entire list
    ls = (vma->snapshot_pte_list) ? (struct list_head *)vma->snapshot_pte_list :  version_list->list.prev;
    //printk("up: Starting with %p pid %d\n", ls, current->pid);
    //we set the subscribers version list ptr to new_list at the end, so lets start it at NULL
    new_list=NULL;
    //TODO: make the TLB stuff work with our new setup
    flush_entire_tlb=0;
    //start walking through the list....stop when you get to any list with a version number greater than what we're updating to
    for (pos_outer = ls, pos_outer_tmp = pos_outer->prev;
	 prefetch(pos_outer->prev), pos_outer != &list_to_stop_at->list;
	 pos_outer = pos_outer_tmp, pos_outer_tmp = pos_outer->prev){
      //get the version entry
      latest_version_entry = list_entry( pos_outer, struct snapshot_version_list, list);
      if (!latest_version_entry->visible || latest_version_entry->version_num > target_version_number){
	//printk(KSNAP_LOG_LEVEL "not visible....%d version %p number %d target %d visible %d\n", 
	//     current->pid, latest_version_entry, latest_version_entry->version_num, target_version_number, latest_version_entry->visible);
	break;
      }
      else if (latest_version_entry->committer == vma){
	//printk(KSNAP_LOG_LEVEL "committer thing....%d\n", current->pid);
	//no need to update to stuff we committed
	new_list = pos_outer;
	continue;
      }
      uint64_t register v = latest_version_entry->version_num;
      //OK, lets now walk the actual committed ptes
      list_for_each(pos, &latest_version_entry->pte_list->list){
	//get the pte entry
	tmp_pte_list = list_entry(pos, struct snapshot_pte_list, list);
	//is the pte outdated? If so, then no use wasting time updating our page table
	if (tmp_pte_list->obsolete_version <= target_version_number){
	  //printk(KSNAP_LOG_LEVEL "Found an obsolete entry obsolete %lu target %lu\n", tmp_pte_list->obsolete_version, target_version_number);
	  continue;
	}
	//printk(KSNAP_LOG_LEVEL "Updating %lu pid %d\n", tmp_pte_list->page_index, current->pid);
	if (merge && 
	    !update_only &&
	    ksnap_meta_search_dirty_list(vma, tmp_pte_list->page_index) &&
	    (dirty_entry=conv_dirty_search_lookup(cv_user, tmp_pte_list->page_index)) ){
	  //we have to merge our changes with the committed stuff
	  ksnap_merge(pfn_to_page(tmp_pte_list->pfn), 
		      (unsigned int *)((tmp_pte_list->page_index << PAGE_SHIFT) + vma->vm_start),
		      dirty_entry->ref_page, pfn_to_page(tmp_pte_list->pfn));
	  //cv_stats_inc_merged_pages(&cv_seg->cv_stats);
	  merge_count++;
	}
	else if (!merge_only){
	  /*if (tmp_pte_list->page_index == 65){
	    printk(KSNAP_LOG_LEVEL "pid %d updating 65 pfn %lu, version %lu, target %lu, merge %d, dirty %p\n", current->pid,
		   tmp_pte_list->pfn, latest_version_entry->version_num, target_version_number, merge, ksnap_get_dirty_ref_page(vma, tmp_pte_list->page_index));
	    __debug_print_dirty_list(cv_user);
	    }*/
	  pte_copy_entry (tmp_pte_list->pte, tmp_pte_list->pfn, tmp_pte_list->page_index, vma, !flush_entire_tlb);
	  ++gotten_pages;
	}
      }
      //done traversing a list of ptes
      new_list = pos_outer;
    }
    //done traversing the versions
    //printk(KSNAP_LOG_LEVEL "Merge only %d new list %p pid %d\n", merge_only, new_list, current->pid);

    //we only change the position of our current version if it wasn't a merge_only
    if (!merge_only && new_list){
      latest_version_entry = list_entry( new_list, struct snapshot_version_list, list);
      atomic_inc(&latest_version_entry->ref_c);
      //only set it to the new list if it's not null
      vma->snapshot_pte_list = (new_list) ? new_list : vma->snapshot_pte_list;
      //printk(KSNAP_LOG_LEVEL "Setting new list to %p pid %d\n", vma->snapshot_pte_list, current->pid);
      //set the new version
      ksnap_meta_set_local_version(vma,target_version_number);
      cv_user->version_num=target_version_number;
    }
    
    if (flush_entire_tlb){
      flush_tlb();
    }
  }

  #ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "UPDATE: pid %d updated to version %llu and merged %d pages and updated %d pages target_input %lu\n", 
  	 current->pid, target_version_number, merge_count, gotten_pages, target_version_input);
  #endif



  cv_stats_add_counter(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), gotten_pages, update_pages);
  return;
}


void cv_update_parallel(struct vm_area_struct * vma, unsigned long flags){
  __cv_update_parallel(vma, flags, 0);
}

//update to a specific version...called by commit and merging is already done
void cv_update_parallel_to_version_no_merge(struct vm_area_struct * vma, uint64_t version){
  //TODO: the flags here are dumb and don't really make a lot of sense in this context. They need to be fixed
  __cv_update_parallel(vma,  (MS_KSNAP_GET | MS_KSNAP_DETERM_LAZY), version);
}
