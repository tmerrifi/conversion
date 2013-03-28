
#ifndef CV_DIRTY_H
#define CV_DIRTY_H

void cv_dirty_remove(struct ksnap_user_data * cv_user_data, struct snapshot_pte_list * entry);

void cv_dirty_add(struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address);

struct snapshot_pte_list * cv_dirty_lookup(struct vm_area_struct * vma, unsigned long index);

void cv_dirty_clear(struct vm_area_struct * vma, struct address_space * mapping);

#endif
