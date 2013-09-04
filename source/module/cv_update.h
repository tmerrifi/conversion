#ifndef CV_UPDATE_H
#define CV_UPDATE_H

#include "conversion.h"

void cv_update_parallel(struct vm_area_struct * vma, unsigned long flags);

void cv_update_parallel_to_version_no_merge(struct vm_area_struct * vma, uint64_t version);

//atomic versions

void cv_update_atomic(struct vm_area_struct * vma, unsigned long flags);

void cv_update_atomic_to_version_no_merge(struct vm_area_struct * vma, uint64_t version);



#endif
