#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/string.h>

#include "conversion.h"


void cv_close(struct vm_area_struct * vma){
  
  struct address_space * mapping = vma->vm_file->f_mapping;
  if (!mapping->ksnap_data){
    return;
  }
  
  struct ksnap * cv = (struct ksnap *)mapping->ksnap_data;
  struct ksnap_user_data * cv_user = ksnap_vma_to_userdata(vma);


  spin_lock(&cv->lock);
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
