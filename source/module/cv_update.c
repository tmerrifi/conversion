  

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
void __debug_print_dirty_list(struct ksnap_user_data * cv_user){
  struct snapshot_pte_list * pte_entry;
  struct list_head * pos, * tmp_pos; //pointers for iterating
  printk(KSNAP_LOG_LEVEL "DIRTY LIST FOR %d\n", current->pid);
  list_for_each_safe(pos, tmp_pos, &(cv_user->dirty_pages_list->list)){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    printk(KSNAP_LOG_LEVEL "      dirty..... index %lu pfn\n", pte_entry->page_index);
  }
}

int __insert_partial_update_page_lookup(struct radix_tree_root * partial_update_page_lookup, uint32_t page_index, 
                                        uint64_t entry_version_num, uint64_t current_version_num){
    void * version_tmp = radix_tree_lookup(partial_update_page_lookup, page_index);
    int is_unique=0;
    if (version_tmp == NULL){
        //we've never done a partial update on it, so its unique
        is_unique=1;
    }
    else {
        //subtract one because we add one to distinguish zero from NULL
        uint64_t old_version_num = ((uint64_t)version_tmp) >> 4;
        //if it was updated in the last "real" update (not partial), then we count this upate
        if (old_version_num <= current_version_num){
            is_unique=1;
            radix_tree_delete(partial_update_page_lookup, page_index);
        }
    }
    //if we've got a new entry, lets insert it into the radix tree
    if (is_unique){
        radix_tree_insert(partial_update_page_lookup, page_index, (void *)(entry_version_num << 4));
    }
    return is_unique;
}

//we use a simple heuristic to determine in which way to flush the TLB. If 
//there are are more than 100 entries to update, then we choose to just flush the whole thing.
//Otherwise, we will do an ivlpg and flush on a per page basis.
int __flush_tlb_per_page(struct list_head * current_version_list, struct list_head * list_to_stop_at, uint64_t target_version_number){
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

void __migrate_page_to_logging(struct vm_area_struct * vma,  struct ksnap_user_data * cv_user, struct snapshot_pte_list * entry){
    struct cv_logging_page_status_entry * logging_status_entry;
    struct page * new_page, * old_page;
    pte_t new_pte_entry;
    uint8_t * local_addr, * kaddr;

    //printk(KERN_EMERG "start migration in update %d", current->pid);
    struct cv_logging_entry * logging_entry = cv_list_entry_get_logging_entry(entry);
    //grab the pte for our address
    pte_t * pte = pte_get_entry_from_address(vma->vm_mm, logging_entry->addr);
    //get the old page
    old_page = pte_page(*pte);
    //next lets get the new page setup
    //allocate a new user page. Its possible that our current page is local only to us. But if we go that route, we'll
    //need to block other threads from potentially updating to our page. That's just too much complexity to avoid this one
    //time cost
    new_page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, vma, logging_entry->addr);
    conv_debug_memory_alloc(new_page);
    __SetPageUptodate(new_page);
    page_add_new_anon_rmap(new_page, vma, logging_entry->addr);
    //printk(KERN_EMERG "__migrate in update 2, page: %d, pid: %d", new_page, current->pid);
    //now do the Copy
    local_addr = logging_entry->addr & PAGE_MASK;
    kaddr = (uint8_t *)kmap_atomic(new_page, KM_USER0);
    memcpy(kaddr,local_addr,PAGE_SIZE);
    kunmap_atomic(kaddr, KM_USER0);
    //printk(KERN_EMERG "__migrate in update 3, page: %d, pid: %d", new_page, current->pid);
    //now update the local logging data structure
    logging_status_entry = cv_logging_page_status_entry_init(pte, page_to_pfn(new_page), entry->page_index, cv_user->version_num);
    //insert this page into our local logging ds
    if (cv_logging_page_status_insert(cv_user, logging_status_entry, entry->page_index)<0){
        BUG();
    }
    //updating the pte with the new PFN and flush the TLB
    new_pte_entry = mk_pte(new_page, vma->vm_page_prot);
    new_pte_entry = pte_wrprotect(new_pte_entry);
    set_pte(pte, new_pte_entry);
    __flush_tlb_one(logging_entry->addr);
    //deal with the old page
    page_remove_rmap(old_page);
    put_page(old_page);

#ifdef CONV_LOGGING_ON
    printk(KERN_EMERG "cv_update: migrate page, new page %p, old page %p, pid: %d\n", new_page, old_page, current->pid);
#endif    
}

