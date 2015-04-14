
#ifdef __cplusplus
 extern "C" {
#endif

#ifndef KSNAP_H
#define KSNAP_H

#include <semaphore.h>
#include <stdint.h>

#include "shmUtility.h"
#include "bitmap.h"


typedef struct{
  int size_of_segment;
  void * segment;
  int fd;
  char * name;
  char * file_name;
  sem_t * cv_sem;
  size_t editing_unit;
}conv_seg;

struct ksnap_meta_data_local{
    unsigned int meta_data_size; //in pages
    unsigned char dirty_list_mode; //bitmap or list
    unsigned int dirty_page_count; 
    unsigned int dirty_list_size; //how many pages can we fit in it?
    unsigned int snapshot_version_num; //the current version number
    unsigned int partial_version_num; //set after doing a partial update
    unsigned int updated_pages; //the number of pages updated by the last update
    unsigned int partial_updated_unique_pages; //unique updated pages from multiple calls to partial_update
    unsigned int merged_pages; //the number of pages updated by the last update
    unsigned int pid;
};

struct ksnap_meta_data_shared{
    unsigned int snapshot_version_num;
    unsigned int linearized_version_num; /*a version number set once a commit has been linearized*/
    unsigned int logical_page_count; /*How many pages in our segment have *some* physical frame that has been committed.*/
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
#define MADV_KSNAP_SLEEP 203
#define MADV_KSNAP_WAKE 204
#define MADV_KSNAP_TRACK 210


     //perform a combined update and commit
#define CONV_COMMIT_AND_UPDATE 1
     //perform a normal update without committing. Merges your working set with committed data
#define CONV_UPDATE 2
     //performs an update without committing. Doesn't merge your data with committed
#define CONV_UPDATE_NO_MERGE 4
     //do an update without merging but don't actually move the version ahead.
#define CONV_UPDATE_PARTIAL 8
     //performs a deferred work commit and update (see function for details)
#define CONV_COMMIT_AND_UPDATE_DEFERRED_START 16
     //performs a deferred work commit and update (see function for details)
#define CONV_COMMIT_AND_UPDATE_DEFERRED_END 32
     //performs a deferred work update (see function for details)
#define CONV_UPDATE_DEFERRED_START 64
     //performs a deferred work update (see function for details)
#define CONV_UPDATE_DEFERRED_END 128
     //print out a trace of debugging info
#define CONV_TRACE 256
     //revert the current working set
#define CONV_REVERT 512
     
#define META_LOCAL_OFFSET_FROM_SEGMENT 4
#define META_SHARED_OFFSET_FROM_SEGMENT 2


#define __get_meta_local_page(seg) ((struct ksnap_meta_data_local *)((unsigned char *)seg->segment - KSNAP_PAGE_SIZE*(META_LOCAL_OFFSET_FROM_SEGMENT)))
#define __get_meta_shared_page(seg) ((struct ksnap_meta_data_shared *)((unsigned char *)seg->segment - KSNAP_PAGE_SIZE*(META_SHARED_OFFSET_FROM_SEGMENT)))
   
#define conv_get_current_version_num(seg) (__get_meta_local_page(seg)->snapshot_version_num)
#define conv_get_committed_version_num(seg) (__get_meta_shared_page(seg)->snapshot_version_num)

#define __newer_version_available(seg) (__get_meta_local_page(seg)->snapshot_version_num < __get_meta_shared_page(seg)->snapshot_version_num)

     //create a new segment, give it a name and address.
     conv_seg * conv_checkout_create(int size_of_segment, char * segment_name, void * desired_address);

     //NOT CURRENTLY AVAILABLE
     void conv_set_editing_unit_bytes(conv_seg * seg, size_t editing_unit);

     //the main conversion function a program will use. When conv_fence returns a new version has been created and any
     //modifications by commits with a lower version number are now visible in your local copy. This is a combined
     //update/commit as described in the paper.
     void conv_fence(conv_seg * seg);

     //performs just an update...doesn't commit your changes and merges with your current change set
     void conv_update(conv_seg * seg);

     //does the same thing as conv_fence (just a longer and more specific name). Kept around to support some earlier 
     //software that used this function.
     void conv_commit_and_update(conv_seg * seg);

     //The garbage collector won't collect any versions with a higher version number than minimum version number
     //for all "active" threads. For example, if the parent thread goes to is sleeping (waiting on a condition
     //variable or joining) than any subsequent versions won't be collected. By calling conv_sleep, that is a hint
     //to conversion that we don't need to worry about concurrent updates from this thread. We can collect obsolete
     //versions without considering this thread's version number. conv_wake undoes this bahavior.
     void conv_sleep(conv_seg * seg);
     void conv_wake(conv_seg * seg);

     //In the case where conversion operations are done inside a critical section (determinism)
     //we can get better performance by doing conv_commit_and_update_deferred_start under lock
     //and then calling conv_commit_and_update_deferred_end after we release the lock
     void conv_commit_and_update_deferred_start(conv_seg * seg);
     void conv_commit_and_update_deferred_end(conv_seg * seg);

     //Allow a segment to perform updates (no merging) without actually rev'ing the version number.
     //This is useful if some thread is waiting for another to commit, but knows it has lots of work
     //to do to catch-up to the current version. It can perform the partial update safely while it waits.
     void conv_partial_background_update(conv_seg * seg);

     //how many pages in the segment have been touched in this segment by all processes?
     unsigned int conv_get_logical_page_count(conv_seg * seg);

     //how many pages are currently dirty
     unsigned int conv_get_dirty_page_count(conv_seg * seg); 

     //how many pages did we retrieve on our last commit?
     unsigned int conv_get_updated_page_count(conv_seg * seg);

     //how many pages were merged on our last commit?
     unsigned int conv_get_merged_page_count(conv_seg * seg);

     //some specialized functions used for DMT (deterministic multi-threading)
     void conv_set_partial_updated_unique_pages(conv_seg * seg, unsigned int val);
     unsigned int conv_get_partial_updated_unique_pages(conv_seg * seg);
     unsigned int conv_get_partial_version_num(conv_seg * seg);
     unsigned int conv_get_linearized_version_num(conv_seg * seg);

     
     void conv_clear_local_stats(conv_seg * seg);
     void conv_print_trace(conv_seg * seg);

     void conv_revert(conv_seg * seg);
     
#define KSNAP_OWNER SHM_CORE
#define KSNAP_READER SHM_CLIENT
#define KSNAP_SHARED SHM_SHARED

#define KSNAP_DEBUG 1
#define KSNAP_NO_DEBUG 0


     /*#define KSNAP_SYNC_TRACE 1
#define KSNAP_SYNC_GET 8
#define KSNAP_SYNC_MAKE 16
#define KSNAP_SYNC_MERGE 32
#define KSNAP_SYNC_PARTIAL 64
#define CONVERSION_DETERM_TOKEN_RELEASE 128*/

#define KSNAP_NO_SYNC MS_SYNC

#endif

#ifdef __cplusplus
 }
#endif
