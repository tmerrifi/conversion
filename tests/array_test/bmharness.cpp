/**
 *  Copyright (C) 2011
 *  University of Rochester Department of Computer Science
 *    and
 *  Lehigh University Department of Computer Science and Engineering
 *
 * License: Modified BSD
 *          Please see the file LICENSE.RSTM for licensing information
 */

#ifndef BMHARNESS_HPP__
#define BMHARNESS_HPP__

#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <pthread.h>
#include "bmconfig.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include "mm.h"
#include "ksnap.h"

using std::string;
using std::cout;

sem_t sem_global;

int * tx_per_thread;


#define faiptr(p)           __sync_fetch_and_add(p, 1)
#define faa64(p, a)         __sync_fetch_and_add(p, a)
#define faaptr(p, a)        __sync_fetch_and_add(p, a)

inline uint64_t getElapsedTime()
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    uint64_t tt = (((long long)t.tv_sec) * 1000000000L) + ((long long)t.tv_nsec);
    return tt;
}


Config::Config() :
    bmname(""),
    duration(1),
    execute(0),
    threads(1),
    nops_after_tx(0),
    elements(256),
    lookpct(34),
    inspct(56),
    qrypct(10),
    sets(1),
    ops(1),
    useconversion(false),
    time(0),
    running(true),
    txcount(0),
    print_query_time(false)
{
}

Config CFG;

namespace
{

  /**
   * Print benchmark configuration output
   */
  void dump_csv()
  {
    int total_tx=0;
    for(int i=0;i<200;++i){
      total_tx+=tx_per_thread[i];
    }

    // csv output
    std::cout << "csv"
	      << ", B=" << CFG.bmname     << ", R=" << CFG.lookpct
	      << ", d=" << CFG.duration   << ", p=" << CFG.threads
	      << ", X=" << CFG.execute    << ", m=" << CFG.elements
	      << ", S=" << CFG.sets       << ", O=" << CFG.ops
	      << ", txns=" << total_tx << ", time=" << CFG.time
	      << ", throughput="
	      << (1000000000LL * total_tx) / (CFG.time)
	      << std::endl;
  }

