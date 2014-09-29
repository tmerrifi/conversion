
#include <asm/atomic.h>
#include "conversion.h"

#ifndef CV_MEMORY_ACCOUNTING_H
#define CV_MEMORY_ACCOUNTING_H

#ifdef CV_MEM_ACCOUNTING_ON

static inline void cv_memory_accounting_inc_pages(struct ksnap * cv_seg){
    int max = 0;
    int result = atomic_add_return(1, &cv_seg->pages_allocated);
 update:
    max = atomic_read(&cv_seg->max_pages);
    if (result > max){
        if (atomic_cmpxchg(&cv_seg->max_pages, max, result) != max)
            goto update;
    }
}

static inline void cv_memory_accounting_dec_pages(struct ksnap * cv_seg){
    atomic_dec(&cv_seg->pages_allocated);
}

static inline void cv_memory_accounting_print(struct ksnap * cv_seg){
    printk(KSNAP_LOG_LEVEL "max pages: %d bytes %llu\n", atomic_read(&cv_seg->max_pages), ((uint64_t)atomic_read(&cv_seg->max_pages)) * 4096ULL);
}

#else

#define cv_memory_accounting_inc_pages(cv_seg)

#define cv_memory_accounting_dec_pages(cv_seg)

#define cv_memory_accounting_print(cv_seg)

#endif

#endif
