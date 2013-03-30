
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>	//for memory mapping
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "shmUtility.h"

size_t coreUtil_getFileSize(int fd){
	size_t sizeInBytes=0;
	struct stat fileStats;
	if (fstat(fd,&fileStats) != -1){
		sizeInBytes=(fileStats.st_size > 0) ? fileStats.st_size : 0;
	}
	return sizeInBytes;
}


unsigned long get_commit_interval(int commit_interval){

	return commit_interval << 23;
	
}

void * coreUtil_openSharedMemory(char * segmentName, void * address, int defaultSize, int callingProcess, int * fd, int typeOfCommit, int commit_interval){
	int open_flags, mmap_prots, shm_type;
	
	switch(callingProcess){
	case(SHM_CREATE_ONLY):	
	  open_flags=O_CREAT | O_RDWR | O_EXCL;
	  mmap_prots=PROT_READ|PROT_WRITE;
	  shm_type=MAP_PRIVATE;
	  break;
	case(SHM_CORE):
	  open_flags=O_CREAT | O_RDWR;
	  mmap_prots=PROT_READ|PROT_WRITE;
	  shm_type=MAP_PRIVATE;
	  break;
	case(SHM_CLIENT):
	  open_flags=O_RDONLY;
	  mmap_prots=PROT_READ;
	  shm_type=MAP_SHARED | MAP_POPULATE;
	  break;
	case (SHM_SHARED):
	case (SHM_SHARED_NO_ADDRESS):
	  open_flags=O_CREAT | O_RDWR;
	  mmap_prots=PROT_READ|PROT_WRITE;
	  shm_type=MAP_SHARED;
	  break;
	case (SHM_PRIVATE_POPULATE):
	  open_flags=O_CREAT | O_RDWR;
	  mmap_prots=PROT_READ|PROT_WRITE;
	  shm_type=MAP_PRIVATE | MAP_POPULATE;
	  break;
	}
	void * mem = NULL;
	
	int tmp_fd = 0;		//to allow people to pass in NULL just in case they don't care about getting back the file descriptor
	if (!fd){		
	  fd = &tmp_fd;		
	}
	*fd = open(segmentName, open_flags, 0777);
	if (*fd != -1){
	  int sizeInBytes=coreUtil_getFileSize(*fd);
	  if (sizeInBytes == 0 && (callingProcess == SHM_CORE || callingProcess == SHM_SHARED || SHM_SHARED_NO_ADDRESS) ){
	    ftruncate(*fd, defaultSize);
	    sizeInBytes=defaultSize;
	  }
	  if (sizeInBytes > 0){
	    int flags = 0x0;
	    flags |= shm_type;
	    flags |= typeOfCommit;
	    flags |= get_commit_interval(commit_interval);
	    if (callingProcess != SHM_SHARED_NO_ADDRESS){
	      flags |= MAP_FIXED;
	    }
	    mem = mmap(address,sizeInBytes,mmap_prots,flags,*fd,0);
	    if (!mem){
	      printf("trying %s %d %p\n", segmentName, *fd, address);
	      perror("mmap failed on \n");
	    }
	  }	
	}
	else{
	  perror("failed to open file\n");
	}
	return mem;
}

void coreUtil_closeSharedMemory(void * addr, int mappingSize, int fd){
	if (munmap(addr, mappingSize) == -1){
		perror("unmapping (closing) the slab failed");
	}
	close(fd);	
}

void * coreUtil_resizeSharedMemory(void * addr, int currentMappingSize, int newMappingSize, int fd){
	void * mem = NULL;
	if (munmap(addr, currentMappingSize) == -1){
		perror("unmapping (closing) the slab failed");
	}
	else if (ftruncate(fd, newMappingSize) == -1) {
		perror("error resizing the file (ftruncate)");
	}
	else {
		mem = mmap(addr, newMappingSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);	//now map it into memory
		if ((int)mem == -1){
			perror("An error occured when mapping a shared memory segment in resize for object slab.");
		}
	}
	
	return mem;
}

void coreUtil_removeSharedMemory(char * segmentName){
	if (shm_unlink(segmentName) == -1){
		perror("Error unlinking");
	}
}




