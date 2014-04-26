
#include <stdlib.h>
#include <string.h>

#include "time_util.h"


struct timespec * time_util_create_timespec(int milliseconds){
  struct timespec * t = malloc(sizeof(struct timespec));
  memset(t,0,sizeof(struct timespec));
  t->tv_sec = (milliseconds/1000 > 0) ? milliseconds/1000 : 0;
  long mill_tmp = (milliseconds/1000 > 0) ? milliseconds-(1000*t->tv_sec) : milliseconds;
  t->tv_nsec = mill_tmp*1000000;
  return t;
}

struct timespec * time_util_create_timespec_us(int microseconds){
  struct timespec * t = malloc(sizeof(struct timespec));
  memset(t,0,sizeof(struct timespec));
  t->tv_sec = (microseconds/1000000 > 0) ? microseconds/1000000 : 0;
  long micro_tmp = (microseconds/1000000 > 0) ? microseconds-(1000000*t->tv_sec) : microseconds;
  t->tv_nsec = micro_tmp*1000;
  return t;
}

long time_util_time_diff(struct timespec * start, struct timespec * end){
  return (end->tv_sec-start->tv_sec)*1000000+(end->tv_nsec-start->tv_nsec)/1000;
}

unsigned long long time_util_time_diff_ns(struct timespec * start, struct timespec * end){
  return (end->tv_sec-start->tv_sec)*1000000000ULL+(end->tv_nsec-start->tv_nsec);
}