  /**
   *  Print usage
   */
  void usage()
  {
      std::cerr << "Usage: CounterBench -C <stm algorithm> [flags]\n";
      std::cerr << "    -d: number of seconds to time (default 1)\n";
      std::cerr << "    -X: execute fixed tx count, not for a duration\n";
      std::cerr << "    -p: number of threads (default 1)\n";
      std::cerr << "    -N: nops between transactions (default 0)\n";
      std::cerr << "    -R: % lookup txns (remainder split ins/rmv)\n";
      std::cerr << "    -m: range of keys in data set\n";
      std::cerr << "    -B: name of benchmark\n";
      std::cerr << "    -S: number of sets to build (default 1)\n";
      std::cerr << "    -O: operations per transaction (default 1)\n";
      std::cerr << "    -h: print help (this message)\n\n";
      std::cerr << "    -q: % of query trans";
      std::cerr << "    -Q: % of threads that perform queries";
  }

/**
 *  Parse command line arguments
 */
void
parseargs(int argc, char** argv)
{
  // parse the command-line options
  int opt;
  while ((opt = getopt(argc, argv, "N:d:p:hX:B:m:R:S:O:c:q:Q:i:P:C:")) != -1) {
    switch(opt) {
    case 'd': CFG.duration      = strtol(optarg, NULL, 10); break;
    case 'p': CFG.threads       = strtol(optarg, NULL, 10); break;
    case 'N': CFG.nops_after_tx = strtol(optarg, NULL, 10); break;
    case 'X': CFG.execute       = strtol(optarg, NULL, 10); break;
    case 'B': CFG.bmname        = std::string(optarg); break;
    case 'm': CFG.elements      = strtol(optarg, NULL, 10); break;
    case 'S': CFG.sets          = strtol(optarg, NULL, 10); break;
    case 'O': CFG.ops           = strtol(optarg, NULL, 10); break;
    case 'c': CFG.useconversion  = (strtol(optarg, NULL, 10) > 0) ? true : false ; break;
    case 'R':
      CFG.lookpct = CFG.qrypct + strtol(optarg, NULL, 10);
      CFG.inspct = (100 - CFG.qrypct - strtol(optarg, NULL, 10))/2 + CFG.lookpct;
      break;
    case 'q': 
      CFG.qrypct = strtol(optarg,NULL,10); 
      break;
    case 'Q':
      CFG.threadq = strtol(optarg,NULL,10);
      break;
    case 'P':
      (strtol(optarg, NULL, 10)==1) ? CFG.print_query_time=true : CFG.print_query_time=false;
      break;
    case 'h':
      usage();
      exit(1);
    }
  }
  printf("query per %d lookup %d insert %d\n", CFG.qrypct, CFG.lookpct, CFG.inspct);
}

/**
 *  Run some nops between transactions, to simulate some time being spent on
 *  computation
 */
void
nontxnwork()
{
  if (CFG.nops_after_tx){
      for (uint32_t i = 0; i < CFG.nops_after_tx; i++){
	for (int i = 0; i < 64; i++){
	  __asm__ volatile("nop");
	}
      }
  }
}

/*** Signal handler to end a test */
extern "C" void catch_SIGALRM(int) {
    CFG.running = false;
}

uint64_t * barriers;

/**
 *  Support a few lightweight barriers
 */
void
barrier(uint32_t which)
{
  //static volatile uint32_t barriers[16] = {0};

  //CFENCE;
  faiptr(&barriers[which]);
  while (barriers[which] != CFG.threads) { 
    sched_yield();
  }

  //CFENCE;
}

/*** Run a timed or fixed-count experiment */
void
run(uintptr_t id)
{
    // wait until all threads created, then set alarm and read timer
    barrier(0);

    if (id == 0) {
        if (!CFG.execute) {
	  signal(SIGALRM, catch_SIGALRM);
	  alarm(CFG.duration);
        }
        CFG.time = getElapsedTime();
    }
    // wait until read of start timer finishes, then start transactios
    if (id != 0){
      thread_init();
    }
    barrier(1);
    conv_seg * cv_seg;
    cv_seg=conv_open_exisiting("snapshot_stm");
    uint32_t count = 0;
    uint32_t seed = (id*100000)+((id*55)/((id+1)*4)); // not everyone needs a seed, but we have to support it
    srand(time(NULL));
    if (!CFG.execute) {
      // run txns until alarm fires
      while (CFG.running) {
	bench_test(id, &seed, cv_seg);
	++count;
	nontxnwork(); // some nontx work between txns?
      }
    }
    else {
        // run fixed number of txns
      for (uint32_t e = 0; e < CFG.execute; e++) {
	bench_test(id, &seed, cv_seg);
	++count;
	nontxnwork(); // some nontx work between txns?
      }
    }

    // wait until all txns finish, then get time
    barrier(2);
    if (id == 0)
      CFG.time = getElapsedTime() - CFG.time;

    //verify results
    bench_verify(cv_seg);

    // add this thread's count to an accumulator
    faa64(&CFG.txcount, count);
    tx_per_thread[getpid()%200]=count;
}

/**
 *  pthread wrapper for running the experiments
 *
 *  NB: noinline prevents this from getting inlined into main (and prevents
 *      run from being inlined there as well. This eliminates an
 *      _ITM_initializeProcess ordering problem if there's a transaction
 *      lexically scoped inside of main.
 */
void*
run_wrapper(void* i)
{
  run((uintptr_t)i);
  return NULL;
}
}

/**
 *  Main routine: parse args, set up the TM system, prep the benchmark, run
 *  the experiments, verify results, print results, and shut down the system
 */
int main(int argc, char** argv) {
    parseargs(argc, argv);
    bench_reparse();
    
    void* args[256];
    int pids[256];

    barriers = (uint64_t *)mmap(NULL, sizeof(uint64_t)*16, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    memset(barriers, 0, sizeof(uint32_t)*16);
    
    tx_per_thread = (int *)mmap(NULL, sizeof(int)*200, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    memset(tx_per_thread, 0, sizeof(int)*200);


    bench_init();
    
    // set up configuration structs for the threads we'll create
    for (uint32_t i = 0; i < CFG.threads; i++)
      args[i] = (void*)i;



    // actually create the threads
    for (uint32_t j = 1; j < CFG.threads; j++){
      //pthread_create(&tid[j], &attr, &run_wrapper, args[j]);
      int pid=fork();

      if (pid==0){
	run_wrapper(args[j]);
	exit(1);
      }
      else{
	pids[j]=pid;
      }
    }


    // all of the other threads should be queued up, waiting to run the
    // benchmark, but they can't until this thread starts the benchmark
    // too...
    run_wrapper(args[0]);

    // Don't call any more transactional functions, because run_wrapper called
    // shutdown.

    // everyone should be done.  Join all threads so we don't leave anything
    // hanging around
    int statloc;
    for (uint32_t k = 1; k < CFG.threads; k++)
      waitpid(pids[k],&statloc,0);

    dump_csv();

    return 0;
}

#endif // BMHARNESS_HPP__
