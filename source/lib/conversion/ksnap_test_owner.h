

#define ksnap_test_owner_type_fork 1
#define ksnap_test_owner_type_memcpy 2
#define ksnap_test_owner_type_snap 3

//this structure encapsulates how the test should be conducted
typedef struct{
  int sleep_ms; //how much should I sleep between tests
  int bytes_per_page; //how many bytes per page should I write to
  int total_num_of_writes;
  int writes_between_sleep; //how many writes to do before sleeping
  int writes_between_settled; //
}ksnap_test_owner_profile;

//A library 
void ksnap_test_owner_init(int type_of_segment, int size_of_segment, 
			  char * segment_name, ksnap_test_owner_profile * test_profile);
