AC_PREREQ([2.67])

AC_INIT([libsampgdk], [0.0.0])
AM_INIT_AUTOMAKE([1.9 foreign])

AC_CONFIG_SRCDIR([src/core.cpp])
#AC_CONFIG_HEADERS([config.h])

LT_INIT([disable-static])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h malloc.h stddef.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([getpagesize memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
