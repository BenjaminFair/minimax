# rule for processing test files
.ts.c:
	checkmk $< > $@

TESTS = check_tree
check_PROGRAMS = check_tree
check_tree_SOURCES = check_tree.ts $(top_builddir)/src/tree.h
check_tree_CFLAGS = @CHECK_CFLAGS@
check_tree_LDADD = $(top_builddir)/src/libtree.la @CHECK_LIBS@

MOSTLYCLEANFILES = check_tree.c