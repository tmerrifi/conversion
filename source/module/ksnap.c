
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
  ksnap_vma_to_userdata(new_vma)->dirty_pages_list = _snapshot_create_pte_list();

  printk(KSNAP_LOG_LEVEL "COPYING USER DATA!!!!! pid %d new vma %p user %p list %p old vma %p\n", 
	 current->pid, new_vma, ksnap_vma_to_userdata(new_vma), ksnap_vma_to_userdata(new_vma)->dirty_pages_list, old_vma);

  atomic_set(&(ksnap_vma_to_userdata(new_vma)->dirty_page_count), 0);
  //printk("setting vma to null %p %d\n", new_vma, current->pid);
  //new_vma->snapshot_pte_list=NULL;
  //printk("copy...don't copy %d\n", (old_vma->vm_flags | VM_DONTCOPY));
  INIT_RADIX_TREE(&ksnap_vma_to_userdata(new_vma)->dirty_list_lookup, GFP_KERNEL);
  //getrawmonotonic(&tv2);
  //printk("userdata copy: %lu\n", tv2.tv_nsec - tv1.tv_nsec);
  //printk("the vma im copying....new %p old %p\n", new_vma, old_vma);
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
    vma->vm_file->f_mapping->ksnap_data=NULL;
  }

 finished:
  spin_unlock(&cv->lock);
  kfree(vma->ksnap_user_data);
}
