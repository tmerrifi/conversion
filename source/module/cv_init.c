#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/dcache.h>
#include <linux/pagemap.h>
#include <linux/rmap.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <asm-generic/mman-common.h>
#include <linux/semaphore.h>


#include "conversion.h"
#include "cv_init.h"
#include "ksnap_version_list.h"
#include "cv_stats.h"
#include "cv_meta_data.h"
#include "cv_event.h"
#include "cv_profiling.h"
#include "cv_determinism.h"

MODULE_LICENSE("GPL");

int ksnap_tracking_on(struct vm_area_struct * vma){
  if (!vma->ksnap_user_data){
    return -EBADF;
  }
  else{
    ksnap_vma_to_userdata(vma)->use_tracking=1;
    return 0;
  }
}

int ksnap_tracking_off(struct vm_area_struct * vma){
  if (!vma->ksnap_user_data){
    return -EBADF;
  }
  else{
    ksnap_vma_to_userdata(vma)->use_tracking=0;
    return 0;
  }
}

int ksnap_open (struct vm_area_struct * vma, unsigned long flags){
  
  struct ksnap * ksnap_data;
  struct ksnap_user_data * user_data;
  struct address_space * mapping = vma->vm_file->f_mapping;
  
  if (vma->ksnap_user_data){
    printk(KSNAP_LOG_LEVEL "this happened!!!! %p\n", mapping->ksnap_data);
    return -EBADF;
  }

  if (!mapping->ksnap_data){
    int i=0;
    for (;i<500;++i){
      per_thread_debug.location[i]=0;
    }
  }

  //get the main ksnap_data (version list, etc...) from the mapping
  ksnap_data = (mapping->ksnap_data) ? mapping->ksnap_data : ksnap_init_snapshot(mapping, vma);
  BUG_ON(!ksnap_data);
  user_data = kmalloc(sizeof(struct ksnap_user_data), GFP_KERNEL);
  BUG_ON(!user_data);
  memset(user_data,0,sizeof(struct ksnap_user_data));
  user_data->id=atomic_inc_return(&ksnap_data->id_counter);
  user_data->vma =vma;
  user_data->dirty_pages_list_count=0;
  user_data->version_num=0;
  user_data->commits=0;
  user_data->last_commit_time.tv_sec=0;
  user_data->dirty_pages_list = _snapshot_create_pte_list();
  user_data->cv_seg=ksnap_data;
  user_data->status=CV_USER_STATUS_AWAKE;
  cv_defer_work_init(&user_data->defer_work);
  //deferred work entry allocation should be fast
  user_data->deferred_work_mem_cache=KMEM_CACHE(cv_defer_work_entry,0);
  cv_profiling_begin(&user_data->profiling_info, user_data->id);
  INIT_LIST_HEAD(&user_data->segment_list);
  INIT_RADIX_TREE(&user_data->dirty_list_lookup, GFP_KERNEL);
  INIT_RADIX_TREE(&user_data->partial_update_page_lookup, GFP_KERNEL);
  list_add(&user_data->segment_list, &ksnap_data->segment_list);
  vma->ksnap_user_data=user_data;
  tim_debug_instance.ptr_of_interest1=vma;
  //set the readahead window to zero (for now)
  if (vma->vm_file){
    vma->vm_file->f_ra.ra_pages=0;
  }
  cv_event_init(&user_data->event_info, &ksnap_data->start_time);
  
  //calling anon_vma_prepare in the case that we don't have an anon_vma, bug if it returns non-zero;
  BUG_ON(anon_vma_prepare(vma));

  return 0;
}

struct ksnap * ksnap_init_snapshot (struct address_space * mapping, struct vm_area_struct * vma){

#ifdef CONV_LOGGING_ON
    printk(KERN_EMERG " CONVERSION: initializing segment at address %p and vma %p\n", vma->vm_start, vma);
#endif

  struct ksnap * ksnap_data = kmalloc(sizeof(struct ksnap), GFP_KERNEL);
  //do we need to initialize the list?
  //create a new version list node
  ksnap_data->snapshot_pte_list = _snapshot_create_version_list();
  //uncommitted entry
  ksnap_data->uncommitted_version_entry = ksnap_data->snapshot_pte_list->uncommitted_version_entry;
  //now, lets initialize the radix tree for mapping index to pte
  INIT_RADIX_TREE(&ksnap_data->snapshot_page_tree, GFP_KERNEL);
  //setup the wait queue used for blocking snapshot requests
  init_waitqueue_head(&ksnap_data->snapshot_wq);
  //initialize the priority list
  INIT_LIST_HEAD(&ksnap_data->prio_list);
  //initialize the list of vmas
  INIT_LIST_HEAD(&ksnap_data->segment_list);
  //initialize the time since last commit
  ksnap_data->last_commit_time.tv_sec = ksnap_data->last_commit_time.tv_usec = 0;
  ksnap_data->last_acq_time.tv_sec = ksnap_data->last_acq_time.tv_nsec = 0;
  //initialize the last snapshot time
  ksnap_data->last_snapshot_time.tv_sec = ksnap_data->last_snapshot_time.tv_usec = 0;
  //set the revision number to zero
  atomic_set(&ksnap_data->revision_number,0);
  //initialize the ewma to the defined default
  ksnap_data->ewma_adapt = ADAPT_EWMA_DEFAULT_US;
  ksnap_data->pte_list_mem_cache = KMEM_CACHE(snapshot_pte_list, 0);
  ksnap_data->creator_id=current->pid;
  ksnap_data->ppv=cv_per_page_version_init(((vma->vm_end - vma->vm_start)/PAGE_SIZE));
  ksnap_data->committed_version_num=0;
  ksnap_data->next_avail_version_num=0;
  ksnap_data->committed_pages=0;
  ksnap_data->last_committed_pages_gc_start=0;
  ksnap_data->gc_seq_num=0;
  atomic_set(&ksnap_data->gc_thread_count, -1);
  spin_lock_init(&ksnap_data->lock);
  spin_lock_init(&ksnap_data->snapshot_page_tree_lock);
  INIT_WORK(&ksnap_data->garbage_work.work, cv_garbage_collection);
  ksnap_data->garbage_work.cv_seg = ksnap_data;
  atomic64_set(&ksnap_data->committed_version_atomic, 0);
  atomic64_set(&ksnap_data->uncommitted_version_entry_atomic, (uint64_t)ksnap_data->uncommitted_version_entry);
  atomic_set(&ksnap_data->pages_allocated,0);
  atomic_set(&ksnap_data->max_pages,0);
  atomic_set(&ksnap_data->id_counter, 0);
  mapping->ksnap_data = ksnap_data;  
  cv_stats_init(&ksnap_data->cv_stats);
  memset(ksnap_data->cv_per_process_stats, 0, sizeof(struct cv_per_process_detailed_statistics) * CV_MAX_PER_PROCESS_STATS);
  memset(ksnap_data->debug_points, 0, sizeof(int)*32);
  //initialize the hooks to NULL
  CV_HOOKS_INIT(ksnap_data);
  getnstimeofday(&ksnap_data->start_time);
  sema_init(&ksnap_data->sem_gc, 1);
  
#ifdef CV_DETERMINISM
  //make sure to do this after the hooks are initialized
  cv_determinism_init(ksnap_data);
#endif
  return ksnap_data;
}
