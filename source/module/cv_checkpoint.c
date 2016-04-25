#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/tlbflush.h>
#include "cv_pte.h"
#include "conversion.h"

int __checkpoint_page(struct cv_page_entry * page_entry, struct snapshot_pte_list * entry, struct vm_area_struct * vma){
    struct page * current_page, * old_checkpoint_page;
    pte_t page_table_e;
    pte_t * dest_pte;
    
    //grab the current page
    current_page = pfn_to_page(page_entry->pfn);
    if (conv_is_checkpointed_entry(page_entry) &&
        current_page==conv_get_checkpoint_page(page_entry)){
        return 0;
    }
    else{
        //was there an old checkpointed page? If so, get rid of it
        if ((old_checkpoint_page=conv_get_checkpoint_page(page_entry))!=NULL){
            //need to dump the page
            put_page(old_checkpoint_page);
        }            
        //get the pte for this address
        dest_pte = pte_get_entry_from_address(vma->vm_mm, page_entry->addr);
        page_table_e = ptep_get_and_clear(vma->vm_mm, page_entry->addr, dest_pte);
        //we need to write protect the owner's pte again
        page_table_e = pte_wrprotect(page_table_e);	
        //set it back
        set_pte(dest_pte, page_table_e);
        //set page_entry to be a checkpointed page_entry
        conv_set_checkpoint_page(page_entry, current_page);
        entry->checkpoint=1;
        return 1;
    }
}


void conv_checkpoint(struct vm_area_struct * vma){
    struct list_head * pos;
    struct snapshot_pte_list * entry;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    int checkpointed_counter=0;

    //walk through every entry
    list_for_each(pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);
        if (entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING &&
            __checkpoint_page(cv_list_entry_get_page_entry(entry),entry,vma)){
            checkpointed_counter++;
        }
        else if (entry->type==CV_DIRTY_LIST_ENTRY_TYPE_LOGGING){
            BUG();
        }
    }
    if (checkpointed_counter>0){
        flush_tlb();
    }
}
