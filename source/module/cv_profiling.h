
#ifndef CV_PROFILING_H
#define CV_PROFILING_H

#include "conversion.h"

typedef enum {CV_PROFILING_OP_TYPE_COMMIT, CV_PROFILING_OP_TYPE_UPDATE} cv_profiling_op_type;
typedef enum {CV_PROFILING_VALUE_TYPE_COMMIT, CV_PROFILING_VALUE_TYPE_UPDATE, 
              CV_PROFILING_VALUE_TYPE_MERGE, CV_PROFILING_VALUE_TYPE_SKIPPED, 
              CV_PROFILING_VALUE_TYPE_STOPPED_UPDATE_VERSION} cv_profiling_value_type;

#define CV_PROFILING_NUM_PAGES 200

#define CV_PROFILING_TOTAL_OPS 3

//represents a single commit or update operation
struct cv_profiling_single_op{
    cv_profiling_op_type prof_type;
    int committed_pages[CV_PROFILING_NUM_PAGES];
    int total_committed;
    int updated_pages[CV_PROFILING_NUM_PAGES];
    int total_updated;
    int merged_pages[CV_PROFILING_NUM_PAGES];
    int total_merged;
    int skipped_pages[CV_PROFILING_NUM_PAGES];
    int total_skipped;
    int update_stopped_here;
    int version_num;
};

struct cv_profiling_ops{
    struct cv_profiling_single_op single_ops[CV_PROFILING_TOTAL_OPS];
    int count;
    int pid;
};

#ifdef CV_PROFILING_ON

static inline cv_profiling_begin(struct cv_profiling_ops * ops, int pid){
    ops->count=0;
    ops->pid=pid;
}

static inline cv_profiling_op_begin(struct cv_profiling_ops * ops, cv_profiling_op_type prof_type, int version_num){
    ops->count++;
    struct cv_profiling_single_op * op = &ops->single_ops[ops->count % CV_PROFILING_TOTAL_OPS];
    memset(op, 0, sizeof(struct cv_profiling_single_op));
    op->prof_type=prof_type;
    op->version_num=version_num;
}

static inline cv_profiling_add_value(struct cv_profiling_ops * ops, int value, cv_profiling_value_type prof_page_type){

    struct cv_profiling_single_op * op = &ops->single_ops[ops->count % CV_PROFILING_TOTAL_OPS];

    switch (prof_page_type){
    case CV_PROFILING_VALUE_TYPE_UPDATE:
        if (op->total_updated >= 0 && op->total_updated < CV_PROFILING_NUM_PAGES){
            op->updated_pages[op->total_updated]=value;
            op->total_updated++;
        }
        break;
    case CV_PROFILING_VALUE_TYPE_COMMIT:
        if (op->total_committed >= 0 && op->total_committed < CV_PROFILING_NUM_PAGES){
            op->committed_pages[op->total_committed]=value;
            op->total_committed++;
        }
        break;
    case CV_PROFILING_VALUE_TYPE_MERGE:
        if (op->total_merged >= 0 && op->total_merged < CV_PROFILING_NUM_PAGES){
            op->merged_pages[op->total_merged]=value;
            op->total_merged++;
        }
        break;
    case CV_PROFILING_VALUE_TYPE_SKIPPED:
        if (op->total_merged >= 0 && op->total_skipped < CV_PROFILING_NUM_PAGES){
            op->merged_pages[op->total_skipped]=value;
            op->total_skipped++;
        }
        break;
    case CV_PROFILING_VALUE_TYPE_STOPPED_UPDATE_VERSION:
        op->update_stopped_here=value;
        break;
    }
}

static inline cv_profiling_print(struct cv_profiling_ops * ops){
    int i=ops->count;
    int op_count=0;
    char str[20*CV_PROFILING_NUM_PAGES];
    printk(KERN_EMERG "Conversion profiling for thread %d\n", ops->pid);
    for (;i>0 && op_count < CV_PROFILING_TOTAL_OPS;i--){
        op_count++;
        struct cv_profiling_single_op * op = &ops->single_ops[i % CV_PROFILING_TOTAL_OPS];
        printk(KERN_EMERG "...Operation type %d version %d update_stopped_here %d\n", op->prof_type, op->version_num, op->update_stopped_here);
        int k=0;
        int counter=0;
        memset(str, 0, 20*CV_PROFILING_NUM_PAGES);
        for (;k < op->total_committed % CV_PROFILING_NUM_PAGES;++k){
            counter+=sprintf(str+counter,"%d,", op->committed_pages[k]);
        }
        if (counter > 0){
            printk(KERN_EMERG "......Commited pages %s\n", str);
        }
        counter=0;
        memset(str, 0, 20*CV_PROFILING_NUM_PAGES);
        for (k=0;k < op->total_updated % CV_PROFILING_NUM_PAGES;++k){
            counter+=sprintf(str+counter,"%d,", op->updated_pages[k]);
        }
        if (counter > 0){
            printk(KERN_EMERG "......Updated pages %s %d\n", str);
        }
        counter=0;
        memset(str, 0, 20*CV_PROFILING_NUM_PAGES);
        for (k=0;k < op->total_merged % CV_PROFILING_NUM_PAGES;++k){
            counter+=sprintf(str+counter,"%d,", op->merged_pages[k]);
        }
        if (counter > 0){
            printk(KERN_EMERG "......Merged pages %s\n", str);
        }
        counter=0;
        memset(str, 0, 20*CV_PROFILING_NUM_PAGES);
        for (k=0;k < op->total_skipped % CV_PROFILING_NUM_PAGES;++k){
            counter+=sprintf(str+counter,"%d,", op->skipped_pages[k]);
        }
        if (counter > 0){
            printk(KERN_EMERG "......Skipped pages %s\n", str);
        }
    }
}

#else

static inline cv_profiling_begin(struct cv_profiling_ops * ops){}

static inline cv_profiling_op_begin(struct cv_profiling_ops * ops, cv_profiling_op_type prof_type){}

static inline cv_profiling_add_page(struct cv_profiling_ops * ops, int page_index, cv_profiling_value_type prof_page_type){}

static inline cv_profiling_print(struct cv_profiling_ops * ops){}

#endif


#endif
