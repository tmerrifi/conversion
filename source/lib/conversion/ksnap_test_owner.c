

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "ksnap_test_owner.h"
#include "ksnap.h"
#include "shmUtility.h"
#include "time_util.h"
#include "ftrace.h"

void _main_owner_snapshot(ksnap * snap, ksnap_test_owner_profile * test_profile);

void _fork_child(int size_of_segment, char * segment_name, 
		 ksnap_test_owner_profile * test_profile, void (*action) (ksnap * snap, ksnap_test_owner_profile * test_profile));

void ksnap_test_owner_init(int type_of_segment, int size_of_segment, 
			   char * segment_name, ksnap_test_owner_profile * test_profile){

  _fork_child(size_of_segment, segment_name, 
	      test_profile, _main_owner_snapshot);
}

void _main_owner_snapshot(ksnap * snap, ksnap_test_owner_profile * test_profile){
  /*create a sleep timing structure*/
  struct timespec * sleep_timer = time_util_create_timespec(test_profile->sleep_ms);
  char * mem=(char *)snap->segment;
  /*to adhere to the user determined number of bytes to hit per page*/
  int bytes_per_page=0;
  /*a dummy counter*/
  unsigned char counter=0;
  /*total write counter*/
  int total_writes=0;

  srand(time(NULL));
  counter=random()%25;
  printf("in main for the owner\n");
 
  struct ftracer * tracer = ftrace_init();

  for (int i = 0; i < test_profile->total_num_of_writes;++i){
    counter++;
    printf("writing %d\n", counter);
    for(int j=0; j < test_profile->writes_between_sleep;++j){
      if (bytes_per_page < test_profile->bytes_per_page){
        mem=mem+1;
	bytes_per_page++;
      }
      else{
        //go to the next page
        mem+=4096-(((long)mem) % 4096);
        bytes_per_page=0;
      }
      //printf("%d\n", *mem);
      ftrace_on(tracer);
      ftrace_write_to_trace(tracer, "starting write");
      *mem=counter;
      ftrace_off(tracer);
      ++total_writes;
      if (total_writes==test_profile->writes_between_settled){
	printf("calling settled\n");
	ftrace_on(tracer);
	ftrace_write_to_trace(tracer, "starting settle");
	ksnap_settle(snap, KSNAP_NO_DEBUG);
	ftrace_off(tracer);
	total_writes=0;
      }
    }
    printf("I'm sleeping, i is %d\n", i);  
    nanosleep(sleep_timer, NULL);
  }
  printf("i hit exit\n");
  sleep(2);
  ksnap_settle(snap, KSNAP_NO_DEBUG);
  exit(1);
}


/*A function that just forks all the child processes we need, then invokes the right main function on it*/
void _fork_child(int size_of_segment, char * segment_name, 
                    ksnap_test_owner_profile * test_profile, void (*action) (ksnap * snap, ksnap_test_owner_profile * test_profile)){
  int child_pid;
  
  switch(child_pid=fork()){
  case -1:
    perror("something terrible happened.\n");
    break;
    
  case 0:
    printf("I'm a forked OWNER process\n");
    //create a snapshot
    ksnap * snap = ksnap_open(size_of_segment, segment_name, COMMIT_DYN, (void *)0xA0000000);
    action(snap, test_profile);
    break;
    
  }
}
