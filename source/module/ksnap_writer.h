

#ifndef KSNAP_WRITER_H
#define KSNAP_WRITER_H

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>


struct page * ksnap_get_dirty_ref_page(struct vm_area_struct * vma, unsigned long index);

struct snapshot_pte_list * conv_dirty_search_lookup(struct ksnap_user_data * cv_user_data, unsigned long index);

/*remove the old page from the page cache, handle its LRU stuff, etc...*/
void ksnap_remove_old_page(struct address_space * mapping, struct vm_area_struct * vma, 
			   unsigned long index, unsigned long * debug_time, struct page * ref_page);

void ksnap_commit_new_page(struct address_space * mapping, struct vm_area_struct * vma, 
			   struct page * page, struct list_head *  pte_entry_list_head,  unsigned long * debug_time);

void ksnap_add_dirty_page_to_list (struct vm_area_struct * vma, struct page * old_page, pte_t * new_pte, unsigned long address);

void tmp_ksnap_print_dirty(struct vm_area_struct * vma);

void ksnap_revert_dirty_list(struct vm_area_struct * vma, struct address_space * mapping);

#endif
