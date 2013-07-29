
bin_PROGRAMS = nginx

noinst_LTLIBRARIES = libcore.la libunix.la

AM_CFLAGS = -Werror


INCLUDE = -I$(top_srcdir)/src/core -I$(top_srcdir)/src/os/unix

nginx_SOURCES = core/nginx.c
nginx_LDADD = libcore.la libunix.la
nginx_CFLAGS = -I$(top_srcdir)/src/core -I$(top_srcdir)/src/os/unix

libcore_la_SOURCES = 	core/ngx_config.h						\
				core/ngx_core.h core/ngx_log.c					\
				core/rbtree.h core/ngx_string.c					\
				core/ngx_string.h core/ngx_cycle.c				\
				core/ngx_cycle.h core/ngx_times.c

libcore_la_CFLAGS = -I$(top_srcdir)/src/core -I$(top_srcdir)/src/os/unix

libunix_la_SOURCES =  os/unix/ngx_errno.c						\
				os/unix/ngx_errno.h os/unix/ngx_files.h	\
				os/unix/ngx_time.h os/unix/ngx_process.h\
				os/unix/ngx_atomic.h os/unix/ngx_process_cycle.c	\
				os/unix/ngx_time.c os/unix/ngx_alloc.h				\
				os/unix/ngx_alloc.h
libunix_la_LIBADD = libcore.la
libunix_la_CFLAGS = -I$(top_srcdir)/src/core -I$(top_srcdir)/src/os/unix
