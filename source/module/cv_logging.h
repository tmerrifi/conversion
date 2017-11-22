#ifndef CV_LOGGING_H
#define CV_LOGGING_H

#include "cv_merge.h"

struct ksnap;
struct ksnap_user_data;
struct cv_logging_page_status_entry;

//#define CV_LOGGING_MERGE_AND_DIFF

#define CV_LOGGING_COMPUTE_DIFF_PAGES 256

#define CV_FORCE_LOGGING 1

#ifdef CV_FORCE_LOGGING
//every N committed pages, we check to see if this page should be turned into a logging page
//#define CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES 64
#define CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES 1
//how many 64bit words can be different in order to trigger a switch to logging
#define CV_LOGGING_DIFF_THRESHOLD_64 64
#else
//every N committed pages, we check to see if this page should be turned into a logging page
#define CV_LOGGING_DIFF_CHECK_COMMITTED_PAGES 128
//how many 64bit words can be different in order to trigger a switch to logging
#define CV_LOGGING_DIFF_THRESHOLD_64 3

#endif //CV_FORCE_LOGGING

#define CV_LOGGING_DIFF_N 8

#define CV_LOGGING_MERGE_N 8

//size we log in bytes
#define CV_LOGGING_LOG_SIZE 64UL

#define CV_LOGGING_LOG_MASK (~((1<<6)-1))

#define CV_LOGGING_WRITES_THRESHOLD 5

#define CV_LOGGING_INSTRUCTION_MAX_WIDTH 15  //maximum width for an instruction when we decode it

#define CV_LOGGING_MERGE_WORDS (CV_LOGGING_LOG_SIZE/sizeof(uint64_t))

#define CV_LOGGING_LINES_PER_PAGE (PAGE_SIZE/CV_LOGGING_LOG_SIZE)

#define cv_logging_last_n_bits_set(bits, n) ((bits & ((1UL << n)-1))==((1UL << n)-1))

#define cv_logging_is_full_page(e) (e->data_len>=PAGE_SIZE)

#define cv_logging_line_start(addr) (addr & CV_LOGGING_LOG_MASK )

#define cv_logging_line_index(addr) (((addr & CV_LOGGING_LOG_MASK ) & ~PAGE_MASK) / CV_LOGGING_LOG_SIZE )

#define cv_logging_set_dirty(e) (e->dirty=1)

#define cv_logging_clear_dirty(e) (e->dirty=0)

#define cv_logging_is_dirty(e) (e->dirty==1)


int cv_logging_diff_64(uint8_t * local, struct page * ref_page);

void cv_merge_lines(uint8_t * local, uint8_t * latest, uint8_t * ref);

void cv_logging_print_stats(struct ksnap * cv_seg);

void cv_logging_instruction_stats(struct ksnap * cv_seg, struct ksnap_user_data * cv_user, unsigned long addr);

int cv_logging_fault(struct vm_area_struct * vma, struct ksnap * cv_seg, struct ksnap_user_data * cv_user,
                     struct pt_regs * regs, unsigned long faulting_addr);

unsigned long cv_logging_get_index(unsigned long addr, unsigned long page_index, int is_page_level);

/*functions that work with the page_status_entry data structure. That keeps track of each thread's local logging pages*/

int cv_logging_page_status_insert(struct ksnap_user_data * cv_user, struct cv_logging_page_status_entry * entry, unsigned long page_index);

struct cv_logging_page_status_entry * cv_logging_page_status_lookup(struct ksnap_user_data * cv_user, unsigned long page_index);

struct cv_logging_page_status_entry * cv_logging_page_status_entry_init(pte_t * pte, unsigned long pfn,
                                                                        unsigned long page_index, uint64_t version_num);

void cv_merge_line(uint8_t * local, uint8_t * ref, uint8_t * latest);

#define cv_logging_page_status_to_kaddr(e,li) ((uint8_t *)pfn_to_kaddr(e->pfn) + (li * CV_LOGGING_LOG_SIZE) )

uint8_t * cv_logging_allocate_data_entry(int data_len, struct ksnap * cv_seg);

void cv_logging_free_data_entry(int data_len, struct ksnap * cv_seg, void * data);

struct page * cv_logging_cow_page(struct vm_area_struct * vma, pte_t * pte, unsigned long faulting_addr);

#define sum_page(ptr,i,sum) for(i=0;i<PAGE_SIZE/sizeof(int);i++){sum+=*ptr++;}

#ifdef CV_MEMTRACE_DEBUG
#define CV_LOGGING_DEBUG_PRINT_LINE(linedata,p,l,msg)                   \
    if (linedata!=(uint8_t *)0xDEAD && p==LOGGING_DEBUG_PAGE_INDEX && l==LOGGING_DEBUG_LINE) \
        printk( KERN_INFO "memtrace: %d %s, line: %d, page: %d, addr %p, data %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | \
%d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d | %d %d %d %d %d %d %d %d  \n", \
           current->pid,(msg),l,p,linedata,                             \
        (linedata)[0],(linedata)[1],(linedata)[2],(linedata)[3],(linedata)[4],(linedata)[5],(linedata)[6],(linedata)[7], \
           (linedata)[8],(linedata)[9],(linedata)[10],(linedata)[11],(linedata)[12],(linedata)[13],(linedata)[14],(linedata)[15], \
    (linedata)[16],(linedata)[17],(linedata)[18],(linedata)[19],(linedata)[20],(linedata)[21],(linedata)[22],(linedata)[23], \
        (linedata)[24],(linedata)[25],(linedata)[26],(linedata)[27],(linedata)[28],(linedata)[29],(linedata)[30],(linedata)[31], \
        (linedata)[32],(linedata)[33],(linedata)[34],(linedata)[35],(linedata)[36],(linedata)[37],(linedata)[38],(linedata)[39], \
        (linedata)[40],(linedata)[41],(linedata)[42],(linedata)[43],(linedata)[44],(linedata)[45],(linedata)[46],(linedata)[47], \
        (linedata)[48],(linedata)[49],(linedata)[50],(linedata)[51],(linedata)[52],(linedata)[53],(linedata)[54],(linedata)[55], \
    (linedata)[56],(linedata)[57],(linedata)[58],(linedata)[59],(linedata)[60],(linedata)[61],(linedata)[62],(linedata)[63]);

    /* else{ \ */
    /* trace_printk("memtrace: nope\n");\ */
    /* } */

#else
#define CV_LOGGING_DEBUG_PRINT_LINE(linedata,p,l,msg)   \
    
#endif


#endif
