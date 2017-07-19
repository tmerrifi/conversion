
#include "ticket_lock.h"

void ticket_lock_init(struct ticket_lock_t * lock, ticket_lock_mode_t mode){
    BUG_ON(lock==NULL);
    //start this at one and serve the first thread to increment
    atomic64_set(&lock->now_serving, 1);
    atomic64_set(&lock->next_ticket, 0);
    atomic64_set(&lock->readers, 0);
    lock->mode = mode;
    printk(KERN_EMERG "ticket_lock_init mode....%d, lock %p\n", lock->mode, lock);
}

void __debug_print_state(struct ticket_lock_t * lock){
    printk(KERN_EMERG "lock %p, mode %d, next %ld, serving %ld, readers %ld\n", lock, lock->mode, 
	   atomic64_read(&lock->next_ticket), atomic64_read(&lock->now_serving), atomic64_read(&lock->readers));
}

int __ticket_lock_tryacquire(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry, __ticket_lock_op_mode_t op_mode){
    int result;
    printk(KERN_EMERG "mode....%d, lock %p\n", lock->mode, lock);
    BUG_ON(op_mode != TICKET_LOCK_OP_NORMAL && lock->mode == TICKET_LOCK_MODE_NORMAL);
    //do we need a ticket or do we have one already?
    if (entry->our_ticket == NULL_TICKET) {
	u64 ticket = (u64)atomic64_inc_return(&lock->next_ticket);
	/*in the case that we've incremented and return the NULL_TICKET value, we need to get another ticket*/
	if (ticket == NULL_TICKET) {
	    ticket = (u64)atomic64_inc_return(&lock->next_ticket);
	}
	entry->our_ticket = ticket;
    }

    if (atomic64_read(&lock->now_serving) == entry->our_ticket && lock->mode == TICKET_LOCK_MODE_NORMAL) {
	result = 1;
    }
    //its our turn and we're a reader
    else if (atomic64_read(&lock->now_serving) == entry->our_ticket && 
	     op_mode == TICKET_LOCK_OP_READ) {
	//we need to bump the number of readers and then increment the ticket
	atomic64_inc(&lock->readers);
	atomic64_inc(&lock->now_serving);
	result = 1;
    }
    else if (atomic64_read(&lock->now_serving) == entry->our_ticket && 
	     op_mode == TICKET_LOCK_OP_WRITE && 
	     atomic64_read(&lock->readers) == 0) {
	result = 1;
    }
    else{
	result = 0;
    }
    entry->mode = op_mode;
    printk(KERN_EMERG "in trylock for lock %p, returning %d\n", lock, result);
    __debug_print_state(lock);
    return result;
}


int ticket_lock_trylock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_NORMAL);
}

int ticket_lock_trywritelock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_WRITE);
}

int ticket_lock_tryreadlock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_READ);
}


int __ticket_lock_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry,  __ticket_lock_op_mode_t op_mode){
    //its possible here for a thread to arrive with our_ticket set to NULL_TICKET because of reentrace handled in lock_hashmap
    if (op_mode == TICKET_LOCK_OP_NORMAL || op_mode == TICKET_LOCK_OP_WRITE) {
	atomic64_inc(&lock->now_serving);
    }
    else if (op_mode == TICKET_LOCK_OP_READ) {
	BUG_ON(atomic64_read(&lock->readers) <= 0);
	atomic64_dec(&lock->readers);
    }
    entry->our_ticket = NULL_TICKET;
    printk(KERN_EMERG "in release for lock %p\n", lock);
    __debug_print_state(lock);
    return 1;
}

int ticket_lock_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_release(lock, entry, TICKET_LOCK_OP_NORMAL);
}

int ticket_lock_write_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_release(lock, entry, TICKET_LOCK_OP_WRITE);
}

int ticket_lock_read_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    return __ticket_lock_release(lock, entry, TICKET_LOCK_OP_READ);
}

void ticket_lock_init_entry(struct ticket_lock_entry_t * entry){
    entry->our_ticket = NULL_TICKET;
    entry->mode = TICKET_LOCK_OP_NULL;
}
