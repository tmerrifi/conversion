#ifndef CV_COUNTERS
#define CV_COUNTERS

typedef enum{COUNTER_FIRST=0,
             /*monitoring migration checking and diffing*/
             COUNTER_LOGGING_MIGRATIONS, COUNTER_LOGGING_MIGRATION_CHECK_SUCCESS, COUNTER_LOGGING_MIGRATION_CHECK_FAILED,
             COUNTER_LOGGING_MIGRATION_CHECK_0_4, COUNTER_LOGGING_MIGRATION_CHECK_5_9, COUNTER_LOGGING_MIGRATION_CHECK_10_19,
             COUNTER_LOGGING_MIGRATION_CHECK_20_49,COUNTER_LOGGING_MIGRATION_CHECK_50_INF,COUNTER_FAULT_CYCLES_0_499,
             /*page fault cycle latency counters*/
             COUNTER_FAULT_CYCLES_500_999,COUNTER_FAULT_CYCLES_1000_1999,COUNTER_FAULT_CYCLES_2000_2999,COUNTER_FAULT_CYCLES_3000_4999,COUNTER_FAULT_CYCLES_5000_6999,
             COUNTER_FAULT_CYCLES_7000_9999,COUNTER_FAULT_CYCLES_10000_12999,COUNTER_FAULT_CYCLES_13000_17999,COUNTER_FAULT_CYCLES_18000_INF,
             /*logging path counters*/
             COUNTER_LOGGING_FAULT_PAGE_COPY_OTHER,COUNTER_LOGGING_FAULT_PAGE_COPY_FORCED,COUNTER_LOGGING_FAULT_PAGE_COPY_THRESHOLD_EXCEEDED,
             COUNTER_LOGGING_FAULT_INTERPRET_ALLOC, COUNTER_LOGGING_FAULT_INTERPRET_NOALLOC,
             /*CoW fault handler counters*/
             COUNTER_COW_FAULT,
             /*commit entries*/
             COUNTER_COMMIT_ENTRIES_LT_5,COUNTER_COMMIT_ENTRIES_LT_10,COUNTER_COMMIT_ENTRIES_LT_15,COUNTER_COMMIT_ENTRIES_LT_20,COUNTER_COMMIT_ENTRIES_LT_25,
             COUNTER_COMMIT_ENTRIES_LT_30,COUNTER_COMMIT_ENTRIES_LT_40,COUNTER_COMMIT_ENTRIES_LT_50,COUNTER_COMMIT_ENTRIES_LT_75,COUNTER_COMMIT_ENTRIES_LT_100,
             COUNTER_COMMIT_ENTRIES_LT_250,COUNTER_COMMIT_ENTRIES_LT_500,COUNTER_COMMIT_ENTRIES_LT_1000,COUNTER_COMMIT_ENTRIES_LT_5000,COUNTER_COMMIT_ENTRIES_LT_10000,
             COUNTER_COMMIT_ENTRIES_LT_INF,
             /*commit latency counters*/
             COUNTER_COMMIT_CYCLES_LT_10000,COUNTER_COMMIT_CYCLES_LT_25000,COUNTER_COMMIT_CYCLES_LT_50000,COUNTER_COMMIT_CYCLES_LT_75000,
             COUNTER_COMMIT_CYCLES_LT_100000,COUNTER_COMMIT_CYCLES_LT_150000,COUNTER_COMMIT_CYCLES_LT_200000,COUNTER_COMMIT_CYCLES_LT_500000,
             COUNTER_COMMIT_CYCLES_INF,COUNTER_COMMIT_CYCLES_TOTAL,
             /*commit logging counters*/
             COUNTER_COMMIT_LOGGING_NO_MERGE, COUNTER_COMMIT_LOGGING_FAST_PAGE_MERGE, COUNTER_COMMIT_LOGGING_SLOW_PAGE_MERGE, COUNTER_COMMIT_LOGGING_FAST_LINE_MERGE,
             /*update latency counters*/
             COUNTER_UPDATE_CYCLES_LT_10000,COUNTER_UPDATE_CYCLES_LT_50000,COUNTER_UPDATE_CYCLES_LT_100000,COUNTER_UPDATE_CYCLES_LT_200000,
             COUNTER_UPDATE_CYCLES_LT_500000,COUNTER_UPDATE_CYCLES_INF,COUNTER_UPDATE_CYCLES_TOTAL,
             /*TLB ops*/
             COUNTER_TLB_PAGE_FLUSH,COUNTER_TLB_FLUSH,
             /********************/
             COUNTER_LAST};


#ifdef CV_COUNTERS_ON

#define init_counters() ((uint64_t *)kzalloc(sizeof(uint64_t) * (COUNTER_LAST-COUNTER_FIRST), GFP_KERNEL))

#define ADD_COUNTER(counter,n) (cv_user->counters[counter]+=n)

#define INC(counter) (cv_user->counters[counter]++)

#define GET_COUNTER(counter) (cv_user->counters[counter])

