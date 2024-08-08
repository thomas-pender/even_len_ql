AC_PREREQ([2.71])
AC_INIT([evenlen_ql], [0.0])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/A.c])
AC_CONFIG_HEADERS([src/config.h])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

AM_PROG_AR

LT_PREREQ([2.4.6])
LT_INIT([dlopen])

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

if test "x${DX_FLAG_doc}" = "x1"; then
_doxy=yes
fi

AM_CONDITIONAL([DOXY_], [test "x${_doxy}" = xyes])
#-------------------------------------------------

: ${CFLAGS="-O3"}
AC_PROG_CC

#-------------------------------------------------
# Golang compilation
#-------------------------------------------------
AC_ARG_ENABLE([go],
[AS_HELP_STRING([--disable-go],
[disable compilation of golang scripts @<:@default: enabled@:>@])],
[_go=${enableval}], [_go=yes])

AM_CONDITIONAL([GO_], [test "x${_go}" = xyes])

if test "x${_go}" = xyes; then
AC_PROG_GO
GOFLAGS="-O3"
GOEXT=go
AC_SUBST([GOEXT])
AC_SUBST([GOFLAGS])
fi
#-------------------------------------------------

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

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_RESTRICT
AC_TYPE_SIZE_T

AC_CONFIG_FILES([Makefile Doxyfile])

AC_OUTPUT

cat << EOF

============================================================

${PACKAGE_NAME} Version ${PACKAGE_VERSION}

C compiler: '${CC} ${CFLAGS} ${CPPFLAGS} ${LDFLAGS} ${LIBS}'
Go compiler (enabled? ${_go}): '${GOC} ${GOFLAGS}'

Package features:
EOF

if test "x${async_exec}" = xyes; then
cat << EOF
        - asynchronous execution enabled.
EOF
else
cat << EOF
        - asynchronous execution disabled.
EOF
fi

if test "x${_go}" = xyes; then
cat << EOF
        - Go compilation enabled.
EOF
else
cat << EOF
        - Go compilation disabled.
EOF
fi

if test "x${_doxy}" = xyes; then
cat << EOF
        - Doxygen documentation enabled.
EOF
else
cat << EOF
        - Doxygen documentation disabled.
EOF
fi

cat << EOF

Compile with 'make'.

============================================================

EOF
