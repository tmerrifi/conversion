
#ifndef KSNAP_H
#define KSNAP_H

#include <linux/wait.h>
#include <linux/slab.h>
#include "cv_meta_data.h"
#include "cv_stats.h"
#include "cv_per_page_version.h"
#include "cv_garbage.h"
#include "cv_hooks.h"
#include "cv_event.h"
#include "cv_profiling.h"

#define SNAPSHOT_PREFIX "snapshot"
#define SNAPSHOT_DEBUG Y

/*operations*/
#define CV_SYNC_TRACE 1

/*Policies specified by the subscribers*/
#define COMMIT_ALWAYS	0x100000
#define COMMIT_ADAPT	0x200000
#define COMMIT_DYN		0x400000
#define COMMIT_INTERVAL_SHIFT 23	

/*flag for snapshots*/
#define SNAP_BLOCKING		0x10
#define SNAP_NONBLOCKING	0x20

/*Used for doing the exponentially weighted moving average*/
#define ADAPT_EWMA_COEFF		20
#define ADAPT_EWMA_FACTOR		100		
#define ADAPT_EWMA_DEFAULT_US 	1000
/*How old is too old for a snapshot when using adapt?*/
#define ADAPT_AGE_FACTOR		3

#define DO_ADAPT_NO_MATTER_WHAT 1 

#define MAX_VERSION_NUM 50000000000ULL

#define KSNAP_LOG_LEVEL KERN_EMERG

#define CV_USER_STATUS_AWAKE 1

#define CV_USER_STATUS_ASLEEP 0




/*a structure that defines a node in the pte list. Each version of the snapshot memory keeps a list
of pte values that have changed. A subscriber traverses the pte_list for each version that has changed
since the last snapshot and then changes it's page table to use the pte's in the list.*/
struct snapshot_pte_list{
    struct list_head list;
    pte_t * pte;	
    unsigned long addr;
    unsigned long pfn;
    unsigned long page_index;
    struct page * ref_page;
    struct snapshot_version_list * version_list; //purly for debugging
    uint64_t wait_revision;
    uint64_t obsolete_version;
    struct mm_struct * mm; //use to do memory accounting
};

/*this structure is a list of snapshot_pte_list objects. Each node in this list represents a version of the
snapshot*/
struct snapshot_version_list{
  struct list_head list;
  struct snapshot_pte_list * pte_list;
  struct snapshot_pte_list * original_pte_list;
  struct snapshot_version_list * uncommitted_version_entry;
  struct snapshot_version_list * latest_version_entry;
  struct vm_area_struct * committer;
  atomic_t ref_c;
  uint64_t version_num;
  unsigned int updated_ptes;
  uint8_t visible;  //is this version available for updating?
  uint32_t num_of_entries; // how many entries are in this version?
};



struct ksnap{
    struct snapshot_version_list * snapshot_pte_list;	/*TODO: change to list_head if that's what we want this to be....*/
    struct radix_tree_root snapshot_page_tree; /*used for keeping track of the current page index -> pte, gets used when we get snapshot*/
    spinlock_t snapshot_page_tree_lock;
    wait_queue_head_t snapshot_wq;		/*wait queue for blocking get_snapshot requests*/
    atomic_t revision_number;			/*the current revision number*/
    atomic_t id_counter;
    struct list_head prio_list; 		/*an ordered list of dynamic priorities*/
    struct timeval last_commit_time;	/*the last time that we committed*/
    struct timeval last_snapshot_time;	/*the last time that a subscriber tried to take a snapshot*/
    uint64_t last_committed_pages_gc_start; /*number of comitted pages last time we started the gc*/
    uint64_t committed_pages;             /* committed pages not yet GC'd*/
    unsigned long ewma_adapt;			/*keeping track of the ewma (in microseconds) of the rate of get_snapshots from subscribers*/
    unsigned long sub_interval; 		/*the amount of time requested by this subscriber*/
    struct list_head segment_list;        /*the vma's mapping this segment*/
    struct kmem_cache * pte_list_mem_cache;
    spinlock_t lock;
    struct cv_statistics cv_stats;
    struct cv_per_process_detailed_statistics cv_per_process_stats[CV_MAX_PER_PROCESS_STATS];
    int creator_id;
    struct cv_per_page_version * ppv;
    struct snapshot_version_list * uncommitted_version_entry;
    uint64_t committed_version_num;
    uint64_t next_avail_version_num;
    atomic_t gc_thread_count;
    volatile uint64_t gc_seq_num;
    struct cv_garbage_work garbage_work;
    atomic64_t committed_version_atomic;
    atomic64_t uncommitted_version_entry_atomic;
    struct timespec last_acq_time;
    int debug_points[32];
    struct conversion_hooks hooks; /*for applications that want to tie into conversion events*/
    void * app_data; /*for applications (ex: determinsim) that want to store segment specific data*/
    struct timespec start_time;
    atomic_t pages_allocated;
    atomic_t max_pages;
};

struct ksnap_user_data{
    unsigned char use_tracking;
    unsigned char use_adapt;              /* which policy does this user want to use? */
    unsigned char use_periodic;
    unsigned char use_always;
    unsigned long periodic_commit_interval;
    void * current_snapshot;
    struct snapshot_pte_list * dirty_pages_list;
    uint32_t dirty_pages_list_count;   //TODO: get rid of the atomic one when you can
    atomic_t dirty_page_count;
    rwlock_t metadata_lock;
    struct list_head segment_list;
    struct vm_area_struct * vma;
    struct ksnap_meta_data_local * meta_data;
    struct ksnap_dirty_list_entry * dirty_list_bitmap;   /*the meta data that is exported to userspace that contains a bitmap (or a list)*/
    struct radix_tree_root dirty_list_lookup; /*find the relevant entry in the dirty list*/
    struct radix_tree_root partial_update_page_lookup;
    int id;
    uint64_t version_num;
    uint64_t partial_version_num; /*keeps track of the version we've done a partial update to*/
    int commits;
    struct timespec last_commit_time;
    uint64_t debug_version_num;
    struct cv_event_info event_info;
    struct ksnap * cv_seg;
    int status;
    struct cv_profiling_ops profiling_info;
};

/*this structure keeps track of commit priorities, when should an owner commit?*/
struct commit_prio_list{
	struct list_head list;
	unsigned long microseconds;
};

struct cv_perthread_debug{
  atomic_t id_counter;
  unsigned long location[3000];
};

extern struct cv_perthread_debug per_thread_debug;

#define CV_DEBUG_AVAIL_THREAD_SLOTS 32
#define CV_DEBUG_NUM_SLOTS 10

#define cv_per_thread_debug_insert(num, spot)				\
  per_thread_debug.location[(current->pid % CV_DEBUG_AVAIL_THREAD_SLOTS)*CV_DEBUG_NUM_SLOTS + spot]=(unsigned long)num;

#define cv_per_thread_debug_inc(spot)				\
  per_thread_debug.location[(current->pid % CV_DEBUG_AVAIL_THREAD_SLOTS)*CV_DEBUG_NUM_SLOTS + spot]++;

#define ksnap_vma_to_ksnap(v) ((struct ksnap *)(((struct address_space *)v->vm_file->f_mapping)->ksnap_data))

#define mapping_to_ksnap(m) ((struct ksnap *)m->ksnap_data)

#define ksnap_vma_to_userdata(v) ((struct ksnap_user_data *)v->ksnap_user_data)

//used to copy a vma's user-specific data when process is forked
void ksnap_userdata_copy (struct vm_area_struct * new_vma, struct vm_area_struct * old_vma);

void cv_close (struct vm_area_struct * vma);

#endif
