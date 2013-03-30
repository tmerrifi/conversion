
#ifdef __cplusplus
 extern "C" {
#endif

#include <time.h>

struct timespec * time_util_create_timespec(int milliseconds);

struct timespec * time_util_create_timespec_us(int microseconds);

long time_util_time_diff(struct timespec * start, struct timespec * end);

#ifdef __cplusplus
 }
#endif
