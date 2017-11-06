


#ifndef KSNAP_MERGE_H
#define KSNAP_MERGE_H

#include <linux/kernel.h>
#include <linux/mm.h>

extern uint8_t * cv_merge_empty_page;

void ksnap_merge_init(void);

void cv_merge_free(void);

int ksnap_merge(struct page * latest_page, uint8_t * local, struct page * ref_page, struct page * local_page);

int cv_three_way_merge(uint8_t * local, uint8_t * ref, uint8_t * latest, int words_to_merge);

uint8_t * compute_local_addr_for_diff(struct vm_area_struct * vma, unsigned long pfn, unsigned long page_index, int checkpointed);

#endif
