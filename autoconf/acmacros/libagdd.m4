# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

dnl
dnl Macros to build against libagdd
dnl
dnl It is assumed that either libagdd files match this directory
dnl structure:
dnl
dnl AGDD_PREFIX/lib
dnl AGDD_PREFIX/include
dnl 
dnl or that they can be specified explicitly with --with-* flags
dnl 
dnl
dnl Calling AGDD_SETUP will result in these definitions:
dnl
dnl AGDD_ENABLE - "yes" or "no".  If no, the following are garbage:
dnl AGDD_LINK - holding the link statement (-L... -l...)
dnl AGDD_INCLUDE - holding the includes (-I...)
dnl

AC_DEFUN([AGDD_SETUP], [


dnl
dnl Basic checking to use Libagdd or not and if an 
dnl installation area is specified
dnl

libagdd_enable=""
libagdd_prefix=""

AC_MSG_CHECKING(for libagdd)

AC_ARG_WITH(libagdd,
	AC_HELP_STRING([--with-libagdd],
		       [libagdd package specification (yes,no,path)]),
	[
if test x$with_libagdd = xyes ; then
	libagdd_enable=yes
	libagdd_prefix=/usr
elif test x$with_libagdd = xno ; then
	libagdd_enable=no
else
	libagdd_enable=yes
	libagdd_prefix=$with_libagdd
fi
],[
	libagdd_enable=yes
	libagdd_prefix=/usr
])

AC_MSG_RESULT([$libagdd_enable $libagdd_prefix])
AGDD_ENABLE=$libagdd_enable
AC_SUBST(AGDD_ENABLE)

dnl
dnl Set/find the compile time include flags
dnl

AC_ARG_WITH([libagdd-include],
	AC_HELP_STRING([--with-libagdd-include],
                       [alternate headers dir (that which holds "*.h")]),
	[libagdd_incdir=$with_libagdd_include],[libagdd_incdir=""])

if test x"$libagdd_enable" = xyes ; then
if test x"$libagdd_incdir" = x ; then
    for try in "$libagdd_prefix/include"  ;
    do
        if ! test -f "$try/AGDD/AGDD_Model.hh" ; then continue; fi
        libagdd_incdir="$try"
        break;
    done
fi
if test x"$libagdd_incdir" != x ; then
	AGDD_INCLUDE="-I$libagdd_incdir"
fi

UTIL_CHECK_PKG_DIR([$libagdd_incdir],[libagdd],[AGDD/AGDD_Model.hh])
AC_SUBST(AGDD_INCLUDE)

fi

dnl
dnl Set/find the link time library flags
dnl

AC_ARG_WITH([libagdd-libdir],
	AC_HELP_STRING([--with-libagdd-libdir], 
                       [libagdd alternate library dir]),
	[libagdd_libdir=$with_libagdd_libdir],[libagdd_libdir=""])

if test x"$libagdd_enable" = xyes ; then

if test x"$libagdd_libdir" = x ; then
    for try in "$libagdd_prefix/lib"
    do
	if ! test -f "${try}/libagdd$shrext_cmds"; then continue; fi
        libagdd_libdir=$try
        break
   done
fi

UTIL_CHECK_PKG_DIR([$libagdd_libdir],[libagdd],[libagdd$shrext_cmds])

AGDD_LINK="-Wl,--rpath -Wl,$libagdd_libdir -L$libagdd_libdir -lagdd"
AC_SUBST(AGDD_LINK)

fi

])

