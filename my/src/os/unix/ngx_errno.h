#ifndef _NGX_ERRNO_H_INCLUDE_
#define _NGX_ERRNO_H_INCLUDE_

#include <errno.h>
#include <ngx_config.h>
#include <ngx_core.h>


#define ngx_errno                  errno

//XWL  init string using constant
#define ngx_string(str)     { sizeof(str) - 1, (u_char *) str }

typedef int				ngx_err_t;

u_char *
ngx_strerror(ngx_err_t err, u_char *errstr, size_t size);

ngx_int_t ngx_strerror_init (void);


#endif
