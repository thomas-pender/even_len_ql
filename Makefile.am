include $(top_srcdir)/aminclude.am
ACLOCAL_AMFLAGS = -I m4

GOC=@GOC@
GOEXT=@GOEXT@

VPATH = $(srcdir):$(builddir)

BUILT_SOURCES = $(builddir)/src/ordered_check_sums

noinst_LIBRARIES = src/liblegendre.a
src_liblegendre_a_SOURCES = src/legendre.h src/bracelets.c \
src/seq_funcs.c src/bracelets.h src/defs.h src/seq_funcs.h
src_liblegendre_a_CPPFLAGS = -I$(top_srcdir)/src

noinst_PROGRAMS = src/A src/B

src_A_SOURCES = src/A.c
src_A_CPPFLAGS = -I$(top_srcdir)/src
src_A_LDADD = src/liblegendre.a

src_B_SOURCES = src/B.c
src_B_CPPFLAGS = -I$(top_srcdir)/src
src_B_LDADD = src/liblegendre.a

$(builddir)/src/ordered_check_sums: src/ordered_check_sums.$(GOEXT)
	-$(GOC) build -o $@ $<

all-local:
	-$(MAKE) doxygen-doc

clean-local:
	-rm -rf docs

CLEANFILES = $(builddir)/src/ordered_check_sums
