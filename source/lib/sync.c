
#include <stdlib.h>
#include <stdio.h>

#include "sync.h"

struct sync_spin_barrier * sync_spin_barrier_init(unsigned int count){
  struct sync_spin_barrier * bar = malloc(sizeof(struct sync_spin_barrier));
  bar->max=count;
  bar->begin=count;
  bar->end=0;
  return bar;
}


void sync_spin_barrier_wait(struct sync_spin_barrier * bar){
  //wait till everyone has left the last barrier
  while(__sync_fetch_and_add(&bar->end,0)>0){
    for(int i=0;i<1000;++i);
  }
  if(__sync_sub_and_fetch(&bar->begin,1)==1){
    __sync_fetch_and_add(&bar->end,bar->max+1);
    __sync_fetch_and_sub(&bar->begin,1);
  }
  else{
    while(__sync_fetch_and_add(&bar->begin,0)>0){
	for(int i=0;i<1000;++i);
      }
  }

  if(__sync_sub_and_fetch(&bar->end,1)==1){
    __sync_fetch_and_add(&bar->begin,bar->max+1);
    __sync_fetch_and_sub(&bar->end,1);
  }
  else{
      while(__sync_fetch_and_add(&bar->end,0)>0){
	for(int i=0;i<1000;++i);
      }
  }
}
