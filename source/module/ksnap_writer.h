

#ifndef KSNAP_WRITER_H
#define KSNAP_WRITER_H

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>


struct page * ksnap_get_dirty_ref_page(struct vm_area_struct * vma, unsigned long index);

struct snapshot_pte_list * conv_dirty_search_lookup(struct ksnap_user_data * cv_user_data, unsigned long index);

void ksnap_add_dirty_page_to_list (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address);

void ksnap_revert_dirty_list(struct vm_area_struct * vma, struct address_space * mapping);

#endif
