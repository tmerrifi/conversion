
#ifdef __cplusplus
 extern "C" {
#endif

#ifndef KSNAP_H
#define KSNAP_H

#include <semaphore.h>

#include "shmUtility.h"
#include "bitmap.h"


typedef struct{
  int size_of_segment;
  void * segment;
  int fd;
  char * name;
  char * file_name;
  sem_t * cv_sem;
}conv_seg;

struct ksnap_meta_data_local{
  unsigned int meta_data_size; //in pages
  unsigned char dirty_list_mode; //bitmap or list
  unsigned int dirty_page_count; 
  unsigned int dirty_list_size; //how many pages can we fit in it?
  unsigned int snapshot_version_num; //the current version number
};

struct ksnap_meta_data_shared{
  unsigned int snapshot_version_num;
};

struct ksnap_dirty_list_entry{
  unsigned int page_index;
};

#define DIRTY_LIST_LISTMODE 0
#define DIRTY_LIST_BITMAPMODE 1

#define KSNAP_PAGE_SIZE 4096

#define MADV_KSNAP_ALWAYS 200
#define MADV_KSNAP_ADAPT 201
#define MADV_KSNAP_PERIODIC 202
#define MADV_KSNAP_TURNOFF 203
#define MADV_KSNAP_TRACK 210

#define META_LOCAL_OFFSET_FROM_SEGMENT 4
#define META_SHARED_OFFSET_FROM_SEGMENT 2


#define __get_meta_local_page(snap) ((struct ksnap_meta_data_local *)((unsigned char *)snap->segment - KSNAP_PAGE_SIZE*(META_LOCAL_OFFSET_FROM_SEGMENT)))
#define __get_meta_shared_page(snap) ((struct ksnap_meta_data_shared *)((unsigned char *)snap->segment - KSNAP_PAGE_SIZE*(META_SHARED_OFFSET_FROM_SEGMENT)))
   
   
   conv_seg * conv_checkout_create(int size_of_segment, char * segment_name, void * desired_address, uint64_t flags);
   conv_seg * conv_open(int size_of_segment, char * segment_name, void * desired_address);
   
   conv_seg * conv_open_exisiting(char * segment_name);
   
   void conv_update(conv_seg * seg);
   void conv_update_mutex(conv_seg * seg, sem_t * sem);

   void conv_merge(conv_seg * seg);

   void conv_commit(conv_seg * seg);
   void conv_commit_mutex(conv_seg * seg, sem_t * sem);

   /*functions for use only by dthreads*/
   void conv_update_only_barrier_determ(conv_seg * seg);
   void conv_merge_barrier_determ(conv_seg * seg);
   void conv_commit_barrier_determ(conv_seg * seg);
   //void conv_commit_and_sync(conv_seg * seg, int debug_it);

#define KSNAP_OWNER SHM_CORE
#define KSNAP_READER SHM_CLIENT
#define KSNAP_SHARED SHM_SHARED

#define KSNAP_DEBUG 1
#define KSNAP_NO_DEBUG 0


#define KSNAP_SYNC_GET 8
#define KSNAP_SYNC_MAKE 16
#define KSNAP_SYNC_MERGE 32
#define KSNAP_SYNC_BARRIER_DETERM 64

#define KSNAP_NO_SYNC MS_SYNC

#endif

#ifdef __cplusplus
 }
#endif
