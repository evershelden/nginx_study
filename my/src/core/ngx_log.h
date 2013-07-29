#ifndef _NGX_LOG_H_INCLUDE_
#define  _NGX_LOG_H_INCLUDE_

#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_errno.h>
#include <stdarg.h>
#include <ngx_log.h>
#include <ngx_string.h>
#include <ngx_files.h>
#include <ngx_conf_file.h>


#define NGX_LOG_STDERR            0
#define NGX_LOG_EMERG             1
#define NGX_LOG_ALERT             2
#define NGX_LOG_CRIT              3
#define NGX_LOG_ERR               4
#define NGX_LOG_WARN              5
#define NGX_LOG_NOTICE            6
#define NGX_LOG_INFO              7
#define NGX_LOG_DEBUG             8
#define NGX_MAX_ERROR_STR   2048


typedef u_char *(*ngx_log_handler_pt) (ngx_log_t *log, u_char *buf, size_t len);

struct ngx_log_s {
	ngx_uint_t           log_level;
	ngx_open_file_t     *file;

	ngx_atomic_uint_t    connection;

	ngx_log_handler_pt   handler;
	void                *data;

	/*
	 * we declare "action" as "char *" because the actions are usually
	 * the static strings and in the "u_char *" case we have to override
	 * their types all the time
	 */

	char                *action;
};

void
ngx_log_stderr (ngx_err_t err, const char *fmt, ...);


u_char *
ngx_log_errno(u_char *buf, u_char *last, ngx_err_t err);


static ngx_inline void
ngx_write_stderr(char *text)
{
	(void) ngx_write_fd(ngx_stderr, text, strlen(text));
}
#endif
