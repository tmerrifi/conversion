
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

#include "shmUtility.h"
#include "ksnap.h"
#include "memcpy_shm.h"
#include "time_util.h"

sem_t * __open_semaphore(char * name, int owner){
  char mutex_name[120];
  sprintf(mutex_name, "%s_%s.sem", name, MEMCPY_SHM_SUFFIX);
  sem_t * mutex = sem_open(mutex_name,((owner)? O_CREAT : 0),0644,1);
  return mutex;
}

void __open_all_segments(struct memcpy_shm * shm, int size_of_segment){
  shm->copy_segments = malloc(sizeof(void *) * (shm->num_of_subscribers + 1));
  for (int i=0;i<(shm->num_of_subscribers + 1); ++i){
    char file_name[120];
    sprintf(file_name,"%s_%d",shm->file_name, i);
    shm->copy_segments[i]=coreUtil_openSharedMemory(file_name, NULL, size_of_segment, SHM_SHARED_NO_ADDRESS, NULL, COMMIT_NONE, 0);
  }
}

struct memcpy_shm * memcpy_shm_open(ksnap * snapshot, void * address, int num_of_subscribers){
  struct memcpy_shm * shm = malloc(sizeof(struct memcpy_shm));
  //create the new file name
  shm->file_name=malloc(120);
  shm->meta_file_name=malloc(120);
  shm->num_of_subscribers=num_of_subscribers;
  sprintf(shm->file_name,"%s_%s",snapshot->name, MEMCPY_SHM_SUFFIX);
  sprintf(shm->meta_file_name, "%s_%s", snapshot->name, MEMCPY_META_SUFFIX);
  shm->segment = coreUtil_openSharedMemory(shm->file_name, address, snapshot->size_of_segment, SHM_SHARED, NULL, COMMIT_NONE, 0);
  shm->metadata = coreUtil_openSharedMemory(shm->meta_file_name, NULL, 
					    (sizeof(struct memcpy_shm_meta_perreader) * (num_of_subscribers + 1) + sizeof(struct memcpy_shm_latest)), 
					     SHM_SHARED_NO_ADDRESS, NULL, COMMIT_NONE, 0);
  printf("metadata %p\n", shm->metadata);
  memset(shm->metadata,0, (sizeof(struct memcpy_shm_meta_perreader) * (num_of_subscribers + 1) + sizeof(struct memcpy_shm_latest)));
  //open all the copy segments
  __open_all_segments(shm, snapshot->size_of_segment);
  shm->snapshot = snapshot;
  shm->mutex = __open_semaphore(snapshot->name, 1);
  printf("opened the sem that I am looking for\n");
  return shm;
}

struct memcpy_shm * memcpy_shm_client_open(ksnap * snapshot, int num_of_subscribers){
    //first, try and unmap the current snapshot
  munmap(snapshot->segment,snapshot->size_of_segment);
  struct memcpy_shm * shm = malloc(sizeof(struct memcpy_shm));
  //create the new file name
  shm->file_name=malloc(120);
  shm->meta_file_name=malloc(120);
  shm->num_of_subscribers=num_of_subscribers;
  shm->file_des=0;
  shm->active_copy_segment=-1;
  sprintf(shm->file_name,"%s_%s",snapshot->name, MEMCPY_SHM_SUFFIX);
  sprintf(shm->meta_file_name, "%s_%s", snapshot->name, MEMCPY_META_SUFFIX);
  shm->metadata = coreUtil_openSharedMemory(shm->meta_file_name, NULL, 
					    sizeof(struct memcpy_shm_latest), 
					    SHM_SHARED_NO_ADDRESS, NULL, COMMIT_NONE, 0);

  //map the new segment where the old one was
  shm->mutex = __open_semaphore(snapshot->name, 0);
  shm->snapshot = snapshot;
  printf("client opening %s...\n", shm->file_name);
  memcpy_shm_client_update(shm);

  return shm;
}

void memcpy_shm_client_update(struct memcpy_shm * memcpy_shm){
  //printf("unmapping\n");

  struct timespec t1, t2, t3, t4;

  if (memcpy_shm->file_des){
    coreUtil_closeSharedMemory(memcpy_shm->segment, memcpy_shm->snapshot->size_of_segment, memcpy_shm->file_des);
  }
  sem_wait(memcpy_shm->mutex);
  clock_gettime(CLOCK_REALTIME, &t2);
  //find the latest segment
  struct memcpy_shm_latest * latest = (struct memcpy_shm_latest *)memcpy_shm->metadata;
  //get the per reader copy metadata
  struct memcpy_shm_meta_perreader * per_reader_iterator = memcpy_shm->metadata + sizeof(struct memcpy_shm_latest);
  //get the new filename
  char file_name[120];
  int latest_id=latest->latest_snapshot;
  //printf("hello....\n");
  if (per_reader_iterator[latest_id].ref_count == 999){
    //printf("in %d copy use...\n", latest_id);
    latest_id=(latest_id+1) % memcpy_shm->num_of_subscribers;
    //printf("new is %d...%d \n", latest_id, memcpy_shm->num_of_subscribers);
  }
  sprintf(file_name,"%s_%d",memcpy_shm->file_name, latest_id);


  //up the ref count for this segment
  per_reader_iterator[latest_id].ref_count++;
  //reduce the ref count of the old segment we were using
  if (memcpy_shm->active_copy_segment >= 0)
    per_reader_iterator[memcpy_shm->active_copy_segment].ref_count--;
  //now update the active copy segment
  memcpy_shm->active_copy_segment = latest_id;
  /*printf("latest snapshot is %s, subscribers are %d, ref count is %d, pid %d, active %d\n", file_name, 
    memcpy_shm->num_of_subscribers, per_reader_iterator[latest->latest_snapshot], getpid(), memcpy_shm->active_copy_segment);*/
  
  //printf("subscriber %d before post mutex\n", getpid());
  sem_post(memcpy_shm->mutex);
  //printf("subscriber %d after post mutex\n", getpid());

  memcpy_shm->segment = coreUtil_openSharedMemory(file_name, memcpy_shm->snapshot->segment, 
						  memcpy_shm->snapshot->size_of_segment, SHM_CLIENT, &memcpy_shm->file_des, COMMIT_NONE, 0);
  
}

void memcpy_shm_settle(struct memcpy_shm * memcpy_shm, ksnap * snapshot){
  //printf("settle 1....\n");
  sem_wait(memcpy_shm->mutex);
  struct memcpy_shm_latest * latest = (struct memcpy_shm_latest *)memcpy_shm->metadata;
  //printf("settle 2....\n");
  int target_segment_number=0;
  struct memcpy_shm_meta_perreader * per_reader_iterator = memcpy_shm->metadata + sizeof(struct memcpy_shm_latest);
  for (int i=(latest->latest_snapshot+1) % memcpy_shm->num_of_subscribers; i< memcpy_shm->num_of_subscribers + 1; ++i){
    if (per_reader_iterator[i].ref_count == 0){
      target_segment_number=i;
      break;
    }
  }
  per_reader_iterator[target_segment_number].ref_count=999;
  sem_post(memcpy_shm->mutex);

  memcpy(memcpy_shm->copy_segments[target_segment_number], snapshot->segment, snapshot->size_of_segment); 

  //printf("settle 3....\n");
  sem_wait(memcpy_shm->mutex);
  //printf("settle 4....\n");

  latest->latest_snapshot = target_segment_number;
  per_reader_iterator[target_segment_number].ref_count=0;
  sem_post(memcpy_shm->mutex);
}
