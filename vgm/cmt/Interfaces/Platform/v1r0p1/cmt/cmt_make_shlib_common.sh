#!/bin/sh

#set -x

#------------------------------------------------------
#
#  Syntax :
#
#  cmt_make_shlib_common.sh extract-arg package extra-args
#
#   with :
#
#      extract-arg  : either "extract" or "no_extract"
#      package      : the current package name
#      extra-args   : extra link options
#
#------------------------------------------------------

extract=$1
shift

tag=$1
shift

lib=$1
shift

extra=$*

here=`pwd`

ld=`${CMTROOT}/mgr/cmt show macro_value shlibbuilder -tag=${tag}`
ldflags=`${CMTROOT}/mgr/cmt show macro_value shlibflags -tag=${tag}`
suffix=`${CMTROOT}/mgr/cmt show macro_value shlibsuffix -tag=${tag}`
libprefix=`${CMTROOT}/mgr/cmt show macro_value library_prefix -tag=${tag}`
libsuffix=`${CMTROOT}/mgr/cmt show macro_value library_suffix -tag=${tag}`

if test "${ld}" = "" ; then
  exit 1
fi

libname=${libprefix}${lib}${libsuffix}
/bin/rm -f ${libname}.${suffix}

result=0

temp_shlib=${lib}temp_shlib

if test ${extract} = "extract"; then
  trap 'cd ${here}; /bin/rm -rf ${temp_shlib}; exit ${result}' 0 1 2 15

  mkdir -p ${temp_shlib}
  /bin/rm -f ${temp_shlib}/*

  (cd ${temp_shlib}; ar x ../${libname}.a)

  #
  # Build a protected list of modules just extracted from
  # the static library
  #  Files containing space characters are accepted
  #
  modules=`ls -1 ${temp_shlib} | \
           grep '[.]o$' | \
           sed -e 's#^#'${temp_shlib}'/#' \
               -e 's#^#"#g' \
               -e 's#$#"#'`

  if test "${QUIET}" = ""; then set -v; fi
  eval ${ld} ${ldflags} -o ${libname}.${suffix} ${modules} ${extra}
  result=$?

  if [ `uname` = Darwin ] ; then
    /bin/rm -f ${lib}.bundle
    opts=" -Wl,-headerpad_max_install_names -Wl,-headerpad,800"
    eval ${ld} -bundle -twolevel_namespace ${opts} -o ${lib}.bundle ${modules} ${extra}
    result=$?
  fi

  if test "${QUIET}" = ""; then set +v; fi

  /bin/rm -rf ${temp_shlib}

else

  if test "${QUIET}" = ""; then set -v; fi

  eval ${ld} ${ldflags} -all ${libname}.a -o ${libname}.${suffix} ${extra} -rpath `pwd`
  result=$?

  if test "${QUIET}" = ""; then set +v; fi

fi




