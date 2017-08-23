#ifndef LOCK_HASHMAP
#define LOCK_HASHMAP

#include "ticket_lock.h"
#include "linux/jhash.h"

#define LOCK_HASHMAP_MIN_SIZE (128)
#define LOCK_HASHMAP_MAX_SIZE (8192) //512K locks

#define LOCK_ACQUIRE_SUCC (1)
#define LOCK_ACQUIRE_FAILED (0)
#define LOCK_RELEASE_SUCC (1)
#define LOCK_RELEASE_FAILED (1)

#define LOCK_HASHMAP_HOLDER_NONE (-1)

//#define LOCKHASH_TRACK_HISTORY 1

#ifdef LOCKHASH_TRACK_HISTORY
#define LOCK_HISTORY_SIZE 50
#endif

#define LOCKHASH_MAX_THREADS 64

#define LOCK_HASHMAP_MAX_ATTEMPTS (1<<15)

typedef enum {
    LOCK_HASHMAP_TICKET, LOCK_HASHMAP_RW_LOCK
} lock_hashmap_type_t;

typedef enum {
    HISTORY_LOCK_OP_ACQ_SUCC = 0, HISTORY_LOCK_OP_ACQ_FAIL = 1, HISTORY_LOCK_OP_REL = 2, HISTORY_LOCK_OP_REL_NESTED = 3, HISTORY_LOCK_OP_ACQ_NESTED = 4
} history_lock_op_t;

struct lock_hashmap_lock_t{
    struct ticket_lock_t ticket_lock;
    s16 lock_holder;
    u16 acquires_reads[LOCKHASH_MAX_THREADS];
    u16 acquires[LOCKHASH_MAX_THREADS];
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
};

static inline u32 __lock_hashmap_hash(u64 key, u32 mix, u64 size){
    return jhash_2words((u32)key, (u32)(key >> 32), mix) % size;
}


u64 __get_lock_hashmap_size(u64 orecs);

int lock_hashmap_init(struct lock_hashmap_t * lock_hashmap, u64 orecs, u32 mix, lock_hashmap_type_t lock_type);

int lock_hashmap_trylock(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

int lock_hashmap_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry);

void lock_hashmap_init_entry(struct lock_hashmap_entry_t * entry, int thread_id);

int lock_hashmap_trywritelock(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

int lock_hashmap_tryreadlock(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

int lock_hashmap_write_release(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

int lock_hashmap_read_release(struct lock_hashmap_t * lock_hashmap, u64 key, struct lock_hashmap_entry_t * entry);

#endif
