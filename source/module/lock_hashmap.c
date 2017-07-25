
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
    ticket_lock_mode_t mode;

    if ((lock_hashmap->locks = kmalloc(lock_hashmap->total_locks * sizeof(struct lock_hashmap_lock_t),  
				       GFP_KERNEL)) == NULL ){
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
	lock_hashmap->locks[i].acquires = 0;
	ticket_lock_init(&lock_hashmap->locks[i].ticket_lock, mode);
	#ifdef LOCKHASH_TRACK_HISTORY
	atomic64_set(&lock_hashmap->locks[i].history_lock_count, 0);
	#endif
    }
    return 1;
}


int lock_hashmap_init(struct lock_hashmap_t * lock_hashmap, uint64_t orecs, u32 mix, lock_hashmap_type_t lock_type){
    int result;
    lock_hashmap->mix = mix;
    lock_hashmap->total_locks = __get_lock_hashmap_size(orecs);
    lock_hashmap->lock_type = lock_type;
    printk(KERN_INFO "lock_hashmap init: size %llu\n", lock_hashmap->total_locks);
    return __lock_hashmap_init_ticket(lock_hashmap, lock_type);
}

void __print_history(struct lock_hashmap_lock_t * lock){
    #ifdef LOCKHASH_TRACK_HISTORY
    int i = 0; 
    printk(KERN_EMERG "************HISTORY************\n");
    for (; i < LOCK_HISTORY_SIZE; i++ ) {
	printk(KERN_EMERG "op: %llu ", lock->history_lock_op[i]);
	printk(KERN_EMERG "op: %d ", lock->history_lock_acquires[i]);
	printk(KERN_EMERG "op: %d \n", lock->history_lock_holders[i]);
    }
    printk(KERN_EMERG "*********HISTORY DONE*********\n");
    #endif
}

void __insert_into_history(struct lock_hashmap_lock_t * lock, history_lock_op_t op, int acquires, int holder){
    #ifdef LOCKHASH_TRACK_HISTORY
    u64 index = (u64)atomic64_inc_return(&lock->history_lock_count);
    lock->history_lock_op[index % LOCK_HISTORY_SIZE] = op;
    lock->history_lock_acquires[index % LOCK_HISTORY_SIZE] = acquires;
    lock->history_lock_holders[index % LOCK_HISTORY_SIZE] = holder;
    #endif
}

int __lock_hashmap_trylock_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
				   int (*func) (struct ticket_lock_t *, struct ticket_lock_entry_t *)){
    int result = LOCK_ACQUIRE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
    //make sure we don't already hold this lock_hashmap
    if (lock->lock_holder == entry->thread_id) {
	result = LOCK_ACQUIRE_SUCC;
	lock->acquires++;
	BUG_ON(lock->acquires < 1);
    }
    else{
	result = func(&lock->ticket_lock, &entry->ticket_entry);
	if (result) {
	    //set lock holder for reentrance
	    lock->lock_holder = entry->thread_id;
	    lock->acquires++;
	}
    }

    __insert_into_history(lock, (result) ? HISTORY_LOCK_OP_ACQ_SUCC : HISTORY_LOCK_OP_ACQ_FAIL, 
			  lock->acquires, lock->lock_holder);

//    printk(KERN_EMERG "trylock....index: %u %p lock %p thread_id %d holder %d acquires %d result %d\n",
//	   index, entry, lock, entry->thread_id, lock->lock_holder, lock->acquires, result);
    return result;
}

int __lock_hashmap_release_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
				   int (*func) (struct ticket_lock_t *, struct ticket_lock_entry_t *)){
    int result = LOCK_RELEASE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
    if (lock->lock_holder != entry->thread_id) {
	printk(KERN_EMERG " holder %d thread %d lock %p acquires %d\n", 
	       lock->lock_holder, entry->thread_id, lock, lock->acquires);
	__print_history(lock);
	BUG();
    }
    else{
	BUG_ON(lock->lock_holder != entry->thread_id);
	BUG_ON(lock->acquires < 1);
	if (--lock->acquires == 0) {
	    //only remove lock holder if number of acquires == 0
	    lock->lock_holder = LOCK_HASHMAP_HOLDER_NONE;
	    __insert_into_history(lock, HISTORY_LOCK_OP_REL,
				  lock->acquires, lock->lock_holder);
	    result = func(&lock->ticket_lock, &entry->ticket_entry);
	    //	printk(KERN_EMERG "release....index: %u %p lock %p thread_id %d holder %d acquires %d result %d\n",
	    //	       index, entry, lock, entry->thread_id, lock->lock_holder, lock->acquires, result);
	}
	else{
	    //HISTORY_LOCK_OP_REL_NESTED
	    __insert_into_history(lock, HISTORY_LOCK_OP_REL_NESTED,
				  lock->acquires, lock->lock_holder);
	    //	printk(KERN_EMERG "release nested....index: %u %p lock %p thread_id %d holder %d acquires %d result %d\n",
	    //	index, entry, lock, entry->thread_id, lock->lock_holder, lock->acquires, result);
	}
    }

    return result;
}

int lock_hashmap_trylock(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, ticket_lock_trylock);
}

int lock_hashmap_trywritelock(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, ticket_lock_trywritelock);
}

int lock_hashmap_tryreadlock(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_trylock_generic(lock_hashmap, key, entry, ticket_lock_tryreadlock);
}

int lock_hashmap_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_release);
}

int lock_hashmap_write_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_write_release);
}

int lock_hashmap_read_release(struct lock_hashmap_t * lock_hashmap, uint64_t key, struct lock_hashmap_entry_t * entry){
    return __lock_hashmap_release_generic(lock_hashmap, key, entry, ticket_lock_read_release);
}

void lock_hashmap_init_entry(struct lock_hashmap_entry_t * entry, int thread_id){
    entry->thread_id = thread_id;
    ticket_lock_init_entry(&entry->ticket_entry);
}
