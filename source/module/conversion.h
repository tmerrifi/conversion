
#ifndef KSNAP_H
#define KSNAP_H

#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/fs.h>


#include "cv_meta_data.h"
#include "cv_stats.h"
#include "cv_logging.h"
#include "cv_per_page_version.h"
#include "cv_garbage.h"
#include "cv_hooks.h"
#include "cv_event.h"
#include "cv_profiling.h"
#include "cv_defer_work.h"


#define SNAPSHOT_PREFIX "snapshot"
#define SNAPSHOT_DEBUG Y

/*operations*/
#define CV_SYNC_TRACE 1


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
//checkpoint (local commit)
#define CONV_CHECKPOINT 1024


#define CONV_DO_WORK_NOW 0
#define CONV_DEFER_WORK 1

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

#define MAX_VERSION_NUM 100000000000ULL

#define CV_LOG_LEVEL KERN_INFO

#define CV_USER_STATUS_AWAKE 1

#define CV_USER_STATUS_ASLEEP 0

#define LOGGING_SIZE_BYTES (64*8) //one cache line

#define LOGGING_DEBUG_PAGE_INDEX 3
#define LOGGING_DEBUG_INDEX 0
#define LOGGING_DEBUG_LINE 2


struct cv_logging_data_entry{
    uint8_t data[LOGGING_SIZE_BYTES];
};


struct cv_logging_entry{
    uint8_t * data;
    unsigned long addr; //cache line addr
    uint32_t line_index;
    unsigned long data_len;
    uint8_t * local_checkpoint_data;
    uint8_t dirty; //used by checkpoint to make sure we don't checkpoint the same data twice
};

struct cv_page_entry{
    pte_t * pte;	
    unsigned long addr;
    unsigned long pfn;
    struct page * ref_page;
    struct page * local_checkpoint_page;
};

typedef enum{ CV_DIRTY_LIST_ENTRY_TYPE_PAGING=0, CV_DIRTY_LIST_ENTRY_TYPE_LOGGING=1} dirty_list_entry_type;

/*a structure that defines a node in the pte list. Each version of the snapshot memory keeps a list
of pte values that have changed. A subscriber traverses the pte_list for each version that has changed
since the last snapshot and then changes it's page table to use the pte's in the list.*/
struct snapshot_pte_list{
    dirty_list_entry_type type;
    struct list_head list;
    unsigned long page_index;
    uint64_t wait_revision;
    uint64_t obsolete_version;
    uint8_t checkpoint;
    struct mm_struct * mm; //use to do memory accounting
    union{
        struct cv_page_entry page_entry;
        struct cv_logging_entry logging_entry;
    };
};

#define cv_list_entry_get_page_entry(e) ((e) ? &e->page_entry : NULL)

#define cv_list_entry_get_logging_entry(e) ((e) ? &e->logging_entry : NULL)


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

struct cv_logging_page_status_entry{
    unsigned long pfn;
    pte_t * pte;
    uint32_t logging_writes;
    uint32_t entries_allocated;
    unsigned long page_index;
    uint64_t cow_version; //we use this to keep track of the last time we COW'd, which happens after we've forked
    struct snapshot_pte_list * lines[PAGE_SIZE/CV_LOGGING_LOG_SIZE];
    struct snapshot_pte_list * page_entry;
    struct snapshot_pte_list * wait_entry;
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
    struct semaphore sem_gc;
    /*LOGGING FIELDS*/
    uint64_t logging_stats_opcode[256];
    uint64_t logging_stats_opcode_two[256];
    struct radix_tree_root logging_entry_lookup;
    atomic_t logging_pages_count;
    struct kmem_cache * logging_data_entry_mem_cache;
    /***DONE WITH LOGGING***/
    
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
    struct cv_defer_work defer_work;
    struct kmem_cache * deferred_work_mem_cache;
    uint64_t committed_non_logging_entries; //the entries we commit at the page level, used to determine when to test a page for logging
#ifdef CV_DETERMINISM
    uint32_t clock_tick_buffer; //keeps clock ticks buffered for some time
#endif //CV_DETERMINISM
    /********LOGGING STUFF********/
    struct radix_tree_root logging_page_status;
    /******************************/
    uint64_t forked_version_num; //we track the last forked version number so we can CoW logging pages if we need to.
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

#define page_index_to_addr(vma, page) (((page->index << PAGE_SHIFT) + vma->vm_start))

//used to copy a vma's user-specific data when process is forked
void ksnap_userdata_copy (struct vm_area_struct * new_vma, struct vm_area_struct * old_vma);

void cv_close (struct vm_area_struct * vma);

void conv_revert(struct vm_area_struct * vma);

void conv_checkpoint(struct vm_area_struct * vma);

#define conv_get_checkpoint_page(entry) \
    (entry->local_checkpoint_page)

#define conv_is_checkpointed_entry(entry) \
    (entry->local_checkpoint_page!=NULL)

#define conv_set_checkpoint_page(entry, page)        \
    entry->local_checkpoint_page=page;

#define conv_is_checkpointed_logging_entry(entry) \
    (entry->local_checkpoint_data!=NULL)

#define conv_debug_logging_is_line(page_index, line_index) \
    (page_index==LOGGING_DEBUG_PAGE_INDEX && line_index==LOGGING_DEBUG_INDEX)

#ifdef CV_DEBUG_MEMORY_ALLOC
#define conv_debug_memory_alloc(ptr)\
    printk(CV_LOG_LEVEL "allocate: %s %d %p\n", __FILE__, __LINE__, ptr);
#define conv_debug_memory_free(ptr)\
    printk(CV_LOG_LEVEL "free: %s %d %p\n", __FILE__, __LINE__, ptr);
#else
#define conv_debug_memory_alloc(ptr)
#define conv_debug_memory_free(ptr)
#endif



void cv_logging_line_debug_print(struct snapshot_pte_list * dirty_list_entry,
                                 struct cv_logging_entry * logging_entry,
                                 char * message);

#ifdef CONV_LOGGING_ON
#define CV_LOG_MESSAGE(...) printk(CV_LOG_LEVEL __VA_ARGS__)
#elif CONV_LOGGING_ON_TRACE
#define CV_LOG_MESSAGE(...) trace_printk(CV_LOG_LEVEL __VA_ARGS__)
#else
#define CV_LOG_MESSAGE(...)
#endif

#endif
