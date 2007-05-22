# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

dnl
dnl Macros to let one build against libagdd
dnl

# macro that calls all the AGDD setup macros in sequence
AC_DEFUN([LIBAGDD_SETUP], [

LIBAGDD_WITH
LIBAGDD_WITH_INCLUDE
LIBAGDD_WITH_LIB
LIBAGDD_SUBST

])

AC_DEFUN([LIBAGDD_WITH], [

AC_MSG_CHECKING(for libagdd installation location)

AC_ARG_WITH(libagdd,
	AC_HELP_STRING([--with-libagdd=<path>],
		[libagdd installation location [[/usr]] ]),
	[libagdd_prefix=$with_libagdd],
	[libagdd_prefix=/usr])

AC_MSG_RESULT([$libagdd_prefix])

UTIL_CHECK_PKG_DIR([$libagdd_prefix], [libagdd])

LIBAGDD_INCLUDE="-I$libagdd_prefix/include"
LIBAGDD_LIB="-L$libagdd_prefix/lib -lagdd"

])

AC_DEFUN([LIBAGDD_WITH_INCLUDE], [

AC_MSG_CHECKING(for libagdd include directory)

AC_ARG_WITH(libagdd-include,
	AC_HELP_STRING([--with-libagdd-include=<path>],
		[libagdd alternate include directory ]),
	[libagdd_include=$with_libagdd_include],
	[libagdd_include=$libagdd_prefix/include])

AC_MSG_RESULT([$libagdd_include])

UTIL_CHECK_PKG_DIR([$libagdd_include], [libagdd], [AGDD/AGDD_Model.hh])

LIBAGDD_INCLUDE="-I$libagdd_include"

])

AC_DEFUN([LIBAGDD_WITH_LIB], [

AC_MSG_CHECKING(for libagdd lib directory)

AC_ARG_WITH(libagdd-lib,
	AC_HELP_STRING([--with-libagdd-lib=<path>],
		[libagdd alternate lib directory ]),
	[libagdd_libdir=$with_libagdd_lib],
	[libagdd_libdir=$libagdd_prefix/lib])

AC_MSG_RESULT([$libagdd_lib])

UTIL_CHECK_PKG_DIR([$libagdd_libdir], [libagdd], [libagdd.la])

LIBAGDD_LIB="-L$libagdd_libdir -lagdd"

])

AC_DEFUN([LIBAGDD_SUBST], [

AC_SUBST(LIBAGDD_PREFIX)
AC_SUBST(LIBAGDD_INCLUDE)
AC_SUBST(LIBAGDD_LIB)

])
