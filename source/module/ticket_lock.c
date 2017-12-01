
#include "ticket_lock.h"

void ticket_lock_init(struct ticket_lock_t * lock, ticket_lock_mode_t mode){
    BUG_ON(lock==NULL);
    BUILD_BUG_ON(sizeof(struct ticket_lock_t) != 28);
    //start this at one and serve the first thread to increment
    //atomic64_set(&lock->now_serving, 1);
    lock->now_serving.counter = 1;
    //atomic64_set(&lock->next_ticket, 0);
    lock->next_ticket = 0;
    //atomic64_set(&lock->readers, 0);
    lock->readers.counter = 0;
    lock->mode = mode;
}

int __ticket_lock_tryacquire(struct ticket_lock_t * lock, 
			     struct ticket_lock_entry_t * entry, 
			     __ticket_lock_op_mode_t op_mode,
			     ticket_lock_acq_mode_t acq_mode){
    int result = 0;
    BUG_ON(op_mode != TICKET_LOCK_OP_NORMAL && lock->mode == TICKET_LOCK_MODE_NORMAL);
    //do we need a ticket or do we have one already?
    if (entry->our_ticket == NULL_TICKET) {
	entry->our_ticket = ticket_lock_get_ticket(lock);
    }

    entry->mode = op_mode;

    if (acq_mode != TICKET_LOCK_ACQ_ONLY_GET_TICKET) {

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

    }

    BUG_ON(entry->our_ticket == NULL_TICKET || entry->mode == TICKET_LOCK_OP_NULL);

    return result;
}

int ticket_lock_trylock(struct ticket_lock_t * lock, 
			struct ticket_lock_entry_t * entry,
			ticket_lock_acq_mode_t acq_mode){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_NORMAL, acq_mode);
}

void ticket_lock_acquire(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry){
    int i;
    u64 counter = 0;
    const u64 SPIN_BASE = 10000;

    while (1) {
        if (ticket_lock_trylock(lock, entry, TICKET_LOCK_ACQ_NORMAL)) {
	    return;
	}
	else{
	    counter <<= 1;
	    for (i = 0; i < (SPIN_BASE * (counter)); i++) {  }
	}
    }
}

int ticket_lock_trywritelock(struct ticket_lock_t * lock, 
			     struct ticket_lock_entry_t * entry,
			     ticket_lock_acq_mode_t acq_mode){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_WRITE, acq_mode);
}

int ticket_lock_tryreadlock(struct ticket_lock_t * lock, 
			    struct ticket_lock_entry_t * entry,
			    ticket_lock_acq_mode_t acq_mode){
    return __ticket_lock_tryacquire(lock, entry, TICKET_LOCK_OP_READ, acq_mode);
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
