## Process this file with automake to produce Makefile.in

AM_CFLAGS =\
	-Wall\
	-g\
	-D PACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-D PACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-D PACKAGE_DATA_DIR=\""$(datadir)"\" \
	-D PACKAGE_PREFIX=\""$(prefix)"\" \
	-D PACKAGE_LIB_DIR=\""$(libdir)"\" \
	-D GIR_DIR=\""$(datadir)/gir-1.0"\" \
	$(GKIU_CFLAGS)

bin_PROGRAMS = gkiu

gkiu_SOURCES = \
	main.c     \
	main.h      \
	manager.c  \
	manager.h  \
	config.c   \
	config.h   

gkiu_LDADD = $(GKIU_LIBS)

uninstall-local:
	-rm -r $(datadir)/gkiu

