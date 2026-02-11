#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([morse], [0.1])
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_SEARCH_LIBS([sin], [m])
AC_SEARCH_LIBS([ao_initialize], [ao])

# Checks for header files.
AC_CHECK_HEADERS([string.h unistd.h])
AC_CHECK_HEADERS([ao/ao.h], [have_ao=yes], [have_ao=no])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])
AM_PROG_AR
LT_INIT

AM_CONDITIONAL([HAVE_AO], [test "x$have_ao" = "xyes"])

AC_OUTPUT
