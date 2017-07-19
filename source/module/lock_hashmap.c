
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

int __lock_hashmap_trylock_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
				   int (*func) (struct ticket_lock_t *, struct ticket_lock_entry_t *)){
    int result = LOCK_ACQUIRE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
    //make sure we don't already hold this lock_hashmap
    if (lock->lock_holder == entry->thread_id) {
	result = LOCK_ACQUIRE_SUCC;
	BUG_ON(lock->acquires < 1);
    }
    else{
	result = func(&lock->ticket_lock, &entry->ticket_entry);
	if (result) {
	    //set lock holder for reentrance
	    lock->lock_holder = entry->thread_id;
	}
    }
    lock->acquires++;
    printk(KERN_EMERG "trylock....index: %u %p lock %p thread_id %d holder %d acquires %d result %d\n", 
	   index, entry, lock, entry->thread_id, lock->lock_holder, lock->acquires, result);
    return result;
}

int __lock_hashmap_release_generic(struct lock_hashmap_t * lock_hashmap, uint64_t key, 
				   struct lock_hashmap_entry_t *entry, 
				   int (*func) (struct ticket_lock_t *, struct ticket_lock_entry_t *)){
    int result = LOCK_RELEASE_FAILED;
    u32 index = __lock_hashmap_hash(key, lock_hashmap->mix, lock_hashmap->total_locks);
    struct lock_hashmap_lock_t * lock = &lock_hashmap->locks[index];
    BUG_ON(lock->lock_holder != entry->thread_id);
    BUG_ON(lock->acquires < 1);
    if (--lock->acquires == 0) {
	result = func(&lock->ticket_lock, &entry->ticket_entry);
	//only remove lock holder if number of acquires == 0
	lock->lock_holder = LOCK_HASHMAP_HOLDER_NONE;
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
