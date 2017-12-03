
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/mm.h>

#include "ticket_lock.h"
#include "lock_hashmap.h"

u64 __get_lock_hashmap_size(u64 orecs){
    u64 size=0;

    if (orecs < LOCK_HASHMAP_MIN_SIZE) {
	size = LOCK_HASHMAP_MIN_SIZE;
    }
    else if (orecs > LOCK_HASHMAP_MAX_SIZE) {
	size = LOCK_HASHMAP_MAX_SIZE;
    }
    else{
	size = (orecs >> 4);
    }

    return size;
}

int __lock_hashmap_init_ticket(struct lock_hashmap_t * lock_hashmap, lock_hashmap_type_t lock_type){
    int i;
    int j;

    ticket_lock_mode_t mode;
    
    if ((lock_hashmap->locks = kmalloc(lock_hashmap->total_locks * 
				       sizeof(struct lock_hashmap_lock_t) + 64, GFP_KERNEL)) == NULL ){
	printk(KERN_EMERG "__lock_hashmap_init_ticket: initialization kmalloc failed\n" );
	return 0;
    }

    for ( i = 0; i < lock_hashmap->total_locks; i++ ) {
	switch (lock_type) {
	case LOCK_HASHMAP_TICKET: 
	    mode = TICKET_LOCK_MODE_NORMAL;
	    break;
	case LOCK_HASHMAP_RW_LOCK:
	    mode = TICKET_LOCK_MODE_RWLOCK;
	    break;
	default:
	    BUG();
	}
	lock_hashmap->locks[i].lock_holder = LOCK_HASHMAP_HOLDER_NONE;

	for (j = 0; j < LOCKHASH_MAX_THREADS; j++) {
	    __lock_hashmap_init_acquire(&lock_hashmap->locks[i]);
	}

	ticket_lock_init(&lock_hashmap->locks[i].ticket_lock, mode);
	#ifdef LOCKHASH_TRACK_HISTORY
	atomic64_set(&lock_hashmap->locks[i].history_lock_count, 0);
	for (j = 0; j < LOCK_HISTORY_SIZE; j++) {
	    lock_hashmap->locks[i].history_lock_op[j] = -1;
	}
	#endif
    }
    
    return 1;
}


int lock_hashmap_init(struct lock_hashmap_t * lock_hashmap, uint64_t orecs, u32 mix, lock_hashmap_type_t lock_type){
    int result;
    lock_hashmap->mix = mix;
    lock_hashmap->total_locks = __get_lock_hashmap_size(orecs);
    lock_hashmap->lock_type = lock_type;
//  printk(KERN_EMERG "lock_hashmap init: size %llu %llu %u total: %lu\n",
//         lock_hashmap->total_locks, orecs, sizeof(struct lock_hashmap_lock_t),
//         lock_hashmap->total_locks * sizeof(struct lock_hashmap_lock_t) );
    return __lock_hashmap_init_ticket(lock_hashmap, lock_type);
}

void __print_history(struct lock_hashmap_lock_t * lock){
    #ifdef LOCKHASH_TRACK_HISTORY
    int i = 0; 
    printk(KERN_EMERG "************HISTORY: current: %llu ************\n", (u64)atomic64_read(&lock->history_lock_count));
    for (; i < LOCK_HISTORY_SIZE; i++ ) {
	printk(KERN_EMERG "i: %d\n", i);
	printk(KERN_EMERG "op: %llu ", lock->history_lock_op[i]);
	printk(KERN_EMERG "holder: %d \n", lock->history_lock_holders[i]);
	printk(KERN_EMERG "ticket: %llu \n", lock->history_lock_ticket[i]);
	printk(KERN_EMERG "mode: %d \n", lock->history_lock_mode[i]);
	printk(KERN_EMERG "acquire: %d \n", lock->history_lock_acquires[i]);
	printk(KERN_EMERG "thread_id: %d \n", lock->history_lock_threadid[i]);
	printk(KERN_EMERG "***********************************");
    }
    printk(KERN_EMERG "*********HISTORY DONE*********\n");
    #endif
}

void __insert_into_history(struct lock_hashmap_lock_t * lock, history_lock_op_t op, 
			   int holder, u64 ticket, int mode, int acquires, int thread_id){
    #ifdef LOCKHASH_TRACK_HISTORY
    u64 index = (u64)atomic64_inc_return(&lock->history_lock_count);
    lock->history_lock_op[index % LOCK_HISTORY_SIZE] = op;
    lock->history_lock_holders[index % LOCK_HISTORY_SIZE] = holder;
    lock->history_lock_ticket[index % LOCK_HISTORY_SIZE] = ticket;
    lock->history_lock_mode[index % LOCK_HISTORY_SIZE] = mode;
    lock->history_lock_acquires[index % LOCK_HISTORY_SIZE] = acquires;
    lock->history_lock_threadid[index % LOCK_HISTORY_SIZE] = thread_id;
    #endif
}

