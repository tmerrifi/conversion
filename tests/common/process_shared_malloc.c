#include <stdlib.h>
#include <sys/mman.h>

void * process_shared_malloc(size_t size_of_mapping){
    void * mem = NULL;
    if ((mem = mmap(NULL,size_of_mapping,PROT_READ | PROT_WRITE,
                    MAP_SHARED|MAP_ANONYMOUS,-1,0))==NULL){
        perror("mmap failed for size %d", size_of_mapping);
        exit(1);
    }
    return mem;
}
