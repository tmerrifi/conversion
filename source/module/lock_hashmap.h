#ifndef LOCK_HASHMAP
#define LOCK_HASHMAP

#include "ticket_lock.h"
#include "linux/jhash.h"

#define LOCK_HASHMAP_MIN_SIZE (128)
#define LOCK_HASHMAP_MAX_SIZE ((1<<16)) //512K locks

#define LOCK_ACQUIRE_SUCC (1)
#define LOCK_ACQUIRE_FAILED (0)
#define LOCK_RELEASE_SUCC (1)
#define LOCK_RELEASE_FAILED (1)

#define LOCK_HASHMAP_HOLDER_NONE (-1)

//#define LOCKHASH_TRACK_HISTORY 1

#ifdef LOCKHASH_TRACK_HISTORY
#define LOCK_HISTORY_SIZE 50
#endif

#define LOCKHASH_MAX_THREADS 128

#define LOCK_HASHMAP_MAX_ATTEMPTS (1<<15)

typedef enum {
   LOCK_HASHMAP_ACQ_ONLY_GET_TICKET, LOCK_HASHMAP_ACQ_NORMAL
} lock_hashmap_acq_mode_t;

typedef enum {
    LOCK_HASHMAP_TICKET, LOCK_HASHMAP_RW_LOCK
} lock_hashmap_type_t;

typedef enum {
    HISTORY_LOCK_OP_ACQ_SUCC = 0, HISTORY_LOCK_OP_ACQ_FAIL = 1, HISTORY_LOCK_OP_REL = 2, HISTORY_LOCK_OP_REL_NESTED = 3, HISTORY_LOCK_OP_ACQ_NESTED = 4
} history_lock_op_t;

struct __attribute__ ((__packed__)) lock_hashmap_reentrace_counter_t{
    u16 counter;
    //u8 padding[64 - sizeof(u16)];
};

struct __attribute__ ((__packed__)) lock_hashmap_lock_t{
    struct ticket_lock_t ticket_lock; //TICKET_LOCK_SIZE
    s16 lock_holder; //2
    struct lock_hashmap_reentrace_counter_t num_acquires_reads[LOCKHASH_MAX_THREADS]; //2*128=
    struct lock_hashmap_reentrace_counter_t num_acquires[LOCKHASH_MAX_THREADS]; //2*128=
#ifdef LOCKHASH_TRACK_HISTORY 
    u64 history_lock_ticket[LOCK_HISTORY_SIZE];
    u64 history_lock_holders[LOCK_HISTORY_SIZE];
    int history_lock_acquires[LOCK_HISTORY_SIZE];
    int history_lock_op[LOCK_HISTORY_SIZE];
    int history_lock_mode[LOCK_HISTORY_SIZE];
    int history_lock_threadid[LOCK_HISTORY_SIZE];
    atomic64_t history_lock_count;
#endif
};

//BUILD_BUG_ON(sizeof(lock_hashmap_lock_t) != 64);

struct lock_hashmap_t{
    u64 total_locks;
    struct lock_hashmap_lock_t * locks;
    u32 mix;
    lock_hashmap_type_t lock_type;
};

struct lock_hashmap_entry_t{
    struct ticket_lock_entry_t ticket_entry;
    int thread_id;
    int attempts;
    int succeeded;
};

static inline u32 __lock_hashmap_hash(u64 key, u32 mix, u64 size){
    return jhash_2words((u32)key, (u32)(key >> 32), mix) % size;
}

static inline void __lock_hashmap_inc_acquire_read(struct lock_hashmap_lock_t * lock, int thread_id){
    lock->num_acquires_reads[thread_id].counter++;
}

static inline void __lock_hashmap_dec_acquire_read(struct lock_hashmap_lock_t * lock, int thread_id){
    lock->num_acquires_reads[thread_id].counter--;
}

static inline u16 __lock_hashmap_get_acquire_read(struct lock_hashmap_lock_t * lock, int thread_id){
    return lock->num_acquires_reads[thread_id].counter;
}

static inline void __attribute__((always_inline)) __lock_hashmap_inc_acquire(struct lock_hashmap_lock_t * lock, int thread_id){
    lock->num_acquires[thread_id].counter++;
}

static inline void __lock_hashmap_dec_acquire(struct lock_hashmap_lock_t * lock, int thread_id){
    lock->num_acquires[thread_id].counter--;
}

static inline u16 __lock_hashmap_get_acquire(struct lock_hashmap_lock_t * lock, int thread_id){
    return lock->num_acquires[thread_id].counter;
}

static inline void __attribute__((always_inline)) __lock_hashmap_init_acquire(struct lock_hashmap_lock_t * lock){
    int j;
    for (j = 0; j < LOCKHASH_MAX_THREADS; j++) {
	lock->num_acquires[j].counter = 0;
	lock->num_acquires_reads[j].counter = 0;
    }
}

static inline void lock_hashmap_prefetch_lock(struct lock_hashmap_t * lock_hashmap, uint64_t key){
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
    prefetchw(lock);
}

static inline struct lock_hashmap_lock_t * lock_hashmap_get_ticket_lock(struct lock_hashmap_t * lock_hashmap, uint64_t key){
   u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
   return &lock_hashmap->locks[index];
}

static inline int lock_hashmap_is_lock_entry_held(struct lock_hashmap_entry_t * entry){
   return entry->succeeded;
}

static inline int lock_hashmap_set_lock_entry_held(struct lock_hashmap_entry_t * entry){
   entry->succeeded = 1;
}

static inline int lock_hashmap_set_lock_entry_free(struct lock_hashmap_entry_t * entry){
   entry->succeeded = 0;
}


static inline int __attribute__((always_inline)) lock_hashmap_trywritelock(struct lock_hashmap_t * lock_hashmap, u64 key, 
                                            struct lock_hashmap_entry_t * entry, lock_hashmap_acq_mode_t acq_mode){

   u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
   struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
   int result = LOCK_ACQUIRE_FAILED;

    if (__lock_hashmap_get_acquire(lock, entry->thread_id) > 0) {
	//we already hold the lock as a writer
	__lock_hashmap_inc_acquire(lock, entry->thread_id);
	result = LOCK_ACQUIRE_SUCC;
    }
    else{
	//we allow it to enter here even if we currently hold the lock for read.
	//In that case, we still attempt to acquire the lock in order to get a ticket
	//to preserve the order of committers
	if (result = ticket_lock_trywritelock(&lock->ticket_lock, &entry->ticket_entry, 
                          (acq_mode == LOCK_HASHMAP_ACQ_ONLY_GET_TICKET) ? 
                           TICKET_LOCK_ACQ_ONLY_GET_TICKET : TICKET_LOCK_ACQ_NORMAL)){
	    __lock_hashmap_inc_acquire(lock, entry->thread_id);
	}
    }

    return result;

}

u64 __get_lock_hashmap_size(u64 orecs);

int lock_hashmap_init(struct lock_hashmap_t * lock_hashmap, u64 orecs, u32 mix, lock_hashmap_type_t lock_type);

int lock_hashmap_trylock(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry, lock_hashmap_acq_mode_t acq_mode);

int lock_hashmap_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry);

void lock_hashmap_init_entry(struct lock_hashmap_entry_t * entry, int thread_id);

int lock_hashmap_tryreadlock(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry, lock_hashmap_acq_mode_t acq_mode);

int lock_hashmap_write_release(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

int lock_hashmap_read_release(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

#endif