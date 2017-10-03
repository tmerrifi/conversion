
#ifndef CV_GARBAGE_H
#define CV_GARBAGE_H

#include "conversion.h"

struct cv_garbage_work{
  struct work_struct work;
  struct ksnap * cv_seg;
};

#define CV_GARBAGE_MAX_THREADS 1
//when should we start caring about garbage?
#define CV_GARBAGE_INIT_PAGES ((512) * 50)
//every CV_GARBAGE_START_INC we start a collection
#define CV_GARBAGE_START_INC ((512) * 100)

void cv_garbage_final(struct ksnap * cv_seg);
void cv_garbage_collection(struct work_struct * work);

void cv_gc_logging_page_status_entries(struct ksnap_user_data * cv_user);

#endif
