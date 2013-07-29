#include <stdio.h>
#include <ngx_core.h>
#include <ngx_errno.h>
#include <ngx_cycle.h>
#include <ngx_process_cycle.h>
#include <ngx_string.h>
#include <nginx.h>
#include <ngx_files.h>
#include <ngx_log.h>

#define NGX_CONF_PATH			"/etc/nginx.conf"
#define NGX_CONFIGURE			"/etc/nginx.conf"


static ngx_uint_t   ngx_show_help;			//option:  show help info
static ngx_uint_t   ngx_show_version;		//option:  show version
static ngx_uint_t   ngx_show_configure;		//option:  show configure info
static u_char      *ngx_prefix;				//option:  -p <prefix_path>
static u_char      *ngx_conf_file;			//option:  -c <configure file>
static u_char      *ngx_conf_params;		//option:  -g <global device>
static char        *ngx_signal;				//option:  -s <signal>

/*
 *========================================
 *  deal with option
 *
 *  RET:  0 if success, otherwise non 0
 *========================================
 */
static ngx_int_t
ngx_get_options(int argc, char *const *argv)
{
	u_char     *p;
	ngx_int_t   i;

	for (i = 1; i < argc; i++) {

		p = (u_char *) argv[i];

		if (*p++ != '-') {
			ngx_log_stderr(0, "invalid option: \"%s\"", argv[i]);
			return NGX_ERROR;
		}

		while (*p) {

			switch (*p++) {

				case '?':
				case 'h':
					ngx_show_version = 1;
					ngx_show_help = 1;
					break;

				case 'v':
					ngx_show_version = 1;
					break;

				case 'V':
					ngx_show_version = 1;
					ngx_show_configure = 1;
					break;

				case 't':
					ngx_test_config = 1;
					break;

				case 'q':
					ngx_quiet_mode = 1;
					break;

				case 'p':
					if (*p) {
						ngx_prefix = p;
						goto next;
					}

					if (argv[++i]) {
						ngx_prefix = (u_char *) argv[i];
						goto next;
					}

					ngx_log_stderr(0, "option \"-p\" requires directory name");
					return NGX_ERROR;

				case 'c':
					if (*p) {
						ngx_conf_file = p;
						goto next;
					}

					if (argv[++i]) {
						ngx_conf_file = (u_char *) argv[i];
						goto next;
					}

					ngx_log_stderr(0, "option \"-c\" requires file name");
					return NGX_ERROR;

				case 'g':
					if (*p) {
						ngx_conf_params = p;
						goto next;
					}

					if (argv[++i]) {
						ngx_conf_params = (u_char *) argv[i];
						goto next;
					}

					ngx_log_stderr(0, "option \"-g\" requires parameter");
					return NGX_ERROR;

				case 's':
					if (*p) {
						ngx_signal = (char *) p;

					} else if (argv[++i]) {
						ngx_signal = argv[i];

					} else {
						ngx_log_stderr(0, "option \"-s\" requires parameter");
						return NGX_ERROR;
					}

					if (ngx_strcmp(ngx_signal, "stop") == 0
							|| ngx_strcmp(ngx_signal, "quit") == 0
							|| ngx_strcmp(ngx_signal, "reopen") == 0
							|| ngx_strcmp(ngx_signal, "reload") == 0)
					{
						ngx_process = NGX_PROCESS_SIGNALLER;
						goto next;
					}

					ngx_log_stderr(0, "invalid option: \"-s %s\"", ngx_signal);
					return NGX_ERROR;

				default:
					ngx_log_stderr(0, "invalid option: \"%c\"", *(p - 1));
					return NGX_ERROR;
			}
		}

next:

		continue;
	}

	return NGX_OK;
}

int
main (int argc, char *const *argv)
{
	ngx_log_t		*log;
	ngx_cycle_t		*cycle, init_cycle;

	if (ngx_strerror_init () != NGX_OK) {
		return 1;
	}

	// 参数处理
	if (ngx_get_options (argc, argv) != NGX_OK) {
		return 1;
	}

	if (ngx_show_version) {
		ngx_write_stderr("nginx version: " NGINX_VER NGX_LINEFEED);

		if (ngx_show_help) {
			ngx_write_stderr(
					"Usage: nginx [-?hvVtq] [-s signal] [-c filename] "
					"[-p prefix] [-g directives]" NGX_LINEFEED
					NGX_LINEFEED
					"Options:" NGX_LINEFEED
					"  -?,-h         : this help" NGX_LINEFEED
					"  -v            : show version and exit" NGX_LINEFEED
					"  -V            : show version and configure options then exit"
					NGX_LINEFEED
					"  -t            : test configuration and exit" NGX_LINEFEED
					"  -q            : suppress non-error messages "
					"during configuration testing" NGX_LINEFEED
					"  -s signal     : send signal to a master process: "
					"stop, quit, reopen, reload" NGX_LINEFEED
#ifdef NGX_PREFIX
					"  -p prefix     : set prefix path (default: "
					NGX_PREFIX ")" NGX_LINEFEED
#else
					"  -p prefix     : set prefix path (default: NONE)" NGX_LINEFEED
#endif
					"  -c filename   : set configuration file (default: "
					NGX_CONF_PATH ")" NGX_LINEFEED
					"  -g directives : set global directives out of configuration "
					"file" NGX_LINEFEED NGX_LINEFEED
					);
		}

		if (ngx_show_configure) {
			ngx_write_stderr(
#ifdef NGX_COMPILER
					"built by " NGX_COMPILER NGX_LINEFEED
#endif
#if (NGX_SSL)
#ifdef SSL_CTRL_SET_TLSEXT_HOSTNAME
					"TLS SNI support enabled" NGX_LINEFEED
#else
					"TLS SNI support disabled" NGX_LINEFEED
#endif
#endif
					"configure arguments:" NGX_CONFIGURE NGX_LINEFEED);
		}

		if (!ngx_test_config) {
			return 0;
		}
	}

	ngx_time_init ();

	ngx_pid = ngx_getpid ();

	// 初始化日志
	log = ngx_log_init (ngx_prefix);

	if (log == NULL) {
		return 1;
	}

	return 0;
}
