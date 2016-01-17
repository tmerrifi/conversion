#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/mman.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/task_clock.h>

#include "cv_determinism.h"

void __add_clock_ticks(struct ksnap * cv, struct ksnap_user_data * cv_user, uint32_t ticks){
    if (cv_user){
        cv_user->clock_tick_buffer+=ticks;
        if (cv_user->clock_tick_buffer >= CV_DETERMINISM_TICK_BUFFER_FLUSH_SIZE &&
            current->task_clock.user_status){
            //flush it
            task_clock_func.task_clock_add_ticks(current->task_clock.group_info, cv_user->clock_tick_buffer);
            cv_user->clock_tick_buffer=0;
        }
    }
}

void cv_determinism_on_commit_entry(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_commit_type_t type ){
    switch(type){
    case CV_HOOKS_COMMIT_ENTRY_SKIP:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_SKIP);
        break;
    case CV_HOOKS_COMMIT_ENTRY_MERGE:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_MERGE);
        break;
    case CV_HOOKS_COMMIT_ENTRY_COMMIT:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_COMMIT);
        break;
 }
}

void cv_determinism_on_update_entry(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_update_type_t type ){
    switch(type){
    case CV_HOOKS_UPDATE_ENTRY_SKIP:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_SKIP);
        break;
    case CV_HOOKS_UPDATE_ENTRY_MERGE:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_MERGE);
        break;
    case CV_HOOKS_UPDATE_ENTRY_UPDATE:
        __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_UPDATE);
        break;
    }    
}

void cv_determinism_on_cow(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page){
    __add_clock_ticks(cv, cv_user, CV_DETERMINISM_TICKS_COW);
}

void cv_determinism_init(struct ksnap * cv_seg){
    //set hooks
    printk(KERN_EMERG "initializing determ %p", cv_seg);
    cv_seg->hooks.cv_on_commit_entry=cv_determinism_on_commit_entry;
    cv_seg->hooks.cv_on_update_entry=cv_determinism_on_update_entry;
    cv_seg->hooks.cv_on_cow=cv_determinism_on_cow;
        
}

