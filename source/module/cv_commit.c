#include <linux/kernel.h>	
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
#include <asm/page.h>
#include <asm/tlbflush.h>
#include <linux/kdebug.h>
#include <linux/notifier.h>
#include <linux/random.h>
#include <linux/spinlock.h>
#include <linux/mman.h>
#include <linux/hardirq.h>

#include "conversion.h"
#include "ksnap_writer.h"
#include "ksnap_version_list.h"
#include "cv_stats.h"
#include "cv_meta_data.h"
#include "cv_pte.h"
#include "cv_lock_list.h"
#include "cv_commit.h"
#include "cv_per_page_version.h"
#include "cv_merge.h"
#include "cv_update.h"
#include "cv_debugging.h"
#include "cv_dirty.h"
#include "cv_event.h"
#include "cv_logging.h"

void __remove_old_logging_page(struct ksnap * cv_seg, struct snapshot_pte_list * entry, uint64_t page_index, uint64_t our_version_number){
    struct snapshot_pte_list * old_entry;
    old_entry=cv_per_page_version_get_logging_page_entry(cv_seg->ppv, page_index);
    if (old_entry!=NULL){
        old_entry->obsolete_version=our_version_number;
    }
    //now we need to walk through the committed line sized entries and remove those
    int i=0;
    for (;i<PAGE_SIZE/CV_LOGGING_LOG_SIZE;i++){
        old_entry=cv_per_page_version_get_logging_line_entry(cv_seg->ppv, page_index, i);
        if (old_entry){
            uint64_t old_version = cv_per_page_version_get_logging_line_entry_version(cv_seg->ppv,
                                                                                      page_index,
                                                                                      i);
            if(old_version>our_version_number){
                //grab the PTE
                struct snapshot_pte_list * pte_old = cv_per_page_version_get_logging_line_entry(cv_seg->ppv,
                                                                                                page_index,
                                                                                                i);
                BUG();
            }
            old_entry->obsolete_version=our_version_number;
            cv_per_page_version_clear_logging_line_entry(cv_seg->ppv, page_index, i);
        }
    }
}


void __remove_old_logging_line(struct ksnap * cv_seg, struct snapshot_pte_list * entry, uint64_t page_index, uint64_t line_index, uint64_t our_version_number){
    struct snapshot_pte_list * old_entry;
    old_entry=cv_per_page_version_get_logging_line_entry(cv_seg->ppv, page_index, line_index);
    if (old_entry!=NULL){
        old_entry->obsolete_version=our_version_number;
    }
}

//remove the old page from the page cache, handle its LRU stuff, etc...
int __remove_old_page(struct address_space * mapping, struct vm_area_struct * vma, 
		       unsigned long index, struct page * ref_page, uint64_t our_version){
    struct ksnap * cv_seg;
    struct snapshot_pte_list * old_entry;
    
    cv_seg = ksnap_vma_to_ksnap(vma);
    //get the current entry from the per-page version list
    old_entry = cv_per_page_version_get_version_entry(cv_seg->ppv, index);
    if (old_entry==NULL){
        return 0;
    }
    old_entry->obsolete_version=our_version;
    return 1;
}

void __update_page_mapping(struct address_space * mapping, struct vm_area_struct * vma, 
			   struct page * page, struct snapshot_pte_list * version_list_entry){
    struct ksnap * cv_seg;

    cv_seg = ksnap_vma_to_ksnap(vma);
    //make sure the page wasn't free'd out from under us
    if (!page_count(page)){
        BUG();
    }
    cv_per_page_version_update_version_entry(cv_seg->ppv, version_list_entry);
    get_page(page);
    return;
}


