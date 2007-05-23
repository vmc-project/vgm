# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} \
         -I$(VGM_SOURCE)/packages/VGM/include \
         -I$(VGM_SOURCE)/packages/BaseVGM/include 

basevgmsrc=$(VGM_SOURCE)/packages/BaseVGM/source

lib_LTLIBRARIES = libBaseVGM.la

nodist_libBaseVGM_la_SOURCES =                        \
	$(basevgmsrc)/common/utilities.cxx \
	$(basevgmsrc)/materials/VMaterialFactory.cxx \
	$(basevgmsrc)/materials/VMedium.cxx \
	$(basevgmsrc)/materials/element.cxx \
	$(basevgmsrc)/materials/isotope.cxx \
	$(basevgmsrc)/materials/material.cxx \
	$(basevgmsrc)/solids/VBooleanSolid.cxx \
	$(basevgmsrc)/solids/VBox.cxx \
	$(basevgmsrc)/solids/VCons.cxx \
	$(basevgmsrc)/solids/VCtubs.cxx \
	$(basevgmsrc)/solids/VEllipticalTube.cxx \
	$(basevgmsrc)/solids/VExtrudedSolid.cxx \
	$(basevgmsrc)/solids/VPara.cxx \
	$(basevgmsrc)/solids/VPolycone.cxx \
	$(basevgmsrc)/solids/VPolyhedra.cxx \
	$(basevgmsrc)/solids/VSphere.cxx \
	$(basevgmsrc)/solids/VTorus.cxx \
	$(basevgmsrc)/solids/VTrap.cxx \
	$(basevgmsrc)/solids/VTrd.cxx \
	$(basevgmsrc)/solids/VTubs.cxx \
	$(basevgmsrc)/solids/solid.cxx \
	$(basevgmsrc)/volumes/VFactory.cxx \
	$(basevgmsrc)/volumes/VPlacement.cxx \
	$(basevgmsrc)/volumes/VVolume.cxx 

basevgminc=$(VGM_SOURCE)/packages/BaseVGM/include/BaseVGM


basevgmcomincdir = $(includedir)/BaseVGM/common
nodist_basevgmcominc_HEADERS = \
	$(basevgminc)/common/utilities.h

basevgmmatincdir = $(includedir)/BaseVGM/materials
nodist_basevgmmatinc_HEADERS = \
	$(basevgminc)/materials/VMaterialFactory.h \
	$(basevgminc)/materials/VMedium.h

basevgmsolincdir = $(includedir)/BaseVGM/solids
nodist_basevgmsolinc_HEADERS = \
	$(basevgminc)/solids/VBooleanSolid.h \
	$(basevgminc)/solids/VBox.h \
	$(basevgminc)/solids/VCons.h \
	$(basevgminc)/solids/VCtubs.h \
	$(basevgminc)/solids/VEllipticalTube.h \
	$(basevgminc)/solids/VExtrudedSolid.h \
	$(basevgminc)/solids/VPara.h \
	$(basevgminc)/solids/VPolycone.h \
	$(basevgminc)/solids/VPolyhedra.h \
	$(basevgminc)/solids/VSphere.h \
	$(basevgminc)/solids/VTorus.h \
	$(basevgminc)/solids/VTrap.h \
	$(basevgminc)/solids/VTrd.h \
	$(basevgminc)/solids/VTubs.h

basevgmvolincdir = $(includedir)/BaseVGM/volumes
nodist_basevgmvolinc_HEADERS = \
	$(basevgminc)/volumes/VFactory.h \
	$(basevgminc)/volumes/VPlacement.h \
	$(basevgminc)/volumes/VVolume.h


