/**
 *  Copyright (C) 2011
 *  University of Rochester Department of Computer Science
 *    and
 *  Lehigh University Department of Computer Science and Engineering
 *
 * License: Modified BSD
 *          Please see the file LICENSE.RSTM for licensing information
 */

/**
 *  Step 1:
 *    Include the configuration code for the harness, and the API code.
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include "bmconfig.hpp"
#include "time_util.h"
#include "mm.h"

/**
 *  We provide the option to build the entire benchmark in a single
 *  source. The bmconfig.hpp include defines all of the important functions
 *  that are implemented in this file, and bmharness.cpp defines the
 *  execution infrastructure.
 */
#ifdef SINGLE_SOURCE_BUILD
#include "bmharness.cpp"
#endif

/**
 *  Step 2:
 *    Declare the data type that will be stress tested via this benchmark.
 *    Also provide any functions that will be needed to manipulate the data
 *    type.  Take care to avoid unnecessary indirection.
 */

#define sem_count 500

int* matrix;

int query_ctr;
int max;
sem_t * matrix_sem[sem_count];
sem_t * global_sem;

struct timespec last;

/**
 *  Step 3:
 *    Declare an instance of the data type, and provide init, test, and verify
 *    functions
 */

/*** Initialize an array that we can use for our MCAS test */
void bench_init()
{
  MM_create(40*(1<<20), "snapshot_stm");
  matrix = (int*)MM_malloc(CFG.elements * sizeof(int));
  //matrix_sem = (sem_t *)mmap(NULL, sizeof(sem_t)*sem_count, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  //global_sem = (sem_t *)mmap(NULL, sizeof(sem_t)*1, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  
  char mutex_name[100];
  for (int i=0;i<sem_count;++i){
    sprintf(mutex_name, "fgl_%d.sem", i);
    matrix_sem[i] = sem_open(mutex_name,O_CREAT,0644,1);
  }
  global_sem = sem_open("global.sem",O_CREAT,0644,1);
  query_ctr=0;
}

void thread_init()
{
  char mutex_name[100];
  for (int i=0;i<sem_count;++i){
    sprintf(mutex_name, "fgl_%d.sem", i);
    matrix_sem[i] = sem_open(mutex_name,0);
  }
  global_sem = sem_open("global.sem",O_CREAT,0644,1);
}

int compute_total(){
  int total=0;
  for (uint32_t i=1;i<CFG.elements;++i){
    total+=matrix[i];
  }
  return total;
}

int __attribute__((optimize("O0"))) find_max(){
  uint32_t max=0;
  for (uint32_t i=1;i<CFG.elements;++i){
    int val=matrix[i];
    if (val>max){
      max=val;
    }
  }
  return max;
}


/*** Run a bunch of random transactions */
void __attribute__((optimize("O0"))) bench_test(uintptr_t id, uint32_t* seed, conv_seg * cv_seg)
{
    // cache the seed locally so we can restore it on abort
    //
    // NB: volatile needed because using a non-volatile local in conjunction
    //     with a setjmp-longjmp control transfer is undefined, and gcc won't
    //     allow it with -Wall -Werror.
  volatile uint32_t local_seed = *seed;
  uint32_t loc;
  uint32_t act = rand() % 100;
  uint32_t lookupval;

  uint32_t qrypct=((id+1) <= CFG.threadq) ? CFG.qrypct : 0;    
  if (act<qrypct){
    query_ctr++;
    conv_update(cv_seg);
    #ifdef CV_UNIT_TESTS
    int total=compute_total();
    if (total!=matrix[0]){
      printf("UNIT TEST ERROR!!! total %d stored %d\n", total, matrix[0]);
    }
    #else
    max=find_max();
    #endif
  }
  else if (act<CFG.lookpct){
    loc = (rand() % (CFG.elements -1)) + 1;
    conv_update(cv_seg);
    lookupval=matrix[loc];
  }
  else{
    //add 1 to avoid 0, where we store the total if we are running unit tests
    loc = (rand() % (CFG.elements -1)) + 1;
    #ifdef CV_UNIT_TESTS
    conv_update_mutex(cv_seg, matrix_sem[loc % sem_count]);
    matrix[loc]++;
    matrix[0]=compute_total();
    conv_commit_mutex(cv_seg, matrix_sem[loc % sem_count]);
    #else
    conv_update_mutex(cv_seg, matrix_sem[loc % sem_count]);
    matrix[loc]++;
    conv_commit_mutex(cv_seg, matrix_sem[loc % sem_count]);
    #endif
  }
}

/*** Ensure the final state of the benchmark satisfies all invariants */
bool bench_verify(conv_seg * seg) { 
  conv_update(seg);
  int total=compute_total();
  double write_percentage = ((double)CFG.lookpct)/100;
  if (total < (write_percentage*CFG.execute*.5*CFG.threads)){
    printf("FAILED: total writes %d, expected %d\n", total, (int)(write_percentage*CFG.execute*.5*CFG.threads));
  }

  return true;
}

/**
 *  Step 4:
 *    Include the code that has the main() function, and the code for creating
 *    threads and calling the three above-named functions.  Don't forget to
 *    provide an arg reparser.
 */

/*** Deal with special names that map to different M values */
void bench_reparse()
{
    if      (CFG.bmname == "")          CFG.bmname   = "MCAS";
}