void copy_logging_data(struct vm_area_struct * vma,
                       struct ksnap * cv_seg,
                       struct ksnap_user_data * cv_user,
                       uint8_t * destination_page,
                       struct snapshot_pte_list * entry,
                       struct cv_logging_entry * logging_entry,
                       struct cv_logging_page_status_entry * logging_status_entry){

    uint64_t line_version, page_version;
    struct snapshot_pte_list * line_entry;
    int line_index=0;

    if (logging_status_entry->cow_version < cv_user->forked_version_num){
        //we need to cow our page because it might be in use by another forked process as a reference page...
#ifdef CONV_LOGGING_ON
        printk(KERN_EMERG "cv_update: CoW'd oldpage: pid: %d, page: %d\n", current->pid, entry->page_index);
#endif
        struct page * new_page=cv_logging_cow_page(vma, logging_status_entry->pte, logging_entry->addr);
        //update the logging_status_entry structure
        logging_status_entry->pfn=page_to_pfn(new_page);
        logging_status_entry->cow_version=cv_user->version_num;
        //we need to make it write protected since cv_logging_cow_page doesn't do that.
        pte_t pte_temp = pte_wrprotect(*logging_status_entry->pte);
        //set it back
        set_pte(logging_status_entry->pte, pte_temp);
        //flush the tlb entry
        __flush_tlb_one(logging_entry->addr);
        //need to set destination_page * again since we've changed it.
        destination_page=(uint8_t *)pfn_to_kaddr(logging_status_entry->pfn);
    }
    
    if (cv_logging_is_full_page(logging_entry) && !cv_per_page_version_logging_page_entry_is_max_version(cv_seg->ppv, entry->page_index)){
        //a full page can only be copied if its the latest entry (considering both pages and lines). Otherwise, we need
        //to go line by line and only copy stuff that is not outdated.
        //printk(KERN_INFO "Whoops! Need to go line by line, index: %d!\n", entry->page_index);
        page_version=cv_per_page_version_logging_get_full_page_version(cv_seg->ppv, entry->page_index);
        cv_per_page_logging_entry_line_for_each(cv_seg->ppv,entry->page_index,
                                                line_entry,line_version){
            if (page_version>line_version){
                //the page is newer
                //printk(KERN_INFO "copy the page in here....%d, %lu, %lu\n", line_index, line_version, page_version);

                memcpy(destination_page + (CV_LOGGING_LOG_SIZE*line_index),
                        logging_entry->data + (CV_LOGGING_LOG_SIZE*line_index),
                        CV_LOGGING_LOG_SIZE);
            }
            line_index++;
        }
    }
    else{
        //copy the data
        memcpy(destination_page + (CV_LOGGING_LOG_SIZE * logging_entry->line_index),
               logging_entry->data,
               logging_entry->data_len);
    }
}


