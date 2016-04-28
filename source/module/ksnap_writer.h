

#ifndef KSNAP_WRITER_H
#define KSNAP_WRITER_H

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>


struct snapshot_pte_list * conv_dirty_search_lookup(struct ksnap_user_data * cv_user_data, unsigned long index);

void conv_dirty_delete_lookup(struct ksnap_user_data * cv_user_data, unsigned long index);

void ksnap_add_dirty_page_to_list (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address);

void ksnap_revert_dirty_list(struct vm_area_struct * vma, struct address_space * mapping);

void conv_add_dirty_page_to_lookup(struct vm_area_struct * vma, struct snapshot_pte_list * new_dirty_entry, unsigned long index);


#endif
