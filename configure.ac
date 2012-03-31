#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([aldo], [0.7.7], [Giuseppe Martino denever@users.sf.net])
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

CPPFLAGS="-I${includedir}"
LDFLAGS="-L${libdir}"
LIBS="-L${libdir} ${LIBS}"

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
#AC_PROG_RANLIB

# Checks for header files.
AC_HEADER_STDC	    
AC_CHECK_LIB(ao, main)
AC_CHECK_HEADERS(ao/ao.h, [], [echo "Error! You need to have libao (www.xiph.org/ao) around.";exit -1])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_CHECK_FUNCS([floor])

AC_CONFIG_FILES([Makefile
		 include/Makefile
                 src/Makefile])
AC_OUTPUT
