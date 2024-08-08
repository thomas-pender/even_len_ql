include $(top_srcdir)/aminclude.am
ACLOCAL_AMFLAGS = -I m4

GOEXT=@GOEXT@

noinst_LTLIBRARIES = src/liblegendre.la
src_liblegendre_la_SOURCES = $(top_srcdir)/src/legendre.h \
$(top_srcdir)/src/bracelets.c $(top_srcdir)/src/seq_funcs.c \
$(top_srcdir)/src/bracelets.h $(top_srcdir)/src/defs.h \
$(top_srcdir)/src/seq_funcs.h
src_liblegendre_la_CPPFLAGS = -I$(top_srcdir)/src

if GO_
noinst_PROGRAMS = src/A src/B src/ordered_check_sums
src_ordered_check_sums_SOURCES = $(top_srcdir)/src/ordered_check_sums.$(GOEXT)
else
noinst_PROGRAMS = src/A src/B
endif

src_A_SOURCES = $(top_srcdir)/src/A.c
src_A_CPPFLAGS = -I$(top_srcdir)/src
src_A_LDADD = $(top_builddir)/src/liblegendre.la

src_B_SOURCES = src/B.c
src_B_CPPFLAGS = -I$(top_srcdir)/src
src_B_LDADD = $(top_builddir)/src/liblegendre.la

if GO_
$(top_builddir)/src/ordered_check_sums: $(top_srcdir)/src/ordered_check_sums.$(GOEXT)
	$(GOC) $(GOFLAGS) -o $@ $<
endif

if DOXY_
all-local:
	$(MAKE) doxygen-doc
endif

clean-local:
	-rm -rf $(top_builddir)/docs $(top_builddir)/src

EXTRA_DIST = $(top_srcdir)/docs_pages $(top_srcdir)/data $(top_srcdir)/README.md
