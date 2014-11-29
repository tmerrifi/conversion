  
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>
#include <sys/syscall.h>

#include "ksnap.h"
#include "shmUtility.h"
#include "ftrace.h"

#define __CONV_CREATE 1
#define __CONV_NO_CREATE 0

#if __x86_64__
/* 64-bit */
#define __CONV_SYS_CALL 303

#else

#define __CONV_SYS_CALL 341

#endif


//what should the size of the metadata segment be?
int __compute_meta_data_pages(int size_in_bytes){
  int total_pages = (size_in_bytes/(KSNAP_PAGE_SIZE))+1;
  //add 2 extra pages, 1 for ksnap_meta_data and 1 to be safe for dirty pages
  int meta_data_pages = (total_pages/KSNAP_PAGE_SIZE) + 2;
  return meta_data_pages;
}

size_t __get_file_size(int fd){
	size_t sizeInBytes=0;
	struct stat fileStats;
	if (fstat(fd,&fileStats) != -1){
		sizeInBytes=(fileStats.st_size > 0) ? fileStats.st_size : 0;
	}
	return sizeInBytes;
}

//we only want the file name...not a path
char * __strip_file_name(char * file_name){
  char * return_ptr=NULL;
  char ** file_name_ptr=&file_name;
  while(*file_name_ptr){
    return_ptr=strsep(file_name_ptr, "/");
  }
  return return_ptr;
}


void * __open_shared_memory_segment(int size_of_segment, char * file_name, void * desired_address, int * fd, int flags, int create){
  void * mem;
  int tmp_fd, size_of_file;
  char file_path[200];
  int tries=0;

  if (fd==NULL){
    fd = &tmp_fd;
  }
  sprintf(file_path,"%sXXXXXX",file_name);
  //create the segment, if it already exists we must fail
  if (create){
    //*fd = open(file_path, O_CREAT | O_RDWR | O_EXCL, 0644);
    *fd = mkstemp(file_path);
    if (*fd==-1){
      //we've failed! return null
      goto error;
    }
  }
  else{
    *fd = open(file_path, O_RDWR, 0644);
    if (*fd==-1){
      goto error;
    }
  }

 success:
  if (create){
    ftruncate(*fd, size_of_segment);
  }
  if (desired_address){
    flags |= MAP_FIXED;
  }

  mem = mmap(desired_address,size_of_segment,PROT_READ|PROT_WRITE,flags,*fd,0);
  if (!mem){
    goto error;
  }
  return mem;

 error:
  fprintf(stderr, "failed to create file for segment %s\n", file_name);
  return NULL;

}

unsigned int __compute_dirty_list_length(unsigned int meta_data_pages){
    return (meta_data_pages - 1) * ((KSNAP_PAGE_SIZE/sizeof(unsigned long)) - 10);
}

unsigned int conv_get_linearized_version_num(conv_seg * seg){
    return __get_meta_shared_page(seg)->linearized_version_num;
}

unsigned int conv_get_logical_page_count(conv_seg * seg){
    return __get_meta_shared_page(seg)->logical_page_count;
}

unsigned int conv_get_dirty_page_count(conv_seg * seg){
    return __get_meta_local_page(seg)->dirty_page_count;
}

unsigned int conv_get_merged_page_count(conv_seg * seg){
    return __get_meta_local_page(seg)->merged_pages;
}

unsigned int conv_get_updated_page_count(conv_seg * seg){
    return __get_meta_local_page(seg)->updated_pages;
}

void conv_clear_local_stats(conv_seg * seg){
    __get_meta_local_page(seg)->updated_pages=0;
    __get_meta_local_page(seg)->merged_pages=0;
    __get_meta_local_page(seg)->dirty_page_count=0;
}

