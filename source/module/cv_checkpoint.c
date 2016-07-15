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

int __checkpoint_logging(struct cv_logging_entry * logging_entry, struct snapshot_pte_list * entry,
                         struct ksnap_user_data * cv_user,
                         struct vm_area_struct * vma){

    struct cv_logging_page_status_entry * logging_entry_status;
    struct ksnap * cv_seg = ksnap_vma_to_ksnap(vma);
    pte_t page_table_e;
    
    if (cv_logging_is_dirty(logging_entry)){
        //printk(KERN_EMERG "check logging index: %d, pid: %d, entry: %p", entry->page_index, current->pid, entry);
        //just write over the old data
        if (!logging_entry->local_checkpoint_data){
            logging_entry->local_checkpoint_data=cv_logging_allocate_data_entry(logging_entry->data_len, cv_seg);
            conv_debug_memory_alloc(logging_entry->local_checkpoint_data);
        }
        memcpy(logging_entry->local_checkpoint_data, (uint8_t *)logging_entry->addr, logging_entry->data_len);
        cv_logging_clear_dirty(logging_entry);
        //if its a page level logging entry, we need to enable write protection again
        if (cv_logging_is_full_page(logging_entry)){
            logging_entry_status = cv_logging_page_status_lookup(cv_user, entry->page_index);
            page_table_e = ptep_get_and_clear(vma->vm_mm, (uint8_t *)logging_entry->addr, logging_entry_status->pte);
            //make write-protected
            set_pte(logging_entry_status->pte, pte_wrprotect(page_table_e));
            __flush_tlb_one(logging_entry->addr);
        }
        //printk(KERN_EMERG "is checkpointed??? %d\n", conv_is_checkpointed_logging_entry(logging_entry));
        return 1;
    }
    else{
        //printk(KERN_EMERG "check logging NOT DIRTY index: %d, pid: %d", entry->page_index, current->pid);
        return 0;
    }
}

void conv_checkpoint(struct vm_area_struct * vma){
    struct list_head * pos;
    struct snapshot_pte_list * entry;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    int checkpointed_counter=0;

    //printk(KERN_EMERG "checkpointing...%d\n", current->pid);
    //walk through every entry
    list_for_each(pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);
        if (entry->type==CV_DIRTY_LIST_ENTRY_TYPE_PAGING &&
            __checkpoint_page(cv_list_entry_get_page_entry(entry),
                              entry,
                              vma)){
            checkpointed_counter++;
        }
        else if (entry->type==CV_DIRTY_LIST_ENTRY_TYPE_LOGGING){
            __checkpoint_logging(cv_list_entry_get_logging_entry(entry),
                                 entry,
                                 cv_user,
                                 vma);
        }
    }
    //printk(KERN_EMERG "done checkpointing...%d\n", current->pid);
    if (checkpointed_counter>0){
        flush_tlb();
    }
}
