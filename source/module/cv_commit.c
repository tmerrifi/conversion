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

//remove the old page from the page cache, handle its LRU stuff, etc...
void __remove_old_page(struct address_space * mapping, struct vm_area_struct * vma, 
		       unsigned long index, struct page * ref_page, uint64_t our_version){

  struct list_head * old_entry_lh;
  struct snapshot_pte_list * old_entry; 

  old_entry_lh = radix_tree_lookup(&mapping_to_ksnap(mapping)->snapshot_page_tree, index);
  if (old_entry_lh==NULL){
    return;
  }
  old_entry = list_entry(old_entry_lh, struct snapshot_pte_list, list);
  old_entry->obsolete_version=our_version;
}

void __update_page_mapping(struct address_space * mapping, struct vm_area_struct * vma, 
			   struct page * page, struct snapshot_pte_list * version_list_entry, int stats){
  struct ksnap * cv_seg;
  int insert_error=0;
  cv_seg = ksnap_vma_to_ksnap(vma);
  //make sure the page wasn't free'd out from under us
  if (!page_count(page)){
    BUG();
  }
  do{
    //lets now add our new pte into the pte radix tree
    insert_error = radix_tree_insert(&cv_seg->snapshot_page_tree, page->index, &version_list_entry->list);
    //if it wasn't an eexist error, then something is wrong and we have a bug
    if (insert_error == -EEXIST){
      radix_tree_delete(&cv_seg->snapshot_page_tree, page->index);
    }
    else if(insert_error){
      BUG();
      return;
    }
  }while(insert_error);

  cv_per_page_version_update_version_entry(cv_seg->ppv, version_list_entry);
  get_page(page);
  return;
}

void cv_commit_page(struct snapshot_pte_list * version_list_entry, struct vm_area_struct * vma, uint64_t our_revision, int stats){
  struct page * page;
  struct address_space * mapping = NULL;
  struct snapshot_pte_list * committed_entry;
  struct ksnap * cv_seg;
  pte_t page_table_e;

  cv_seg = ksnap_vma_to_ksnap(vma);
  //first we get the address_space
  mapping = vma->vm_file->f_mapping;
  //the pfn in our current page table doesn't equal the one we are trying to commit. Perhaps a fork() occured since our last commit?
  if (pte_pfn(*(version_list_entry->pte)) != version_list_entry->pfn){
    return;
  }
  //lets get that page struct that is pointed to by this pte...
  page = pfn_to_page(version_list_entry->pfn);
  BUG_ON(page==NULL);
  //has this page been committed since we've updated? Then we need to merge
  committed_entry = cv_version_list_lookup(cv_seg, version_list_entry->page_index);
  if (committed_entry && pfn_to_page(committed_entry->pfn) != version_list_entry->ref_page){
    ksnap_merge(pfn_to_page(committed_entry->pfn),
		(unsigned int *)((version_list_entry->page_index << PAGE_SHIFT) + vma->vm_start), 
		version_list_entry->ref_page, pfn_to_page(version_list_entry->pfn));
    
    cv_stats_inc_merged_pages(&cv_seg->cv_stats);
  }

  //get the pre-existing pte value and clear the pte pointer
  page_table_e = ptep_get_and_clear(vma->vm_mm, version_list_entry->addr, version_list_entry->pte);
  //we need to write protect the owner's pte again
  page_table_e = pte_wrprotect(page_table_e);	
  //set it back
  set_pte(version_list_entry->pte, page_table_e);

  //flush the tlb cache
  flush_tlb_page(vma, version_list_entry->addr);
  __remove_old_page(mapping, vma, page->index, version_list_entry->ref_page, our_revision);
  __update_page_mapping(mapping, vma, page, version_list_entry, stats);
  if (version_list_entry->ref_page){
    put_page(version_list_entry->ref_page);
  }
  
}


