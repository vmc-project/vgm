# -*- autoconf -*-
# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see autoconf/COPYING.
# Contact: bv@bnl.gov

dnl
dnl Autoconf macros to build against Xerces-C
dnl
dnl Calling XERCESC_SETUP will produce these macros:
dnl 
dnl XERCES_ENABLE - "yes" or "no", if "no" the following will be garbage:
dnl XERCES_INCLUDE - compile time include flags
dnl XERCES_LINK - link time library flags
dnl


AC_DEFUN([XERCESC_SETUP], [

AC_MSG_CHECKING(for Xerces-C)

AC_ARG_WITH(xerces,
	AC_HELP_STRING([--with-xerces],
	[XERCES package specification (yes,no,path)]),
	[
if test x$with_xerces = xyes ; then
	xerces_enable=yes
	xerces_prefix=/usr
elif test x$with_xerces = xno ; then
	xerces_enable=no
else
	xerces_enable=yes
	xerces_prefix=$with_xerces
fi
],[
	xerces_enable=yes
	xerces_prefix=/usr
])


AC_MSG_RESULT([$xerces_prefix])
XERCES_ENABLE=$xerces_enable
AC_SUBST(XERCES_ENABLE)


dnl
dnl Set/find the compile time include flags
dnl

AC_ARG_WITH([xerces-include],
	AC_HELP_STRING([--with-xerces-include],
                       [alternate header dir (that which holds "/xercesc/*/*.hpp")]),
	[
	xerces_incdir=$with_xerces_include
	XERCES_INCLUDE="-I$with_xerces_include"
	],[
	xerces_incdir="$xerces_prefix/include"
	XERCES_INCLUDE=""
	])

if test x"$xerces_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$xerces_incdir],[Xerces-C],[xercesc/dom/DOMNode.hpp])
AC_SUBST(XERCES_INCLUDE)
fi

dnl
dnl Set/find the link time library flags
dnl

AC_ARG_WITH([xerces-libdir],
	AC_HELP_STRING([--with-xerces-libdir], 
                       [Xerces-C alternate library dir]),
	[
	xerces_libdir=$with_xerces_libdir
	XERCES_LINK="-Wl,-rpath -Wl,$xerces_libdir -L$xerces_libdir -lxerces-c"
	],[
	xerces_libdir="$xerces_prefix/lib"
	XERCES_LINK="-lxerces-c"
	])

if test x"$xerces_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$xerces_libdir],[Xerces-C])
AC_SUBST(XERCES_LINK)
fi

])
