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



#include "conversion.h"


void cv_close(struct vm_area_struct * vma){

  //

  

  struct address_space * mapping = vma->vm_file->f_mapping;
  if (!mapping->ksnap_data){
    return;
  }
  
  struct ksnap * cv = (struct ksnap *)mapping->ksnap_data;
  struct ksnap_user_data * cv_user = ksnap_vma_to_userdata(vma);

  spin_lock(&cv->lock);

  int i=0;
  for (;i<10;++i){
    printk(KSNAP_LOG_LEVEL "%d %d, ", i, cv_user->debug_commit_times[i]);
  }
  printk("\n\n");
  printk(KSNAP_LOG_LEVEL "status....0 %d 1 %d 2 %d 3 %d 4 %d 5 %d 6 %d\n", 
	 cv->debug_points[0], cv->debug_points[1], cv->debug_points[2], cv->debug_points[3], cv->debug_points[4], cv->debug_points[5], cv->debug_points[6]);
  printk(KSNAP_LOG_LEVEL "the committed version %lu\n", cv->committed_version_num);
  
  printk(KSNAP_LOG_LEVEL "\n\nPRINTING USERS\n");
  struct list_head * pos;
  list_for_each(pos, &cv->segment_list){
    struct ksnap_user_data * user = list_entry(pos, struct ksnap_user_data, segment_list);
    printk(KSNAP_LOG_LEVEL "user id %d version num %llu\n", user->id, user->debug_version_num);
  }

  //walk the version list
  printk(KSNAP_LOG_LEVEL "\n\nPRINTING LIST\n");
  int counter=0;
  struct snapshot_version_list * vl;
  list_for_each(pos, &cv->snapshot_pte_list->list){
    vl=list_entry(pos, struct snapshot_version_list, list);
    printk(KSNAP_LOG_LEVEL "num %llu visible %d\n", vl->version_num, vl->visible);
    if (counter>5){
      break;
    }
  }

  if (vma->vm_file->f_mapping->ksnap_data == NULL){
    goto finished;
  }

  if(current->pid==cv->creator_id){
    cv_stats_print_all(&(cv->cv_stats), 
		       cv->cv_per_process_stats,
		       atomic_read(&cv->id_counter));
  }
  //deregister this vma
  list_del(&cv_user->segment_list);
  if (list_empty(&cv->segment_list)){
    //free the version list
    cv_garbage_final(cv);
    kfree(cv->ppv->entries);
    kfree(cv->ppv);
    //no one else is around, time to free this thing
    while(atomic_read(&cv->gc_thread_count)>=0){
      msleep(1);
    }
    kfree(cv);
    vma->vm_file->f_mapping->ksnap_data=NULL;
  }

 finished:
  spin_unlock(&cv->lock);
  kfree(vma->ksnap_user_data);



#ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "Closing process %d\n", current->pid);
#endif
}
