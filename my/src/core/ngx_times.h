#ifndef _NGX_TIMES_H_INCLUDED_
#define _NGX_TIMES_H_INCLUDED_

#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_string.h>

typedef struct {
	time_t      sec;
	ngx_uint_t  msec;
	ngx_int_t   gmtoff;
} ngx_time_t;

void ngx_time_init (void);

void
ngx_gmtime(time_t t, ngx_tm_t *tp);

void
ngx_time_update (void);

void
test_print_time (void);
#endif