void __cv_update_parallel(struct vm_area_struct * vma, unsigned long flags, uint64_t target_version_input, int defer_work){
  //struct vm_area_struct * master_vma;
  /*for iterating through the list*/
  struct list_head * pos, * pos_outer, * pos_outer_tmp, * ls, * new_list;
  /*for storing pte values from list*/
  struct snapshot_pte_list * tmp_pte_list, * dirty_entry;
  struct cv_page_entry * page_entry, * dirty_entry_page;
  struct snapshot_version_list * latest_version_entry;
  struct address_space * mapping;
  int gotten_pages = 0;
  int ignored_pages = 0;
  int merge_count=0;
  int partial_unique_count=0;
  //are we merging????
  unsigned int merge=(flags & CONV_UPDATE);
  //if we pass in the partial flag, we perform the work up to the latest version, without merging
  unsigned int partial_update=(flags & CONV_UPDATE_NO_MERGE) && (flags & CONV_UPDATE_PARTIAL);
  //if this is set, we keep the version number where it is. Next time around we'll perform only merges
  //and any subsequent commits
  uint8_t keep_current_version=(partial_update && target_version_input==0);
  int flush_tlb_per_page=1;
  struct ksnap * cv_seg;
  struct ksnap_user_data * cv_user;
  uint64_t target_version_number; //what version are we updating to?
  struct snapshot_version_list * version_list, * list_to_stop_at;
  uint64_t old_version;
  unsigned int first_update_after_partial;
  struct cv_logging_entry * logging_entry;
  struct cv_logging_page_status_entry * logging_status_entry;
  uint8_t * local_addr;
  
  cv_stats_function_init();
  
  cv_stats_start(mapping_to_ksnap(mapping), 0, update_latency);
  if (vma==NULL || vma->vm_mm == NULL || vma->vm_file==NULL || vma->vm_file->f_mapping==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: vma not setup right\n");
  }

  if ((flags & CONV_UPDATE) && (flags & CONV_UPDATE_PARTIAL)){
      printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: can't combine partial updates with merging\n");
  }

  mapping=vma->vm_file->f_mapping;
  //get the conversion segment data structure
  cv_seg=ksnap_vma_to_ksnap(vma);
  //get the user segment data structure
  cv_user=ksnap_vma_to_userdata(vma);
  
  first_update_after_partial=(!partial_update && cv_user->partial_version_num>0);
  if (cv_seg==NULL){
    printk(KSNAP_LOG_LEVEL "CV UPDATE FAILED: segment is null for some reason, vma is %p vm_file %p f_mapping %p seg %p\n", 
	   vma, vma->vm_file, vma->vm_file->f_mapping, vma->vm_file->f_mapping->ksnap_data);
  }

  //if the target was passed in....use that!
  target_version_number=(target_version_input==0) ? cv_seg->committed_version_num : target_version_input;
  list_to_stop_at=(struct snapshot_version_list *)cv_seg->uncommitted_version_entry;

  //set the number of updated pages to zero
  cv_meta_set_updated_page_count(vma, 0);  
  cv_meta_set_merged_page_count(vma, 0);

  if (target_version_number<=cv_user->version_num){
#ifdef CONV_LOGGING_ON
      printk(KSNAP_LOG_LEVEL "IN UPDATE %d for segment %p, left because we are fully up to date\n", current->pid, cv_seg);
#endif
    return;
  }

  cv_profiling_op_begin(&cv_user->profiling_info, CV_PROFILING_OP_TYPE_UPDATE,target_version_number);

#ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "IN UPDATE %d for segment %p\n", current->pid,cv_seg);
#endif

  //grab the head of the version list
  version_list=(struct snapshot_version_list *)mapping_to_ksnap(mapping)->snapshot_pte_list;
  //we're going to update, so increment the stats
  cv_stats_inc_reader_get_snapshots(&cv_seg->cv_stats);        
  //only go in here if there is an element in the list (prev != next)
  if (version_list && version_list->list.prev != version_list->list.next){
    //if the subscriber's vma has a previous ptr into the list, use that. If not, just use the entire list
    ls = (vma->snapshot_pte_list) ? (struct list_head *)vma->snapshot_pte_list :  version_list->list.prev;
    //we set the subscribers version list ptr to new_list at the end, so lets start it at NULL
    new_list=NULL;
    //start walking through the list....stop when you get to any list with a version number greater than what we're updating to
    for (pos_outer = ls, pos_outer_tmp = pos_outer->prev;
	 prefetch(pos_outer->prev), pos_outer != &list_to_stop_at->list;
	 pos_outer = pos_outer_tmp, pos_outer_tmp = pos_outer->prev){
      //get the version entry
      latest_version_entry = list_entry( pos_outer, struct snapshot_version_list, list);
      cv_profiling_add_value(&cv_user->profiling_info,list_to_stop_at->version_num,CV_PROFILING_VALUE_TYPE_STOPPED_UPDATE_VERSION);
      if (!latest_version_entry->visible || latest_version_entry->version_num > target_version_number){
          break;
      }
      else if (latest_version_entry->committer == vma || latest_version_entry->version_num <= cv_user->version_num){
          //no need to update to stuff we committed
          new_list = pos_outer;
          continue;
      }
#ifdef CONV_LOGGING_ON
          printk(KERN_EMERG "    Update %d for segment %p, going for version %d, target is %d, target input %d\n", current->pid, cv_seg, latest_version_entry->version_num, target_version_number, target_version_input);
#endif
      //OK, lets now walk the actual committed ptes
      list_for_each(pos, &latest_version_entry->pte_list->list){
	//get the pte entry
	tmp_pte_list = list_entry(pos, struct snapshot_pte_list, list);
#ifdef CONV_LOGGING_ON
        printk(KERN_EMERG ".........walking entry %p, pid %d, type %d, page id: %d, version %lu",
               tmp_pte_list, current->pid, tmp_pte_list->type, tmp_pte_list->page_index, latest_version_entry->version_num);
#endif
        if (tmp_pte_list->type == CV_DIRTY_LIST_ENTRY_TYPE_PAGING){
            //*********We are committing a page*************
            page_entry = cv_list_entry_get_page_entry(tmp_pte_list);
            //is the pte outdated? If so, then no use wasting time updating our page table
            if (tmp_pte_list->obsolete_version <= target_version_number){
                cv_profiling_add_value(&cv_user->profiling_info,tmp_pte_list->page_index,CV_PROFILING_VALUE_TYPE_SKIPPED);
                CV_HOOKS_UPDATE_ENTRY(cv_seg, cv_user, tmp_pte_list->page_index, CV_HOOKS_UPDATE_ENTRY_SKIP);
#ifdef CONV_LOGGING_ON
                printk(KERN_EMERG ".........walking entry %p, pid %d, type %d, page id: %d, version %lu",
                       tmp_pte_list, current->pid, tmp_pte_list->type,
                       tmp_pte_list->page_index, latest_version_entry->version_num);
#endif
                continue;
            }
            dirty_entry=conv_dirty_search_lookup(cv_user, tmp_pte_list->page_index, 0, 1);
            if (merge && dirty_entry){
                //we have to merge our changes with the committed stuff
                if (dirty_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING){
                    dirty_entry_page=cv_list_entry_get_page_entry(dirty_entry);
                    //printk(KERN_EMERG "pid %d, merging page %d\n", current->pid, tmp_pte_list->page_index);
                    local_addr=compute_local_addr_for_diff(vma, dirty_entry_page->pfn, dirty_entry->page_index, dirty_entry->checkpoint);
                    ksnap_merge(pfn_to_page(page_entry->pfn), 
                                local_addr,
                                dirty_entry_page->ref_page, pfn_to_page(page_entry->pfn));
#ifdef CONV_LOGGING_ON
                    printk(KERN_EMERG "    Update %d for segment %p, merge page index %d\n", current->pid, cv_seg, tmp_pte_list->page_index);
#endif
                    cv_stats_inc_merged_pages(&cv_seg->cv_stats);
                    merge_count++;
                    cv_profiling_add_value(&cv_user->profiling_info,tmp_pte_list->page_index,CV_PROFILING_VALUE_TYPE_MERGE);
                    CV_HOOKS_UPDATE_ENTRY(cv_seg, cv_user, tmp_pte_list->page_index, CV_HOOKS_UPDATE_ENTRY_MERGE);
                }
                else if (dirty_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_LOGGING){
                    BUG();
                }
            }
            //if we have a partial version, it means that we previously did a partial upate. If so, and this entry's version number
            //is less than our partial version number, then this update is superfluous
            else if (!dirty_entry && !(cv_user->partial_version_num >= latest_version_entry->version_num)){
                cv_stats_start(mapping_to_ksnap(mapping), 2, commit_waitlist_latency);
                cv_profiling_add_value(&cv_user->profiling_info,tmp_pte_list->page_index,CV_PROFILING_VALUE_TYPE_UPDATE);
                pte_copy_entry (page_entry->pte, page_entry->pfn, tmp_pte_list->page_index, vma, flush_tlb_per_page, defer_work, cv_user);
#ifdef CONV_LOGGING_ON
                printk(KERN_EMERG "    Update %d for segment %p, update page index %d, page is %p \n", 
                       current->pid, cv_seg, tmp_pte_list->page_index, page_entry);
#endif
                cv_stats_end(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), 2, commit_waitlist_latency);
                if (__insert_partial_update_page_lookup(&cv_user->partial_update_page_lookup, tmp_pte_list->page_index, 
                                                        latest_version_entry->version_num, cv_user->version_num)){
                    ++partial_unique_count;
                }
                ++gotten_pages;
                CV_HOOKS_UPDATE_ENTRY(cv_seg, cv_user, tmp_pte_list->page_index, CV_HOOKS_UPDATE_ENTRY_UPDATE);
            }
            else{
                cv_profiling_add_value(&cv_user->profiling_info,tmp_pte_list->page_index,CV_PROFILING_VALUE_TYPE_SKIPPED);
                ++ignored_pages;
            }
        }
        else{
            
            //LOGGING CODE
            logging_entry = cv_list_entry_get_logging_entry(tmp_pte_list);
            dirty_entry=conv_dirty_search_lookup_line_and_page(cv_user, tmp_pte_list->page_index, logging_entry->line_index);
            
            /* if (tmp_pte_list->page_index==LOGGING_DEBUG_PAGE_INDEX && logging_entry->line_index==LOGGING_DEBUG_LINE){ */
            /*     printk(KERN_INFO "memcpy %p %d %d pid %d, logging_entry %p, version %lu, entry %p, %lu\n", */
            /*            logging_entry->data, */
            /*            logging_entry->data_len, */
            /*            logging_entry->line_index, */
            /*            current->pid, */
            /*            logging_entry, */
            /*            latest_version_entry->version_num, */
            /*            tmp_pte_list, */
            /*            tmp_pte_list->obsolete_version); */
            /* } */

            //check to see if the current guy is obsolete
            if (tmp_pte_list->obsolete_version <= target_version_number){
#ifdef CONV_LOGGING_ON
                printk(KERN_EMERG "cv_update of logging page SKIP 1 ...%d %d %lu %lu",
                       current->pid, tmp_pte_list->page_index,
                       tmp_pte_list->obsolete_version, target_version_number);
#endif
                continue;
            }

            logging_status_entry=cv_logging_page_status_lookup(cv_user, tmp_pte_list->page_index);
            
            /*the dirty entry search above looks for both a page entry or a logging entry...but there is a case where a 
              dirty line can't be found. Essentially, we have no way of looking up *any* line thats dirty for this page.
              So instead we use the logging_status_entry's "entries_allocated" field to tell us if there are dirty
              entries for this page...so we avoid merging.*/
            if (!dirty_entry && cv_logging_is_full_page(logging_entry) && logging_status_entry && logging_status_entry->entries_allocated > 0){
#ifdef CONV_LOGGING_ON
                printk(KERN_EMERG "cv_update of logging page SKIP 2 ...%d %d %lu %lu",
                       current->pid, tmp_pte_list->page_index,
                       tmp_pte_list->obsolete_version, target_version_number);
#endif
                continue;
            }
            
            /* else if (dirty_entry){ */
            /*     BUG(); */
            /* } */
            else if (!dirty_entry){
                /* printk(KERN_EMERG "UPDATE of logging page...%d %d version %lu addr %p %x", */
                /*        current->pid, tmp_pte_list->page_index, latest_version_entry->version_num, */
                /*        logging_entry->addr & (~PAGE_MASK), (CV_LOGGING_LOG_SIZE * logging_entry->line_index)); */
                //ok do the update
                logging_status_entry=cv_logging_page_status_lookup(cv_user, tmp_pte_list->page_index);
                if (!logging_status_entry){
                    //we need to migrate...luckily its not dirty
                    __migrate_page_to_logging(vma, cv_user, tmp_pte_list);
                    logging_status_entry=cv_logging_page_status_lookup(cv_user, tmp_pte_list->page_index);
                    BUG_ON(logging_status_entry==NULL);
                }

                /* memcpy( ((uint8_t *)pfn_to_kaddr(logging_status_entry->pfn)) + (CV_LOGGING_LOG_SIZE * logging_entry->line_index), */
                /*         logging_entry->data, */
                /*         logging_entry->data_len); */

                uint8_t old_data = *(((uint8_t *)pfn_to_kaddr(logging_status_entry->pfn)) + LOGGING_DEBUG_INDEX);
                
                copy_logging_data(vma, cv_seg, cv_user,
                                  (uint8_t *)pfn_to_kaddr(logging_status_entry->pfn),
                                  tmp_pte_list,
                                  logging_entry, logging_status_entry);
                
                CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)(pfn_to_kaddr(logging_status_entry->pfn))
                                            + (CV_LOGGING_LOG_SIZE *
                                               ((!cv_logging_is_full_page(logging_entry)) ?
                                                logging_entry->line_index : LOGGING_DEBUG_LINE)),
                                            tmp_pte_list->page_index,
                                            logging_entry->line_index,
                                            "cv_update.c: after update ");


                CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)(logging_entry->data)
                                            + (CV_LOGGING_LOG_SIZE *
                                               ((!cv_logging_is_full_page(logging_entry)) ?
                                                logging_entry->line_index : LOGGING_DEBUG_LINE)),
                                            tmp_pte_list->page_index,
                                            logging_entry->line_index,
                                            "cv_update.c: after update logging data ");

#ifdef CONV_LOGGING_ON
                printk(KERN_EMERG "cv_update: pid: %d, entry is %p, version: %lu, page-index: %d, is full page: %d\n",
                       current->pid, tmp_pte_list, latest_version_entry->version_num,
                       tmp_pte_list->page_index, cv_logging_is_full_page(logging_entry));
#endif
            }
        }
      }