static inline int __lock_hashmap_trylock_read(struct lock_hashmap_lock_t * lock, 
                                              struct lock_hashmap_entry_t *entry, 
                                              int thread_id,
                                              int (*func)(struct ticket_lock_t *, 
                                                             struct ticket_lock_entry_t *, 
                                                             ticket_lock_acq_mode_t mode),
                                              lock_hashmap_acq_mode_t acq_mode){
    history_lock_op_t history_op;
    int result = LOCK_ACQUIRE_FAILED;

    if (__lock_hashmap_get_acquire_read(lock, thread_id) > 0) {
	//we already hold the lock as a reader
	__lock_hashmap_inc_acquire_read(lock, thread_id);

	result = LOCK_ACQUIRE_SUCC;
	history_op = HISTORY_LOCK_OP_ACQ_NESTED;
    }
    else{
	if (result = func(&lock->ticket_lock, &entry->ticket_entry,
                          (acq_mode == LOCK_HASHMAP_ACQ_ONLY_GET_TICKET) ? 
                           TICKET_LOCK_ACQ_ONLY_GET_TICKET : TICKET_LOCK_ACQ_NORMAL)){
	    __lock_hashmap_inc_acquire_read(lock, thread_id);
	    history_op = HISTORY_LOCK_OP_ACQ_SUCC;
	}
	else{
	    history_op = HISTORY_LOCK_OP_ACQ_FAIL;
	}
    }
    
    __insert_into_history(lock, history_op, lock->lock_holder, 
			  entry->ticket_entry.our_ticket, TICKET_LOCK_OP_NORMAL,
			  __lock_hashmap_get_acquire(lock, thread_id), thread_id);
    
    return result;
}

static inline int __lock_hashmap_trylock_write(struct lock_hashmap_lock_t * lock, 
                                               struct lock_hashmap_entry_t *entry, 
                                               int thread_id,
                                               int (*func)(struct ticket_lock_t *, 
                                                             struct ticket_lock_entry_t *, 
                                                             ticket_lock_acq_mode_t mode),
                                               lock_hashmap_acq_mode_t acq_mode){
    history_lock_op_t history_op;
    int result = LOCK_ACQUIRE_FAILED;

    if (__lock_hashmap_get_acquire(lock, thread_id) > 0) {
	//we already hold the lock as a writer
	__lock_hashmap_inc_acquire(lock, thread_id);
	result = LOCK_ACQUIRE_SUCC;
	history_op = HISTORY_LOCK_OP_ACQ_NESTED;
    }
    else{
	//we allow it to enter here even if we currently hold the lock for read.
	//In that case, we still attempt to acquire the lock in order to get a ticket
	//to preserve the order of committers
	if (result = func(&lock->ticket_lock, &entry->ticket_entry, 
                          (acq_mode == LOCK_HASHMAP_ACQ_ONLY_GET_TICKET) ? 
                           TICKET_LOCK_ACQ_ONLY_GET_TICKET : TICKET_LOCK_ACQ_NORMAL)){
	    __lock_hashmap_inc_acquire(lock, thread_id);
	    history_op = HISTORY_LOCK_OP_ACQ_SUCC;
	}
	else{
	    history_op = HISTORY_LOCK_OP_ACQ_FAIL;
	}
    }

    __insert_into_history(lock, history_op, lock->lock_holder, 
			  entry->ticket_entry.our_ticket, TICKET_LOCK_OP_NORMAL,
			  __lock_hashmap_get_acquire(lock, thread_id), thread_id);
    
    return result;
}

static inline int __lock_hashmap_trylock_basic(struct lock_hashmap_lock_t * lock, 
                                               struct lock_hashmap_entry_t *entry, 
                                               int thread_id,
                                               int (*func)(struct ticket_lock_t *, 
                                                             struct ticket_lock_entry_t *, 
                                                             ticket_lock_acq_mode_t mode),
                                               lock_hashmap_acq_mode_t acq_mode){
    history_lock_op_t history_op;
    int result = LOCK_ACQUIRE_FAILED;

    if (__lock_hashmap_get_acquire(lock, thread_id) > 0) {
	result = LOCK_ACQUIRE_SUCC;
	__lock_hashmap_inc_acquire(lock, thread_id);
	history_op = HISTORY_LOCK_OP_ACQ_NESTED;

    }
    else if (result = func(&lock->ticket_lock, 
                           &entry->ticket_entry, 
                           (acq_mode == LOCK_HASHMAP_ACQ_ONLY_GET_TICKET) ? 
                           TICKET_LOCK_ACQ_ONLY_GET_TICKET : TICKET_LOCK_ACQ_NORMAL)) {
	//on successful acquisition, make sure there is no current lock holder
	if (lock->lock_holder != LOCK_HASHMAP_HOLDER_NONE){
	    __print_history(lock);
	    BUG();
	}
	//set lock holder for debugging
	lock->lock_holder = entry->thread_id;
	__lock_hashmap_inc_acquire(lock, thread_id);
	history_op = (result) ? HISTORY_LOCK_OP_ACQ_SUCC : HISTORY_LOCK_OP_ACQ_FAIL;
    }

    __insert_into_history(lock, history_op, lock->lock_holder, 
			  entry->ticket_entry.our_ticket, TICKET_LOCK_OP_NORMAL,
			  __lock_hashmap_get_acquire(lock, thread_id), thread_id);

    return result;
}

