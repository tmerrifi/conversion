#include "conversion.h"

struct cv_determinism_seg{
    uint32_t * token_addr;
};

#ifndef CV_DETERMINISM_TICK_BUFFER_FLUSH_SIZE
#define CV_DETERMINISM_TICK_BUFFER_FLUSH_SIZE 5000
#endif

#define CV_DETERMINISM_TICKS_COMMIT 100
#define CV_DETERMINISM_TICKS_SKIP 10
#define CV_DETERMINISM_TICKS_UPDATE 50
#define CV_DETERMINISM_TICKS_MERGE 400
#define CV_DETERMINISM_TICKS_COW 1000


void cv_determinism_init(struct ksnap *);

void cv_determinism_on_commit_entry(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_commit_type_t type );

void cv_determinism_on_update_entry(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page, cv_hooks_update_type_t type );

void cv_determinism_on_cow(struct ksnap * cv, struct ksnap_user_data * cv_user, unsigned int logical_page);
