#include "conversion.h"

struct cv_determinism_seg{
    uint32_t * token_addr;
};

void cv_determinism_init(struct vm_area_struct * vma, unsigned long token_addr);

void cv_determinism_on_commit_begin(struct ksnap * cv_seg, unsigned long flags);

void cv_determinism_on_update_begin(struct ksnap * cv_seg, unsigned long flags);
