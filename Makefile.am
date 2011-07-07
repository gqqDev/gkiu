## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/introspection
SUBDIRS = src modules po data m4

gkiudocdir = ${prefix}/doc/gkiu

gkiudoc_DATA = \
	README.asciidoc\
	COPYING\
	AUTHORS\
	INSTALL

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST += $(gkiudoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gkiudocdir)

