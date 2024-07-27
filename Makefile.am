include $(top_srcdir)/aminclude.am
ACLOCAL_AMFLAGS = -I m4

noinst_LIBRARIES = common/liblegendre.a
common_liblegendre_a_SOURCES = common/bracelets.h common/defs.h common/seq_funcs.h common/bracelets.c common/seq_funcs.c
common_liblegendre_a_CPPFLAGS = -I$(top_srcdir)/common

noinst_PROGRAMS = src/A src/B

src_A_SOURCES = src/A.c common/legendre.h
src_A_CPPFLAGS = -I$(top_srcdir)/common
src_A_LDADD = common/liblegendre.a

src_B_SOURCES = src/B.c common/legendre.h
src_B_CPPFLAGS = -I$(top_srcdir)/common
src_B_LDADD = common/liblegendre.a

clean-obj:
	-rm -f common/*.[ao] src/*.o

go: src/ordered_check_sums.go
	-go build -o src/ordered_check_sums src/ordered_check_sums.go

install-exec-hook: all go doxygen-doc clean-obj

uninstall-hook: distclean
	-rm -rf docs/

CLEANFILES = src/ordered_check_sums