void __merge_full_page_with_cache_lines(struct cv_logging_entry * logging_entry,
                                        struct cv_logging_page_status_entry * logging_page_status,
                                        struct snapshot_pte_list * entry,
                                        struct ksnap * cv_seg,
                                        struct ksnap_user_data * cv_user){
    //a full page is being committed *AFTER* one or more lines have been committed. Meaning we have to walk
    int i=0;
    uint8_t * data;
    uint8_t * ref_data;

#ifdef CONV_LOGGING_ON
    CV_LOG_MESSAGE( "in __merge_full_page... pid: %d\n", current->pid);
#endif

    CV_LOG_MESSAGE( "in __merge_full_page... page version num %llu, our version num %llu\n",
           cv_per_page_version_logging_get_full_page_version(cv_seg->ppv, entry->page_index), cv_user->version_num);

    uint8_t * latest_full_page_data=NULL;
        
    //we need to check here and make sure that we don't also have a full page that has been committed since our last
    //update. If it has, then we have to merge with that full page before we merge at the line level
    if (cv_per_page_version_logging_get_full_page_version(cv_seg->ppv, entry->page_index) > cv_user->version_num){
        //CV_LOG_MESSAGE( " doing the page level merge first ");
        //get the last committed full page

        struct snapshot_pte_list * latest_committed_full_page_entry = cv_per_page_version_get_logging_page_entry(cv_seg->ppv,
                                                                               entry->page_index);
        //grab the actual data
        latest_full_page_data = cv_list_entry_get_logging_entry(latest_committed_full_page_entry)->data;

        /* CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)data, */
        /*                             entry->page_index, */
        /*                             LOGGING_DEBUG_LINE, */
        /*                             "page merge latest"); */
        
        /* //do the merge */
        /* cv_three_way_merge(data, logging_entry->data, latest_data, (PAGE_SIZE/sizeof(uint64_t))); */
    }
    
    for (;i<(PAGE_SIZE/CV_LOGGING_LOG_SIZE);i++){
        //check each cacheline to see if the version is newer
        if (cv_per_page_version_get_logging_line_entry_version(cv_seg->ppv,entry->page_index,i) > cv_user->version_num){
            CV_LOG_MESSAGE( "in __merge_full_page... MADE IT pid: %d, line: %d\n", current->pid, i);
            struct snapshot_pte_list * latest_entry =  cv_per_page_version_get_logging_line_entry(cv_seg->ppv, entry->page_index,i);
            BUG_ON(latest_entry==NULL);
            struct cv_logging_entry * latest_logging_entry = cv_list_entry_get_logging_entry(latest_entry);
            BUG_ON(latest_logging_entry==NULL);
            data=(uint8_t *)cv_logging_page_status_to_kaddr(logging_page_status, latest_logging_entry->line_index);
            ref_data=logging_entry->data + (i*CV_LOGGING_LOG_SIZE);

            CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)data,
                                        entry->page_index,
                                        i,
                                        "cv_commit before merge");

            CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)latest_logging_entry->data,
                                        entry->page_index,
                                        i,
                                        "cv_commit before merge latest");

            CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)ref_data,
                                        entry->page_index,
                                        i,
                                        "cv_commit before merge ref");
            
            //whelp...gotta merge
            cv_three_way_merge(data,
                               ref_data,
                               latest_logging_entry->data,
                               CV_LOGGING_MERGE_WORDS);

            CV_LOGGING_DEBUG_PRINT_LINE((uint8_t *)data,
                                        entry->page_index,
                                        i,
                                        "cv_commit after merge");
        }
        else if (latest_full_page_data){
            //there is a full page that has been committed since we last updated/committed...so we have to look here too
            data=(uint8_t *)cv_logging_page_status_to_kaddr(logging_page_status, i);
            ref_data=logging_entry->data + (i*CV_LOGGING_LOG_SIZE);
            cv_three_way_merge(data,
                               ref_data,
                               latest_full_page_data + (i*CV_LOGGING_LOG_SIZE),
                               CV_LOGGING_MERGE_WORDS);

        }
    }
}

void cv_commit_logging_entry(struct cv_logging_entry * logging_entry, struct snapshot_pte_list * entry,
                             struct vm_area_struct * vma,
                             struct ksnap * cv_seg, struct ksnap_user_data * cv_user,
                             uint64_t our_version_number, struct cv_logging_page_status_entry * logging_page_status){
    struct snapshot_pte_list * latest_entry;
    struct cv_logging_entry * latest_logging_entry=NULL;    
    char * latest, * local;
    uint64_t latest_version_num;
    pte_t pte_temp;
    unsigned long long start_tsc = native_read_tsc();

    latest_entry = cv_per_page_version_get_logging_entry_and_version(cv_seg->ppv, entry->page_index,
                                                                     logging_entry->line_index, &latest_version_num,
                                                                     cv_logging_is_full_page(logging_entry));    
#ifdef CONV_LOGGING_ON
    printk(KERN_INFO "committing logging entry our version %lu, latest %lu, line index %lu, size %d, page index: %d, pid: %d\n",  
           cv_user->version_num, latest_version_num, logging_entry->line_index, logging_entry->data_len, entry->page_index, current->pid);  
#endif
    
    if (latest_version_num > cv_user->version_num){
        if (latest_entry){
            latest_logging_entry = cv_list_entry_get_logging_entry(latest_entry);
        }
#ifdef CONV_LOGGING_ON
        CV_LOG_MESSAGE( "committing logging entry and need to merge pid: %d, index %d",
               current->pid, logging_entry->line_index);
#endif
        //grab the logging entry that is committed (latest)
        
        //are we a full page or just a cache line?
        if (cv_logging_is_full_page(logging_entry)){

            //there are two possibilities here. Firstly, the latest version committed
            //could be full page. In which case we are in luck and only have to merge
            //with that page
            if (latest_logging_entry && cv_logging_is_full_page(latest_logging_entry)){
                //do the merge with the latest version
                cv_three_way_merge((uint8_t *)cv_logging_page_status_to_kaddr(logging_page_status, logging_entry->line_index),
                                   logging_entry->data,
                                   latest_logging_entry->data,
                                   (PAGE_SIZE/sizeof(uint64_t)));
                //now copy the full page into the entry data
                CV_LOGGING_DEBUG_PRINT_LINE( (uint8_t *)latest_logging_entry->data + (LOGGING_DEBUG_LINE * CV_LOGGING_LOG_SIZE),
                                             entry->page_index, LOGGING_DEBUG_LINE, "merge latestentry fullpage ");
                CV_LOGGING_DEBUG_PRINT_LINE( (uint8_t *)logging_entry->data + (LOGGING_DEBUG_LINE * CV_LOGGING_LOG_SIZE),
                                             entry->page_index, LOGGING_DEBUG_LINE, "merge latestentry fullpage ref data");
                INC(COUNTER_COMMIT_LOGGING_FAST_PAGE_MERGE);
            }
            else{
                //need to traverse all of the lines and merge :(
                __merge_full_page_with_cache_lines(logging_entry, logging_page_status, entry, cv_seg, cv_user);
                INC(COUNTER_COMMIT_LOGGING_SLOW_PAGE_MERGE);
            }
        }
        else{
            //we are committing a small (cache line) entry
            if (cv_logging_is_full_page(latest_logging_entry)){
                //its a full page, need to index into it to merge
                latest = latest_logging_entry->data + (logging_entry->line_index*CV_LOGGING_LOG_SIZE);
            }
            else{
                //its a line
                latest = latest_logging_entry->data;
            }
            //do the merge
            cv_three_way_merge((uint8_t *)cv_logging_page_status_to_kaddr(logging_page_status,logging_entry->line_index),
                               logging_entry->data,
                               latest,
                               CV_LOGGING_MERGE_WORDS);
            INC(COUNTER_COMMIT_LOGGING_FAST_LINE_MERGE);
        }
    }
    else{
        INC(COUNTER_COMMIT_LOGGING_NO_MERGE);
    }
    //we need to copy our new data into our entry
    memcpy(logging_entry->data, (uint8_t *)logging_entry->addr, logging_entry->data_len);
    
    if (cv_logging_is_full_page(logging_entry)){
        //need to write protect again
        pte_temp = pte_wrprotect(*logging_page_status->pte);	
        //set it back
        set_pte(logging_page_status->pte, pte_temp);
        //flush the tlb entry
        __flush_tlb_one(logging_entry->addr);
        INC(COUNTER_TLB_PAGE_FLUSH);
        //CV_LOG_MESSAGE( "done committing and write protecting page, pid: %d, page index: %d\n",
        //     current->pid, latest_entry->page_index);
        __remove_old_logging_page(cv_seg, entry, entry->page_index, our_version_number);
        BUG_ON(logging_page_status->logging_writes > 0);
    }
    else{
        logging_page_status->lines[logging_entry->line_index]=NULL;
        __remove_old_logging_line(cv_seg, entry, entry->page_index, logging_entry->line_index, our_version_number);
        logging_page_status->logging_writes=0;
        logging_page_status->entries_allocated--;
    }

    //update the ppv with our version...do this *after* we make the old entry obsolete.
    cv_per_page_version_update_logging_entry(cv_seg->ppv, entry->page_index, entry, our_version_number, logging_entry->line_index);
    
    COUNTER_COMMIT_LOGGING_ENTRY_LATENCY(native_read_tsc() - start_tsc);
}

