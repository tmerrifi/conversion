
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/slab.h>


#include "cv_lock_list.h"

struct cv_lock_list_entry * cv_lock_list_init(void){
  struct cv_lock_list_entry * lock_list = kmalloc(sizeof(struct cv_lock_list_entry), GFP_KERNEL);
  INIT_LIST_HEAD(&lock_list->list);
  return lock_list;
}

void cv_lock_list_add_entry(struct cv_lock_list_entry * list, uint32_t lock_index){
  struct cv_lock_list_entry * new_entry = kmalloc(sizeof(struct cv_lock_list_entry), GFP_KERNEL);
  //printk(KERN_INFO " ADDED %d lock\n", lock_index);
  new_entry->lock_index = lock_index;
  INIT_LIST_HEAD(&new_entry->list);
  list_add(&new_entry->list, &list->list);
}

void cv_lock_list_clear(struct cv_lock_list_entry * list){
  struct list_head * pos, * tmp;
  struct cv_lock_list_entry * entry;

  list_for_each_safe(pos, tmp, &list->list){
    entry=list_entry(pos, struct cv_lock_list_entry, list);
    list_del(pos);
    kfree(entry);
  }
}

unsigned long cv_lock_list_count(struct vm_area_struct * vma){
  printk("number of locks....%lu \n", ((vma->vm_end - vma->vm_start)/PAGE_SIZE)/CV_LL_PAGES_PER_LOCK);
  return ((vma->vm_end - vma->vm_start)/PAGE_SIZE)/CV_LL_PAGES_PER_LOCK;
}
