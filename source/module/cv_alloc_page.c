

#include "cv_alloc_page.h"

void cv_alloc_page_prep_for_list(struct page * pg){
    //we need to remove from the LRU...we are about to add it to our list, which abuses the LRU list_head field
    if (PageLRU(pg)) {
        unsigned long flags;
        struct zone *zone = page_zone(pg);
        spin_lock_irqsave(&zone->lru_lock, flags);
        BUG_ON(!PageLRU(pg));
        __ClearPageLRU(pg);
        //TODO: we should really call del_page_from_lru here...but we need to export a bunch of stuff to do it
        list_del(&pg->lru);
        ClearPageActive(pg);
        spin_unlock_irqrestore(&zone->lru_lock, flags);
    }
}

void __prep_new_page(struct page * pg){
    atomic_set(&pg->_count, 1);
    set_page_private(pg, 0);
}

int cv_alloc_page_list_size(struct cv_alloc_page * cap){
    return cap->size;
}

void cv_alloc_page_init(struct cv_alloc_page * cap){
    spin_lock_init(&cap->lock);
    INIT_LIST_HEAD(&cap->list);
    cap->size=0;
}

void cv_alloc_page_append_pages(struct cv_alloc_page * cap, struct list_head * list, int size){
    spin_lock(&cap->lock);
    list_splice(list, &cap->list);
    cap->size+=size;
    spin_unlock(&cap->lock);
}

struct page * cv_alloc_page_get(struct cv_alloc_page * cap){
    struct page * pg=NULL;
    spin_lock(&cap->lock);
    if (!list_empty(&cap->list)){
        pg=list_first_entry(&cap->list, struct page, lru);
        list_del(&pg->lru);
        __prep_new_page(pg);
        cap->size--;
    }
    spin_unlock(&cap->lock);
    return pg;
}

void cv_alloc_page_print_list(struct cv_alloc_page * cap, int thread_id){
    struct list_head * pos;
    struct page * pg;
    //printk(KERN_EMERG "  Printing list for thread %d\n", thread_id);
    spin_lock(&cap->lock);
    int counter=0;
    list_for_each(pos, &cap->list){
        pg=list_entry(pos, struct page, lru);
        //printk(KERN_EMERG "   page index: %d\n", pg->index);
        ++counter;
    }
    spin_unlock(&cap->lock);
}

int cv_alloc_page_list_free_space(struct cv_alloc_page * cap){
    return (cap->size < CV_ALLOC_PAGE_LIST_MAX) ? CV_ALLOC_PAGE_LIST_MAX-cap->size : 0;
}
