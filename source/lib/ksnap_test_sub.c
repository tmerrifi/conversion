
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "ksnap_test_sub.h"
#include "ksnap.h"
#include "shmUtility.h"
#include "time_util.h"
#include "ftrace.h"

/*the functions that actually DO SOMETHING inside a child process*/
void _main_fork();
void _main_memcpy();
void _main_snap(ksnap * snap,  ksnap_test_subs_profile * test_profile);

void _fork_children(int size_of_segment, char * segment_name, 
                    ksnap_test_subs_profile * test_profile, void (*action) (ksnap * snap, ksnap_test_subs_profile * test_profile), int subid);

void ksnap_test_subs_init(int num_of_subscribers, int type_of_subscribers, int size_of_segment, 
                          char * segment_name, ksnap_test_subs_profile * test_profile){

  for(int i=0; i < num_of_subscribers; ++i){
    
    if (test_profile && test_profile->action){
      _fork_children(size_of_segment, segment_name, test_profile, test_profile->action,i);
    }
    else{
      switch(type_of_subscribers){
      case ksnap_test_sub_type_fork:
      
	break;

      case ksnap_test_sub_type_memcpy:
	printf("memcpy\n");
	return;
	break;
        
      case ksnap_test_sub_type_snap:
	_fork_children(size_of_segment, segment_name, test_profile, _main_snap,i);
	break;
      }
    }  
  }
}

//this function is passed as an action to _fork_children. During a test, this is the function that each process executes
void _main_snap(ksnap * snap,  ksnap_test_subs_profile * test_profile){

  /*create a sleep timing structure*/
  struct timespec * sleep_timer = time_util_create_timespec(test_profile->sleep_ms);
  char * mem=(char *)snap->segment;
  /*to adhere to the user determined number of bytes to hit per page*/
  int bytes_per_page=0;
  /*a dummy counter since we are just adding all the numbers up in the snapshot*/
  int total=0;
  int total2=0;
  int update_counter=0;

  printf("in main\n");
 
  struct ftracer * tracer = ftrace_init();

  for (int i = 0; i < test_profile->total_num_of_reads;++i){
    total=0;
    for(int j=0; j < test_profile->reads_between_sleep;++j){
      if (update_counter==test_profile->reads_between_updates){
	update_counter=0;
	ksnap_update(snap, KSNAP_NO_DEBUG);
      }
      if (bytes_per_page < test_profile->bytes_per_page){
        mem=mem+1;
	bytes_per_page++;
      }
      else{
        //go to the next page
        printf("going to next page\n");
	mem+=4096-(((long)mem) % 4096);
        bytes_per_page=0;
      }
      total+=*mem;
      ++update_counter;
    }
    printf("total is %d\n", total);
    nanosleep(sleep_timer, NULL);
  }
  printf("finished\n");
  sleep(2);
  ksnap_update(snap, KSNAP_NO_DEBUG);
  exit(1);
}

/*A function that just forks all the child processes we need, then invokes the right main function on it*/
void _fork_children(int size_of_segment, char * segment_name, 
                    ksnap_test_subs_profile * test_profile, void (*action) (ksnap * snap, ksnap_test_subs_profile * test_profile), int subid){
  int child_pid;
  ksnap * snap;

  switch(child_pid=fork()){
  case -1:
    perror("something terrible happened.\n");
    break;
    
  case 0:
    //create a snapshot
    test_profile->sub_id=subid;
    if (test_profile->open_ksnap){
      printf("open?\n");
      munmap(test_profile->desired_address, size_of_segment);
      snap = ksnap_open(size_of_segment, segment_name, test_profile->policy, test_profile->desired_address);
    }
    else{
      printf("create no open?\n");
      snap = ksnap_create_no_open(size_of_segment, segment_name, COMMIT_ALWAYS, 100, KSNAP_READER, test_profile->desired_address);
    }
    action(snap, test_profile);
    break;
    
  }
}
