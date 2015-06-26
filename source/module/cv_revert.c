#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/tlbflush.h>
#include "cv_pte.h"
#include "conversion.h"
#include "ksnap_writer.h"

//revert the current working set
void conv_revert(struct vm_area_struct * vma){
    struct list_head * pos, * tmp_pos;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    struct snapshot_pte_list * entry;
    struct page * current_page, * restore_page;
    pte_t * dest_pte;
    pte_t new_pte;
    
    //walk through every entry
    list_for_each_safe(pos, tmp_pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);            
        //grab the current page
        current_page = pfn_to_page(entry->pfn);
        //if the entry has been checkpointed but nothing new has been created (we didn't CoW after the checkpoint)
        //then we can dip out right now
        if (conv_is_checkpointed_entry(entry) && conv_get_checkpoint_page(entry)==current_page){
            continue;
        }
        //get the pte for this address
        dest_pte = pte_get_entry_from_address(vma->vm_mm, entry->addr);
        BUG_ON(dest_pte==NULL);
        //remove from rmap
        page_remove_rmap(current_page);
        put_page(current_page);
        //if we don't have a ref page we need to do something different
        if (entry->ref_page || conv_is_checkpointed_entry(entry)){
            restore_page=(conv_is_checkpointed_entry(entry)) ? conv_get_checkpoint_page(entry) : entry->ref_page;
            //add the old page back
            page_add_anon_rmap(restore_page, vma, PAGE_ALIGN(entry->addr));
            //create the new pte based on the old page
            new_pte=mk_pte(restore_page, vma->vm_page_prot);
            //clear the accessed bit
            pte_mkold(new_pte);
            //now set the new pte
            set_pte(dest_pte, new_pte);
            entry->pfn=page_to_pfn(conv_get_checkpoint_page(entry));
        }
        else{
            //clear the pte
            *dest_pte=native_make_pte(0);
        }
        //only do this if it hasn't been checkpointed
        if (!conv_is_checkpointed_entry(entry)){
            conv_dirty_delete_lookup(cv_user, entry->page_index);
            //remove this entry
            list_del(pos);
            cv_meta_dec_dirty_page_count(vma);
        }
    }
    //flush it up!
    flush_tlb();
}
