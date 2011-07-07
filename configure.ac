dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(gkiu,[2.9.9])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

datadir=${datarootdir}/gkiu
libdir=${libdir}/gkiu

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_CONFIG_SRCDIR([src/main.c])

AC_PROG_CC

# pkg-config
PKG_CONFIG=[pkg-config]

#
# Gobject Introspection
#
AC_CONFIG_MACRO_DIR([m4])
INTROSPECTION_SCANNER=`$PKG_CONFIG --variable=g_ir_scanner gobject-introspection-1.0`
INTROSPECTION_COMPILER=`$PKG_CONFIG --variable=g_ir_compiler gobject-introspection-1.0`
INTROSPECTION_GENERATE=`$PKG_CONFIG --variable=g_ir_generate gobject-introspection-1.0`
INTROSPECTION_GIRDIR=`$PKG_CONFIG --variable=girdir gobject-introspection-1.0`
INTROSPECTION_TYPELIBDIR="$($PKG_CONFIG --variable=typelibdir gobject-introspection-1.0)"
INTROSPECTION_CFLAGS=`$PKG_CONFIG --cflags gobject-introspection-1.0`
INTROSPECTION_LIBS=`$PKG_CONFIG --libs gobject-introspection-1.0`
INTROSPECTION_MAKEFILE=`$PKG_CONFIG --variable=datadir gobject-introspection-1.0`/gobject-introspection-1.0/Makefile.introspection

AC_SUBST(INTROSPECTION_SCANNER)
AC_SUBST(INTROSPECTION_COMPILER)
AC_SUBST(INTROSPECTION_GENERATE)
AC_SUBST(INTROSPECTION_GIRDIR)
AC_SUBST(INTROSPECTION_TYPELIBDIR)
AC_SUBST(INTROSPECTION_CFLAGS)
AC_SUBST(INTROSPECTION_LIBS)
AC_SUBST(INTROSPECTION_MAKEFILE)

dnl ================================================================
dnl Python
dnl ================================================================

PYTHON_REQUIRED=2.5.2

AM_PATH_PYTHON($PYTHON_REQUIRED, [found_python="yes"],[found_python="no (python interpretor >= ${PYTHON_REQUIRED} not found"])

dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=[gkiu]
LOCALEDIR=[mo]
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

AM_PROG_LIBTOOL

PKG_CHECK_MODULES(GKIU, [
gio-2.0 \
gtk+-3.0 \
libpeas-gtk-1.0 \
libpeas-1.0 \
libnotify >= 0.7.0 \
gnome-keyring-1])

AC_CONFIG_FILES([
Makefile
src/Makefile
m4/Makefile
po/Makefile.in
data/Makefile
modules/Makefile
modules/keyring/Makefile
modules/iMode/Makefile
modules/imui/Makefile
])

AC_OUTPUT

echo "

================================================
Source code location                : ${srcdir}
Compiler                            : ${CC}
Installation prefix                 : ${prefix}
================================================

Now type 'make' to compile.
"