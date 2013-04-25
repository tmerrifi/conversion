
#include "ksnap.h"

#define NUM_OF_PAGES 1
#define NUM_OF_THREADS 5

void run(){
  printf("RUNNING! %d\n", getpid());
}

int main(){
  
  //conv_checkout_create((1<<12) * NUM_OF_PAGES, "simple_test", NULL, 0);
  
  int i=0;
  int pid=0;
  int pids[NUM_OF_THREADS];
  memset(pids,0,sizeof(int)*NUM_OF_THREADS);
  
  for (;i<NUM_OF_THREADS;++i){
    pid = fork();
    if (pid==0){
      run();
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
  printf("ALL DONE\n");
}
