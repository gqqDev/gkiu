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

dnl ================================================================
dnl Python
dnl ================================================================

PYTHON_REQUIRED=2.5.2

AM_PATH_PYTHON($PYTHON_REQUIRED, [found_python="yes"],[found_python="no (python interpretor >= ${PYTHON_REQUIRED} not found"])

dnl ================================================================
dnl Vala
dnl ================================================================
AC_DEFUN([CHECK_VALAC],
[AC_PATH_PROG([VALAC], [valac], [])
 AS_IF([test -z "$VALAC"],
   [AC_MSG_WARN([No Vala compiler found.  You will not be able to compile .vala source files.])],
   [AS_IF([test -n "$1"],
      [AC_MSG_CHECKING([$VALAC is at least version $1])
       am__vala_version=`$VALAC --version | sed 's/Vala  *//'`
       AS_VERSION_COMPARE([$1], ["$am__vala_version"],
         [AC_MSG_RESULT([yes])],
         [AC_MSG_RESULT([yes])],
         [AC_MSG_RESULT([no])])])])
])

VALA_REQUIRED=0.11.1

AC_ARG_ENABLE([vala],
	      AS_HELP_STRING([--enable-vala],[Enable Vala support]),
	      [enable_vala=$enableval],
	      [enable_vala=auto])

if test "$enable_vala" = "no"; then
	found_vala="no (disabled, use --enable-vala to enable)"
else
	CHECK_VALAC($VALA_REQUIRED)
	if test "$VALAC" = ""; then
		found_vala="no (valac >= $VALA_REQUIRED not found)"
	else
		found_vala="yes"
	fi
fi

if test "$enable_vala" = "yes" -a "$found_vala" != "yes"; then
	AC_MSG_ERROR([$found_vala])
fi

AM_CONDITIONAL([ENABLE_VALA],[test "$found_vala" = "yes"])

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
gtk+-3.0 >= 3.0 \
libpeas-gtk-1.0 \
libpeas-1.0 \
libnotify >= 0.7.0 \
gnome-keyring-1 \
dbus-glib-1])

AC_CONFIG_FILES([
Makefile
src/Makefile
m4/Makefile
po/Makefile.in
data/Makefile
data/pictures/Makefile
modules/Makefile
modules/keyring/Makefile
modules/iMode/Makefile
modules/imui/Makefile
modules/messenger/Makefile
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
