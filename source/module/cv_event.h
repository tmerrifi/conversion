
#ifndef CV_EVENT_H
#define CV_EVENT_H

#include "conversion.h"

typedef enum {CV_EVENT_NORMAL_PAGE_COMMIT=1, CV_EVENT_WAITLIST_PAGE_COMMIT=10, 
              CV_EVENT_WAITLIST_SPIN=20, CV_EVENT_OP_COMMIT_PAGE=2, 
              CV_EVENT_OP_UPDATE_VERSION=3, CV_EVENT_OP_DIRTY_DELETE_OP=4,
              CV_EVENT_OP_PTE_STUFF=5, CV_EVENT_OP_LIST_LOOKUP=6, CV_EVENT_OP_LIST_DELETE=7,
              CV_EVENT_OP_MERGE=100} cv_event_type;

#define CV_EVENT_PER_USER_MAX_EVENTS 500

struct cv_event{
    uint64_t start_time_us;
    uint64_t end_time_us;
    int committed_thus_far;
    int page;
    cv_event_type type;
};

struct cv_event_info{
    uint64_t count;
    struct timespec start;
    struct cv_event events[CV_EVENT_PER_USER_MAX_EVENTS];
};

static inline uint64_t __elapsed_time_ns(struct timespec * start, struct timespec * end){
  return (end->tv_sec-start->tv_sec)*1000000000ULL+(end->tv_nsec-start->tv_nsec);
}


static inline void cv_event_init(struct cv_event_info * cve, struct timespec * start_time){
#ifdef CV_EVENT_ON
    //set the number of events to 0
    cve->count=0;
    //use the creation time of the segment to synchronize time across threads
    memcpy(&cve->start, start_time, sizeof(struct timespec));
#endif
}

static inline void cv_event_start_event(struct cv_event_info * cve, cv_event_type type, int page, int committed_thus_far){
#ifdef CV_EVENT_ON
    struct timespec current_time;
    if (cve->count < CV_EVENT_PER_USER_MAX_EVENTS){
        getnstimeofday(&current_time);
        cve->events[cve->count].start_time_us=
            (__elapsed_time_ns(&cve->start,&current_time));
        cve->events[cve->count].type=type;
        cve->events[cve->count].page=page;
        cve->events[cve->count].committed_thus_far=committed_thus_far;
    }
#endif
}

static inline void cv_event_end_event(struct cv_event_info * cve, cv_event_type type){
#ifdef CV_EVENT_ON
    struct timespec current_time;
    if (cve->count < CV_EVENT_PER_USER_MAX_EVENTS){
        getnstimeofday(&current_time);
        cve->events[cve->count].end_time_us=
            (__elapsed_time_ns(&cve->start,&current_time));
        cve->count++;
    }
#endif
}

static inline void cv_event_print(struct cv_event_info * cve, int id){
#ifdef CV_EVENT_ON
    int i=0;
    for(;i<cve->count;++i){
        printk(KERN_INFO "EVENT: %d %llu %llu %d %d %d\n", 
               id, cve->events[i].start_time_us, 
               cve->events[i].end_time_us, cve->events[i].type,
               cve->events[i].page, cve->events[i].committed_thus_far);
    }
#endif
}

#endif
