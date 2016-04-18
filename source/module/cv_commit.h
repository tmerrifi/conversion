
#ifndef CV_COMMIT_H
#define CV_COMMIT_H

#include "conversion.h"


void cv_commit_page(struct cv_page_entry * version_list_entry, struct vm_area_struct * vma,
                    uint64_t our_revision, unsigned long page_index, int checkpointed);


void cv_commit_version_parallel(struct vm_area_struct * vma, int defer_work);

void cv_commit_version_atomic(struct vm_area_struct * vma, unsigned long flags);

#endif