void __ksnap_open_meta_data_segments(int size_of_segment, char * segment_name, conv_seg * snap, int create){
  char meta_data_local_name[200];
  char meta_data_shared_name[200];
  sprintf(meta_data_local_name,"meta_local_%s_%d.mem", segment_name, getpid());
  sprintf(meta_data_shared_name,"meta_shared_%s.mem", segment_name);
  int meta_data_pages = __compute_meta_data_pages(size_of_segment);
  //
  void * meta_data_local = __open_shared_memory_segment(meta_data_pages*KSNAP_PAGE_SIZE, 
							meta_data_local_name, snap->segment - (KSNAP_PAGE_SIZE*(meta_data_pages-1)) - (META_LOCAL_OFFSET_FROM_SEGMENT*KSNAP_PAGE_SIZE),
							NULL, MAP_PRIVATE, create);
  
  memset(meta_data_local,0,meta_data_pages*KSNAP_PAGE_SIZE);


  void * meta_data_shared = __open_shared_memory_segment(1*KSNAP_PAGE_SIZE, 
							 meta_data_shared_name, snap->segment - (META_SHARED_OFFSET_FROM_SEGMENT*KSNAP_PAGE_SIZE), 
							 NULL, MAP_SHARED, create);

  if (create){
    memset(meta_data_shared,0,1*KSNAP_PAGE_SIZE);
  }

  mlock(meta_data_local,meta_data_pages*KSNAP_PAGE_SIZE);
  mlock(meta_data_shared,1*KSNAP_PAGE_SIZE);
  __get_meta_local_page(snap)->meta_data_size = meta_data_pages;
  __get_meta_local_page(snap)->dirty_list_size = __compute_dirty_list_length(meta_data_pages);
}

conv_seg * __create_conv_seg(int size_of_segment, char * segment_name){
  conv_seg * snap = malloc(sizeof(conv_seg));
  snap->name = malloc(100);
  snap->file_name = malloc(100);
  sprintf(snap->file_name, "%s.mem", segment_name);
  sprintf(snap->name, "%s", __strip_file_name(segment_name));
  snap->size_of_segment = size_of_segment;
  return snap;
}

//open up the segment, if create is set then we ONLY create...else we ONLY open (not create)
conv_seg * __conv_open(int size_of_segment, char * segment_name, void * desired_address, int create){
  int meta_data_pages;
  int created;

  conv_seg * snap = __create_conv_seg(size_of_segment, segment_name);
  snap->segment = __open_shared_memory_segment(snap->size_of_segment, snap->file_name, desired_address, &snap->fd, MAP_PRIVATE, create);

  madvise(snap->segment, snap->size_of_segment, MADV_KSNAP_ALWAYS);
  madvise(snap->segment, snap->size_of_segment, MADV_KSNAP_TRACK);
  __ksnap_open_meta_data_segments(size_of_segment, snap->name, snap, create);
  //set default editing unit to one byte
  snap->editing_unit=1;
  return snap;
}

conv_seg * conv_checkout_open(int size_of_segment, char * segment_name, void * desired_address){
  return __conv_open(size_of_segment, segment_name, desired_address, __CONV_NO_CREATE);
}

conv_seg * conv_checkout_create(int size_of_segment, char * segment_name, void * desired_address){
  return __conv_open(size_of_segment, segment_name, desired_address, __CONV_CREATE);
}

void conv_set_editing_unit_bytes(conv_seg * seg, size_t editing_unit){
    seg->editing_unit=editing_unit;
}

//what if we want to work with a segment that is already opened in our address space? This is useful for when we are using the
//malloc library and we don't have control (or full control) of the mmap() call and where it maps to. So, we have to go find the address
//so we can still call msync on it.
conv_seg * conv_open_exisiting(char * segment_name){
  char * search_name[1000];
  FILE * fp;
  conv_seg * seg;
  int pid = getpid();
  //a buffer for the command we need to run (a shell script with some input params)
  char command[200];
  //a buffer for storing the segment address we get
  char segment_address[20];
  
  sprintf(search_name, "%s.convmem", segment_name);

  sprintf(command,"find_snapshot_mapping.sh %d %s\n", pid, search_name); 
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("failed to find snapshot, could not execute external shell.\n" );
    return NULL;
  }

  //get the segment address, the formula just *2 because it's in hex and 
  //-3 because proc doesn't seem to output the last 2 bytes (since it's obviously word aligned I guess)
  if (fgets(segment_address, (sizeof(void *)*2)-3, fp)==NULL){
    perror("failed to find existing snapshot\n");
    return NULL;
  }
  else{ 
    seg = malloc(sizeof(conv_seg));
    seg->segment = (void *)strtol(segment_address, NULL, 16);
    seg->name = segment_name;
  }
  //now we need to get the size, so we grab the end address. There is a space in the output so the formula changes by 1
  if (fgets(segment_address, (sizeof(void *)*2)-2, fp)==NULL){
    perror("failed to find existing snapshot\n");
    return NULL;
  }
  else{
    unsigned long end_address = strtol(segment_address, NULL, 16);
    seg->size_of_segment=end_address - (unsigned long)seg->segment;
  }
  /* close */
  pclose(fp);
  //mark it as a snapshot
  madvise(seg->segment, seg->size_of_segment, MADV_KSNAP_ALWAYS);
  madvise(seg->segment, seg->size_of_segment, MADV_KSNAP_TRACK);

  __ksnap_open_meta_data_segments( seg->size_of_segment, segment_name, seg, __CONV_CREATE);
  return seg;
}