void cv_commit_page(struct cv_page_entry * version_list_entry, struct vm_area_struct * vma,
                    uint64_t our_revision, unsigned long page_index, int checkpointed){
  struct page * page;
  struct address_space * mapping = NULL;
  struct cv_page_entry * committed_entry;
  struct ksnap * cv_seg;
  struct ksnap_user_data * cv_user;
  uint8_t * local_addr;
  pte_t page_table_e;

  cv_seg = ksnap_vma_to_ksnap(vma);
  cv_user = ksnap_vma_to_userdata(vma);
  //first we get the address_space
  mapping = vma->vm_file->f_mapping;
  //the pfn in our current page table doesn't equal the one we are trying to commit. Perhaps a fork() occured since our last commit?
  if (pte_pfn(*(version_list_entry->pte)) != version_list_entry->pfn){
      CV_HOOKS_COMMIT_ENTRY(cv_seg, cv_user, page_index, CV_HOOKS_COMMIT_ENTRY_SKIP);
    return;
  }
  //lets get that page struct that is pointed to by this pte...
  page = pfn_to_page(version_list_entry->pfn);
  BUG_ON(page==NULL);
  //has this page been committed since we've updated? Then we need to merge
  committed_entry = cv_list_entry_get_page_entry(cv_per_page_version_get_version_entry(
                                                                                       cv_seg->ppv,
                                                                                       page_index));

#ifdef CONV_LOGGING_ON
  CV_LOG_MESSAGE( "cv_commit: COMMITTING PAGE %p, pid %d, version %lu, index: %d\n", page, current->pid, our_revision, page_index);
#endif

  CV_LOGGING_DEBUG_PRINT_LINE(compute_local_addr_for_diff(vma, version_list_entry->pfn, page_index, checkpointed) + (CV_LOGGING_LOG_SIZE * LOGGING_DEBUG_LINE),
                              page_index, LOGGING_DEBUG_LINE, "cv_commit: commit_page");

  
  if (committed_entry && pfn_to_page(committed_entry->pfn) != version_list_entry->ref_page){
      local_addr=compute_local_addr_for_diff(vma, version_list_entry->pfn, page_index, checkpointed);
      /*if (checkpointed){
          //we do this because we modify our page and the current version is write-protected
          local_addr=(uint8_t *)pfn_to_kaddr(version_list_entry->pfn);
      }
      else{
          local_addr=(uint8_t *)((page_index << PAGE_SHIFT) + vma->vm_start);
          }*/
      INC(COUNTER_COMMIT_MERGE);
      ksnap_merge(pfn_to_page(committed_entry->pfn),
                  local_addr,
                  version_list_entry->ref_page,
                  pfn_to_page(version_list_entry->pfn));
      cv_stats_inc_merged_pages(&cv_seg->cv_stats);
      cv_profiling_add_value(&cv_user->profiling_info,page_index,CV_PROFILING_VALUE_TYPE_MERGE);
      CV_HOOKS_COMMIT_ENTRY(cv_seg, cv_user, page_index, CV_HOOKS_COMMIT_ENTRY_MERGE);
#ifdef CONV_LOGGING_ON
      CV_LOG_MESSAGE( "cv_commit: MERGING COMMITTING PAGE %p, pid %d, version %lu, index: %d\n", page, current->pid, our_revision, page_index);
#endif
  }
  else{
      cv_profiling_add_value(&cv_user->profiling_info,page_index,CV_PROFILING_VALUE_TYPE_COMMIT);
      CV_HOOKS_COMMIT_ENTRY(cv_seg, cv_user, page_index, CV_HOOKS_COMMIT_ENTRY_COMMIT);
  }
  //get the pre-existing pte value and clear the pte pointer
  page_table_e = ptep_get_and_clear(vma->vm_mm, version_list_entry->addr, version_list_entry->pte);
  //we need to write protect the owner's pte again
  page_table_e = pte_wrprotect(page_table_e);	
  //set it back
  set_pte(version_list_entry->pte, page_table_e);

  if (!__remove_old_page(mapping, vma, page->index, version_list_entry->ref_page, our_revision)){
      //first time we've seen this page
      cv_meta_inc_logical_page_count(vma);
  }
  __update_page_mapping(mapping, vma, page, container_of(version_list_entry, struct snapshot_pte_list, page_entry));
  if (version_list_entry->ref_page){
      cv_page_debugging_inc_flag(version_list_entry->ref_page, CV_PAGE_DEBUG_REFPAGE_PUT_COUNT);
      put_page(version_list_entry->ref_page);
  }
  if (conv_is_checkpointed_entry(version_list_entry) && page!=conv_get_checkpoint_page(version_list_entry)){
      put_page(conv_get_checkpoint_page(version_list_entry));
  }
}

