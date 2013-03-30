
#ifndef SHM_UTILITY_H

#define SHM_UTILITY_H

#include <sys/mman.h>	//for memory mapping


//DESCRIPTION: we need to concat the name of the graph with "vertices". This is how we will get the file
//or the shared memory region where the vertices are stored.
//ARGS: graphName: The name of the graph
size_t coreUtil_getFileSize(int fd);

size_t coreUtil_getFileSize(int fd);
void * coreUtil_openSharedMemory(char * segmentName, void * address, int defaultSize, int callingProcess, int * fd, int typeOfCommit, int commit_interval);
void coreUtil_closeSharedMemory(void * addr, int mappingSize, int fd);
void * coreUtil_resizeSharedMemory(void * addr, int currentMappingSize, int newMappingSize, int fd);
void coreUtil_removeSharedMemory(char * segmentName);

#define SHM_CLIENT 0		//the client can only read
#define SHM_CORE 1			//the core can read/write/create
#define SHM_CREATE_ONLY 2
#define SHM_SHARED 3
#define SHM_SHARED_NO_ADDRESS 4
#define SHM_PRIVATE_POPULATE 5

/*Policies specified by the subscribers*/
#define COMMIT_NONE     0
#define COMMIT_ALWAYS	0x100000
#define COMMIT_ADAPT	0x200000
#define COMMIT_DYN		0x400000

/*flag for snapshots*/
#define SNAP_BLOCKING		0x10
#define SNAP_NONBLOCKING	0x20

#endif
