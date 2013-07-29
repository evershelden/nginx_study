#ifndef _NGX_CORE_H_INCLUDE_
#define _NGX_CORE_H_INCLUDE_

#include <sys/types.h>
#include <inttypes.h>


#define LF     (u_char) 10

#define NGX_OK			0
#define NGX_ERROR		-1

#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

#define ngx_abs(value)       (((value) >= 0) ? (value) : - (value))
#define ngx_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))


typedef int                      ngx_fd_t;
typedef struct ngx_log_s         ngx_log_t;
typedef struct ngx_open_file_s   ngx_open_file_t;

#endif
