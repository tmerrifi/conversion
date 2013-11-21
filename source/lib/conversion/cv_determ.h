
#ifdef __cplusplus
 extern "C" {
#endif

#ifndef CV_DETERM_H
#define CV_DETERM_H

#include "ksnap.h"
     
     void conv_determ_init(conv_seg * seg, void * token_addr);

     void conv_determ_commit_and_update_token_release(conv_seg * seg);


#endif

#ifdef __cplusplus
 }
#endif
