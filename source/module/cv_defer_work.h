#ifndef CV_DEFER_WORK_H
#define CV_DEFER_WORK_H

typedef enum {CV_DEFER_ENTRY_PTE_UPDATE} cv_defer_work_type;

struct cv_defer_work_entry{
    //the work to be done
    struct list_head list;
    cv_defer_work_type entry_type;
    size_t addr;
    unsigned long index;
    struct page * new_page;
    struct page * old_page;
    struct vm_area_struct * vma;
    unsigned long pfn;
};

struct cv_defer_work{
    struct list_head entry_list;
    struct kmem_cache * entry_mem_cache;
};

static inline void cv_defer_work_init(struct cv_defer_work * cdw){
    INIT_LIST_HEAD(&cdw->entry_list);
    //deferred work entry allocation should be fast
    cdw->entry_mem_cache=KMEM_CACHE(cv_defer_work_entry,0);
}

static inline struct cv_defer_work_entry * cv_defer_work_entry_create(struct cv_defer_work *cdw, cv_defer_work_type type){
    struct cv_defer_work_entry * entry = kmem_cache_alloc(cdw->entry_mem_cache, GFP_KERNEL);
    entry->entry_type=type;
    INIT_LIST_HEAD(&entry->list);
    return entry;
}

static inline void cv_defer_work_push(struct cv_defer_work * cdw, struct cv_defer_work_entry * entry){
    list_add(&entry->list, &cdw->entry_list);
}

static inline struct cv_defer_work_entry * cv_defer_work_pop(struct cv_defer_work * cdw){
    struct cv_defer_work_entry * entry = list_first_entry(&cdw->entry_list, struct cv_defer_work_entry, list);
    list_del(&entry->list);
    return entry;
}

static inline void cv_defer_work_entry_free(struct cv_defer_work * cdw,struct cv_defer_work_entry * entry){
    kmem_cache_free(cdw->entry_mem_cache, entry);

}


#endif
