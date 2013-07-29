#ifndef _NGX_CONFIG_H_INCLUDE_
#define _NGX_CONFIG_H_INCLUDE_

#include <stdint.h>
#include <sys/resource.h>

#ifndef NGX_SYS_NERR
#define NGX_SYS_NERR  135
#endif

typedef intptr_t        ngx_int_t;
typedef uintptr_t       ngx_uint_t;
typedef intptr_t        ngx_flag_t;

#define ngx_cdecl

#define NGX_PREFIX				"/tmp"
#define NGX_ERROR_LOG_PATH		"a.log"

#define NGX_INT32_LEN   sizeof("-2147483648") - 1
#define NGX_INT64_LEN   sizeof("-9223372036854775808") - 1

#if (NGX_PTR_SIZE == 4)
#define NGX_INT_T_LEN   NGX_INT32_LEN
#else
#define NGX_INT_T_LEN   NGX_INT64_LEN
#endif

#if ((__GNU__ == 2) && (__GNUC_MINOR__ < 8))
#define NGX_MAX_UINT32_VALUE  (uint32_t) 0xffffffffLL
#else
#define NGX_MAX_UINT32_VALUE  (uint32_t) 0xffffffff
#endif

#define NGX_MAX_INT32_VALUE   (uint32_t) 0x7fffffff

#ifndef ngx_inline
#define ngx_inline      inline
#endif


#ifndef NGX_PTR_SIZE
#define NGX_PTR_SIZE  8
#endif

#endif
