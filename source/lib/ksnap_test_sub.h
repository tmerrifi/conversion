
#ifndef KSNAP_TEST_SUB_H
#define KSNAP_TEST_SUB_H 

#include "ksnap.h"

#define ksnap_test_sub_type_fork 1
#define ksnap_test_sub_type_memcpy 2
#define ksnap_test_sub_type_snap 3

typedef struct{
  int num_of_subscribers;
  int size_of_segment;
}ksnap_test_subs;

//this structure encapsulates how the test should be conducted
typedef struct _ksnap_test_subs_profile{
  int sleep_ms; //how much should I sleep between tests
  int bytes_per_page; //how many bytes per page should I write to
  int total_num_of_reads;
  int reads_between_sleep; //how many writes to do before sleeping
  int reads_between_updates;
  void (*action) (ksnap *, struct _ksnap_test_subs_profile *);
  void * desired_address;
  void * action_data;
  int total_time;
  int open_ksnap;
  int num_of_subscribers;
  int sub_id;
  void * fork_stats;
  int policy;
}ksnap_test_subs_profile;

//A library 

void ksnap_test_subs_init(int num_of_subscribers, int type_of_subscribers, int size_of_segment, 
			  char * segment_name, ksnap_test_subs_profile * test_profile);

#endif
