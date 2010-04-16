# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

dnl
dnl macros for VGM Autoconf build system
dnl

# macro to check whether a test file exists
# FIXME: replace calls to this with autoconf's builtin _TEST_FILE macro
AC_DEFUN([UTIL_CHECK_TEST_FILE], [

if test -z $1; then
  AC_MSG_ERROR([macro requires an argument of file to test]);
else
  arg_test_file=$1
fi

AC_CHECK_FILE($arg_test_file,
	[okay=yes],
	[okay=no])

if test $okay = no; then
  AC_MSG_ERROR([test file ${arg_test_file} was not found])
fi

])

# macro to check a package directory with an (optional) test file
#
# args:
# $1 = dir to check
# $2 = pkg name
# $3 = test file relative to $1
AC_DEFUN([UTIL_CHECK_PKG_DIR], [

# pkg name
if test -z ${2}; then
  AC_MSG_ERROR([missing mandatory package name])
else
  arg_pkg=$2
fi

# dir to check
if test -z $1; then
  AC_MSG_ERROR([${arg_pkg} dir was not specified])
else
  arg_dir=$1
fi

# optional test file
if test -n ${3}; then
  arg_test_file=$3
fi

# never allow a 'no' choice for core packages
if test ${arg_dir} = "no"; then
  AC_MSG_ERROR(['no' is not a valid choice])
fi

# null arg, i.e. not specified
if test ${arg_dir} = ""; then
  AC_MSG_ERROR([${arg_pkg} was not specified])
fi

# dir does not exist
if ! test -e ${arg_dir}; then
  AC_MSG_ERROR([directory ${arg_dir} for package ${arg_pkg} does not exist])
else
  # not a directory
  if ! test -d ${arg_dir}; then
    AC_MSG_ERROR([$arg_dir is not a directory])
  fi
fi

# check test file relative to input path (optional)
if test -n ${arg_test_file}; then
  UTIL_CHECK_TEST_FILE( [${arg_dir}/${arg_test_file}] )
fi

])

# From: http://ac-archive.sourceforge.net/ac-archive/ax_ext_have_lib.html
# AX_EXT_HAVE_LIB(/lib /usr/lib /usr/local/lib /usr/lib/mysql /usr/local/mysql/lib, mysqlclient, mysql_init, [-lz])
AC_DEFUN([UTIL_HAVE_LIB],
[
new_ldflags=${LDFLAGS}
new_libs=$LIBS
AC_CHECK_LIB([$2], $3, new_libs="-l$2"; ext_lib_found="yes",  ext_lib_found="no")
for dir in $1
do
if test $ext_lib_found = no
then
ext_haslib_cvdir=`echo $dir | $as_tr_sh`
AC_CACHE_CHECK([for $2 library with -L$dir], [ext_cv${ext_haslib_cvdir}_haslib_$2],
[ext_func_search_save_LIBS=$LIBS
ext_func_save_ldflags=${LDFLAGS}
LIBS="-l$2 $4 ${ext_func_search_save_LIBS}"
LDFLAGS="-L$dir ${ext_func_save_ldflags}"
AC_TRY_LINK_FUNC([$3], [eval "ext_cv${ext_haslib_cvdir}_haslib_$2"="yes"],
[eval "ext_cv${ext_haslib_cvdir}_haslib_$2"="no"])
LIBS=$ext_func_search_save_LIBS
LDFLAGS=$ext_func_save_ldflags
])
if eval `echo 'test x${'ext_cv${ext_haslib_cvdir}_haslib_$2'}' = "xyes"`; then
new_libs="-l$2 ${new_libs}"
new_ldflags="-L${dir} ${new_ldflags}"
ext_lib_found="yes"
fi
fi
done
LIBS=$new_libs
LDFLAGS=$new_ldflags
])
