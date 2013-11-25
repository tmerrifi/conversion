#include <ksnap.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "../common/process_shared_malloc.h"

#define THREADS 8
#define PAGE_SIZE (1<<12)
#define PAGES THREADS
#define ARR_SIZE (PAGES * (1<<12))
#define ITERATIONS 150

#define is_writer_thread(id) (id % 2 == 0)

u_int8_t * arr, * mem1, * mem2, * mem3, * mem4;
conv_seg * seg;

pthread_barrier_t * barrier;
sem_t sem;

void print_relevant_bytes(u_int8_t * mem, int id, int iteration, char * message){
    printf("%s, id: %d, iteration: %d, pid: %d\n", message, id, iteration, getpid());
    for (int i=0;i<PAGES;++i){
        printf("Page: %d, ", i);
        for (int j=0;j<THREADS;++j){
            printf("%d:%d ", j, *(mem+(PAGE_SIZE * i)+j));
        }
        printf("\n");
    }
    printf("\n");
}

//write to the first byte of page[id]
void do_work(int id, int iteration){
    if (is_writer_thread(id)){
        //touch every page
        for (int i=0;i<PAGES;++i){
            *(arr+(PAGE_SIZE * i)+id)+=1;
        }
    }
    else{
        //just touch our page
        *(arr+(PAGE_SIZE * id)+id)+=1;
    }
}

void check_partial(int id, int iteration){
    //make sure we didn't merge
    for (int i=0;i<THREADS;++i){
        //only test it for writer threads
        if (is_writer_thread(i)){
            //check if a merge took place
            if (*(arr + (PAGE_SIZE * id) + i)==(iteration+1)){
                printf("FAILURE!!!!! Merge is detected, id: %d, it: %d\n", id, iteration);
            }
        }
    }

    //make sure we updated partially
    for (int i=0;i<PAGES;++i){
        //check all pages that aren't ours
        if (i!=id){
            for (int j=0;j<THREADS;++j){
                //the writer thread updates for this page should be visible
                if (is_writer_thread(j)){
                    if (*(arr + (PAGE_SIZE * i) + j)!=(iteration+1)){
                        printf("FAILURE!!!!! Updates aren't right, id: %d, it: %d\n", id, iteration);
                        printf("Expected page %d, byte %d to be %d\n", i, j, iteration+1);
                        print_relevant_bytes(arr, id, iteration, "FAILURE");
                    }
                }
            }
        }
    }
}


void check_merged(int id, int iteration){
    sem_wait(&sem);
    for (int i=0;i<PAGES;++i){
        for (int j=0;j<THREADS;++j){
            //the writer thread updates for this page should be visible
            if (is_writer_thread(j)){
                if (*(arr + (PAGE_SIZE * i) + j)!=(iteration+1)){
                    printf("FAILURE!!!!! Not merged correctly, id: %d, it: %d\n", id, iteration);
                    printf("Expected page %d, byte %d to be %d\n", i, j, iteration+1);
                    print_relevant_bytes(arr, id, iteration, "FAILURE");
                    printf("printing before merge\n");
                    print_relevant_bytes(mem1, id, iteration, "FAILURE mem1");
                    print_relevant_bytes(mem2, id, iteration, "FAILURE mem2");
                    print_relevant_bytes(mem3, id, iteration, "FAILURE mem3");
                    print_relevant_bytes(mem4, id, iteration, "FAILURE mem4");

                    goto end;
                }
            }
        }
    }
 end:
    fflush(stdout);
    sem_post(&sem);
}

void run(int id){
    if (is_writer_thread(id)){
        printf("writer thread: %d\n", id);
    }
    else{
        printf("checker thread: %d\n", id);
    }

    mem1 = malloc(ARR_SIZE * sizeof(u_int8_t));
    mem2 = malloc(ARR_SIZE * sizeof(u_int8_t));
    mem3 = malloc(ARR_SIZE * sizeof(u_int8_t));
    mem4 = malloc(ARR_SIZE * sizeof(u_int8_t));

    for (int i=0;i<ITERATIONS;++i){
        if (!is_writer_thread(id)){
            //touch "your" page
            do_work(id, i);
            //wait for the writer threads to be done
            pthread_barrier_wait(barrier);
            //wait for writer threads to merge
            pthread_barrier_wait(barrier);
            //perform a partial update
            //print_relevant_bytes(id,i,"pre merge");
            conv_partial_background_update(seg);
            //conv_merge(seg);
            //print_relevant_bytes(id,i,"post merge");
            //verify it did what we expected
            check_partial(id, i);
            //commit our changes, and merge
            conv_commit_and_update(seg);
            pthread_barrier_wait(barrier);
            //synchronize everyone
            conv_merge(seg);
            check_merged(id,i);
            pthread_barrier_wait(barrier);
        }
        else{
            do_work(id, i);
            //print_relevant_bytes(id,i,"pre merge");
            //commit our stuff
            //store old stuff
            memcpy(mem1, arr, ARR_SIZE * sizeof(u_int8_t));
            conv_commit_and_update(seg);
            memcpy(mem2, arr, ARR_SIZE * sizeof(u_int8_t));
            //wait for people to finish their work
            pthread_barrier_wait(barrier);
            //merge with other writers
            conv_merge(seg);
            memcpy(mem3, arr, ARR_SIZE * sizeof(u_int8_t));
            //print_relevant_bytes(id,i,"before check merged");
            check_merged(id,i);
            pthread_barrier_wait(barrier);
            //wait for updaters to do their partial and check
            pthread_barrier_wait(barrier);
            //sync up with everyone
            conv_merge(seg);
            memcpy(mem4, arr, ARR_SIZE * sizeof(u_int8_t));
            pthread_barrier_wait(barrier);
        }
    }
    exit(1);
}

int main(){
    seg = conv_checkout_create(ARR_SIZE * sizeof(u_int8_t), "partial_test", NULL, 0);
    arr = (u_int8_t *)seg->segment;
    memset(arr,0,sizeof(u_int8_t)*ARR_SIZE);
    conv_commit_and_update(seg);
    //allocate some memory in a shared place
    barrier=process_shared_malloc(sizeof(pthread_barrier_t));
    //need to mark the barrier as process shared
    pthread_barrierattr_t attr;
    pthread_barrierattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
    pthread_barrier_init(barrier, &attr, THREADS);
    //initializing a mutex
    sem_init(&sem,1,1);
    pid_t pids[THREADS];

    for (int i=0; i<THREADS;++i){
        int pid=fork();
        if (pid==0){
            //child
            run(i);
        }
        else{
            pids[i]=pid;
        }
    }

    for (int i=0; i<THREADS;++i){
        waitpid(pids[i], NULL, 0);
    }
}
