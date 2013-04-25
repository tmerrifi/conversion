#ifndef CV_UPDATE_H
#define CV_UPDATE_H

#include "ksnap.h"

void cv_update_parallel(struct vm_area_struct * vma, unsigned long flags);

void cv_update_parallel_to_version_no_merge(struct vm_area_struct * vma, uint64_t version);

#endif
