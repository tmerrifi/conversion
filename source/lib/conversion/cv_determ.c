
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