#ifdef CONV_LOGGING_ON
      printk(KERN_EMERG "  Updated to version %d\n", latest_version_entry->version_num);
#endif
      //done traversing a list of ptes
      new_list = pos_outer;
    }
    old_version = cv_user->version_num;
    //done traversing the versions
    if (new_list && !keep_current_version){
        latest_version_entry = list_entry( new_list, struct snapshot_version_list, list);
        atomic_inc(&latest_version_entry->ref_c);
        //only set it to the new list if it's not null
        vma->snapshot_pte_list = (new_list) ? new_list : vma->snapshot_pte_list;
        //set the new version
        ksnap_meta_set_local_version(vma,target_version_number);
        cv_user->version_num=target_version_number;
        cv_user->partial_version_num=0;
        cv_meta_set_partial_version_num(vma, 0);
    }
    else if (new_list && keep_current_version){
        cv_user->partial_version_num=target_version_number;
        cv_meta_set_partial_version_num(vma, target_version_number);
    }
    
    //we didn't flush along the way....we need to flush the whole thing
    if (!flush_tlb_per_page){
        flush_tlb();
    }
  }
#ifdef CONV_LOGGING_ON
    printk(KSNAP_LOG_LEVEL "UPDATE for segment %p: pid %d updated to version %llu old version %llu and merged %d pages and updated %d \
pages target_input %lu committed version %llu ignored %d, keep current %d, first_update %d, partial pages %d\n", 
           cv_seg, current->pid, target_version_number, old_version, merge_count, gotten_pages, 
           target_version_input, atomic64_read(&cv_seg->committed_version_atomic), ignored_pages, 
           keep_current_version, first_update_after_partial, cv_meta_get_partial_updated_unique_pages(vma));

#endif

    cv_stats_end(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), 0, update_latency);
    cv_stats_add_counter(mapping_to_ksnap(mapping), ksnap_vma_to_userdata(vma), gotten_pages, update_pages);
    cv_meta_set_updated_page_count(vma, gotten_pages);
    cv_meta_set_merged_page_count(vma, merge_count);
    cv_meta_inc_partial_updated_unique_pages(vma, partial_unique_count);
    
    return;
}


void cv_update_parallel(struct vm_area_struct * vma, unsigned long flags, int defer_work){
    __cv_update_parallel(vma, flags, 0, defer_work);
}

//update to a specific version...called by commit and merging is already done
void cv_update_parallel_to_version_no_merge(struct vm_area_struct * vma, uint64_t version, int defer_work){
  //TODO: the flags here are dumb and don't really make a lot of sense in this context. They need to be fixed
    __cv_update_parallel(vma,  (CONV_UPDATE_NO_MERGE | CONV_UPDATE_PARTIAL), version, defer_work);
}
