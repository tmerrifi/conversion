
#include <stdlib.h>
#include <stdio.h>

#include "ksnap.h"

#define NUM_OF_PAGES 1
#define NUM_OF_THREADS 4
#define ARRAY_SIZE_BYTES (NUM_OF_PAGES * (1<<12))

#define NUM_OF_RUNS 10
#define NUM_OF_ITERATIONS 10

int sum_up(conv_seg * array_seg){
  int i,j, sum;
  sum=0;
  char * array = array_seg->segment;

  for (i=0;i<ARRAY_SIZE_BYTES;++i){
    sum+=array[i];
  }
  return sum;
}

void run(conv_seg * array_seg, int id){
  char * array = array_seg->segment;
  srand(time(NULL));
  int i,j, sum;
  i=j=0;
  int start_index = (ARRAY_SIZE_BYTES/NUM_OF_THREADS)*id;
  printf("start index for id %d is %d\n", id, start_index);

  for (;i<NUM_OF_RUNS;++i){
    for (;j<NUM_OF_ITERATIONS;++j){
      array[id + rand()%(ARRAY_SIZE_BYTES/NUM_OF_THREADS)]++;
    }
    sleep(1);
    //a poor man's barrier
    sum = sum_up(array_seg);
    printf("sum is %d\n", sum);
    sleep(1);
    j=0;
  }
}

int main(){
  
  conv_seg * array_segment = conv_checkout_create((1<<12) * NUM_OF_PAGES, "simple_test", NULL, 0);

  int i=0;
  int pid=0;
  int pids[NUM_OF_THREADS];
  memset(pids,0,sizeof(int)*NUM_OF_THREADS);
  
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

}
