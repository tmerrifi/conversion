
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/time.h>
#include <asm/atomic.h>

#include "conversion.h"
#include "cv_stats.h"

void cv_stats_init(struct cv_statistics * stats){
  atomic_set(&stats->total_ksnap_pages_allocated, 0);
  atomic_set(&stats->total_owner_commits, 0);
  atomic_set(&stats->total_reader_get_snapshots, 0);
  atomic_set(&stats->total_ksnap_page_faults, 0);
  atomic_set(&stats->total_merged_pages, 0);
}

#ifdef CV_STATS_ON

void cv_stats_print_all(struct cv_statistics * cv_stats, struct cv_per_process_detailed_statistics * cv_per_proc, int total_threads){

  __cv_stats_add_avg(commit_wait_lock, cv_per_proc, total_threads);
  __cv_stats_add_avg(update_wait_lock, cv_per_proc, total_threads);
  __cv_stats_add_avg(update_latency, cv_per_proc, total_threads);
  __cv_stats_add_avg(commit_latency, cv_per_proc, total_threads);
  __cv_stats_add_avg(lock_latency_1, cv_per_proc, total_threads);
  __cv_stats_add_avg(lock_latency_2, cv_per_proc, total_threads);
  __cv_stats_add_avg(commit_inter_latency, cv_per_proc, total_threads);
  __cv_stats_add_avg(commit_waitlist_latency, cv_per_proc, total_threads);
  __cv_stats_add_avg(commit_acq_latency, cv_per_proc, total_threads);


  __cv_stats_simple_counter_avg(commit_pages, cv_per_proc, total_threads);
  __cv_stats_simple_counter_avg(update_pages, cv_per_proc, total_threads);  
  __cv_stats_simple_counter_avg(version_diff, cv_per_proc, total_threads);


  printk(KSNAP_LOG_LEVEL "Conversion_stats totals: pages merged: %d pages allocated: %d owner commits: %d get_snapshots: %d page_faults: %d \
commit_wait_lock %llu update_wait_lock %llu update_latency %llu commit_latency %llu commit_avg_pages %lu update_avg_pages %lu commit_lock1 %lld \
commit_lock2 %lld inter_commit %lld versiondiff %lu waitlist %lld acq %lld\n", 
	 atomic_read(&cv_stats->total_merged_pages),
	 atomic_read(&cv_stats->total_ksnap_pages_allocated),
	 atomic_read(&cv_stats->total_owner_commits),
	 atomic_read(&cv_stats->total_reader_get_snapshots),
	 atomic_read(&cv_stats->total_ksnap_page_faults),
	 __cv_stats_print_avg(commit_wait_lock),
	 __cv_stats_print_avg(update_wait_lock),
	 __cv_stats_print_avg(update_latency),
	 __cv_stats_print_avg(commit_latency),
	 __cv_stats_simple_counter_mean(commit_pages),
	 __cv_stats_simple_counter_mean(update_pages),
	 __cv_stats_print_avg(lock_latency_1),
	 __cv_stats_print_avg(lock_latency_2),
	 __cv_stats_print_avg(commit_inter_latency),
	 __cv_stats_simple_counter_mean(version_diff),
	 __cv_stats_print_avg(commit_waitlist_latency),
	 __cv_stats_print_avg(commit_acq_latency)
	 );
}

void cv_stats_inc_pages_allocated(struct cv_statistics * stats){
  atomic_inc(&stats->total_ksnap_pages_allocated);
}

void cv_stats_dec_pages_allocated(struct cv_statistics * stats){
  atomic_dec(&stats->total_ksnap_pages_allocated);
}

void cv_stats_inc_total_owner_commits(struct cv_statistics * stats){
  atomic_inc(&stats->total_owner_commits);
}

void cv_stats_dec_total_owner_commits(struct cv_statistics * stats){
  atomic_dec(&stats->total_owner_commits);
}

void cv_stats_inc_reader_get_snapshots(struct cv_statistics * stats){
  atomic_inc(&stats->total_reader_get_snapshots);
}

void cv_stats_dec_reader_get_snapshots(struct cv_statistics * stats){
  atomic_dec(&stats->total_reader_get_snapshots);
}

void cv_stats_inc_ksnap_page_faults(struct cv_statistics * stats){
  atomic_inc(&stats->total_ksnap_page_faults);
}

void cv_stats_dec_ksnap_page_faults(struct cv_statistics * stats){
  atomic_dec(&stats->total_ksnap_page_faults);
}

void cv_stats_inc_merged_pages(struct cv_statistics * stats){
  atomic_inc(&stats->total_merged_pages);
}

#else

void cv_stats_print_all(struct cv_statistics * cv_stats, struct cv_per_process_detailed_statistics * cv_per_proc, int total_threads){}

void cv_stats_inc_pages_allocated(struct cv_statistics * stats){}

void cv_stats_dec_pages_allocated(struct cv_statistics * stats){}

void cv_stats_inc_total_owner_commits(struct cv_statistics * stats){}

void cv_stats_dec_total_owner_commits(struct cv_statistics * stats){}

void cv_stats_inc_reader_get_snapshots(struct cv_statistics * stats){}

void cv_stats_dec_reader_get_snapshots(struct cv_statistics * stats){}

void cv_stats_inc_ksnap_page_faults(struct cv_statistics * stats){}

void cv_stats_dec_ksnap_page_faults(struct cv_statistics * stats){}

void cv_stats_inc_merged_pages(struct cv_statistics * stats){}

#endif

unsigned long cv_stats_elapsed_time_ns(struct timespec * start, struct timespec * end){
  return (end->tv_sec-start->tv_sec)*1000000000+(end->tv_nsec-start->tv_nsec);
}