static inline int __lock_hashmap_trylock_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
                                                 int (*func)(struct ticket_lock_t *, 
                                                             struct ticket_lock_entry_t *, 
                                                             ticket_lock_acq_mode_t mode),
                                   int mode,
                                   lock_hashmap_acq_mode_t acq_mode){

    int thread_id = entry->thread_id;
    //lets make sure the thread_id isn't too large
    BUG_ON(thread_id > LOCKHASH_MAX_THREADS-1 || thread_id < 0);

    int result = LOCK_ACQUIRE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];

    switch (mode) {
    case TICKET_LOCK_OP_NORMAL:
	result = __lock_hashmap_trylock_basic(lock, entry, thread_id, func, acq_mode);
	break;
    case TICKET_LOCK_OP_WRITE:
	result = __lock_hashmap_trylock_write(lock, entry, thread_id, func, acq_mode);
	break;
    case TICKET_LOCK_OP_READ: 
	result = __lock_hashmap_trylock_read(lock, entry, thread_id, func, acq_mode);
	break;
    default:
	BUG();
	break;
    }
 
    return result;
}

int __lock_hashmap_release_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
				   int (*func) (struct ticket_lock_t *, struct ticket_lock_entry_t *), 
				   int mode){

    history_lock_op_t history_op;
    int thread_id = entry->thread_id;
    int result = LOCK_RELEASE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];

    //lets make sure the thread_id isn't too large or too small
    BUG_ON(thread_id > LOCKHASH_MAX_THREADS-1 || thread_id < 0);

    if (mode == TICKET_LOCK_OP_NORMAL || mode == TICKET_LOCK_OP_WRITE){
	BUG_ON(__lock_hashmap_get_acquire(lock, thread_id) == 0);
	__lock_hashmap_dec_acquire(lock,thread_id);
	if (__lock_hashmap_get_acquire(lock,thread_id) == 0) {
	    //only remove lock holder if number of acquires == 0
	    lock->lock_holder = LOCK_HASHMAP_HOLDER_NONE;
	    result = func(&lock->ticket_lock, &entry->ticket_entry);
	    history_op = HISTORY_LOCK_OP_REL;
	}
	else{
	    history_op = HISTORY_LOCK_OP_REL_NESTED;
	}
    } 
    else if (mode == TICKET_LOCK_OP_READ) {
	BUG_ON(__lock_hashmap_get_acquire_read(lock, thread_id) == 0);
	__lock_hashmap_dec_acquire_read(lock, thread_id);
	if (__lock_hashmap_get_acquire_read(lock, thread_id) == 0) {
	    //only remove lock holder if number of acquires_reads == 0
	    result = func(&lock->ticket_lock, &entry->ticket_entry);
	    history_op = HISTORY_LOCK_OP_REL;
	}
	else{
	    history_op = HISTORY_LOCK_OP_REL_NESTED;
	}
    }

    __insert_into_history(lock, history_op,
			  lock->lock_holder, 
			  entry->ticket_entry.our_ticket, 
			  mode,__lock_hashmap_get_acquire(lock, thread_id), thread_id);

    return result;
}

int lock_hashmap_trylock(struct lock_hashmap_t * lock_hashmap, 
                         uint64_t key, 
                         struct lock_hashmap_entry_t * entry,
                         lock_hashmap_acq_mode_t acq_mode){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, 
                                          ticket_lock_trylock, 
                                          TICKET_LOCK_OP_NORMAL,
                                          acq_mode);
}

int lock_hashmap_trywritelock(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
                              struct lock_hashmap_entry_t * entry,
                              lock_hashmap_acq_mode_t acq_mode){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, 
                                          ticket_lock_trywritelock, 
                                          TICKET_LOCK_OP_WRITE,
                                          acq_mode);
}

int lock_hashmap_tryreadlock(struct lock_hashmap_t * lock_hashmap, 
                             uint64_t key, 
                             struct lock_hashmap_entry_t * entry,
                             lock_hashmap_acq_mode_t acq_mode){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, 
                                          ticket_lock_tryreadlock, 
                                          TICKET_LOCK_OP_READ,
                                          acq_mode);
}

int lock_hashmap_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_release, TICKET_LOCK_OP_NORMAL);
}

int lock_hashmap_write_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_write_release, TICKET_LOCK_OP_WRITE);
}

int lock_hashmap_read_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_read_release, TICKET_LOCK_OP_READ);
}

void lock_hashmap_init_entry(struct lock_hashmap_entry_t * entry, int thread_id){
    entry->thread_id = thread_id;
    entry->attempts = 0;
    entry->succeeded = 0;
    ticket_lock_init_entry(&entry->ticket_entry);
}