/*This is the main commit function. */
void cv_commit_version_parallel(struct vm_area_struct * vma, unsigned long flags){
  struct ksnap * cv_seg; //main conversion datastructure
  struct ksnap_user_data * cv_user;
  struct snapshot_version_list * next_version_entry; //after claiming a new version, we add a new version on the end
  struct snapshot_version_list * our_version_entry; //the version that we claim as "ours" from the version list
  struct snapshot_version_list * version_entry_it; //used when we walk the list to find out if others have committed before us
  struct snapshot_pte_list * wait_list, * pte_entry;
  uint64_t our_version_number;
  struct list_head * pos, * tmp_pos, * version_pos;  //pointers for iterating
  uint64_t max_version_number; //after we commit, others may have beat us to the punch...this is used when we iterate through the list to find out

  int committed_pages=0;
 
  if (vma==NULL || vma->vm_file==NULL || vma->vm_file->f_mapping==NULL){
    return;
  }

  //printk(KSNAP_LOG_LEVEL "IN COMMIT %d\n", current->pid);

  //get conversion for this segment
  cv_seg=mapping_to_ksnap(vma->vm_file->f_mapping);
  //get conversion user data
  cv_user=ksnap_vma_to_userdata(vma);

  cv_user->commits++;

  if (list_empty(&(cv_user->dirty_pages_list->list))){
    printk(KSNAP_LOG_LEVEL "whoops!\n");
    return;
  }

  cv_seg->debug_points[cv_user->id]=0xB1;

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
  cv_seg->debug_points[cv_user->id]=0xB2;
  //GLOBAL LOCK ACQUIRE
  cv_stats_start(cv_seg, 1, commit_wait_lock);
  spin_lock(&cv_seg->lock);
  cv_stats_end(cv_seg, cv_user, 1, commit_wait_lock);
  //get the right version number
  cv_seg->next_avail_version_num++;
  our_version_number=cv_seg->next_avail_version_num;
  //claim the list we'll be using to add to the version list
  our_version_entry = cv_seg->uncommitted_version_entry;
  //add our "next version" to the end of the list for the next committer to use
  list_add(&next_version_entry->list, &cv_seg->snapshot_pte_list->list);
  //setup the new "next" version
  cv_seg->uncommitted_version_entry = next_version_entry;
  cv_per_page_version_walk(cv_user->dirty_pages_list, wait_list,
			   cv_seg->ppv, our_version_number);
  spin_unlock(&cv_seg->lock);
  //GLOBAL LOCK RELEASED
  cv_seg->debug_points[cv_user->id]=0xB3;

  atomic64_set(&cv_seg->uncommitted_version_entry_atomic, (uint64_t)cv_seg->uncommitted_version_entry);

  cv_stats_add_counter(cv_seg, cv_user, our_version_number - cv_user->version_num, version_diff);
  
  //set the version entry version number  
  our_version_entry->version_num=our_version_number;
  //set the number of ptes we are committing
  our_version_entry->updated_ptes=cv_user->dirty_pages_list_count;
  //mark it as ours
  our_version_entry->committer=vma;
  cv_seg->debug_points[cv_user->id]=0xB4;
  //Now we need to traverse our dirty list, and commit
  list_for_each_safe(pos, tmp_pos, &(cv_user->dirty_pages_list->list)){
    pte_entry = list_entry(pos, struct snapshot_pte_list, list);
    cv_commit_page(pte_entry, vma, our_version_number, 0);
    //removing from the dirty list
    list_del(pos);
    list_add(pos, &our_version_entry->pte_list->list);
    cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
    ++committed_pages;
  }
  cv_seg->debug_points[cv_user->id]=0xB5;
  

  //now we need to commit the stuff in the 
  while(!list_empty(&wait_list->list)){
    if ((pte_entry=cv_per_page_version_walk_unsafe(wait_list, cv_seg->ppv))){
      //grab the currently committed entry
      cv_commit_page(pte_entry, vma, our_version_number, 1);
      //remove from the waitlist
      list_del(&pte_entry->list);
      list_add(&pte_entry->list, &our_version_entry->pte_list->list);
      cv_per_page_version_update_actual_version(cv_seg->ppv, pte_entry->page_index, our_version_number);
      ++committed_pages;
    }
  }
  cv_seg->debug_points[cv_user->id]=0xB6;
  //cv_stats_end(cv_seg, cv_user, 6, commit_waitlist_latency);      
  cv_stats_add_counter(cv_seg, cv_user, committed_pages, commit_pages);
  //no need to lock this...it doesn't have to be precise
  cv_seg->committed_pages+=our_version_entry->updated_ptes;
  //ok, we can finally commit our stuff
  cv_stats_start(cv_seg, 2, commit_wait_lock);
  cv_seg->debug_points[cv_user->id]=0xB7;
  spin_lock(&cv_seg->lock);
  cv_stats_end(cv_seg, cv_user, 2, commit_wait_lock);
  //make our version visible
  our_version_entry->visible=1;
  //set the number of pages 
  our_version_entry->num_of_entries=committed_pages;
  //we only have the right to commit if we are one greater than the current committed version
  if (our_version_number == cv_seg->committed_version_num+1){
    //walk from our version up...find the largest visible entry
    //list_for_each_prev(version_pos, our_version_entry->list.next){
    version_entry_it=our_version_entry;
    for(version_pos=&our_version_entry->list; version_entry_it->visible==1; version_pos=version_pos->prev){
      version_entry_it=list_entry(version_pos, struct snapshot_version_list, list);
      if (version_entry_it->visible){
	max_version_number=version_entry_it->version_num;
      }
    }
    cv_seg->committed_version_num=max_version_number;
    atomic64_set(&cv_seg->committed_version_atomic, cv_seg->committed_version_num);
    BUG_ON(cv_seg->committed_version_num < our_version_number);
    //export the new version to user space
    ksnap_meta_set_shared_version(vma, cv_seg->committed_version_num);
  }
  spin_unlock(&cv_seg->lock);
  cv_seg->debug_points[cv_user->id]=0xB8;
  
  if (cv_seg->committed_pages > 10000 &&  
      (cv_seg->committed_pages - cv_seg->last_committed_pages_gc_start) > CV_GARBAGE_START_INC && 
      atomic_inc_and_test(&cv_seg->gc_thread_count)){
    cv_seg->last_committed_pages_gc_start = cv_seg->committed_pages;
    schedule_work(&cv_seg->garbage_work.work);
  }


  BUG_ON(!list_empty(&(cv_user->dirty_pages_list->list)) && !list_empty(&wait_list->list));

  //now we perform an update so that we are fully up to date....the merging has already been done here in commit
  //if our version is not visible...we must wait.
  if (cv_seg->committed_version_num < our_version_number){
    cv_seg->debug_points[cv_user->id]=0xB9;
    printk(KSNAP_LOG_LEVEL "committed %lu ours %lu\n", cv_seg->committed_version_num, our_version_number);
    while(cv_seg->committed_version_num < our_version_number){}
  }
  cv_seg->debug_points[cv_user->id]=0xB10;

  //ok, its safe to update now
  //cv_update_parallel_to_version_no_merge(vma, our_version_number);
  cv_meta_set_dirty_page_count(vma, 0);
  cv_stats_end(cv_seg, cv_user, 0, commit_latency);
  #ifdef CONV_LOGGING_ON
  if (committed_pages > 50){
    printk(KSNAP_LOG_LEVEL "IN COMMIT %d, committed pages %d....our version num %lu committed %lu\n", 
	   current->pid, committed_pages, our_version_number, cv_seg->committed_version_num);
  }
  #endif
  cv_seg->debug_points[cv_user->id]=0xBF;

}

