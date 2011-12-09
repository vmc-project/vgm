# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see autoconf/COPYING.
# Contact: bv@bnl.gov

dnl
dnl CLHEP autoconf macros
dnl 
dnl Calling CLHEP_SETUP will produce these macros:
dnl 
dnl CLHEP_ENABLE - "yes" or "no", if "no" the following will be garbage:
dnl CLHEP_INCLUDE - compile time include flags
dnl CLHEP_LINK - link time library flags
dnl 



AC_DEFUN([CLHEP_SETUP], [

dnl
dnl Basic checking to use CLHEP or not and if an 
dnl installation area is specified
dnl

clhep_enable=""
clhep_prefix=""

AC_MSG_CHECKING(for CLHEP)

AC_ARG_WITH(clhep,
	AC_HELP_STRING([--with-clhep],
	[CLHEP package specification (yes,no,path)]),
	[
if test x$with_clhep = xyes ; then
	clhep_enable=yes
	clhep_prefix=/usr
elif test x$with_clhep = xno ; then
	clhep_enable=no
else
	clhep_enable=yes
	clhep_prefix=$with_clhep
fi
],[
	clhep_enable=yes
	clhep_prefix=/usr
])


AC_MSG_RESULT([$clhep_prefix])
CLHEP_ENABLE=$clhep_enable
AC_SUBST(CLHEP_ENABLE)


dnl
dnl Set/find the compile time include flags
dnl

AC_ARG_WITH([clhep-include],
	AC_HELP_STRING([--with-clhep-include],
                       [alternate headers dir (that which holds "/CLHEP/*/*.h")]),
	[
	clhep_incdir=$with_clhep_include
	CLHEP_INCLUDE="-I$with_clhep_include"
	],[
	clhep_incdir="$clhep_prefix/include"
	if test "$clhep_libdir" = "/usr"; then
		CLHEP_INCLUDE=""
	else
		CLHEP_INCLUDE="-I$clhep_prefix/include"
	fi
	])

if test x"$clhep_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$clhep_incdir],[CLHEP],[CLHEP/Evaluator/Evaluator.h])
AC_SUBST(CLHEP_INCLUDE)
fi

dnl
dnl Set/find the link time library flags
dnl

AC_ARG_WITH([clhep-libdir],
	AC_HELP_STRING([--with-clhep-libdir], 
                       [CLHEP alternate library dir]),
	[
	clhep_libdir=$with_clhep_libdir
	CLHEP_LINK="-L$clhep_libdir -lCLHEP"
	],[
	clhep_libdir="$clhep_prefix/lib"
	if test "$clhep_libdir" = "/usr" ; then
		CLHEP_LINK="-lCLHEP"
	else
		CLHEP_LINK="-Wl,-rpath -Wl,$clhep_libdir -L$clhep_libdir -lCLHEP"
	fi
	])

if test x"$clhep_enable" = xyes ; then
UTIL_CHECK_PKG_DIR([$clhep_libdir],[CLHEP])
AC_SUBST(CLHEP_LINK)
fi

if test x"$clhep_enable" = xno ; then
  CLHEP_INCLUDE=""
  CLHEP_LINK=""
fi

])
