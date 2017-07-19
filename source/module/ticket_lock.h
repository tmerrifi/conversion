
#ifndef TICKET_LOCK_H
#define TICKET_LOCK_H

#include <linux/types.h>
#include <asm/atomic.h>

#define NULL_TICKET (~0ULL)

typedef enum { TICKET_LOCK_MODE_NORMAL, TICKET_LOCK_MODE_RWLOCK } ticket_lock_mode_t;

typedef enum { TICKET_LOCK_OP_NORMAL, TICKET_LOCK_OP_READ, TICKET_LOCK_OP_WRITE, TICKET_LOCK_OP_NULL } __ticket_lock_op_mode_t;

struct ticket_lock_t{
    atomic64_t now_serving;
    atomic64_t next_ticket;
    atomic64_t readers;
    ticket_lock_mode_t mode;
};

struct ticket_lock_entry_t{
    u64 our_ticket;
    __ticket_lock_op_mode_t mode;
};

void ticket_lock_init(struct ticket_lock_t * lock, ticket_lock_mode_t mode);

int ticket_lock_trylock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_trywritelock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_tryreadlock(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_write_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

int ticket_lock_read_release(struct ticket_lock_t * lock, struct ticket_lock_entry_t * entry);

void ticket_lock_init_entry(struct ticket_lock_entry_t * entry);


#endif
