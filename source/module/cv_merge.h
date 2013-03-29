


#ifndef KSNAP_MERGE_H
#define KSNAP_MERGE_H

#include <linux/kernel.h>
#include <linux/mm.h>

extern unsigned int * cv_merge_empty_page;

void ksnap_merge_init(void);

void cv_merge_free(void);

void ksnap_merge(struct page * latest_page, unsigned int * local, struct page * ref_page, struct page * local_page);

#endif
