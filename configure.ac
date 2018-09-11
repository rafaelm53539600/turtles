AC_INIT([turtle], [0.1], [rmartine@ucm.es])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CHECK_HEADERS([curses.h ],
        [curses_headers=yes; break;])
AS_IF([test "x$curses_headers" != "xyes"],
        [AC_MSG_ERROR([Unable to find the curses headers])])	
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
src/Makefile
])
AC_OUTPUT
