#ifndef _NGX_STRING_H_INCLUDE_
#define _NGX_STRING_H_INCLUDE_

#include <string.h>
#include <ngx_core.h>
#include <stdarg.h>
#include <ngx_time.h>
#include <ngx_process.h>
#include <ngx_config.h>
#include <ngx_atomic.h>

typedef struct {
	size_t		len;
	u_char		*data;
}ngx_str_t;


typedef struct {
	unsigned    len:28;

	unsigned    valid:1;
	unsigned    no_cacheable:1;
	unsigned    not_found:1;
	unsigned    escape:1;

	u_char     *data;
} ngx_variable_value_t;

#define ngx_strlen(s)			strlen((const char *) s)

#define ngx_strcmp(s1, s2)		strcmp((const char *) s1, (const char *) s2)

#define ngx_strncmp(s1, s2, n)	\
	strncmp ((const char *) s1, (const char *) s2, n)



#define ngx_memcpy(dst, src, n)   (void) memcpy(dst, src, n)
#define ngx_cpymem(dst, src, n)   (((u_char *) memcpy(dst, src, n)) + (n))

u_char *
ngx_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args);

u_char * ngx_cdecl
ngx_slprintf(u_char *buf, u_char *last, const char *fmt, ...);

u_char *
ngx_cpystrn(u_char *dst, u_char *src, size_t n);
#endif
