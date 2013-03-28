
#ifndef CV_COMMIT_H
#define CV_COMMIT_H

#include "ksnap.h"


void cv_commit_page(struct snapshot_pte_list * version_list_entry, struct vm_area_struct * vma, uint64_t our_revision, int stats);

void cv_commit_version_parallel(struct vm_area_struct * vma, unsigned long flags);

#endif
