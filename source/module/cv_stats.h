
#ifndef KSNAP_STATS_H
#define KSNAP_STATS_H

#define CV_MAX_PER_PROCESS_STATS 100

struct cv_statistics{
  atomic_t total_ksnap_pages_allocated;
  atomic_t total_owner_commits;
  atomic_t total_reader_get_snapshots;
  atomic_t total_ksnap_page_faults;
  atomic_t total_merged_pages;
};

struct cv_per_process_detailed_statistics{
  long long commit_wait_lock;
  long long update_wait_lock;
  long commit_wait_lock_count;
  long update_wait_lock_count;
  long long update_latency;
  long update_latency_count;
  long long commit_latency;
  long commit_latency_count;
  long commit_pages;
  long commit_pages_count;
  long update_pages;
  long update_pages_count;
  long lock_latency_1;
  long lock_latency_1_count;
  long lock_latency_2;
  long lock_latency_2_count;
  long commit_inter_latency;
  long commit_inter_latency_count;
  long commit_acq_latency;
  long commit_acq_latency_count;
  long version_diff;
  long version_diff_count;
  long commit_waitlist_latency;
  long commit_waitlist_latency_count;
};

void __conv_time_and_print_end(struct timespec *);

#define conv_time_and_print_section()\
    struct timespec ts_start##__FILE__##__LINE__;                       \
    int loop_var_time_and_print___##__LINE__;                           \
    getrawmonotonic(&ts_start##__FILE__##__LINE__);                     \
    for (loop_var_time_and_print___##__LINE__ = 0;                      \
         loop_var_time_and_print___##__LINE__ < 1;                      \
         loop_var_time_and_print___##__LINE__++, __conv_time_and_print_end(&ts_start##__FILE__##__LINE__) )
    

#ifdef CV_STATS_ON

#define cv_stats_function_init() \
  struct timespec ts[20];

#define cv_stats_add_counter(conversion, userdata, count, property)	      \
  conversion->cv_per_process_stats[userdata->id].property##_count+=1; \
  conversion->cv_per_process_stats[userdata->id].property+=count; 

#define cv_stats_start(conversion, num, property) \
  getrawmonotonic(&ts[num*2]);

#define __cv_stats_simple_counter_avg(property, stats, thread_count) \
  long total##property=0; \
  long total##property##count=0; \
  int property##loopvar=0; \
  for (;property##loopvar < thread_count; ++property##loopvar){ \
  total##property+=stats[property##loopvar].property; \
  total##property##count+=stats[property##loopvar].property##_count; \
  }

#define __cv_stats_simple_counter_mean(property)	\
  ((total##property##count > 0) ? ((total##property*1000)/total##property##count) : 0)

#define cv_stats_end(conversion, userdata, num, property)	\
  getrawmonotonic(&ts[num*2+1]); \
  conversion->cv_per_process_stats[userdata->id].property+=cv_stats_elapsed_time_ns(&ts[num*2],&ts[num*2+1]); \
  conversion->cv_per_process_stats[userdata->id].property##_count+=1;
  //printk(KERN_INFO "ns %llu count....%d\n", conversion->cv_per_process_stats[userdata->id].property, conversion->cv_per_process_stats[userdata->id].property##_count);

#define __cv_stats_add_avg(property, stats, thread_count) \
  long long total##property=0; \
  long total##property##count=0; \
  int property##loopvar=0; \
  for (;property##loopvar < thread_count; ++property##loopvar){ \
  total##property+=stats[property##loopvar].property; \
  total##property##count+=stats[property##loopvar].property##_count; \
  }

#define __cv_stats_print_avg(property) \
  ((total##property##count) ? total##property/total##property##count : 0)



#else


#define cv_stats_function_init()

#define cv_stats_add_counter(conversion, userdata, count, property)

#define cv_stats_start(conversion, num, property) 

#define __cv_stats_simple_counter_avg(property, stats, thread_count)

#define __cv_stats_simple_counter_mean(property)     

#define cv_stats_end(conversion, userdata, num, property) 

#define __cv_stats_add_avg(property, stats, thread_count) 

#define __cv_stats_print_avg(property)


#endif

void cv_stats_init(struct cv_statistics * stats);

void cv_stats_print_all(struct cv_statistics * cv_stats, struct cv_per_process_detailed_statistics * cv_per_proc, int total_threads);

void cv_stats_inc_pages_allocated(struct cv_statistics * stats);

void cv_stats_dec_pages_allocated(struct cv_statistics * stats);

void cv_stats_inc_total_owner_commits(struct cv_statistics * stats);

void cv_stats_dec_total_owner_commits(struct cv_statistics * stats);

void cv_stats_inc_reader_get_snapshots(struct cv_statistics * stats);

void cv_stats_dec_reader_get_snapshots(struct cv_statistics * stats);

void cv_stats_inc_ksnap_page_faults(struct cv_statistics * stats);

void cv_stats_inc_merged_pages(struct cv_statistics * stats);

void cv_stats_dec_ksnap_page_faults(struct cv_statistics * stats);

unsigned long cv_stats_elapsed_time_ns(struct timespec * old_ts, struct timespec * current_ts);


#endif
