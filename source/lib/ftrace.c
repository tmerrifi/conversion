
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#include "ftrace.h"

struct ftracer * ftrace_init(){
  struct ftracer * tracer = malloc(sizeof(struct ftracer));	
  if (tracer){
    tracer->fd_onoff = open("/sys/kernel/debug/tracing/tracing_on", O_WRONLY);
    tracer->fd_marker = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY);	
    tracer->fd_pid = open("/sys/kernel/debug/tracing/set_ftrace_pid", O_WRONLY);	
  }
  return tracer;
}

void ftrace_close(struct ftracer * tracer){
  close(tracer->fd_onoff);
  close(tracer->fd_marker);
  close(tracer->fd_pid);
}

void ftrace_on(struct ftracer * tracer){
  if (tracer){
    write(tracer->fd_onoff, "1", 1);
    lseek(tracer->fd_onoff,0,SEEK_SET);
  }
  else{
    perror("your tracer is NULL");	
  }
}

void ftrace_off(struct ftracer * tracer){
  if (tracer){
    write(tracer->fd_onoff, "0", 1);
    lseek(tracer->fd_onoff,0,SEEK_SET);
  }
  else{
    perror("your tracer is NULL");	
  }
}

void ftrace_pid_set(struct ftracer * tracer, int pid){
  char pid_str[50];
  sprintf(pid_str, "%d", pid);
  if (tracer){
    write(tracer->fd_pid, pid_str, strlen(pid_str));    
  }
  else{
    perror("LIBFTRACE: your tracer is NULL");	    
  }
}

void ftrace_pid_clear(struct ftracer * tracer){
  char * clear="-1";
  if (tracer){
    write(tracer->fd_marker, clear, strlen(clear));    
  }
  else{
    perror("LIBFTRACE: your tracer is NULL");	    
  }
}

void ftrace_write_to_trace(struct ftracer * tracer, char * str){
  if (tracer){
    write(tracer->fd_marker, str, strlen(str));
  }
  else{
    perror("LIBFTRACE: your tracer is NULL");	
  }
}
