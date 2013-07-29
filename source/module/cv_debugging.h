
#ifndef CV_DEBUGGING
#define CV_DEBUGGING

#include <linux/mm.h>

//Keeps track of how many times a page ref count is "put" in GC
#define CV_PAGE_DEBUG_GARBAGE_PUT_COUNT 0
#define CV_PAGE_DEBUG_REFPAGE_PUT_COUNT 1
#define CV_PAGE_DEBUG_UPDATE_OLDPAGE_PUT 2

#ifdef CV_DEBUG_ON
//if debugging is turned on...
#define cv_page_debugging_clear_flags(page,counter) \
    counter=0; \
    for (;counter<20;++counter) { \
        page->snap_page_debug[counter]=0; \
    }

#define cv_page_debugging_inc_flag(page, flag) \
    page->snap_page_debug[flag]++;

#define cv_page_debugging_print(page,counter)         \
    counter=0; \
    for (;counter<20;++counter) { \
        printk(KSNAP_LOG_LEVEL "PAGE FLAGS for %p\n", page); \
        printk(KSNAP_LOG_LEVEL "%d: %lu, ", counter, page->snap_page_debug[counter]); \
    } \
    printk(KSNAP_LOG_LEVEL "\n\n");

#define cv_page_debugging_set_flag(page,flag,val)       \
    page->snap_page_debug[flag]=val;

#else

//stubs for when debugging is off
#define cv_page_debugging_clear_flags(page,i)

#define cv_page_debugging_inc_flag(page, flag)

#define cv_page_debugging_print(page,counter)

#define cv_page_debugging_set_flag(page,flag,val)

#endif


#endif
