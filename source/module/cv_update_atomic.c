

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

#include "conversion.h"
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

#define CONV_TLB_FLUSH_ENTRIES 5

//a debugging function to print the entries in the dirty list
static void __debug_print_dirty_list(struct ksnap_user_data * cv_user){
  struct snapshot_pte_list * pte_entry;
  struct list_head * pos, * tmp_pos; //pointers for iterating
  printk(KSNAP_LOG_LEVEL "DIRTY LIST FOR %d\n", current->pid);
  list_for_each_safe(pos, tmp_pos, &(cv_user->dirty_pages_list->list)){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    printk(KSNAP_LOG_LEVEL "      dirty..... index %lu pfn %lu\n", pte_entry->page_index, pte_entry->pfn);
  }

}

//we use a simple heuristic to determine in which way to flush the TLB. If 
//there are are more than 100 entries to update, then we choose to just flush the whole thing.
//Otherwise, we will do an ivlpg and flush on a per page basis.
static int __flush_tlb_per_page(struct list_head * current_version_list, struct list_head * list_to_stop_at, uint64_t target_version_number){
  struct list_head * list_tmp;
  struct snapshot_version_list * version;
  int total_entries = 0;

  for (list_tmp = current_version_list->prev;
       prefetch(current_version_list->prev), current_version_list != list_to_stop_at;
       current_version_list = list_tmp, list_tmp = current_version_list->prev){
    //get the version entry
    version = list_entry( current_version_list, struct snapshot_version_list, list);
    if (!version->visible || version->version_num > target_version_number){
      break;
    }
    total_entries+=version->num_of_entries;
    if (total_entries >= CONV_TLB_FLUSH_ENTRIES){
      //ok, we've met the threshold...lets return false
      return 0;
    }
  }
  
  //we will flush per page
  return 1;
}

