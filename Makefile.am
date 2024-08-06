include $(top_srcdir)/aminclude.am
ACLOCAL_AMFLAGS = -I m4

GOEXT=@GOEXT@

VPATH = $(srcdir):$(builddir)

noinst_LIBRARIES = src/liblegendre.a
src_liblegendre_a_SOURCES = src/legendre.h src/bracelets.c \
src/seq_funcs.c src/bracelets.h src/defs.h src/seq_funcs.h
src_liblegendre_a_CPPFLAGS = -I$(top_srcdir)/src

if GO_
noinst_PROGRAMS = src/A src/B src/ordered_check_sums
else
noinst_PROGRAMS = src/A src/B
src_ordered_check_sums_SOURCES = src/ordered_check_sums.$(GOEXT)
endif

src_A_SOURCES = src/A.c
src_A_CPPFLAGS = -I$(top_srcdir)/src
src_A_LDADD = $(top_builddir)/src/liblegendre.a

src_B_SOURCES = src/B.c
src_B_CPPFLAGS = -I$(top_srcdir)/src
src_B_LDADD = $(top_builddir)/src/liblegendre.a

if GO_
$(top_builddir)/src/ordered_check_sums: $(top_srcdir)/src/ordered_check_sums.$(GOEXT)
	$(GOC) $(GOFLAGS) -o $@ $<
endif

all-local:
	-$(MAKE) doxygen-doc

clean-local:
	-rm -rf $(builddir)/docs

EXTRA_DIST = $(srcdir)/docs_pages $(srcdir)/var $(srcdir)/README.md
