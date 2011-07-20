# -*- autoconf -*-
# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2011, Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see autoconf/COPYING.
# Contact: ivana@ipno.in2p3.fr

dnl
dnl Autoconf macros to build against xpat 
dnl
dnl Calling EXPAT_SETUP will produce these macros:
dnl 
dnl EXPAT_ENABLE - "yes" or "no", if "no" the following will be garbage:
dnl EXPAT_INCLUDE - compile time include flags
dnl EXPAT_LINK - link time library flags
dnl


AC_DEFUN([EXPAT_SETUP], [

AC_MSG_CHECKING(for Expat)

AC_ARG_WITH(expat,
	AC_HELP_STRING([--with-expat],
	[Expat package specification (yes,no,path)]),
	[
if test x$with_expat = xyes ; then
	expat_enable=yes
	expat_prefix=/usr
elif test x$with_expat = xno ; then
	expat_enable=no
else
	expat_enable=yes
	expat_prefix=$with_expat
fi
],[
	expat_enable=yes
	expat_prefix=/usr
])


AC_MSG_RESULT([$expat_prefix])
EXPAT_ENABLE=$expat_enable
AC_SUBST(EXPAT_ENABLE)


dnl
dnl Set/find the compile time include flags
dnl

AC_ARG_WITH([expat-include],
	AC_HELP_STRING([--with-expat-include],
                       [alternate header dir (that which holds "expat.h")]),
	[
	expat_incdir=$with_expat_include
	EXPAT_INCLUDE="-I$with_expat_include"
	],[
	expat_incdir="$expat_prefix/include"
	EXPAT_INCLUDE=""
	])

if test x"$expat_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$expat_incdir],[Expat],[expat.h])
AC_SUBST(EXPAT_INCLUDE)
fi

dnl
dnl Set/find the link time library flags
dnl

AC_ARG_WITH([expat-libdir],
	AC_HELP_STRING([--with-expat-libdir], 
                       [Expat alternate library dir]),
	[
	expat_libdir=$with_expat_libdir
	EXPAT_LINK="-Wl,-rpath -Wl,$expat_libdir -L$expat_libdir -lexpat"
	],[
	expat_libdir="$expat_prefix/lib"
	EXPAT_LINK="-lexpat"
	])

if test x"$expat_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$expat_libdir],[Expat])
AC_SUBST(EXPAT_LINK)
fi

])
