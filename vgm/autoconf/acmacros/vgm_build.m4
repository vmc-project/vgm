# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

dnl
dnl m4 macros for setting up VGM
dnl

# Macro to define VGM_SOURCE, used for building VGM, not building
# against VGM.

AC_DEFUN([VGM_SETUP], [

VGM_WITH_SOURCE
VGM_ENABLES

])

AC_DEFUN([VGM_WITH_SOURCE], [

AC_MSG_CHECKING(for VGM source location)

AC_ARG_WITH(vgm-source,
	AC_HELP_STRING([--with-vgm-source=<path>],
		[VGM source location, absolute path ]),
	[VGM_SOURCE=$with_vgm_source],
	[VGM_SOURCE="`pwd`/.."])

AC_MSG_RESULT([$VGM_SOURCE])

UTIL_CHECK_PKG_DIR([$VGM_SOURCE], [VGM], 
                   [packages/VGM/include/VGM/volumes/IFactory.h])

AC_SUBST(VGM_SOURCE)

])

# Macros to enable/disable different VGM packages.  Used for building
# VGM, not building against VGM.

AC_DEFUN([VGM_ENABLES], [

VGM_PACKAGES="VGM ClhepVGM BaseVGM"

# G4
AC_MSG_CHECKING(to build Geant4GM VGM package)

AC_ARG_ENABLE(Geant4GM, 
	AC_HELP_STRING([--enable-Geant4GM],[Build Geant4GM subpackage [[default=yes]] ]),
	[VGM_ENABLE_GEANT4GM=$enable_Geant4GM],
	[VGM_ENABLE_GEANT4GM=yes])

AC_MSG_RESULT([$VGM_ENABLE_GEANT4GM])

if test x$VGM_ENABLE_GEANT4GM = xyes ; then
    VGM_PACKAGES="$VGM_PACKAGES Geant4GM"
fi


# ROOT
AC_MSG_CHECKING(to build RootGM VGM package)

AC_ARG_ENABLE(RootGM, 
	AC_HELP_STRING([--enable-RootGM],[Build RootGM subpackage [[default=yes]] ]),
	[VGM_ENABLE_ROOTGM=$enable_ROOTGM],
	[VGM_ENABLE_ROOTGM=yes])

AC_MSG_RESULT([$VGM_ENABLE_ROOTGM])

if test x$VGM_ENABLE_ROOTGM = xyes ; then
    VGM_PACKAGES="$VGM_PACKAGES RootGM"
fi


# XmlVGM
AC_MSG_CHECKING(to build XmlVGM VGM package)

AC_ARG_ENABLE(XmlVGM, 
	AC_HELP_STRING([--enable-XmlVGM],[Build XmlVGM subpackage [[default=yes]] ]),
	[VGM_ENABLE_XMLVGM=$enable_XMLVGM],
	[VGM_ENABLE_XMLVGM=yes])

AC_MSG_RESULT([$VGM_ENABLE_XMLVGM])

if test x$VGM_ENABLE_XMLVGM = xyes ; then
    VGM_PACKAGES="$VGM_PACKAGES XmlVGM"
fi


# AgddGM (uncomment when included) 
#AC_MSG_CHECKING(to build AgddGM VGM package)
#
#AC_ARG_ENABLE(AgddGM, 
#	AC_HELP_STRING([--enable-AgddGM],[Build AgddGM subpackage [[default=yes]] ]),
#	[VGM_ENABLE_AGDDGM=$enable_AGDDGM],
#	[VGM_ENABLE_AGDDGM=yes])
#
#AC_MSG_RESULT([$VGM_ENABLE_AGDDGM])
#if test x$VGM_ENABLE_AGDDGM = xyes ; then
#    VGM_PACKAGES="$VGM_PACKAGES AgddGM"
#fi

AC_SUBST(VGM_PACKAGES)


])

