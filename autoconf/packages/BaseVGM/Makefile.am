# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} \
         -I../../../packages/VGM/include \
         -I../../../packages/BaseVGM/include 

basevgmsrc=../../../packages/BaseVGM/source

lib_LTLIBRARIES = libBaseVGM.la

libBaseVGM_la_SOURCES =                        \
	$(basevgmsrc)/common/utilities.cxx \
	$(basevgmsrc)/materials/VMaterialFactory.cxx \
	$(basevgmsrc)/materials/VMedium.cxx \
	$(basevgmsrc)/materials/element.cxx \
	$(basevgmsrc)/materials/isotope.cxx \
	$(basevgmsrc)/materials/material.cxx \
	$(basevgmsrc)/solids/VArb8.cxx \
	$(basevgmsrc)/solids/VBooleanSolid.cxx \
	$(basevgmsrc)/solids/VBox.cxx \
	$(basevgmsrc)/solids/VCons.cxx \
	$(basevgmsrc)/solids/VCtubs.cxx \
	$(basevgmsrc)/solids/VDisplacedSolid.cxx \
	$(basevgmsrc)/solids/VEllipticalTube.cxx \
	$(basevgmsrc)/solids/VExtrudedSolid.cxx \
	$(basevgmsrc)/solids/VHype.cxx \
	$(basevgmsrc)/solids/VPara.cxx \
	$(basevgmsrc)/solids/VParaboloid.cxx \
	$(basevgmsrc)/solids/VPolycone.cxx \
	$(basevgmsrc)/solids/VPolyhedra.cxx \
	$(basevgmsrc)/solids/VSphere.cxx \
	$(basevgmsrc)/solids/VTessellatedSolid.cxx \
	$(basevgmsrc)/solids/VTorus.cxx \
	$(basevgmsrc)/solids/VTrap.cxx \
	$(basevgmsrc)/solids/VTrd.cxx \
	$(basevgmsrc)/solids/VTubs.cxx \
	$(basevgmsrc)/solids/solid.cxx \
	$(basevgmsrc)/volumes/VFactory.cxx \
	$(basevgmsrc)/volumes/VPlacement.cxx \
	$(basevgmsrc)/volumes/VVolume.cxx 

basevgminc=../../../packages/BaseVGM/include/BaseVGM


basevgmcomincdir = $(includedir)/BaseVGM/common
basevgmcominc_HEADERS = \
	$(basevgminc)/common/utilities.h

basevgmmatincdir = $(includedir)/BaseVGM/materials
basevgmmatinc_HEADERS = \
	$(basevgminc)/materials/VMaterialFactory.h \
	$(basevgminc)/materials/VMedium.h

basevgmsolincdir = $(includedir)/BaseVGM/solids
basevgmsolinc_HEADERS = \
	$(basevgminc)/solids/VArb8.h \
	$(basevgminc)/solids/VBooleanSolid.h \
	$(basevgminc)/solids/VBox.h \
	$(basevgminc)/solids/VCons.h \
	$(basevgminc)/solids/VCtubs.h \
	$(basevgminc)/solids/VDisplacedSolid.h \
	$(basevgminc)/solids/VEllipticalTube.h \
	$(basevgminc)/solids/VExtrudedSolid.h \
	$(basevgminc)/solids/VHype.h \
	$(basevgminc)/solids/VPara.h \
	$(basevgminc)/solids/VParaboloid.h \
	$(basevgminc)/solids/VPolycone.h \
	$(basevgminc)/solids/VPolyhedra.h \
	$(basevgminc)/solids/VSphere.h \
	$(basevgminc)/solids/VTessellatedSolid.h \
	$(basevgminc)/solids/VTorus.h \
	$(basevgminc)/solids/VTrap.h \
	$(basevgminc)/solids/VTrd.h \
	$(basevgminc)/solids/VTubs.h

basevgmvolincdir = $(includedir)/BaseVGM/volumes
basevgmvolinc_HEADERS = \
	$(basevgminc)/volumes/VFactory.h \
	$(basevgminc)/volumes/VPlacement.h \
	$(basevgminc)/volumes/VVolume.h


