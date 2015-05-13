#include <linux/mm.h>
#include <linux/rmap.h>
#include <asm/tlbflush.h>
#include "cv_pte.h"
#include "conversion.h"

//revert the current working set
void conv_revert(struct vm_area_struct * vma){
    struct list_head * pos, * tmp_pos;
    struct ksnap_user_data * cv_user=ksnap_vma_to_userdata(vma);
    struct snapshot_pte_list * entry;
    struct page * current_page;
    pte_t * dest_pte;
    pte_t new_pte;
    
    //walk through every entry
    list_for_each_safe(pos, tmp_pos, &cv_user->dirty_pages_list->list){
        entry = list_entry(pos, struct snapshot_pte_list, list);
        //grab the current page
        current_page = pfn_to_page(entry->pfn);
        //printk(KERN_EMERG "rolling back %d %p\n", entry->page_index, current_page);
        //get the pte for this address
        dest_pte = pte_get_entry_from_address(vma->vm_mm, entry->addr);
        BUG_ON(dest_pte==NULL);
        //remove from rmap
        page_remove_rmap(current_page);
        put_page(current_page);
        //if we don't have a ref page we need to do something different
        if (entry->ref_page){
            //printk(KERN_EMERG "has ref page %p", entry->ref_page);
            //add the old page back
            page_add_anon_rmap(entry->ref_page, vma, PAGE_ALIGN(entry->addr));
            //create the new pte based on the old page
            new_pte=mk_pte(entry->ref_page, vma->vm_page_prot);
            //clear the accessed bit
            pte_mkold(new_pte);
            //now set the new pte
            set_pte(dest_pte, new_pte);
        }
        else{
            //printk(KERN_EMERG "no ref page");
            //clear the pte
            *dest_pte=native_make_pte(0);
        }
        //remove this entry
        list_del(pos);
    }
    cv_meta_set_dirty_page_count(vma, 0);
    //flush it up!
    flush_tlb();
    //printk(KERN_EMERG "done with conv_revert");
}