static void __cv_update_atomic(struct vm_area_struct * vma, unsigned long flags, uint64_t target_version_input){
  //struct vm_area_struct * master_vma;
  /*for iterating through the list*/
  struct list_head * pos, * pos_outer, * pos_outer_tmp, * ls, * new_list;
  /*for storing pte values from list*/
  struct snapshot_pte_list * tmp_pte_list, * dirty_entry;
  struct snapshot_version_list * latest_version_entry;
  struct address_space * mapping;
  int gotten_pages = 0;
  int merge_count=0;
  unsigned int merge=(flags & MS_KSNAP_GET_MERGE);
  //if we pass in the partial flag, we perform the work up to the latest version, without merging
  unsigned int partial_update=(flags & MS_KSNAP_GET) && (flags & MS_KSNAP_PARTIAL);
  int flush_tlb_per_page=1;
  struct ksnap * cv_seg;
  struct ksnap_user_data * cv_user;
  uint64_t target_version_number; //what version are we updating to?
  struct snapshot_version_list * version_list, * list_to_stop_at;
  //if this is set, we keep the version number where it is. Next time around we'll perform only merges
  //and any subsequent commits
  uint8_t keep_current_version=(partial_update && target_version_input==0);

  int skipped;
  int versions[4];

  memset(versions,0,sizeof(int)*4);

  cv_stats_function_init();
  
#ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "IN UPDATE\n");
#endif

  cv_stats_start(mapping_to_ksnap(mapping), 0, update_latency);
  if (vma==NULL || vma->vm_mm == NULL || vma->vm_file==NULL || vma->vm_file->f_mapping==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: vma not setup right\n");
  }

  mapping=vma->vm_file->f_mapping;
  //get the conversion segment data structure
  cv_seg=ksnap_vma_to_ksnap(vma);
  //get the user segment data structure
  cv_user=ksnap_vma_to_userdata(vma);
  //if we aren't merging then revert everything in our dirty page list
  if (!merge){
      //TODO: provide an error on conflict here!!!!
      ksnap_revert_dirty_list(vma, mapping);
  }

  if (cv_seg==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: segment is null for some reason, vma is %p vm_file %p f_mapping %p seg %p\n", 
	   vma, vma->vm_file, vma->vm_file->f_mapping, vma->vm_file->f_mapping->ksnap_data);
  }

  //grab the lock
  spin_lock(&cv_seg->lock);
  
  //if the target was passed in....use that!
  target_version_number=(target_version_input==0) ? atomic64_read(&cv_seg->committed_version_atomic) : target_version_input;
  list_to_stop_at=(struct snapshot_version_list *)atomic64_read(&cv_seg->uncommitted_version_entry_atomic);

  if (target_version_number<=cv_user->version_num){
      spin_unlock(&cv_seg->lock);
      return;
  }


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
    //flush on a per-page basis? Or just flush the entire thing?
    //flush_tlb_per_page=__flush_tlb_per_page(ls, &list_to_stop_at->list, target_version_number);
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
      //OK, lets now walk the actual committed ptes
      list_for_each(pos, &latest_version_entry->pte_list->list){
	//get the pte entry
	tmp_pte_list = list_entry(pos, struct snapshot_pte_list, list);
	//is the pte outdated? If so, then no use wasting time updating our page table
	if (tmp_pte_list->obsolete_version <= target_version_number){
	  continue;
	}
        dirty_entry=conv_dirty_search_lookup(cv_user, tmp_pte_list->page_index);
	if (merge && dirty_entry){
	  //we have to merge our changes with the committed stuff
	  ksnap_merge(pfn_to_page(tmp_pte_list->pfn), 
		      (uint8_t *)((tmp_pte_list->page_index << PAGE_SHIFT) + vma->vm_start),
		      dirty_entry->ref_page, pfn_to_page(tmp_pte_list->pfn));
	  //cv_stats_inc_merged_pages(&cv_seg->cv_stats);
	  merge_count++;
	}
        else if (!dirty_entry && !(cv_user->partial_version_num >= latest_version_entry->version_num)){
	  cv_stats_start(mapping_to_ksnap(mapping), 2, commit_waitlist_latency);
	  pte_copy_entry (tmp_pte_list->pte, tmp_pte_list->pfn, tmp_pte_list->page_index, vma, flush_tlb_per_page);
	  cv_stats_end(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), 2, commit_waitlist_latency);
	  ++gotten_pages;
#ifdef CONV_LOGGING_ON
          printk(KERN_EMERG "    Update %d for segment %p, update page index %d \n", 
                 current->pid, cv_seg, tmp_pte_list->page_index);
#endif
          versions[tmp_pte_list->page_index]++;
	}
        else{
            versions[tmp_pte_list->page_index]++;
        }
        
      }
      //done traversing a list of ptes
      new_list = pos_outer;
    }

    //done traversing the versions
    //we only change the position of our current version if it wasn't a merge_only
    if (new_list && !keep_current_version){
      latest_version_entry = list_entry( new_list, struct snapshot_version_list, list);
      atomic_inc(&latest_version_entry->ref_c);
      //only set it to the new list if it's not null
      vma->snapshot_pte_list = (new_list) ? new_list : vma->snapshot_pte_list;
      //set the new version
      ksnap_meta_set_local_version(vma,target_version_number);
      cv_user->version_num=target_version_number;
      cv_user->partial_version_num=0;
    }
    else if (new_list && keep_current_version){
        cv_user->partial_version_num=target_version_number;
    }

    //we didn't flush along the way....we need to flush the whole thing
    if (!flush_tlb_per_page){
      flush_tlb();
    }
  }

  //grab the lock
  spin_unlock(&cv_seg->lock);
  
#ifdef CONV_LOGGING_ON
    printk(KSNAP_LOG_LEVEL "UPDATE: pid %d updated to version %llu and merged %d pages and updated %d pages target_input %lu\n", 
	   current->pid, target_version_number, merge_count, gotten_pages, target_version_input);
#endif

  cv_stats_end(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), 0, update_latency);

  cv_stats_add_counter(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), gotten_pages, update_pages);
  return;
}


void cv_update_atomic(struct vm_area_struct * vma, unsigned long flags){
  __cv_update_atomic(vma, flags, 0);
}

//update to a specific version...called by commit and merging is already done
void cv_update_atomic_to_version_no_merge(struct vm_area_struct * vma, uint64_t version){
  //TODO: the flags here are dumb and don't really make a lot of sense in this context. They need to be fixed
  __cv_update_atomic(vma,  (MS_KSNAP_GET | MS_KSNAP_PARTIAL), version);
}
