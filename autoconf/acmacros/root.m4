# $Id$

# -*- mode: autoconf -*- 

dnl
dnl Autoconf macros to build against root.  This based on
dnl root/build/misc/root.m4 as distributed by ROOT.  It has been
dnl modified to allow --with-root=no to work.
dnl

dnl
dnl Call ROOT_SETUP with optional minimum version
dnl
dnl It will produce:
dnl
dnl ROOT_ENABLE - "yes" or "no", if no, the following are garbage
dnl ROOT_INCLUDE - compile time include flags
dnl ROOT_LINK - link time library flags
dnl

AC_DEFUN([ROOT_SETUP],[

root_enable=""
AC_MSG_CHECKING(for ROOT)

AC_ARG_WITH(root,
	AC_HELP_STRING([--with-root],
	[ROOT package specification (yes,no,path)]),
	[
if test x$with_root = xyes ; then
	root_enable=yes
	root_prefix=/usr
elif test x$with_root = xno ; then
	root_enable=no
else
	root_enable=yes
	root_prefix=$with_root
	ROOTSYS=$with_root
	export ROOTSYS
fi
],[
	root_enable=yes
	root_prefix=""
])


AC_MSG_RESULT([$root_prefix])
ROOT_ENABLE=$root_enable
AC_SUBST(ROOT_ENABLE)

if test x"$root_enable" = xyes ; then

ROOT_PATH($1,
	[
	ROOT_INCLUDE="$ROOTCFLAGS"
	ROOT_LINK="-L$ROOTLIBDIR $ROOTLIBS -lGeom"
	],
	AC_MSG_ERROR(Your ROOT version is too old or can't be found))
AC_SUBST(ROOT_INCLUDE)
AC_SUBST(ROOT_LINK)

fi
])


dnl The rest is the original

dnl -*- mode: autoconf -*- 
dnl
dnl $Id$
dnl $Author$
dnl $Date$
dnl
dnl Autoconf macro to check for existence or ROOT on the system
dnl Synopsis:
dnl
dnl  ROOT_PATH([MINIMUM-VERSION, [ACTION-IF-FOUND, [ACTION-IF-NOT-FOUND]]])
dnl
dnl Some examples: 
dnl 
dnl    ROOT_PATH(3.03/05, , AC_MSG_ERROR(Your ROOT version is too old))
dnl    ROOT_PATH(, AC_DEFINE([HAVE_ROOT]))
dnl 
dnl The macro defines the following substitution variables
dnl
dnl    ROOTCONF           full path to root-config
dnl    ROOTEXEC           full path to root
dnl    ROOTCINT           full path to rootcint
dnl    ROOTLIBDIR         Where the ROOT libraries are 
dnl    ROOTINCDIR         Where the ROOT headers are 
dnl    ROOTCFLAGS         Extra compiler flags
dnl    ROOTLIBS           ROOT basic libraries 
dnl    ROOTGLIBS          ROOT basic + GUI libraries
dnl    ROOTAUXLIBS        Auxilary libraries and linker flags for ROOT
dnl    ROOTAUXCFLAGS      Auxilary compiler flags 
dnl    ROOTRPATH          Same as ROOTLIBDIR
dnl
dnl The macro will fail if root-config and rootcint isn't found.
dnl
dnl Christian Holm Christensen <cholm@nbi.dk>
dnl


AC_DEFUN([ROOT_PATH],
[
  AC_ARG_WITH(rootsys,
  [  --with-rootsys          top of the ROOT installation directory],
    user_rootsys=$withval,
    user_rootsys="none")
  if test ! x"$user_rootsys" = xnone; then
    rootbin="$user_rootsys/bin"
  elif test ! x"$ROOTSYS" = x ; then 
    rootbin="$ROOTSYS/bin"
  else 
   rootbin=$PATH
  fi
  AC_PATH_PROG(ROOTCONF, root-config , no, $rootbin)
  AC_PATH_PROG(ROOTEXEC, root , no, $rootbin)
  AC_PATH_PROG(ROOTCINT, rootcint , no, $rootbin)
	
  if test x"$ROOTSYS" = x; then
    ROOTSYS=`dirname $ROOTCONF`
    ROOTSYS=`dirname $ROOTSYS`
    export ROOTSYS
  fi

  if test ! x"$ROOTCONF" = "xno" && \
     test ! x"$ROOTCINT" = "xno" ; then 

    # define some variables 
    ROOTLIBDIR=`$ROOTCONF --libdir`
    ROOTINCDIR=`$ROOTCONF --incdir`
    ROOTCFLAGS=`$ROOTCONF --noauxcflags --cflags` 
    ROOTLIBS=`$ROOTCONF --noauxlibs --noldflags --libs`
    ROOTGLIBS=`$ROOTCONF --noauxlibs --noldflags --glibs`
    ROOTAUXCFLAGS=`$ROOTCONF --auxcflags`
    ROOTAUXLIBS=`$ROOTCONF --auxlibs`
    ROOTRPATH=$ROOTLIBDIR
    ROOTVERSION=`$ROOTCONF --version`
    ROOTSOVERSION=`dirname $ROOTVERSION`
	
    if test $1 ; then 
      AC_MSG_CHECKING(whether ROOT version ($ROOTVERSION) is >= [$1])
      vers=`$ROOTCONF --version | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      requ=`echo $1 | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      if test $vers -lt $requ ; then 
        AC_MSG_RESULT(no)
	no_root="yes"
      else 
        AC_MSG_RESULT(yes)
      fi
    fi
  else
    # otherwise, we say no_root
    no_root="yes"
  fi

  AC_SUBST(ROOTLIBDIR)
  AC_SUBST(ROOTINCDIR)
  AC_SUBST(ROOTCFLAGS)
  AC_SUBST(ROOTLIBS)
  AC_SUBST(ROOTGLIBS) 
  AC_SUBST(ROOTAUXLIBS)
  AC_SUBST(ROOTAUXCFLAGS)
  AC_SUBST(ROOTRPATH)
  AC_SUBST(ROOTVERSION)
  AC_SUBST(ROOTSOVERSION)

  if test "x$no_root" = "x" ; then 
    ifelse([$2], , :, [$2])     
  else 
    ifelse([$3], , :, [$3])     
  fi
])

#
# Macro to check if ROOT has a specific feature:
#
#   ROOT_FEATURE(FEATURE,[ACTION_IF_HAVE,[ACTION_IF_NOT]])
#
# For example 
#
#   ROOT_FEATURE([ldap],[AC_DEFINE([HAVE_ROOT_LDAP])])
# 
AC_DEFUN([ROOT_FEATURE],
[
  AC_REQUIRE([ROOT_PATH])
  feat=$1
  res=`$ROOTCONF --has-$feat` 
  if test "x$res" = "xyes" ; then 
    ifelse([$2], , :, [$2])     
  else 
    ifelse([$3], , :, [$3])     
  fi
])

#
# EOF
#
