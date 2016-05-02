
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
#include <asm/pgtable.h>
#include <asm/tlbflush.h>

#include "conversion.h"
#include "cv_stats.h"
#include "cv_event.h"
#include "ksnap_version_list.h"

//copy the userdata struct, this happens on fork
void ksnap_userdata_copy (struct vm_area_struct * old_vma, struct vm_area_struct * new_vma){

    struct ksnap * cv_seg=ksnap_vma_to_userdata(old_vma)->cv_seg;

    new_vma->ksnap_user_data=kmalloc(sizeof(struct ksnap_user_data), GFP_KERNEL);
    memcpy(new_vma->ksnap_user_data, old_vma->ksnap_user_data, sizeof(struct ksnap_user_data));
    
    ksnap_vma_to_userdata(new_vma)->dirty_pages_list_count=0;
    ksnap_vma_to_userdata(new_vma)->commits=0;
    ksnap_vma_to_userdata(new_vma)->last_commit_time.tv_sec=0;
    ksnap_vma_to_userdata(new_vma)->partial_version_num=0;
    ksnap_vma_to_userdata(new_vma)->id=atomic_inc_return(&cv_seg->id_counter);
    ksnap_vma_to_userdata(new_vma)->dirty_pages_list = _snapshot_create_pte_list();
    ksnap_vma_to_userdata(new_vma)->status = CV_USER_STATUS_AWAKE;
    ksnap_vma_to_userdata(new_vma)->committed_non_logging_entries = 0;

    cv_defer_work_init(&ksnap_vma_to_userdata(new_vma)->defer_work);

    cv_profiling_begin(&ksnap_vma_to_userdata(new_vma)->profiling_info, ksnap_vma_to_userdata(new_vma)->id);

    INIT_LIST_HEAD(&ksnap_vma_to_userdata(new_vma)->segment_list);
    INIT_RADIX_TREE(&ksnap_vma_to_userdata(new_vma)->dirty_list_lookup, GFP_KERNEL);
    INIT_RADIX_TREE(&ksnap_vma_to_userdata(new_vma)->partial_update_page_lookup, GFP_KERNEL);
    INIT_RADIX_TREE(&ksnap_vma_to_userdata(new_vma)->logging_page_status, GFP_KERNEL);
    
    list_add(&ksnap_vma_to_userdata(new_vma)->segment_list, &ksnap_vma_to_ksnap(old_vma)->segment_list);
    atomic_set(&(ksnap_vma_to_userdata(new_vma)->dirty_page_count), 0);
    cv_event_init(&ksnap_vma_to_userdata(new_vma)->event_info, &cv_seg->start_time);
    //calling anon_vma_prepare in the case that we don't have an anon_vma, bug if it returns non-zero;
    BUG_ON(anon_vma_prepare(new_vma));
    
#ifdef CONV_LOGGING_ON
    printk(KSNAP_LOG_LEVEL "New process pid %d new vma %p user %p list %p old vma %p....vm file %p mapping %p seg %p\n", 
           current->pid, new_vma, ksnap_vma_to_userdata(new_vma), 
           ksnap_vma_to_userdata(new_vma)->dirty_pages_list, old_vma, new_vma->vm_file, new_vma->vm_file->f_mapping, new_vma->vm_file->f_mapping->ksnap_data);
#endif
    
}