void cv_commit_migrate_page_to_logging(struct vm_area_struct * vma,
                                       struct ksnap_user_data * cv_user,
                                       struct ksnap * cv_seg,
                                       struct snapshot_pte_list * pte_list_entry,
                                       uint64_t our_version_number){
    uint8_t * user_addr;
    pte_t page_table_e;
    struct page * ref_page;
    
    /* CV_LOG_MESSAGE( "migrating to logging 1, pid: %d, page index: %d\n", */
    /*        current->pid, pte_list_entry->page_index); */
    
    struct cv_page_entry * page_entry = cv_list_entry_get_page_entry(pte_list_entry);
    //do this before we blow away the data
    struct cv_logging_page_status_entry * logging_entry = cv_logging_page_status_entry_init(page_entry->pte,
                                                                                            page_entry->pfn,
                                                                                            pte_list_entry->page_index,
                                                                                            cv_user->version_num);           
    //grab the ref page for copying later
    ref_page = page_entry->ref_page;

#ifdef CONV_LOGGING_ON
    CV_LOG_MESSAGE( "migrating pid: %d page: %d and page is: %p, ref page is: %p, vma: %p",
           current->pid,pte_list_entry->page_index,pfn_to_page(page_entry->pfn), ref_page, vma);
#endif

    //get the user addr
    user_addr=(uint8_t *)((pte_list_entry->page_index << PAGE_SHIFT) + vma->vm_start);

    //for debugging
    uint8_t * data_addr = ((uint8_t*)(page_entry->addr & PAGE_MASK)) + LOGGING_DEBUG_INDEX;
    
     /* CV_LOG_MESSAGE( "migrating to logging 2, pid: %d, page index: %d, logging entry pte: %p, data %d, version %llu\n", */
     /*        current->pid, pte_list_entry->page_index,logging_entry->pte, *data_addr, our_version_number); */
    
    //switch the pte_list_entry to logging type
    pte_list_entry->type=CV_DIRTY_LIST_ENTRY_TYPE_LOGGING;
    //allocate some memory
    pte_list_entry->logging_entry.data = cv_logging_allocate_data_entry(PAGE_SIZE, cv_seg);
    conv_debug_memory_alloc(pte_list_entry->logging_entry.data);
    
    pte_list_entry->logging_entry.data_len = PAGE_SIZE;
    pte_list_entry->logging_entry.addr = user_addr;
    pte_list_entry->logging_entry.line_index = 0;

    
    //CV_LOG_MESSAGE( "migrating to logging 3, pid: %d, page index: %d, memcpy to %p, src %p\n",
    //     current->pid, pte_list_entry->page_index, pte_list_entry->logging_entry.data, local_addr);


    //CV_LOG_MESSAGE( "migrating to logging 4, pid: %d, page index: %d\n", current->pid, pte_list_entry->page_index);

    //do all the stuff we need to do just for the first time we switch to logging. 
    if (!cv_per_page_is_logging_page(cv_seg->ppv, pte_list_entry->page_index)){
        CV_LOGGING_DEBUG_PRINT_LINE(user_addr + (CV_LOGGING_LOG_SIZE * LOGGING_DEBUG_LINE),
                                    pte_list_entry->page_index, LOGGING_DEBUG_LINE, "cv_commit: migrating first before");

        //this stuff only happens the first time through
        cv_per_page_switch_to_logging(cv_seg->ppv, pte_list_entry->page_index);
        //we only do this once, because the commit_logging function will handle this for others
        cv_per_page_version_update_logging_entry(cv_seg->ppv, pte_list_entry->page_index,
                                                 pte_list_entry, our_version_number, 0);

        //do the copy. Safe to copy just from local addr because we've already done any
        //necessary merging
        memcpy(pte_list_entry->logging_entry.data, user_addr, PAGE_SIZE);
        //incrememnt the totoal number of logging pages
        atomic_inc(&cv_seg->logging_pages_count);
        CV_LOGGING_DEBUG_PRINT_LINE(pte_list_entry->logging_entry.data + (CV_LOGGING_LOG_SIZE * LOGGING_DEBUG_LINE),
                                    pte_list_entry->page_index, LOGGING_DEBUG_LINE, "cv_commit: migrating first after");
    }
    else{
        //still need to memcpy, but from a ref page
        BUG_ON(ref_page==NULL);
        uint8_t * ref_kaddr = (uint8_t *)kmap_atomic(ref_page, KM_USER0);
        memcpy(pte_list_entry->logging_entry.data,ref_kaddr,PAGE_SIZE);
        kunmap_atomic(ref_kaddr, KM_USER0);
        CV_LOGGING_DEBUG_PRINT_LINE(pte_list_entry->logging_entry.data + (CV_LOGGING_LOG_SIZE * LOGGING_DEBUG_LINE),
                                    pte_list_entry->page_index, LOGGING_DEBUG_LINE, "cv_commit: migrating");
    }
    
    //insert this page into our local logging ds
    if (cv_logging_page_status_insert(cv_user, logging_entry, pte_list_entry->page_index)<0){
        BUG();
    }
    //CV_LOG_MESSAGE( "migrating to logging 5, pid: %d, page index: %d, pte: %p, page entry pte: %p\n",
    //       current->pid, pte_list_entry->page_index, logging_entry->pte, page_entry->pte);
    
    //need to write protect the page
    //get the pre-existing pte value and clear the pte pointer
    page_table_e = ptep_get_and_clear(vma->vm_mm, user_addr, logging_entry->pte);
    //we need to write protect the owner's pte again
    page_table_e = pte_wrprotect(page_table_e);	
    //set it back
    set_pte(logging_entry->pte, page_table_e);

#ifdef CONV_LOGGING_ON
    CV_LOG_MESSAGE( "done migrating to logging, pid: %d, page index: %d, data %d, obs %lu, entry %p, data_addr %p, addr %p\n",
           current->pid, pte_list_entry->page_index, *data_addr, pte_list_entry->obsolete_version, pte_list_entry, data_addr,pte_list_entry->logging_entry.addr);
#endif
}

