#include <linux/kernel.h>	
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/list.h>
#include <linux/swap.h>
#include <linux/poison.h>
#include <asm/pgtable.h>

#include "conversion.h"
#include "cv_pte.h"
#include "ksnap_writer.h"



int cv_prefetcher_should_prefetch(int page_index, struct ksnap_user_data * cv_user_data){
    struct cv_page_prefetch * pf = cv_prefetcher_get_entry_by_index(cv_user_data->cv_seg, page_index);
    //printk(KERN_EMERG "Should we prefetch %d : %d, %d\n", page_index, (pf->saturating_counter > CV_PREFETCHER_WEAK_AVOID), pf->saturating_counter );
    return (pf->saturating_counter > CV_PREFETCHER_WEAK_AVOID);
    //return 0;
}

int cv_prefetcher_get_page_index_to_prefetch(int page_index, struct ksnap_user_data * cv_user_data){
    struct cv_page_prefetch * pf = cv_prefetcher_get_entry_by_index(cv_user_data->cv_seg, page_index);
    return pf->page_index_to_fetch;
}

struct cv_page_prefetch * cv_prefetcher_get_entry_by_index(struct ksnap * cv_seg, int page_index){
    return &cv_per_page_version_get_ppv_entry(cv_seg->ppv, page_index)->prefetch_info;
}

//this function checks to see if the "page to fetch" actually got touched
int cv_prefetcher_update_page(int page_index, struct ksnap_user_data * cv_user_data){
    struct cv_page_prefetch * pf = cv_prefetcher_get_entry_by_index(cv_user_data->cv_seg, page_index);
    //if we didn't fetch a page, return immediately
    if (pf->saturating_counter > 1 || pf->page_index_to_fetch==CV_PREFETCHER_NO_PAGE){
        return;
    }
    else{
        //go get the entry from the dirty list
        struct snapshot_pte_list * entry = conv_dirty_search_lookup(cv_user_data, pf->page_index_to_fetch);
        if (!entry){
            printk(KERN_EMERG "Conversion Prefetcher: We should have prefetched but its not in the dirty list.");
            BUG();
         }
        else{
            //get the address
            unsigned long prefetch_addr = (pf->page_index_to_fetch << PAGE_SHIFT) + cv_user_data->vma->vm_start;
            //printk(KERN_EMERG "paddr: %lu\n", prefetch_addr);
            pte_t * prefetch_pte = pte_get_entry_from_address(cv_user_data->vma->vm_mm, prefetch_addr);
            int counter_update=0;
            if (!prefetch_pte || !pte_present(*prefetch_pte) ){
                printk(KERN_EMERG "Conversion Prefetcher: No pte entry for the prefetched page.");
                BUG();
            }
            else if (!pte_dirty(*prefetch_pte)){
                //success! The page is dirty, that means we guessed right
                 counter_update=1;
            }
            //now we update the saturating counter
            if (pf->saturating_counter != CV_PREFETCHER_STRONG_AVOID || pf->saturating_counter != CV_PREFETCHER_STRONG_GET){
                 pf->saturating_counter+=counter_update;
                 //printk(KERN_EMERG "new counter: %d", pf->saturating_counter);
            }
         }
    }
}

void cv_prefetcher_on_fault(int page_index, struct ksnap_user_data * cv_user_data){
    struct snapshot_pte_list * entry = NULL;
    struct snapshot_pte_list * dirty_pages_list = cv_user_data->dirty_pages_list;

    if (list_empty(&dirty_pages_list->list)){
        return;
    }
    else{
        //get the tail of the list (the last page added)
        entry = list_entry(dirty_pages_list->list.prev, struct snapshot_pte_list, list);
        if (entry && ((entry->page_index + 1)==page_index || (entry->page_index - 1)==page_index)){
            //are they next to each other? Then prefetch in the future
            struct cv_page_prefetch * pf = cv_prefetcher_get_entry_by_index(cv_user_data->cv_seg, entry->page_index);
            if (pf->page_index_to_fetch==page_index && pf->saturating_counter < CV_PREFETCHER_STRONG_GET ){
                //increase the saturating counter
                pf->saturating_counter++;
            }
            else if (pf->page_index_to_fetch!=page_index) {
                //new page to prefetch...reset the counter
                pf->saturating_counter=CV_PREFETCHER_STRONG_AVOID;
                pf->page_index_to_fetch=page_index;
                //printk(KERN_EMERG "updated index %d to prefetch %d, saturating counter %d\n", entry->page_index, page_index, pf->saturating_counter);
            }
        }
    }
}
