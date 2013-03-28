
#ifndef CV_LOCK_LIST_H
#define CV_LOCK_LIST_H

#include <linux/mm.h>

#define CV_LL_PAGES_PER_LOCK 10

struct cv_lock_list_entry{
  struct list_head list;
  uint32_t lock_index;
};

struct cv_lock_list_entry * cv_lock_list_init(void);

void cv_lock_list_add_entry(struct cv_lock_list_entry * list, uint32_t lock_index);

void cv_lock_list_clear(struct cv_lock_list_entry * list);

unsigned long cv_lock_list_count(struct vm_area_struct * vma);

#define cv_lock_list_index(addr, vma) \
  (((addr - vma->vm_start)/4096)/CV_LL_PAGES_PER_LOCK)

//acquire a lock based on address
#define cv_lock_list_acquire(lock_index, cv)		   \
  spin_lock(&cv->locks[lock_index]);
//  printk("acq lock %p \n", &cv->locks[lock_index]);

#define cv_lock_list_release(lock_index, cv)		   \
  spin_unlock(&cv->locks[lock_index]);
  //  printk("rel lock %p \n", &cv->locks[lock_index]);

#endif
