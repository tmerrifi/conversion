
#ifndef CV_GARBAGE_H
#define CV_GARBAGE_H

#include "conversion.h"

struct cv_garbage_work{
  struct work_struct work;
  struct ksnap * cv_seg;
};

#define CV_GARBAGE_MAX_THREADS 2

#define CV_GARBAGE_START_INC 10000

void cv_garbage_final(struct ksnap * cv_seg);
void cv_garbage_collection(struct work_struct * work);

#endif
