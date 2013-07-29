#ifndef _NGX_ATOMIC_H_INCLUDE_
#define _NGX_ATOMIC_H_INCLUDE_

#include <ngx_core.h>



typedef long						ngx_atomic_int_t;
typedef uint32_t                    ngx_atomic_uint_t;

typedef volatile ngx_atomic_uint_t  ngx_atomic_t;

#define ngx_atomic_cmp_set(lock, old, set)           \
	__sync_bool_compare_and_swap(lock, old, set)


#define ngx_memory_barrier()        __sync_synchronize()

#if (NGX_PTR_SIZE == 8)
#define NGX_ATOMIC_T_LEN            (sizeof("-9223372036854775808") - 1)
#else
#define NGX_ATOMIC_T_LEN            (sizeof("-2147483648") - 1)
#endif

#define ngx_trylock(lock)							\
	(*(lock) == 0 && ngx_atomic_cmp_set(lock, 0, 1))
#define ngx_unlock(lock)			*(lock) = 0

#endif
