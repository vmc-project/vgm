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

AC_DEFUN([VGM_SETUP], [

VGM_ENABLES

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
	[VGM_ENABLE_ROOTGM=$enable_RootGM],
	[VGM_ENABLE_ROOTGM=yes])

AC_MSG_RESULT([$VGM_ENABLE_ROOTGM])

if test x$VGM_ENABLE_ROOTGM = xyes ; then
    VGM_PACKAGES="$VGM_PACKAGES RootGM"
fi

# XmlVGM
AC_MSG_CHECKING(to build XmlVGM VGM package)

AC_ARG_ENABLE(XmlVGM, 
	AC_HELP_STRING([--enable-XmlVGM],[Build XmlVGM subpackage [[default=yes]] ]),
	[VGM_ENABLE_XMLVGM=$enable_XmlVGM],
	[VGM_ENABLE_XMLVGM=yes])

AC_MSG_RESULT([$VGM_ENABLE_XMLVGM])

if test x$VGM_ENABLE_XMLVGM = xyes ; then
    VGM_PACKAGES="$VGM_PACKAGES XmlVGM"
fi


AC_SUBST(VGM_PACKAGES)


])

