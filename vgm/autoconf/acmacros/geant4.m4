# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

dnl
dnl Macros to build against Geant4
dnl
dnl It is assumed that either Geant4 files match this directory
dnl structure:
dnl
dnl GEANT_PREFIX/lib/[geant4]/[GEANT4_SYSTEM]
dnl GEANT_PREFIX/include/[geant4]
dnl 
dnl or that they can be specified explicitly with --with-* flags
dnl 
dnl
dnl Calling GEANT4_SETUP will result in these definitions:
dnl
dnl GEANT4_ENABLE - "yes" or "no".  If no, the following are garbage:
dnl GEANT4_LINK - holding the link statement (-L... -l...)
dnl GEANT4_INCLUDE - holding the includes (-I...)
dnl

AC_DEFUN([GEANT4_SETUP], [


dnl
dnl Basic checking to use Geant4 or not and if an 
dnl installation area is specified
dnl

geant4_enable=""
geant4_prefix=""

AC_MSG_CHECKING(for Geant4)

AC_ARG_WITH(geant4,
	AC_HELP_STRING([--with-geant4],
		       [Geant4 package specification (yes,no,path)]),
	[
if test x$with_geant4 = xyes ; then
	geant4_enable=yes
	geant4_prefix=/usr
elif test x$with_geant4 = xno ; then
	geant4_enable=no
else
	geant4_enable=yes
	geant4_prefix=$with_geant4
fi
],[
	geant4_enable=yes
	geant4_prefix=/usr
])

AC_MSG_RESULT([$geant4_enable $geant4_prefix])
GEANT4_ENABLE=$geant4_enable
AC_SUBST(GEANT4_ENABLE)

dnl
dnl Set/guess the "system" name
dnl

geant4_system=`uname`-${CXX}
AC_ARG_WITH(geant4-system,
	AC_HELP_STRING([--with-geant4-system],
	               [Geant4 system type]),
	[geant4_system=$with_geant4_system])


dnl
dnl Set/find the compile time include flags
dnl

AC_ARG_WITH([geant4-include],
	AC_HELP_STRING([--with-geant4-include],
                       [alternate headers dir (that which holds "*.hh")]),
	[geant4_incdir=$with_geant4_include],[geant4_incdir=""])

if test x"$geant4_enable" = xyes ; then
if test x"$geant4_incdir" = x ; then
    for try in "$geant4_prefix/include/geant4" "$geant4_prefix/include" ;
    do
        if ! test -f "$try/G4RunManager.hh" ; then continue; fi
        geant4_incdir="$try"
        break;
    done
fi
if test x"$geant4_incdir" != x ; then
	GEANT4_INCLUDE="-I$geant4_incdir"
fi

UTIL_CHECK_PKG_DIR([$geant4_incdir],[Geant4],[G4RunManager.hh])
AC_SUBST(GEANT4_INCLUDE)

fi

dnl
dnl Set/find the link time library flags
dnl

AC_ARG_WITH([geant4-libdir],
	AC_HELP_STRING([--with-geant4-libdir], 
                       [Geant4 alternate library dir]),
	[geant4_libdir=$with_geant4_libdir],[geant4_libdir=""])

if test x"$geant4_enable" = xyes ; then

if test x"$geant4_libdir" = x ; then
    for try in "$geant4_prefix/lib/geant4/$geant4_system" "$geant4_prefix/lib/geant4" "$geant4_prefix/lib/$geant4_system" "$geant4_prefix/lib"
    do
        if ! test -f "${try}/liblist"; then continue; fi
        geant4_libdir=$try
        break
   done
fi

UTIL_CHECK_PKG_DIR([$geant4_libdir],[Geant4],[liblist])

GEANT4_LINK="-Wl,-rpath -Wl,$geant4_libdir -L$geant4_libdir `$geant4_libdir/liblist -m $geant4_libdir < $geant4_libdir/libname.map`"
AC_SUBST(GEANT4_LINK)

fi

])