#define PRINT_COUNTER(counter) printk(CV_LOG_LEVEL #counter": %llu\n", GET_COUNTER(counter))

#define COUNTER_COMMIT_ENTRIES(entries)                                 \
    if (entries < 5){                                                   \
        INC(COUNTER_COMMIT_ENTRIES_LT_5);                               \
    }                                                                   \
    else if(entries < 10){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_10);                              \
    }                                                                   \
    else if(entries < 15){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_15);                              \
    }                                                                   \
    else if(entries < 20){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_20);                              \
    }                                                                   \
    else if(entries < 25){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_25);                              \
    }                                                                   \
    else if(entries < 30){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_30);                              \
    }                                                                   \
    else if(entries < 40){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_40);                              \
    }                                                                   \
    else if(entries < 50){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_50);                              \
    }                                                                   \
    else if(entries < 75){                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_75);                              \
    }                                                                   \
    else if(entries < 100){                                              \
        INC(COUNTER_COMMIT_ENTRIES_LT_100);                             \
    }                                                                   \
    else if(entries < 250){                                              \
        INC(COUNTER_COMMIT_ENTRIES_LT_250);                             \
    }                                                                   \
    else if(entries < 500){                                              \
        INC(COUNTER_COMMIT_ENTRIES_LT_500);                             \
    }                                                                   \
    else if(entries < 1000){                                             \
        INC(COUNTER_COMMIT_ENTRIES_LT_1000);                            \
    }                                                                   \
    else if(entries < 5000){                                             \
        INC(COUNTER_COMMIT_ENTRIES_LT_5000);                            \
    }                                                                   \
    else if(entries < 10000){                                            \
        INC(COUNTER_COMMIT_ENTRIES_LT_10000);                           \
    }                                                                   \
    else{                                                               \
        INC(COUNTER_COMMIT_ENTRIES_LT_INF);                             \
    }                                                                   \



#define COUNTER_COMMIT_LATENCY(cycles)                                  \
    ADD_COUNTER(COUNTER_COMMIT_CYCLES_TOTAL,cycles);                    \
    if (cycles < 10000){                                                \
        INC(COUNTER_COMMIT_CYCLES_LT_10000);                            \
    }                                                                   \
    else if(cycles < 25000){                                            \
        INC(COUNTER_COMMIT_CYCLES_LT_50000);                            \
    }                                                                   \
    else if(cycles < 50000){                                            \
        INC(COUNTER_COMMIT_CYCLES_LT_50000);                            \
    }                                                                   \
    else if(cycles < 75000){                                            \
        INC(COUNTER_COMMIT_CYCLES_LT_50000);                            \
    }                                                                   \
    else if(cycles < 100000){                                           \
        INC(COUNTER_COMMIT_CYCLES_LT_100000);                           \
    }                                                                   \
    else if(cycles < 200000){                                           \
        INC(COUNTER_COMMIT_CYCLES_LT_200000);                           \
    }                                                                   \
    else if(cycles < 500000){                                           \
        INC(COUNTER_COMMIT_CYCLES_LT_500000);                           \
    }                                                                   \
    else{                                                               \
        INC(COUNTER_COMMIT_CYCLES_INF);                                 \
    }                                                                   \


#define COUNTER_UPDATE_LATENCY(cycles)                                  \
    ADD_COUNTER(COUNTER_UPDATE_CYCLES_TOTAL,cycles);                    \
    if (cycles < 10000){                                                \
        INC(COUNTER_UPDATE_CYCLES_LT_10000);                            \
    }                                                                   \
    else if(cycles < 50000){                                            \
        INC(COUNTER_UPDATE_CYCLES_LT_50000);                            \
    }                                                                   \
    else if(cycles < 100000){                                           \
        INC(COUNTER_UPDATE_CYCLES_LT_100000);                           \
    }                                                                   \
    else if(cycles < 200000){                                           \
        INC(COUNTER_UPDATE_CYCLES_LT_200000);                           \
    }                                                                   \
    else if(cycles < 500000){                                           \
        INC(COUNTER_UPDATE_CYCLES_LT_500000);                           \
    }                                                                   \
    else{                                                               \
        INC(COUNTER_UPDATE_CYCLES_INF);                                 \
    }                                                                   \


#define COUNTER_FAULT_CHECK(cycles)                                     \
    if (cycles < 500){                                                  \
        INC(COUNTER_FAULT_CYCLES_0_499);                                \
    }                                                                   \
    else if(cycles < 1000){                                             \
        INC(COUNTER_FAULT_CYCLES_500_999);                              \
    }                                                                   \
    else if(cycles < 2000){                                             \
        INC(COUNTER_FAULT_CYCLES_1000_1999);                            \
    }                                                                   \
    else if(cycles < 3000){                                             \
        INC(COUNTER_FAULT_CYCLES_2000_2999);                            \
    }                                                                   \    
    else if(cycles < 5000){                                             \
        INC(COUNTER_FAULT_CYCLES_3000_4999);                            \
    }                                                                   \
    else if(cycles < 7000){                                             \
        INC(COUNTER_FAULT_CYCLES_5000_6999);                            \
    }                                                                   \
    else if(cycles < 10000){                                            \
        INC(COUNTER_FAULT_CYCLES_7000_9999);                            \
    }                                                                   \
    else if(cycles < 13000){                                            \
        INC(COUNTER_FAULT_CYCLES_10000_12999);                          \
    }                                                                   \
    else if(cycles < 18000){                                            \
        INC(COUNTER_FAULT_CYCLES_13000_17999);                          \
    }                                                                   \
    else{                                                               \
        INC(COUNTER_FAULT_CYCLES_18000_INF);                            \
    }                                                                   \

