#ifndef _NGX_PROCESS_CYCLE_H_INCLUDE_
#define _NGX_PROCESS_CYCLE_H_INCLUDE_

#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_process.h>

#define NGX_PROCESS_SINGLE     0
#define NGX_PROCESS_MASTER     1
#define NGX_PROCESS_SIGNALLER  2
#define NGX_PROCESS_WORKER     3
#define NGX_PROCESS_HELPER     4

extern ngx_uint_t		ngx_process;
extern ngx_pid_t		ngx_pid;
#endif
