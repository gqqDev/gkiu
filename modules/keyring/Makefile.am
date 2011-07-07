plugindir = $(libdir)/gkiu/modules/keyring

INCLUDES = \
	-I$(top_srcdir) \
	$(GKIU_CFLAGS)

plugin_LTLIBRARIES = libkeyring.la

libkeyring_la_SOURCES = \
		keyring.c\
		keyring.h

libkeyring_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)
libkeyring_la_LIBADD = $(GKIU_LIBS) 

plugin_DATA = keyring.plugin

EXTRA_DIST = $(plugin_DATA)

# GObject Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS = keyring.gir
INTROSPECTION_SCANNER_ARGS = \
	-I$(top_srcdir) 		\
	--warn-all

introspection_sources = $(INST_H_FILES) $(C_FILES)

keyring.gir: libkeyring.la

keyring_gir_INCLUDES = GObject-2.0 GModule-2.0 Peas-1.0
keyring_gir_CFLAGS = $(GKIU_CFLAGS)
keyring_gir_LIBS = libkeyring.la
keyring_gir_FILES = keyring.c keyring.h

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

keyring.gir: $(G_IR_SCANNER)
	$(INTROSPECTION_SCANNER) -n keyring \
		--program "../../src/gkiu" \
		--add-include-path=. \
		--output $@	\
		--pkg libpeas-1.0 \
		$(keyring_gir_FILES)

CLEANFILES = \
	$(gir_DATA)