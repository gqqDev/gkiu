dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(gkiu,[2.9.9])
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_CONFIG_SRCDIR([src/main.c])

AC_PROG_CC

# pkg-config
PKG_CONFIG=[pkg-config]

dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=[gkiu]
LOCALEDIR=[locale]
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])

AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])

AM_PROG_LIBTOOL

PKG_CHECK_MODULES(GKIU, [
gio-2.0 \
gtk+-3.0 >= 3.0 \
libpeas-gtk-1.0 \
libpeas-1.0 \
dbus-glib-1])

AC_CONFIG_FILES([
Makefile
src/Makefile
po/Makefile.in
data/Makefile
data/pictures/Makefile
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
