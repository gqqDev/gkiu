## Process this file with automake to produce Makefile.in

SUBDIRS = src po data

gkiudocdir = ${prefix}/doc/gkiu

gkiudoc_DATA = \
	README.asciidoc\
	COPYING\
	AUTHORS\
	INSTALL

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(gkiudoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache \

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gkiudocdir)

