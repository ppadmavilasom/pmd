noinst_LTLIBRARIES = libpmdsecurity.la

libpmdsecurity_la_CPPFLAGS = \
    -I$(top_srcdir)/include

libpmdsecurity_la_SOURCES = \
    apisecurity.c \
    authz.c \
    rsa.c \
    utils.c

libpmdsecurity_la_LDFLAGS = \
    -static \
    @top_builddir@/common/libcommon.la
