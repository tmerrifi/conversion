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

void conversion_thread_status (struct vm_area_struct * vma, unsigned long status){
    if (!vma->ksnap_user_data){
        return;
    }
    ksnap_vma_to_userdata(vma)->status = (status == 0) ? CV_USER_STATUS_ASLEEP : CV_USER_STATUS_AWAKE;
    if (status){
        ksnap_vma_to_ksnap(vma)->gc_seq_num++;
    }
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
void cv_msync(struct vm_area_struct * vma, unsigned long flags, size_t editing_unit){
  struct timespec ts1, ts2;  
  if (flags==CONV_TRACE){
      spin_lock(&ksnap_vma_to_ksnap(vma)->lock);
      cv_profiling_print(&ksnap_vma_to_userdata(vma)->profiling_info);
      spin_unlock(&ksnap_vma_to_ksnap(vma)->lock);
  }
  else if (flags==CONV_COMMIT_AND_UPDATE){
      cv_commit_version_parallel(vma, CONV_DO_WORK_NOW);
  }
  else if (flags==CONV_COMMIT_AND_UPDATE_DEFERRED_START){
      cv_commit_version_parallel(vma, CONV_DEFER_WORK);
  }
  else if(flags==CONV_COMMIT_AND_UPDATE_DEFERRED_END){
      //do nothing yet
      do_deferred_work(vma);
  }
  else if (flags==CONV_UPDATE_DEFERRED_START){
      cv_update_parallel(vma, flags, CONV_DEFER_WORK);
  }
  else if (flags==CONV_UPDATE_DEFERRED_END){
      //do nothing yet
      do_deferred_work(vma);
  }
  else if (flags==CONV_REVERT){
      conv_revert(vma);
  }
  else if (flags==CONV_CHECKPOINT){
      conv_checkpoint(vma);
  }
  else{
      cv_update_parallel(vma, flags, CONV_DO_WORK_NOW);
  }
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
    return 1;
}


static struct notifier_block nmi_snap_nb = {
  .notifier_call = snapshot_nmi_dead_callback
  };

void conv_cow_user_page(struct page * new_page, struct page * old_page,
                        unsigned long address, struct vma_area_struct * vma, struct mm_struct * init_mm ){


    char *vfrom, *vto;
    char tmp[PAGE_SIZE/4];
    
    vfrom = kmap_atomic(old_page, KM_USER0);
    vto = kmap_atomic(new_page, KM_USER1);
    pte_t * pte = pte_get_entry_from_address(init_mm, vto);
    if (pte){
        //set to WC
        //*pte=pte_clear_flags(*pte, _PAGE_CACHE_MASK);
        //*pte=pte_set_flags(*pte, _PAGE_CACHE_WC);
        //__flush_tlb_one(vto);
        //printk(KERN_EMERG "vto %p, __pa %p, pte val %p\n", vto, __pa(vto), *pte);

        //prefetch source
        /* int i=0; */
        /* for (i=0;i<PAGE_SIZE;i+=8){ */
        /*     prefetch(vfrom+i); */
        /* } */
        //prefetch destination
        /* for (i=0;i<PAGE_SIZE;i+=8){ */
        /*     prefetch(vto+i); */
        /* } */
        //now do the copy
        //conv_time_and_print_section(){
            memcpy(vto, vfrom, PAGE_SIZE);
            //}
        //put WB back
        //*pte=pte_clear_flags(*pte, _PAGE_CACHE_MASK);
        //__flush_tlb_one(vto);
    }
    else{
        //conv_time_and_print_section(){
            memcpy(vto, vfrom, PAGE_SIZE);
            //}
    }

    kunmap_atomic(vto, KM_USER1);
    kunmap_atomic(vfrom, KM_USER0);
    
}    



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
  mmap_snapshot_instance.conversion_thread_status=conversion_thread_status;
  //mmap_snapshot_instance.conv_cow_user_page=conv_cow_user_page;
  
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
    mmap_snapshot_instance.conversion_thread_status=NULL;
    //mmap_snapshot_instance.conv_cow_user_page=NULL;
    cv_merge_free();
    unregister_die_notifier(&nmi_snap_nb);
}