int cv_commit_do_logging_migration_check(struct vm_area_struct * vma,
                                          struct snapshot_pte_list * pte_list_entry){
    uint8_t * local_addr;
    struct ksnap_user_data * cv_user;
    struct ksnap * cv_seg;
    struct cv_page_entry * page_entry = cv_list_entry_get_page_entry(pte_list_entry);
    int diff=0;
    int result=0;
    cv_user=ksnap_vma_to_userdata(vma);
    cv_seg=ksnap_vma_to_ksnap(vma);

    /* CV_LOG_MESSAGE( "is logging page %d, should check %d, %d\n", */
    /*        cv_per_page_is_logging_page(cv_seg->ppv, pte_list_entry->page_index), */
    /*        ((cv_user->committed_non_logging_entries++) % CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES), CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES); */

#ifdef CV_LOGGING_DISABLED
    return 0;
#else
    //don't want to do this too often - its kinda expensive!
    if (!cv_per_page_is_logging_page(cv_seg->ppv, pte_list_entry->page_index) &&
        cv_user->committed_non_logging_entries++ % CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES == 0){
        page_entry = cv_list_entry_get_page_entry(pte_list_entry);
        //first get the address of our page
        local_addr=compute_local_addr_for_diff(vma, page_entry->pfn, pte_list_entry->page_index, pte_list_entry->checkpoint);
        //CV_LOG_MESSAGE( "doing a logging migration check...pid: %d %d diff? %d\n", current->pid, pte_list_entry->page_index, cv_logging_diff_64(local_addr, page_entry->ref_page));
        //now do a diff to see how many 64bit words changed
        if ((diff=cv_logging_diff_64(local_addr, page_entry->ref_page))<=CV_LOGGING_DIFF_THRESHOLD_64){
            //CV_LOG_MESSAGE( "doing a logging migration check...diff %d...pid: %d...bitmap %lu\n", diff,current->pid,
            //   cv_per_page_get_logging_diff_bitmap(cv_seg->ppv, pte_list_entry->page_index) & 0xFUL);
            COUNTER_MIGRATION_CHECK(diff);
            cv_per_page_update_logging_diff_bitmap(cv_seg->ppv, pte_list_entry->page_index, 1);
            //should we switch over to logging?
            if (cv_logging_should_switch(cv_per_page_get_logging_diff_bitmap(cv_seg->ppv, pte_list_entry->page_index))){
                /* CV_LOG_MESSAGE( "migration check...time to switch pid: %d, page index: %d\n", */
                /*      current->pid, pte_list_entry->page_index); */
                INC(COUNTER_LOGGING_MIGRATIONS);
                result=1;
            }
        }
        else{
            cv_per_page_update_logging_diff_bitmap(cv_seg->ppv, pte_list_entry->page_index, 0);
            INC(COUNTER_LOGGING_MIGRATION_CHECK_FAILED);
            COUNTER_MIGRATION_CHECK(diff);
        }
    }
    return result;
#endif //CV_LOGGING_DISABLED
}

