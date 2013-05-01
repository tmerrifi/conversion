
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <linux/rmap.h>
#include <linux/time.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>

#include "ksnap.h"

int snap_page_counter=0;

MODULE_LICENSE("GPL");

//return a pte given an address
pte_t * pte_get_entry_from_address(struct mm_struct * mm, unsigned long addr){
	
	pgd_t * pgd;
	pud_t *pud;
	pte_t * pte;
	pmd_t *pmd;

	pgd = pgd_offset(mm, addr);
	if (!pgd){
		goto error;
	}
	pud = pud_alloc(mm, pgd, addr);
	if (!pud){
		goto error;
	}
	pmd = pmd_alloc(mm, pud, addr);
	if (!pmd){
		goto error;	
	}
	pte = pte_alloc_map(mm, pmd, addr);
	if (!pte){
		goto error;
	}
	return pte;
	
	error:
		return NULL;
}


//takes a pte (source), and an address (destination) and will create a new (or use an old) pte for address
//and copy the pte into it.
int pte_copy_entry (pte_t * pte, unsigned long pfn, unsigned long index, 
		    struct vm_area_struct * vma, int flush_tlb_entry){
	struct page * page, * old_page;	
	unsigned long readonly_addr;
	pte_t * dest_pte;
	pte_t tmp_ro_pte;
	cv_stats_function_init();

	cv_stats_start(ksnap_vma_to_ksnap(vma), 0, lock_latency_1);
	//calling anon_vma_prepare in the case that we don't have an anon_vma, bug if it returns non-zero;
	BUG_ON(anon_vma_prepare(vma));
	readonly_addr = (index << PAGE_SHIFT) + vma->vm_start;	//get the new address
	dest_pte = pte_get_entry_from_address( vma->vm_mm, readonly_addr);
	old_page = pte_page(*dest_pte);	//getting the page struct for the pte we just grabbed
	cv_stats_end(ksnap_vma_to_ksnap(vma), ksnap_vma_to_userdata(vma), 0, lock_latency_1);
	if (dest_pte && dest_pte->pte!=0 && old_page){
	  BUG_ON(PageBuddy(old_page));
	  BUG_ON(pte_page(*dest_pte)!=old_page);
	  //do this only if the old page is actually mapped into our address space
	  //remove from the rmap
	  page_remove_rmap(old_page);
	  put_page(old_page);
	}
	page = pfn_to_page(pfn);
	//is this page mapped into our address space?
	if (!page_count(page)){
	  printk("page was freed out from under us\n");
	  printk(KSNAP_LOG_LEVEL "%lu  %lu index: %lu, intended index %lu pfn %lu\n", 
		 page->snap_page_debug[10], page->snap_page_debug[11], page->index, index, pfn);
	  BUG();
	}



	//increment the ref count for this page
	get_page(page);	
	//add the page to the rmap
	//page_add_anon_rmap(page,vma,readonly_addr);
	page_add_anon_rmap(page, vma, readonly_addr);
	//create the new pte given a physical page (frame)
	tmp_ro_pte = mk_pte(page, vma->vm_page_prot);
	//clear the accessed bit
	pte_mkold(tmp_ro_pte);
	//flush the tlb for this page
	if (flush_tlb_entry){
	  __flush_tlb_one(readonly_addr);
	}
	//now set the new pte
	set_pte(dest_pte, tmp_ro_pte);
	//set_pte(pte, tmp_master_pte);
	pte_unmap(dest_pte);



	/*if (index % 80==0){
	  printk(KSNAP_LOG_LEVEL "UPDATE PID: %d index %lu page %p\n", current->pid, index, page);
	  }*/

	return 0;
}