#define COUNTER_MIGRATION_CHECK(diff)                   \
    if (diff < 5){                                      \
        INC(COUNTER_LOGGING_MIGRATION_CHECK_0_4);       \
    }                                                   \
    else if (diff < 10){                                \
        INC(COUNTER_LOGGING_MIGRATION_CHECK_5_9);       \
    }                                                   \
    else if (diff < 20){                                \
        INC(COUNTER_LOGGING_MIGRATION_CHECK_10_19);     \
    }                                                   \
    else if (diff < 50){                                \
        INC(COUNTER_LOGGING_MIGRATION_CHECK_20_49);     \
    }                                                   \
    else{                                               \
        INC(COUNTER_LOGGING_MIGRATION_CHECK_50_INF);    \
    }                                                   \

static void counters_print_all(struct ksnap_user_data * cv_user){
    printk(CV_LOG_LEVEL "**********Counters for process %d, conversion segment starting at %p*******\n", cv_user->id,cv_user->vma->vm_start);
    printk(CV_LOG_LEVEL "***Logging migration counters***\n");    
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATIONS);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_SUCCESS);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_FAILED);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_0_4);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_5_9);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_10_19);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_20_49);
    PRINT_COUNTER(COUNTER_LOGGING_MIGRATION_CHECK_50_INF);
    printk(CV_LOG_LEVEL "***Fault latency counters***\n");
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_0_499);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_500_999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_1000_1999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_2000_2999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_3000_4999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_5000_6999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_7000_9999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_10000_12999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_13000_17999);
    PRINT_COUNTER(COUNTER_FAULT_CYCLES_18000_INF);
    printk(CV_LOG_LEVEL "***COMMIT merge counters***\n");
    PRINT_COUNTER(COUNTER_COMMIT_LOGGING_NO_MERGE);
    PRINT_COUNTER(COUNTER_COMMIT_LOGGING_SLOW_PAGE_MERGE);
    PRINT_COUNTER(COUNTER_COMMIT_LOGGING_FAST_PAGE_MERGE);
    PRINT_COUNTER(COUNTER_COMMIT_LOGGING_FAST_LINE_MERGE);
    printk(CV_LOG_LEVEL "***COMMIT latency counters***\n");
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_10000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_25000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_50000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_75000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_100000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_200000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_LT_500000);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_INF);
    PRINT_COUNTER(COUNTER_COMMIT_CYCLES_TOTAL);
    printk(CV_LOG_LEVEL "***COMMIT entries counters***\n");
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_5);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_10);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_15);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_20);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_25);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_30);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_40);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_50);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_75);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_100);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_250);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_500);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_1000);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_5000);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_10000);
    PRINT_COUNTER(COUNTER_COMMIT_ENTRIES_LT_INF);
    printk(CV_LOG_LEVEL "***UPDATE latency counters***\n");
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_LT_10000);
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_LT_50000);
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_LT_100000);
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_LT_200000);
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_LT_500000);
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_INF);    
    PRINT_COUNTER(COUNTER_UPDATE_CYCLES_TOTAL);
    printk(CV_LOG_LEVEL "***Logging fault path counters***\n");
    PRINT_COUNTER(COUNTER_LOGGING_FAULT_PAGE_COPY_FORCED);
    PRINT_COUNTER(COUNTER_LOGGING_FAULT_PAGE_COPY_THRESHOLD_EXCEEDED);
    PRINT_COUNTER(COUNTER_LOGGING_FAULT_PAGE_COPY_OTHER);
    PRINT_COUNTER(COUNTER_LOGGING_FAULT_INTERPRET_ALLOC);
    PRINT_COUNTER(COUNTER_LOGGING_FAULT_INTERPRET_NOALLOC);
    printk(CV_LOG_LEVEL "***CoW fault counters***\n");
    PRINT_COUNTER(COUNTER_COW_FAULT);
    //COUNTER_TLB_PAGE_FLUSH,COUNTER_TLB_FLUSH,
    printk(CV_LOG_LEVEL "***TLB counters***\n");
    PRINT_COUNTER(COUNTER_TLB_PAGE_FLUSH);
    PRINT_COUNTER(COUNTER_TLB_FLUSH);
    
}

#else

#define init_counters()

#define INC(counter)

#define GET_COUNTER(counter)

#define COUNTER_MIGRATION_CHECK(diff)

static void counters_print_all(struct ksnap_user_data * cv_user){ }

#endif

#endif
