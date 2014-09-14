
#ifndef CV_ALLOC_PAGE
#define CV_ALLOC_PAGE

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/string.h>
#include <linux/rmap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/list.h>

struct cv_alloc_page{
    struct list_head list;
    int size;
    spinlock_t lock;
};

#define CV_ALLOC_PAGE_LIST_MAX 4096

void cv_alloc_page_prep_for_list(struct page * pg);

void cv_alloc_page_init(struct cv_alloc_page * cap);

void cv_alloc_page_append_pages(struct cv_alloc_page * cap, struct list_head * list, int size);

struct page * cv_alloc_page_get(struct cv_alloc_page * cap);

int cv_alloc_page_list_size(struct cv_alloc_page * cap);

int cv_alloc_page_list_free_space(struct cv_alloc_page * cap);

void cv_alloc_page_print_list(struct cv_alloc_page * cap, int thread_id);

#endif
