#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/tlbflush.h>
#include "cv_pte.h"
#include "conversion.h"
#include "ksnap_writer.h"

int __revert_page(struct cv_page_entry * page_entry, struct snapshot_pte_list * entry, int page_index,
                  struct list_head * pos, struct ksnap_user_data * cv_user, struct vm_area_struct * vma){
    pte_t * dest_pte;
    pte_t new_pte;
    struct page * current_page, * restore_page;
    
    //grab the current page
    current_page = pfn_to_page(page_entry->pfn);
    //if the entry has been checkpointed but nothing new has been created (we didn't CoW after the checkpoint)
    //then we can dip out right now
    BUG_ON(current_page==NULL);
    if (conv_is_checkpointed_entry(page_entry) && conv_get_checkpoint_page(page_entry)==current_page){
        return 0;
    }
    else{
        //get the pte for this address
        dest_pte = pte_get_entry_from_address(vma->vm_mm,page_entry->addr);
        BUG_ON(dest_pte==NULL);
        //remove from rmap
        page_remove_rmap(current_page);
        put_page(current_page);
        //if we don't have a ref page we need to do something different
        if (page_entry->ref_page || conv_is_checkpointed_entry(page_entry)){
            restore_page=(conv_is_checkpointed_entry(page_entry)) ? conv_get_checkpoint_page(page_entry) : page_entry->ref_page;
            //add the old page back
            page_add_file_rmap(restore_page);
            //create the new pte based on the old page
            new_pte=mk_pte(restore_page, vma->vm_page_prot);
            //now set the new pte
            set_pte(dest_pte, new_pte);
            page_entry->pfn=page_to_pfn(restore_page);
            if (conv_is_checkpointed_entry(page_entry)){
                entry->checkpoint=1;
            }
            page_entry->pfn=page_to_pfn(restore_page);        
        }
        else{
            //clear the pte
            *dest_pte=native_make_pte(0);
        }
        //only do this if it hasn't been checkpointed
        if (!conv_is_checkpointed_entry(page_entry)){
            conv_dirty_delete_lookup(cv_user, page_index);
            //remove this entry
            list_del(pos);
            cv_meta_dec_dirty_page_count(vma);
        }
        return 1;
    }
}

void __revert_logging(struct cv_logging_entry * logging_entry,
                      struct snapshot_pte_list * entry,
                      struct ksnap_user_data * cv_user){
    
    struct cv_logging_page_status_entry * logging_entry_status;
    
    if (!conv_is_checkpointed_logging_entry(logging_entry) || cv_logging_is_dirty(entry)){
        logging_entry_status = cv_logging_page_status_lookup(cv_user, entry->page_index);
        if (conv_is_checkpointed_logging_entry(logging_entry)){
            //roll back to the checkpoint
            memcpy(cv_logging_page_status_to_kaddr(logging_entry_status, logging_entry->line_index),
                   logging_entry->local_checkpoint_data,
                   logging_entry->data_len);
        }
        else{
            //roll back to the old stuff
            memcpy(cv_logging_page_status_to_kaddr(logging_entry_status, logging_entry->line_index),
                   logging_entry->data,
                   logging_entry->data_len);
        }
    }
}

//revert the current working set
void conv_revert(struct vm_area_struct * vma){
    struct list_head * pos, * tmp_pos;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    struct snapshot_pte_list * entry;
    int revert_counter=0;

    //walk through every entry
    list_for_each_safe(pos, tmp_pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);
        if (entry->type == CV_DIRTY_LIST_ENTRY_TYPE_PAGING &&
            __revert_page(cv_list_entry_get_page_entry(entry),
                          entry,
                          entry->page_index,
                          pos,
                          cv_user,vma)){
            revert_counter++;
        }
        else if (entry->type==CV_DIRTY_LIST_ENTRY_TYPE_LOGGING){
            __revert_logging(cv_list_entry_get_logging_entry(entry),
                             entry,
                             cv_user);
        }
    }
    
    if (revert_counter>0){
        //flush it up!
        flush_tlb();
    }
    cv_user->partial_version_num=0;
    cv_meta_set_partial_version_num(vma, 0);

}
