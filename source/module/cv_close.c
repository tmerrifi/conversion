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
#include <linux/vmalloc.h>


#include "conversion.h"
#include "cv_event.h"
#include "cv_memory_accounting.h"
#include "cv_logging.h"
#include "cv_store_interpreter_functions.h"

void cv_close(struct vm_area_struct * vma){

  struct address_space * mapping = vma->vm_file->f_mapping;
  if (!mapping->ksnap_data){
    return;
  }
  
  struct ksnap * cv = (struct ksnap *)mapping->ksnap_data;
  struct ksnap_user_data * cv_user = ksnap_vma_to_userdata(vma);

  //clear local logging page status
  cv_gc_logging_page_status_entries(cv_user);
  
  spin_lock(&cv->lock);
  if (vma->vm_file->f_mapping->ksnap_data == NULL){
    goto unlock_and_leave;
  }
  if(current->pid==cv->creator_id){
    cv_stats_print_all(&(cv->cv_stats), 
		       cv->cv_per_process_stats,
		       atomic_read(&cv->id_counter));
    cv_memory_accounting_print(cv);
  }
  cv_event_print(&cv_user->event_info, cv_user->id);
  counters_print_all(cv_user);
  //deregister this vma
  list_del(&cv_user->segment_list);
  if (list_empty(&cv->segment_list)){
      cv_logging_print_stats(cv);
      //free the version list
      vfree(cv->ppv->entries);
      kfree(cv->ppv);
      while(atomic_read(&cv->gc_thread_count)>=0){
          //use a pause
          rep_nop();
      }
      cv_garbage_final(cv);
      kfree(cv);
      vma->vm_file->f_mapping->ksnap_data=NULL;
      goto leave;
  }

 unlock_and_leave:
  spin_unlock(&cv->lock);
 leave:
  interpret_free_disassemble_cache(cv_user->disassemble_cache);
  kfree(vma->ksnap_user_data);



#ifdef CONV_LOGGING_ON
  printk(KERN_INFO "Closing process %d\n", current->pid);
#endif
}
