
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#include "ksnap.h"
#include "../common/process_shared_malloc.h"

#define NUM_OF_PAGES 100
#define NUM_OF_THREADS 16
#define ARRAY_SIZE_BYTES (NUM_OF_PAGES * (1<<12))

#define NUM_OF_RUNS 1000
#define NUM_OF_ITERATIONS 100

pthread_barrier_t * barrier;
sem_t sem;
int failures=0;
unsigned int time_val=0;
unsigned char * debug_array=NULL;
int * failure_flag=NULL;

int sum_up(conv_seg * array_seg){
  int i,j, sum;
  sum=0;
  unsigned char * array = (unsigned char *)array_seg->segment;
  for (i=0;i<ARRAY_SIZE_BYTES;++i){
    sum+=array[i];
  }
  return sum;
}

int compare_on_error(conv_seg * array_seg){
    int i;
    unsigned char * array = (unsigned char *)array_seg->segment;
    for (i=0;i<ARRAY_SIZE_BYTES;++i){
        if (array[i]!=debug_array[i]){
            printf("oops: %d page %d\n", i, i/4096);
        }
    }
}

void run(conv_seg * array_seg, int id){
  unsigned char * array = (unsigned char *)array_seg->segment;
  int i,j, sum;
  i=j=0;
  int start_index = (ARRAY_SIZE_BYTES/NUM_OF_THREADS)*id;

  for (;i<NUM_OF_RUNS;++i){

      if (*failure_flag){
          conv_print_trace(array_seg);
          break;
      }
      
      for (;j<NUM_OF_ITERATIONS;++j){
          int index = (rand()%(ARRAY_SIZE_BYTES/NUM_OF_THREADS)) + start_index;
          array[index]++;
          debug_array[index]++;
      }
      
      conv_commit(array_seg);
      pthread_barrier_wait(barrier);
      conv_update(array_seg);
      
      //a poor man's barrier
      sum = sum_up(array_seg);
      if (sum != ((i+1)*NUM_OF_ITERATIONS*NUM_OF_THREADS)){
          sem_wait(&sem);
          (*failure_flag)++;
          printf("UNIT TEST ERROR!!! sum %d expected %d iterations %d thread %d\n", sum, ((i+1)*NUM_OF_ITERATIONS*NUM_OF_THREADS), i, id);
          if (*failure_flag==1){
              compare_on_error(array_seg);
          }
          sem_post(&sem);
      }
      j=0;
      pthread_barrier_wait(barrier);
  }
}

int main(){
    
  srand(time(NULL));
  conv_seg * array_segment = conv_checkout_create(ARRAY_SIZE_BYTES, "simple_test", NULL, 0);

  int i=0;
  int pid=0;
  int pids[NUM_OF_THREADS];
  memset(pids,0,sizeof(int)*NUM_OF_THREADS);
  //allocate some memory in a shared place
  barrier=process_shared_malloc(sizeof(pthread_barrier_t));
  debug_array=process_shared_malloc(ARRAY_SIZE_BYTES);
  failure_flag=process_shared_malloc(sizeof(int));
  *failure_flag=0;
  //need to mark the barrier as process shared
  pthread_barrierattr_t attr;
  pthread_barrierattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
  pthread_barrier_init(barrier, &attr, NUM_OF_THREADS);
  //initializing a mutex
  sem_init(&sem,1,1);

  for (;i<NUM_OF_THREADS;++i){
    pid = fork();
    if (pid==0){
      run(array_segment, i);
      exit(1);
    }
    else{
      pids[i]=pid;
    }
  }
  
  //wait
  i=0;
  int status;
  for(;i<NUM_OF_THREADS;++i){
    waitpid(pids[i], status, 0);
  }

  if (*failure_flag==0){
      printf("SUCCESS\n");
  }

  return 0;
}