//lets update and get a new view of the snapshot
void conv_update(conv_seg * seg){
    if (__newer_version_available(seg)){
        syscall(__CONV_SYS_CALL, seg->segment, CONV_UPDATE, seg->editing_unit);
    }
}

void conv_partial_background_update(conv_seg * seg){
    if ((__get_meta_local_page(seg)->partial_version_num == 0 && __newer_version_available(seg)) || 
        (__get_meta_local_page(seg)->partial_version_num > 0 && (__get_meta_local_page(seg)->partial_version_num < __get_meta_shared_page(seg)->snapshot_version_num))){
        syscall(__CONV_SYS_CALL, seg->segment, CONV_UPDATE_NO_MERGE | CONV_UPDATE_PARTIAL, seg->editing_unit);
    }
}

unsigned int conv_get_partial_version_num(conv_seg * seg){
    return __get_meta_local_page(seg)->partial_version_num;
}

unsigned int conv_get_partial_updated_unique_pages(conv_seg * seg){
    return __get_meta_local_page(seg)->partial_updated_unique_pages;
}

void conv_set_partial_updated_unique_pages(conv_seg * seg, unsigned int val){
    __get_meta_local_page(seg)->partial_updated_unique_pages=val;
}

//performs a commit and a combined update (even if there are no dirty pages)
void conv_commit_and_update(conv_seg * seg){
    if(__get_meta_local_page(seg)->dirty_page_count == 0){
        syscall(__CONV_SYS_CALL, seg->segment, CONV_UPDATE, seg->editing_unit);
    }
    else{
        syscall(__CONV_SYS_CALL, seg->segment, CONV_COMMIT_AND_UPDATE, seg->editing_unit);
    }
}

//thread is temporarily not interested in the happenings of this segment
void conv_sleep(conv_seg * seg){
    madvise(seg->segment, seg->size_of_segment, MADV_KSNAP_SLEEP);
}

//waking up from sleep
void conv_wake(conv_seg * seg){
    madvise(seg->segment, seg->size_of_segment, MADV_KSNAP_WAKE);
}

//prints outs the last several conversion ops to the syslog file.
//the output shows what pages were committed/updated/merged
void conv_print_trace(conv_seg * seg){
    syscall(__CONV_SYS_CALL, seg->segment, CONV_TRACE, 0);
}



//In the case where conversion operations are done inside a critical section (determinism)
//we can get better performance by doing conv_commit_and_update_deferred_start under lock
//and then calling conv_commit_and_update_deferred_end after we release the lock
void conv_commit_and_update_deferred_start(conv_seg * seg){
    if(__get_meta_local_page(seg)->dirty_page_count == 0){
        syscall(__CONV_SYS_CALL, seg->segment, CONV_UPDATE_DEFERRED_START, seg->editing_unit);
    }
    else{
        syscall(__CONV_SYS_CALL, seg->segment, CONV_COMMIT_AND_UPDATE_DEFERRED_START, seg->editing_unit);
    }
}

void conv_commit_and_update_deferred_end(conv_seg * seg){
    if(__get_meta_local_page(seg)->dirty_page_count == 0){
        syscall(__CONV_SYS_CALL, seg->segment, CONV_UPDATE_DEFERRED_END, seg->editing_unit);
    }
    else{
        syscall(__CONV_SYS_CALL, seg->segment, CONV_COMMIT_AND_UPDATE_DEFERRED_END, seg->editing_unit);
    }

}
