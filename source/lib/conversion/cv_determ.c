
#include <sys/syscall.h>

#include "ksnap.h"
#include "cv_determ.h"

#if __x86_64__
/* 64-bit */
#define __CONV_DETERM_INIT_SYS_CALL 305

#else

#define __CONV_DETERM_INIT_SYS_CALL 343

#endif

//mark the conversion segment as deterministic
void conv_determ_init(conv_seg * seg, void * token_addr){
    syscall(__CONV_DETERM_INIT_SYS_CALL, (unsigned long)(seg->segment), (unsigned long)token_addr);
}

void conv_determ_commit_and_update_token_release(conv_seg * seg){
    if(__get_meta_local_page(seg)->dirty_page_count == 0){
        msync(seg->segment,seg->size_of_segment, KSNAP_SYNC_MERGE | CONVERSION_DETERM_TOKEN_RELEASE);
    }
    else{
        msync(seg->segment,seg->size_of_segment, KSNAP_SYNC_MAKE | CONVERSION_DETERM_TOKEN_RELEASE);
    }
}

