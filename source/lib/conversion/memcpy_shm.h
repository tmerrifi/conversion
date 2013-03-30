
#ifndef MEMCPY_SHM_H
#define MEMCPY_SHM_H

#include <semaphore.h>

#include "ksnap.h"

struct memcpy_shm{
  void ** copy_segments;
  void * segment;
  void * metadata;
  ksnap * snapshot;
  sem_t * mutex;
  char * file_name;
  char * meta_file_name;
  int file_des;
  int num_of_subscribers;
  int active_copy_segment;
};

struct memcpy_shm_meta_perreader{
  unsigned short ref_count;
};

struct memcpy_shm_latest{
  unsigned short latest_snapshot;
};

#define MEMCPY_SHM_SUFFIX "memcpy_shm"
#define MEMCPY_META_SUFFIX "memcpy_shm_meta"

struct memcpy_shm * memcpy_shm_open(ksnap * snapshot, void * address, int num_of_subscribers);

struct memcpy_shm * memcpy_shm_client_open(ksnap * snapshot, int num_of_subscribers);

void memcpy_shm_client_update(struct memcpy_shm * memcpy_shm);

void memcpy_shm_settle(struct memcpy_shm * memcpy_shm, ksnap * snapshot);
#endif
