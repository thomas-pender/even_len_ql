AC_PREREQ([2.71])
AC_INIT([evenlen_ql], [0.0])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/A.c])
AC_CONFIG_HEADERS([src/config.h])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

#-------------------------------------------------
# doxygen
#-------------------------------------------------
DX_INIT_DOXYGEN([$PACKAGE_NAME],[Doxyfile],doc)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
#-------------------------------------------------

: ${CFLAGS="-O3"}
AC_PROG_CC

#-------------------------------------------------
# Golang compilation
#-------------------------------------------------
AC_ARG_ENABLE([_go],
[AS_HELP_STRING([--disable-go],
[disable compilation of golang scripts @<:@default: enabled@:>@])],
[_go=${enableval}], [_go=yes])

AM_CONDITIONAL([GO_], [test "x${_go}" = xyes])

if test "x${_go}" = xyes; then
: ${GOFLAGS="-O3"}
AC_PROG_GO
GOEXT=go
AC_SUBST([GOEXT])
fi
#-------------------------------------------------

AC_PROG_RANLIB
AM_PROG_AR

#-------------------------------------------------
# asynchronous execution
#-------------------------------------------------
AC_ARG_ENABLE([async-exec],
[AS_HELP_STRING([--disable-async-exec],
[disable asynchronous execution @<:@default: enabled@:>@])],
[async_exec=${enableval}], [async_exec=yes])

if test "x${async_exec}" = xyes; then
  AX_PTHREAD
  CC=$PTHREAD_CC
  LIBS="$PTHREAD_LIBS $LIBS"
  CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
  AC_DEFINE([ASYNC_EXEC], [1], [asynchronous execution enabled])
fi
#-------------------------------------------------

#-------------------------------------------------
# link to -lm (required)
#-------------------------------------------------
AC_CHECK_HEADERS([complex.h], [],
[AC_MSG_ERROR([
========================================
Header complex.h ***NOT*** found @{:@required@:}@.
Stopping...
========================================])])
AC_SEARCH_LIBS([cexp], [m], [], [AC_MSG_ERROR([
========================================
Library -lm ***NOT*** found @{:@required@:}@.
Stopping...
========================================])])
#-------------------------------------------------

AC_CONFIG_FILES([Makefile Doxyfile])

AC_OUTPUT

cat << EOF

============================================================

${PACKAGE_NAME} Version ${PACKAGE_VERSION}

C compiler: '${CC} ${CFLAGS} ${CPPFLAGS} ${LDFLAGS} ${LIBS}'
Go compiler (enabled? ${_go}): '${GOC} ${GOFLAGS}'

Package features:
        - asynchronous execution enabled? ${async_exec}

Compile with 'make'.

============================================================

EOF
