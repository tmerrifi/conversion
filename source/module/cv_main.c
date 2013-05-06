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
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <asm/unistd.h>
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
#include "cv_commit.h"
#include "cv_update.h"

MODULE_LICENSE("GPL");

//used for debugging things that happen within a given thread
struct cv_perthread_debug per_thread_debug;

//is this thing a conversion segment?
int is_snapshot (struct vm_area_struct * vma, struct mm_struct * mm, struct file * f){	 
  return (vma && vma->ksnap_user_data);
}

int __commit_times(uint64_t microsecs){
  int output=0;
  
  if (microsecs < 10){
    output=0;
  }
  else if (microsecs < 20){
    output=1;
  }
  else if (microsecs < 30){
    output=2;
  }
  else if (microsecs < 50){
    output=3;
  }
  else if (microsecs < 200){
    output=4;
  }
  else if (microsecs < 500){
    output=5;
  }
  return output;
}

/*This function's purpose is to be an entry point into our conversion code from the
  msync system call. If we are making a version, then we call commit. otherwise, we perform an update*/
void cv_msync(struct vm_area_struct * vma, unsigned long flags){
  struct timespec ts1, ts2;

  return;

  getrawmonotonic(&ts1);
  if (flags & MS_KSNAP_MAKE){
    cv_commit_version_parallel(vma, flags);
  }
  else{
    cv_update_parallel(vma, flags);
  }
  getrawmonotonic(&ts2);
  if (ts1.tv_nsec % 1000 == 0 &&
      cv_stats_elapsed_time_ns(&ts1, &ts2) > 10000){
    printk(KSNAP_LOG_LEVEL "elapsed time %lu\n", cv_stats_elapsed_time_ns(&ts1, &ts2));
  }
  ksnap_vma_to_userdata(vma)->debug_commit_times[__commit_times(cv_stats_elapsed_time_ns(&ts1, &ts2)/1000)]++;
}

/*call in to our page fault handler code to keep track of this new page*/
int cv_page_fault (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address){
  ksnap_add_dirty_page_to_list (vma, old_page, new_pte, address);
  //do some statistics stuff
  cv_stats_inc_pages_allocated(&mapping_to_ksnap(vma->vm_file->f_mapping)->cv_stats);
  cv_stats_inc_ksnap_page_faults(&mapping_to_ksnap(vma->vm_file->f_mapping)->cv_stats);	
  return 1;
}

int snapshot_nmi_dead_callback(struct notifier_block * nb, unsigned long err, void * data){
  struct page * pg;
    int i=0;
    printk(KSNAP_LOG_LEVEL "DIED!!!!!\n");
    /*for (;i<500;++i){
      printk(KSNAP_LOG_LEVEL "%d:%p,", i, (void *)per_thread_debug.location[i]);
      if (per_thread_debug.location[i]==0x666){
	pg = (struct page *)per_thread_debug.location[i+1];
	printk(KSNAP_LOG_LEVEL "   PAGE COUNT %p %d\n", pg, page_count(pg));
      }
      
    }
    printk( KSNAP_LOG_LEVEL "DONE OUTPUTTING!!!!!\n");*/
    return 1;
}


static struct notifier_block nmi_snap_nb = {
  .notifier_call = snapshot_nmi_dead_callback
  };


int init_module(void)
{
  mmap_snapshot_instance.ksnap_open = ksnap_open;
  mmap_snapshot_instance.ksnap_close = cv_close;
  mmap_snapshot_instance.ksnap_tracking_on = ksnap_tracking_on;
  mmap_snapshot_instance.is_snapshot = is_snapshot;
  mmap_snapshot_instance.snapshot_msync = cv_msync;			//TODO: this function name in the struct should change
  mmap_snapshot_instance.init_snapshot = NULL;
  mmap_snapshot_instance.do_snapshot_add_pte = cv_page_fault;
  mmap_snapshot_instance.ksnap_userdata_copy = ksnap_userdata_copy;
  mmap_snapshot_instance.snap_sequence_number=random32()%10000;
  register_die_notifier(&nmi_snap_nb);
  ksnap_merge_init();
  printk(KSNAP_LOG_LEVEL "vfork!! %d\n", __NR_vfork);
  return 0;
}

void cleanup_module(void)
{

  tim_debug_instance.tim_get_unmapped_area_debug=NULL;
  tim_debug_instance.tim_unmap_debug=NULL;
  mmap_snapshot_instance.ksnap_close = NULL;
  mmap_snapshot_instance.ksnap_open = NULL;
  mmap_snapshot_instance.is_snapshot = NULL;
  mmap_snapshot_instance.snapshot_msync = NULL;
  mmap_snapshot_instance.init_snapshot = NULL;
  mmap_snapshot_instance.do_snapshot_add_pte = NULL;
  mmap_snapshot_instance.init_subscriber = NULL;
  mmap_snapshot_instance.stats_inc_pages_allocated = NULL;
  mmap_snapshot_instance.stats_dec_pages_allocated = NULL;
  mmap_snapshot_instance.ksnap_userdata_copy = NULL;
  mmap_snapshot_instance.ksnap_tracking_on = NULL;
  cv_merge_free();
  unregister_die_notifier(&nmi_snap_nb);
}




