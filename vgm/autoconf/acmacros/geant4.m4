# $Id$

# -*- mode: autoconf -*- 

dnl
dnl Autoconf macros to build against Geant4.  
dnl This based on root.m4 as distributed by ROOT.  
dnl and modified to allow --with-geant4=no to work.
dnl
dnl
dnl Call GEANT4_SETUP with optional minimum version
dnl
dnl It will produce:
dnl
dnl GEANT4_ENABLE - "yes" or "no", if no, the following are garbage
dnl GEANT4_INCLUDE - compile time include flags
dnl GEANT4_LINK - link time library flags
dnl

AC_DEFUN([GEANT4_SETUP],
[

  geant4_enable=""
  AC_ARG_WITH(
    geant4,
    AC_HELP_STRING([--with-geant4],
	           [Geant4 package specification (yes,no,path)]),
    [ if test x$with_geant4 = xyes ; then
        geant4_enable=yes
        geant4_prefix=/usr/local
        geant4bin=/usr/local/bin
      elif test x$with_geant4 = xno ; then
	geant4_enable=no
	geant4bin=""
      else
	geant4_enable=yes
	geant4_prefix=$with_geant4
	geant4bin=${with_geant4}/bin
      fi 
    ],
    [ geant4_enable=yes]
  )

  AC_MSG_RESULT([geant4_enable $geant4_enable])
  GEANT4_ENABLE=$geant4_enable
  AC_SUBST(GEANT4_ENABLE)

  if test x"$geant4_enable" = xyes ; then

dnl
dnl Set/guess the "system" name
dnl
 
    geant4_system=`uname`-${CXX}
    AC_ARG_WITH(
      [geant4-system],
      AC_HELP_STRING([--with-geant4-system],
                     [Geant4 system type]),
      [geant4_system=$with_geant4_system]
    )

dnl
dnl Set the granular libraries flags
dnl

    AC_ARG_WITH(
      [geant4-granular-libs],
      AC_HELP_STRING([--with-geant4-granular-libs],
                     [building with geant4 granular libraries (yes,no)]),
      [ geant4_granular_libs=$with_geant4_granular_libs],
      [ geant4_granular_libs=no ]
    )

dnl
dnl Set/find geant4-config,  
dnl

    inc_to_be_done=""
    lib_to_be_done=""
      AC_PATH_PROG(GEANT4CONF, geant4-config , no, $geant4bin)
      if test ! x"$GEANT4CONF" = "xno" ; then 
        geant4_cflags=`$GEANT4CONF --cflags`
        #additional flags - not handled via geant4-config
        if test index('G4VIS_USE', $geant4_cflags) > 0; then
          geant4_cflags=$geant4_cflags" -DG4VIS_USE"
        fi   
        if test index('G4UI_USE', $geant4_cflags) > 0; then
          geant4_cflags=$geant4_cflags" -DG4UI_USE"
        fi   
        # define variables 
        GEANT4_INCLUDE=$geant4_cflags 
        GEANT4_LINK=`$GEANT4CONF --libs`
        AC_SUBST(GEANT4_INCLUDE)
        AC_SUBST(GEANT4_LINK)
      else
        inc_to_be_done="yes"
        lib_to_be_done="yes"
        geant4_incdir=""
        geant4_libdir=""
        for try in "$geant4_prefix/include/geant4" "$geant4_prefix/include" ;
        do
          if ! test -f "$try/G4RunManager.hh" ; then continue; fi
          geant4_incdir="$try"
          break;
        done
        for try in "$geant4_prefix/lib/geant4/$geant4_system" "$geant4_prefix/lib/geant4" "$geant4_prefix/lib/$geant4_system" "$geant4_prefix/lib"
        do
          if ! test -d "${try}"; then continue; fi
          geant4_libdir=$try
          break
        done
      fi  

dnl
dnl Set/find the compile time include flags 
dnl

    AC_ARG_WITH(
      [geant4-include],
      AC_HELP_STRING([--with-geant4-include],
                     [alternate headers dir (that which holds "*.hh")]),
      [ geant4_incdir=$with_geant4_include
        inc_to_be_done="yes"
      ],
      []
    )

    if test x"$inc_to_be_done" = x"yes" ; then 
      GEANT4_INCLUDE="-I$geant4_incdir"
      #AC_MSG_RESULT(geant4_incdir $geant4_incdir)
      UTIL_CHECK_PKG_DIR([$geant4_incdir],[Geant4],[G4RunManager.hh])
      AC_SUBST(GEANT4_INCLUDE)
    fi    

dnl
dnl Set/find the link time library flags 
dnl

    AC_ARG_WITH(
      [geant4-libdir],
      AC_HELP_STRING([--with-geant4-libdir], 
                     [Geant4 alternate library dir]),
      [ geant4_libdir=$with_geant4_libdir 
        lib_to_be_done="yes"
      ],
      []
    )

    if test x"$lib_to_be_done" = x"yes" ; then 
      #AC_MSG_RESULT(geant4_libdir $geant4_libdir)
      UTIL_CHECK_PKG_DIR([$geant4_libdir],[Geant4])

      if test x"$geant4_granular_libs" = xyes ; then
        GEANT4_LINK="-Wl,-rpath -Wl,$geant4_libdir -L$geant4_libdir `$geant4_libdir/liblist -m $geant4_libdir < $geant4_libdir/libname.map`"
        AC_SUBST(GEANT4_LINK)
      else   
        geant4_libs="-lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -lG4clhep" 
        GEANT4_LINK="-Wl,-rpath -Wl,$geant4_libdir -L$geant4_libdir $geant4_libs"
        AC_SUBST(GEANT4_LINK)
      fi
    fi

  fi # geant4-enable
])
