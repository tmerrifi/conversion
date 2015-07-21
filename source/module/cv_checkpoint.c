#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/tlbflush.h>
#include "cv_pte.h"
#include "conversion.h"


//revert the current working set
void conv_checkpoint(struct vm_area_struct * vma){
    struct list_head * pos;
    struct snapshot_pte_list * entry;
    pte_t page_table_e;
    pte_t * dest_pte;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    struct page * current_page, * old_checkpoint_page;
    int checkpointed_counter=0;

    //printk(KERN_EMERG "CHECKPOINTING!!! %d\n", current->pid);
    
    //walk through every entry
    list_for_each(pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);
        //grab the current page
        current_page = pfn_to_page(entry->pfn);
        if (conv_is_checkpointed_entry(entry) &&
            current_page==conv_get_checkpoint_page(entry)){
        }
        else{
            checkpointed_counter++;
            //was there an old checkpointed page? If so, get rid of it
            if ((old_checkpoint_page=conv_get_checkpoint_page(entry))!=NULL){
                printk(KERN_EMERG "we get here!!!! \n", old_checkpoint_page);
                //need to dump the page
                put_page(old_checkpoint_page);
                //TODO: RMAP???????
            }            
            //get the pte for this address
            dest_pte = pte_get_entry_from_address(vma->vm_mm, entry->addr);
            page_table_e = ptep_get_and_clear(vma->vm_mm, entry->addr, dest_pte);
            //we need to write protect the owner's pte again
            page_table_e = pte_wrprotect(page_table_e);	
            //set it back
            set_pte(dest_pte, page_table_e);
            //set entry to be a checkpointed entry
            conv_set_checkpoint_page(entry, current_page);
            /*if (current_page->index==0){
                printk(KERN_EMERG "....checkpointed page %p pid %d entry %llu addr %p\n", current_page, current->pid, page_table_e, entry->addr);
                }*/
            entry->checkpoint=1;
        }
    }
    if (checkpointed_counter>0){
        flush_tlb();
    }
    //printk(KERN_EMERG "DONE CHECKPOINTING!!! %d\n", current->pid);
}