/*This is the main commit function. */
void cv_commit_version_parallel(struct vm_area_struct * vma, int defer_work){
  struct ksnap * cv_seg; //main conversion datastructure
  struct ksnap_user_data * cv_user;
  struct snapshot_version_list * next_version_entry; //after claiming a new version, we add a new version on the end
  struct snapshot_version_list * our_version_entry; //the version that we claim as "ours" from the version list
  struct snapshot_version_list * version_entry_it; //used when we walk the list to find out if others have committed before us
  struct snapshot_pte_list * wait_list, * pte_entry;
  uint64_t our_version_number;
  struct list_head * pos, * tmp_pos, * version_pos;  //pointers for iterating
  uint64_t max_version_number; //after we commit, others may have beat us to the punch...this is used when we iterate through the list to find out
  int should_migrate;
  int committed_pages=0;
  int pte_updates=0; //used to determine if we need to flush
 
  if (vma==NULL || vma->vm_file==NULL || vma->vm_file->f_mapping==NULL){
    return;
  }

#ifdef CONV_LOGGING_ON
  CV_LOG_MESSAGE( "CONVERSION: IN COMMIT %d vma %p\n", current->pid, vma);
#endif

  //get conversion for this segment
  cv_seg=mapping_to_ksnap(vma->vm_file->f_mapping);
  //get conversion user data
  cv_user=ksnap_vma_to_userdata(vma);

  cv_user->commits++;

  if (list_empty(&(cv_user->dirty_pages_list->list))){
      CV_LOG_MESSAGE( "leaving commit early 1 %d\n", current->pid);
      return;
  }
  
  //initializes variables used to track stats
  cv_stats_function_init();
  //increment total commits
  cv_stats_inc_total_owner_commits(&cv_seg->cv_stats);
  //timer to count commit latency
  cv_stats_start(cv_seg, 0, commit_latency);
  //create the next version that we'll stick on the end for the next committer
  next_version_entry=cv_create_version_list_entry();
  //create the pte list that will store the entries we need to wait on
  wait_list=_snapshot_create_pte_list();
  //GLOBAL LOCK ACQUIRE
  cv_stats_start(cv_seg, 1, commit_wait_lock);
  spin_lock(&cv_seg->lock);
  cv_stats_end(cv_seg, cv_user, 1, commit_wait_lock);
  //get the right version number
  cv_seg->next_avail_version_num+=1;
  our_version_number=cv_seg->next_avail_version_num;
  //claim the list we'll be using to add to the version list
  our_version_entry = cv_seg->uncommitted_version_entry;
  //add our "next version" to the end of the list for the next committer to use
  list_add(&next_version_entry->list, &cv_seg->snapshot_pte_list->list);
  barrier();
  //setup the new "next" version
  cv_seg->uncommitted_version_entry = next_version_entry;
  cv_per_page_version_walk(cv_user->dirty_pages_list, wait_list,
			   cv_seg->ppv, cv_user, cv_seg, our_version_number);
  //we've linearized this version...we can mark it as such for interested parties in userspace
  cv_meta_set_linearized_version(vma, our_version_number);
  spin_unlock(&cv_seg->lock);
  //GLOBAL LOCK RELEASED

  //beging profiling operation
  cv_profiling_op_begin(&cv_user->profiling_info, CV_PROFILING_OP_TYPE_COMMIT,our_version_number);

  cv_stats_add_counter(cv_seg, cv_user, our_version_number - cv_user->version_num, version_diff);
  //*****
  //set the version entry version number  
  our_version_entry->version_num=our_version_number;
  //set the number of ptes we are committing
  our_version_entry->updated_ptes=cv_user->dirty_pages_list_count;
  //mark it as ours
  our_version_entry->committer=vma;

  int counter_tmp=0;
  struct cv_logging_page_status_entry * logging_page_status=NULL;
  

#ifdef CV_COUNTERS_ON    
  unsigned long long start_tsc=native_read_tsc();
#endif

  //Now we need to traverse our dirty list, and commit
  list_for_each_safe(pos, tmp_pos, &(cv_user->dirty_pages_list->list)){
#ifdef CONV_LOGGING_ON
      if (counter_tmp++ % 50000000 == 0){
          CV_LOG_MESSAGE( "still here 1...%d\n", current->pid);
          cv_per_page_version_walk_unsafe_debug(wait_list, cv_seg->ppv);
      }
#endif
      pte_entry = list_entry(pos, struct snapshot_pte_list, list);
      //CV_LOG_MESSAGE( "s1 %d %lu %d %p\n", current->pid, our_version_number, pte_entry->page_index, pte_entry);
      if (pte_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING){

          //check and see if we want to make this a logging page.
          //We do this before we commit, because merging will mess up the diffing.
          if (cv_per_page_is_logging_page(cv_seg->ppv, pte_entry->page_index)){
              //migrate to a logging page
              cv_commit_migrate_page_to_logging(vma, cv_user, cv_seg, pte_entry, our_version_number);
              //grab the user logging page status objoct
              logging_page_status = cv_logging_page_status_lookup(cv_user, pte_entry->page_index);
              cv_commit_logging_entry(cv_list_entry_get_logging_entry(pte_entry), pte_entry, vma,
                                      cv_seg, cv_user, our_version_number, logging_page_status);
              //CV_LOG_MESSAGE( "2e %d %p\n", current->pid, pte_entry);
          }
          else{
              should_migrate=cv_commit_do_logging_migration_check(vma, pte_entry);
              //do page commit here
              cv_commit_page(cv_list_entry_get_page_entry(pte_entry), vma, our_version_number, pte_entry->page_index, pte_entry->checkpoint);
              if (should_migrate){
                  cv_commit_migrate_page_to_logging(vma, cv_user, cv_seg, pte_entry, our_version_number);
              }
          }
          //removing from the dirty list
          list_del(pos);
          list_add(pos, &our_version_entry->pte_list->list);
          cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
          cv_per_page_version_release_entry_lock(cv_seg, pte_entry);
          ++committed_pages;
          ++pte_updates;
          conv_dirty_delete_lookup(cv_user, pte_entry->page_index,0,1);
      }
      else{
          
          //do logging stuff in here!
          //grab the user logging page status objoct
          logging_page_status = cv_logging_page_status_lookup(cv_user, pte_entry->page_index);

          cv_commit_logging_entry(cv_list_entry_get_logging_entry(pte_entry), pte_entry, vma,
                                  cv_seg, cv_user, our_version_number, logging_page_status);
          if (logging_page_status->entries_allocated==0){
              cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
          }
          else{
#ifdef CONV_LOGGING_ON
              CV_LOG_MESSAGE( "avoiding updating actual....pid %d, page index %d, entries allocated %d\n",
                     current->pid, pte_entry->page_index, logging_page_status->entries_allocated);
#endif
          }
          cv_per_page_version_release_entry_lock(cv_seg, pte_entry);
          list_del(pos);
          list_add(pos, &our_version_entry->pte_list->list);
          conv_dirty_delete_lookup(cv_user, pte_entry->page_index,
                                   cv_list_entry_get_logging_entry(pte_entry)->line_index,
                                   cv_logging_is_full_page(cv_list_entry_get_logging_entry(pte_entry)));
          ++committed_pages;
      }
  }

  COUNTER_LATENCY(ENTIRE_COMMIT, native_read_tsc() - start_tsc);

#ifdef CV_COUNTERS_ON    
  unsigned long long start_wait_tsc=native_read_tsc();
#endif

  
  //now we need to commit the stuff in the 
  while(!list_empty(&wait_list->list)){
#ifdef CONV_LOGGING_ON
      if (counter_tmp++ % 50000000 == 0){
          CV_LOG_MESSAGE( "still here...%d\n", current->pid);
          cv_per_page_version_walk_unsafe_debug(wait_list, cv_seg->ppv);
      }
#endif
      if ((pte_entry=cv_per_page_version_walk_unsafe(wait_list, cv_seg->ppv, cv_seg))){
          if (pte_entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING){
              
              //check and see if we want to make this a logging page.
              //We do this before we commit, because merging will mess up the diffing.
              if (cv_per_page_is_logging_page(cv_seg->ppv, pte_entry->page_index)){
                  //migrate to a logging page
                  cv_commit_migrate_page_to_logging(vma, cv_user, cv_seg, pte_entry, our_version_number);
                  //grab the user logging page status objoct
                  logging_page_status = cv_logging_page_status_lookup(cv_user, pte_entry->page_index);
                  //do a logging commit instead
                  cv_commit_logging_entry(cv_list_entry_get_logging_entry(pte_entry), pte_entry, vma,
                                          cv_seg, cv_user, our_version_number, logging_page_status);
              }
              else{
                  should_migrate=cv_commit_do_logging_migration_check(vma, pte_entry);
                  //do page commit here
                  cv_commit_page(cv_list_entry_get_page_entry(pte_entry), vma, our_version_number, pte_entry->page_index, pte_entry->checkpoint);
                  if (should_migrate){
                      cv_commit_migrate_page_to_logging(vma, cv_user, cv_seg, pte_entry, our_version_number);
                  }
              }
              //remove from the waitlist
              list_del(&pte_entry->list);
              list_add(&pte_entry->list, &our_version_entry->pte_list->list);
              cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
              cv_per_page_version_release_entry_lock(cv_seg, pte_entry);
              ++committed_pages;
              ++pte_updates;
              conv_dirty_delete_lookup(cv_user, pte_entry->page_index,0,1);
          }
          else{
              //do logging stuff in here!
              //grab the user logging page status objoct
              logging_page_status = cv_logging_page_status_lookup(cv_user, pte_entry->page_index);
              
              cv_commit_logging_entry(cv_list_entry_get_logging_entry(pte_entry), pte_entry, vma,
                                      cv_seg, cv_user, our_version_number, logging_page_status);
              //what happens if we are committing multiple logging entries for this page? Without this check, we will release
              //the page level lock and waiting threads will begin to commit. That is not ideal. :)
              if (logging_page_status->entries_allocated==0){
                  cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
              }
              else{
#ifdef CONV_LOGGING_ON
                  CV_LOG_MESSAGE( "avoiding updating actual....pid %d, page index %d, logging writes %d, entries allocated %d\n",
                         current->pid, pte_entry->page_index, logging_page_status->logging_writes, logging_page_status->entries_allocated);
#endif
              }
              cv_per_page_version_release_entry_lock(cv_seg, pte_entry);
              list_del(&pte_entry->list);
              list_add(&pte_entry->list, &our_version_entry->pte_list->list);
              conv_dirty_delete_lookup(cv_user, pte_entry->page_index,
                                       cv_list_entry_get_logging_entry(pte_entry)->line_index, 
				       cv_logging_is_full_page(cv_list_entry_get_logging_entry(pte_entry)));
          }
      }
  }

  COUNTER_LATENCY(WAIT_LIST_COMMIT, native_read_tsc() - start_wait_tsc);

  //cv_stats_end(cv_seg, cv_user, 6, commit_waitlist_latency);      
  cv_stats_add_counter(cv_seg, cv_user, committed_pages, commit_pages);
  //no need to lock this...it doesn't have to be precise
  cv_seg->committed_pages+=our_version_entry->updated_ptes;
  //ok, we can finally commit our stuff
  cv_stats_start(cv_seg, 2, commit_wait_lock);
  spin_lock(&cv_seg->lock);
  cv_stats_end(cv_seg, cv_user, 2, commit_wait_lock);
  //make our version visible
  our_version_entry->visible=1;
  //set the number of pages 
  our_version_entry->num_of_entries=committed_pages;
  //reset the number of dirty pages to zero
  cv_user->dirty_pages_list_count=0;
  conv_dirty_clear_lookup(cv_user);

  //we only have the right to commit if we are one greater than the current committed version
  if (our_version_number == cv_seg->committed_version_num+1){
    //walk from our version up...find the largest visible entry
    version_entry_it=our_version_entry;
    for(version_pos=&our_version_entry->list; version_entry_it->visible==1; version_pos=version_pos->prev){
      version_entry_it=list_entry(version_pos, struct snapshot_version_list, list);
      if (version_entry_it->visible){
	max_version_number=version_entry_it->version_num;
      }
    }
    //we use a barrier here because the update is lock free and will simply read this version number
    //to publish that this version is available. Lets make sure everything that happened before it is
    //also published.
    barrier();
    cv_seg->committed_version_num=max_version_number;

#ifdef CONV_LOGGING_ON
    CV_LOG_MESSAGE( "IN COMMIT pid %d, segment %p, old committed version %lu, new version number %lu, next %lu\n", 
           current->pid, cv_seg, max_version_number, cv_seg->committed_version_num, cv_seg->next_avail_version_num);
#endif

    BUG_ON(cv_seg->committed_version_num < our_version_number);
    //export the new version to user space
    ksnap_meta_set_shared_version(vma, cv_seg->committed_version_num);
  }
  spin_unlock(&cv_seg->lock);
  
  if (cv_seg->committed_pages > CV_GARBAGE_INIT_PAGES &&  
      (cv_seg->committed_pages - cv_seg->last_committed_pages_gc_start) > CV_GARBAGE_START_INC) {
      struct cv_garbage_work * garbage_work = kmalloc(sizeof(struct cv_garbage_work), GFP_KERNEL);
      garbage_work->cv_seg = cv_seg;
      INIT_WORK(&garbage_work->work, cv_garbage_collection);
      cv_seg->last_committed_pages_gc_start = cv_seg->committed_pages;
      schedule_work(&garbage_work->work);
  }

  BUG_ON(!list_empty(&(cv_user->dirty_pages_list->list)) && !list_empty(&wait_list->list));

#ifdef CV_COUNTERS_ON    
  unsigned long long current_tsc=native_read_tsc();
#endif

  //now we perform an update so that we are fully up to date....the merging has already been done here in commit
  //if our version is not visible...we must wait.
  while(cv_seg->committed_version_num < our_version_number){
      //pause inside our busy loop
      rep_nop();
  }

  COUNTER_LATENCY(WAIT_ON_OTHERS_COMMIT, native_read_tsc() - current_tsc);

  //ok, its safe to update now
  cv_update_parallel_to_version_no_merge(vma, our_version_number, defer_work);
  if (!defer_work && pte_updates > 0){
      flush_tlb();
      INC(COUNTER_TLB_FLUSH);
  }
  cv_meta_set_dirty_page_count(vma, 0);
  cv_stats_end(cv_seg, cv_user, 0, commit_latency);

  //COUNTER_COMMIT_LATENCY(native_read_tsc() - start_tsc);
  COUNTER_COMMIT_ENTRIES(committed_pages);
  
  CV_LOG_MESSAGE( "IN COMMIT COMPLETE %d for segment %p, committed pages %d....our version num %lu committed %lu next %lu\n", 
                  current->pid, cv_seg, committed_pages, our_version_number, cv_seg->committed_version_num, cv_seg->next_avail_version_num);

}

