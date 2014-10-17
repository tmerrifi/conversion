#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/mman.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>


#include "cv_determinism.h"

void cv_determinism_init(struct vm_area_struct * vma, unsigned long vector_clock_addr){
    struct ksnap_user_data * cv_user;
    struct ksnap * cv_seg;
    int i=0;

    cv_user=ksnap_vma_to_userdata(vma);
    cv_seg=ksnap_vma_to_ksnap(vma);

    cv_user->vector_clock=(uint32_t *)vector_clock_addr;
    //set hooks
    cv_seg->hooks.cv_on_commit_begin=cv_determinism_on_commit_begin;
    cv_seg->hooks.cv_on_update_begin=cv_determinism_on_update_begin;

    for (;i<64;++i){
        if (cv_user->vector_clock[i]==(1<<30)){
            cv_user->consequence_id=i;
        }
    }

    printk(KERN_EMERG "determinism_init %p id: %d", (uint32_t *)vector_clock_addr, cv_user->consequence_id);

    /*struct ksnap * cv_seg;
    //get conversion for this segment
    cv_seg=mapping_to_ksnap(vma->vm_file->f_mapping);
    //set hooks
    cv_seg->hooks.cv_on_commit_begin=cv_determinism_on_commit_begin;
    cv_seg->hooks.cv_on_update_begin=cv_determinism_on_update_begin;
    //set up data and cv_determinism struct
    cv_seg->app_data=(struct cv_determinism_seg *)kmalloc(sizeof(struct cv_determinism_seg), GFP_KERNEL);
    ((struct cv_determinism_seg*)cv_seg->app_data)->token_addr=(uint32_t*)token_addr;
    //printk(KERN_EMERG " in INIT huh? %lu token %p\n", cv_seg->next_avail_version_num, (void *)token_addr);*/
}

void cv_determinism_on_commit_begin(struct ksnap * cv_seg, unsigned long flags){

}

void cv_determinism_on_update_begin(struct ksnap * cv_seg, unsigned long flags){

}
