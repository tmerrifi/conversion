
#ifndef TICKET_LOCK_H
#define TICKET_LOCK_H

#include <linux/types.h>
#include <asm/atomic.h>

#define NULL_TICKET (~0ULL)

typedef enum { TICKET_LOCK_MODE_NORMAL, TICKET_LOCK_MODE_RWLOCK } ticket_lock_mode_t;

typedef enum { TICKET_LOCK_OP_NORMAL, TICKET_LOCK_OP_READ, TICKET_LOCK_OP_WRITE, TICKET_LOCK_OP_NULL } __ticket_lock_op_mode_t;

typedef enum { TICKET_LOCK_ACQ_ONLY_GET_TICKET, TICKET_LOCK_ACQ_NORMAL } ticket_lock_acq_mode_t;

struct __attribute__ ((__packed__)) ticket_lock_t{
    atomic64_t now_serving;
    u64 next_ticket;
    atomic64_t readers;
    ticket_lock_mode_t mode;
}; //(8+8+8+4)=28 bytes

#define TICKET_LOCK_SIZE 28

struct ticket_lock_entry_t{
    u64 our_ticket;
    __ticket_lock_op_mode_t mode;
};

static u64 inline ticket_lock_get_ticket(struct ticket_lock_t * lock){
    u64 ticket = ++(lock->next_ticket);
    /*in the case that we've incremented and return the NULL_TICKET value, we need to get another ticket*/
    if (ticket == NULL_TICKET) {
        ticket = ++(lock->next_ticket);
    }
    return ticket;
}

void ticket_lock_init(struct ticket_lock_t * lock, ticket_lock_mode_t mode);

int ticket_lock_trylock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry, ticket_lock_acq_mode_t acq_mode);

int ticket_lock_trywritelock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry, ticket_lock_acq_mode_t acq_mode);

int ticket_lock_tryreadlock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry, ticket_lock_acq_mode_t acq_mode);

int ticket_lock_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_write_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_read_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

void ticket_lock_init_entry(struct ticket_lock_entry_t * entry);

void ticket_lock_acquire(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

#endif