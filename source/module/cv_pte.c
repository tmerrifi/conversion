
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/pagemap.h>
#include <linux/rmap.h>
#include <linux/time.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>

#include "conversion.h"
#include "cv_debugging.h"
#include "cv_defer_work.h"

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
int __pte_copy_entry (pte_t * pte, unsigned long pfn, unsigned long index, 
                      struct vm_area_struct * vma, int flush_tlb_entry, struct ksnap_user_data * cv_user){
	struct page * page, * old_page;	
	unsigned long readonly_addr;
	pte_t * dest_pte;
	pte_t tmp_ro_pte;
	cv_stats_function_init();

	cv_stats_start(ksnap_vma_to_ksnap(vma), 0, lock_latency_1);

	readonly_addr = (index << PAGE_SHIFT) + vma->vm_start;	//get the new address
	dest_pte = pte_get_entry_from_address( vma->vm_mm, readonly_addr);
	old_page = pte_page(*dest_pte);	//getting the page struct for the pte we just grabbed


	if (dest_pte && dest_pte->pte!=0 && old_page){
	  BUG_ON(PageBuddy(old_page));
	  BUG_ON(pte_page(*dest_pte)!=old_page);
	  //do this only if the old page is actually mapped into our address space
	  //remove from the rmap
          //printk(KERN_EMERG "UPDATE: dump old page: %p\n", old_page);
	  page_remove_rmap(old_page);
          cv_page_debugging_inc_flag(old_page, CV_PAGE_DEBUG_UPDATE_OLDPAGE_PUT);
	  put_page(old_page);
	}
	page = pfn_to_page(pfn);

	//is this page mapped into our address space?
	if (!page_count(page)){
	  printk("page was freed out from under us\n");
	  printk(KERN_INFO "%lu  %lu index: %lu, intended index %lu pfn %lu\n", 
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

	cv_stats_end(ksnap_vma_to_ksnap(vma), ksnap_vma_to_userdata(vma), 0, lock_latency_1);

	return 0;
}

int  __pte_copy_entry_defer (pte_t * pte, unsigned long pfn, unsigned long index, 
                              struct vm_area_struct * vma, struct ksnap_user_data * cv_user){

    //unsigned long addr = (index << PAGE_SHIFT) + vma->vm_start;	//get the new address
    struct page * page = pfn_to_page(pfn);
    //is this page alive and well?
    /*if (!page_count(page)){
        printk("page was freed out from under us\n");
        printk(KERN_INFO "%lu  %lu index: %lu, intended index %lu pfn %lu\n", 
               page->snap_page_debug[10], page->snap_page_debug[11], page->index, index, pfn);
        BUG();
        }*/
    //increment the ref count for this page so it stays alive
    get_page(page);    
    //*************ADD THE DEFERRED WORK ENTRY***************************************
    struct cv_defer_work_entry * entry = cv_defer_work_entry_create(&cv_user->defer_work, CV_DEFER_ENTRY_PTE_UPDATE);
    //entry->addr=addr;
    entry->index=index;
    entry->new_page=page;
    entry->vma=vma;
    entry->pfn=pfn;
    cv_defer_work_push(&cv_user->defer_work, entry);
    //printk(KERN_EMERG "Thread %d PUSEHD: new_page %p, index %d, old_page %p, head %p\n", 
    //current->pid, entry->new_page, entry->index, entry->old_page, &(cv_user->defer_work.entry_list));
    //********************************************************************************
    
    return 0;    
 }




int pte_copy_entry (pte_t * pte, unsigned long pfn, unsigned long index, 
                          struct vm_area_struct * vma, int flush_tlb_entry, int defer_work, struct ksnap_user_data * cv_user){

    if (defer_work){
        return __pte_copy_entry_defer(pte, pfn, index, vma, cv_user);
    }
    else{
        return __pte_copy_entry(pte, pfn, index, vma, flush_tlb_entry, cv_user);
    }
}


void do_deferred_pte_entry_update(struct cv_defer_work_entry * entry){

    	struct page * page, * old_page;	
	unsigned long readonly_addr;
	pte_t * dest_pte;
	pte_t tmp_ro_pte;

        struct vm_area_struct * vma=entry->vma;

        entry->addr = (entry->index << PAGE_SHIFT) + vma->vm_start;	//get the new address        
	readonly_addr = entry->addr;	//get the new address
	dest_pte = pte_get_entry_from_address( vma->vm_mm, readonly_addr);
	old_page = pte_page(*dest_pte);	//getting the page struct for the pte we just grabbed

	if (dest_pte && dest_pte->pte!=0 && old_page){
	  BUG_ON(PageBuddy(old_page));
	  BUG_ON(pte_page(*dest_pte)!=old_page);
	  //do this only if the old page is actually mapped into our address space
	  //remove from the rmap
	  page_remove_rmap(old_page);
          cv_page_debugging_inc_flag(old_page, CV_PAGE_DEBUG_UPDATE_OLDPAGE_PUT);
	  put_page(old_page);
	}
	page = pfn_to_page(entry->pfn);

	//is this page mapped into our address space?
	if (!page_count(page)){
	  printk("page was freed out from under us\n");
	  printk(KERN_INFO "%lu  %lu index: %lu, intended index %lu pfn %lu\n", 
		 page->snap_page_debug[10], page->snap_page_debug[11], page->index, entry->index, entry->pfn);
	  BUG();
	}
	//add the page to the rmap
	page_add_anon_rmap(page, vma, readonly_addr);
	//create the new pte given a physical page (frame)
	tmp_ro_pte = mk_pte(page, vma->vm_page_prot);
	//clear the accessed bit
	pte_mkold(tmp_ro_pte);
	//flush the tlb for this page
        //__flush_tlb_one(readonly_addr);
	//now set the new pte
	set_pte(dest_pte, tmp_ro_pte);
	//set_pte(pte, tmp_master_pte);
	pte_unmap(dest_pte);
	return 0;
}

void do_deferred_work(struct vm_area_struct * vma){
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    while(!list_empty(&(cv_user->defer_work.entry_list))){
        struct cv_defer_work_entry * entry = cv_defer_work_pop(&cv_user->defer_work);
        if (entry->entry_type==CV_DEFER_ENTRY_PTE_UPDATE){
            //printk(KERN_EMERG "Thread %d POPPED: entry %p, new_page %p, index %d, old_page %p\n", 
            //current->pid, entry, entry->new_page, entry->index, entry->old_page);
            do_deferred_pte_entry_update(entry);
        }
        cv_defer_work_entry_free(&cv_user->defer_work, entry);
    }
    flush_tlb();
}
