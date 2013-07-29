#include <ngx_log.h>
#include <ngx_files.h>
#include <ngx_alloc.h>

static ngx_log_t		ngx_log;
static ngx_open_file_t	ngx_log_file;

void ngx_cdecl
ngx_log_stderr(ngx_err_t err, const char *fmt, ...)
{
    u_char   *p, *last;
    va_list   args;
    u_char    errstr[NGX_MAX_ERROR_STR];

    last = errstr + NGX_MAX_ERROR_STR;
    p = errstr + 7;

    ngx_memcpy(errstr, "nginx: ", 7);


    va_start(args, fmt);
    p = ngx_vslprintf(p, last, fmt, args);
    va_end(args);

    if (err) {
        p = ngx_log_errno(p, last, err);
    }


    if (p > last - NGX_LINEFEED_SIZE) {
        p = last - NGX_LINEFEED_SIZE;
    }

    ngx_linefeed(p);

    (void) ngx_write_console(ngx_stderr, errstr, p - errstr);
}

u_char *
ngx_log_errno(u_char *buf, u_char *last, ngx_err_t err)
{
	if (buf > last - 50) {

		/* leave a space for an error code */

		buf = last - 50;
		*buf++ = '.';
		*buf++ = '.';
		*buf++ = '.';
	}

#if (NGX_WIN32)
	buf = ngx_slprintf(buf, last, ((unsigned) err < 0x80000000)
			? " (%d: " : " (%Xd: ", err);
#else
	buf = ngx_slprintf(buf, last, " (%d: ", err);
#endif
	buf = ngx_strerror(err, buf, last - buf);

	if (buf < last) {
		*buf++ = ')';
	}


	return buf;
}

ngx_log_t *
ngx_log_init (u_char *prefix)
{
	u_char 		*p, *name;
	size_t		nlen, plen;

	ngx_log.file = &ngx_log_file;
	ngx_log.log_level = NGX_LOG_NOTICE;

	name = (u_char *) NGX_ERROR_LOG_PATH;

	nlen = ngx_strlen (name);

	if (nlen == 0) {
		ngx_log_file.fd = ngx_stderr;
		return &ngx_log;
	}

	p = NULL;

	if (name[0] != '/') {
		if (prefix) {
			plen = ngx_strlen (prefix);
		} else {
			prefix = (u_char *) NGX_PREFIX;
			plen = ngx_strlen (prefix);
		}

		if (plen) {
			name = malloc (plen + nlen + 2);
			if (name == NULL) {
				return NULL;
			}
			
			p = ngx_cpymem (name, prefix, plen);

			if (!ngx_path_separator (*(p - 1))) {
				*p++ = '/';
			}

			ngx_cpystrn (p, (u_char *) NGX_ERROR_LOG_PATH, nlen + 1);
			p = name;
		}
	}

	ngx_log_file.fd = ngx_open_file (name, NGX_FILE_APPEND,
										   NGX_FILE_CREATE_OR_OPEN,
										   NGX_FILE_DEFAULT_ACCESS);

	if (ngx_log_file.fd == NGX_INVALID_FILE) {
		ngx_log_stderr (ngx_errno,
                       "[alert] could not open error log file: "
                       ngx_open_file_n " \"%s\" failed", name);
		ngx_log_file.fd = ngx_stderr;
	}

	if (p) {
		ngx_free (p);
	}
	return &ngx_log;
}
