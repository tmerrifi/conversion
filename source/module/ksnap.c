
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

#include "ksnap.h"
#include "cv_stats.h"
#include "ksnap_version_list.h"

//copy the userdata struct, this happens on fork
void ksnap_userdata_copy (struct vm_area_struct * old_vma, struct vm_area_struct * new_vma){

  new_vma->ksnap_user_data=kmalloc(sizeof(struct ksnap_user_data), GFP_KERNEL);
  memcpy(new_vma->ksnap_user_data, old_vma->ksnap_user_data, sizeof(struct ksnap_user_data));
  
  ksnap_vma_to_userdata(new_vma)->dirty_pages_list_count=0;
  ksnap_vma_to_userdata(new_vma)->commits=0;
  ksnap_vma_to_userdata(new_vma)->last_commit_time.tv_sec=0;
  ksnap_vma_to_userdata(new_vma)->dirty_pages_list = _snapshot_create_pte_list();
  INIT_LIST_HEAD(&ksnap_vma_to_userdata(new_vma)->segment_list);
  INIT_RADIX_TREE(&ksnap_vma_to_userdata(new_vma)->dirty_list_lookup, GFP_KERNEL);
  list_add(&ksnap_vma_to_userdata(new_vma)->segment_list, &ksnap_vma_to_ksnap(old_vma)->segment_list);
  atomic_set(&(ksnap_vma_to_userdata(new_vma)->dirty_page_count), 0);

  //calling anon_vma_prepare in the case that we don't have an anon_vma, bug if it returns non-zero;
  BUG_ON(anon_vma_prepare(new_vma));

  #ifdef CONV_LOGGING_ON
  printk(KSNAP_LOG_LEVEL "COPYING USER DATA!!!!! pid %d new vma %p user %p list %p old vma %p....vm file %p mapping %p seg %p\n", 
	 current->pid, new_vma, ksnap_vma_to_userdata(new_vma), 
	 ksnap_vma_to_userdata(new_vma)->dirty_pages_list, old_vma, new_vma->vm_file, new_vma->vm_file->f_mapping, new_vma->vm_file->f_mapping->ksnap_data);
  #endif

}

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
    printk(KSNAP_LOG_LEVEL "\n\n**********DOES THIS HAPPEN?\n\n\n\n");
    vma->vm_file->f_mapping->ksnap_data=NULL;
  }

 finished:
  spin_unlock(&cv->lock);
  kfree(vma->ksnap_user_data);
}
