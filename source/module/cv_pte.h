
#ifndef CV_PTE_H
#define CV_PTE_H

extern int snap_page_counter;

//return a pte given an address
pte_t * pte_get_entry_from_address(struct mm_struct * mm, unsigned long addr);

//takes a pte (source), and an address (destination) and will create a new (or use an old) pte for address
//and copy the pte into it.
int pte_copy_entry (pte_t * pte, unsigned long pfn, unsigned long index, 
		    struct vm_area_struct * vma_read_only, int flush_tlb_entry, int defer_work, struct ksnap_user_data * user);

void do_deferred_work(struct vm_area_struct * vma);

#endif
