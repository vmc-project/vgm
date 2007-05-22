# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${ROOT_INCLUDE} \
         -I$(VGM_SOURCE)/packages/VGM/include \
         -I$(VGM_SOURCE)/packages/BaseVGM/include \
         -I$(VGM_SOURCE)/packages/RootGM/include 

rootgmsrc=$(VGM_SOURCE)/packages/RootGM/source

lib_LTLIBRARIES = libRootGM.la

nodist_libRootGM_la_SOURCES =                        \
	$(rootgmsrc)/common/Units.cxx \
	$(rootgmsrc)/common/axis.cxx \
	$(rootgmsrc)/common/transform.cxx \
	$(rootgmsrc)/materials/Element.cxx \
	$(rootgmsrc)/materials/ElementGeo.cxx \
	$(rootgmsrc)/materials/Isotope.cxx \
	$(rootgmsrc)/materials/Material.cxx \
	$(rootgmsrc)/materials/MaterialFactory.cxx \
	$(rootgmsrc)/materials/MaterialMap.cxx \
	$(rootgmsrc)/materials/Medium.cxx \
	$(rootgmsrc)/solids/BooleanSolid.cxx \
	$(rootgmsrc)/solids/Box.cxx \
	$(rootgmsrc)/solids/Cons.cxx \
	$(rootgmsrc)/solids/Ctubs.cxx \
	$(rootgmsrc)/solids/EllipticalTube.cxx \
	$(rootgmsrc)/solids/Para.cxx \
	$(rootgmsrc)/solids/Polycone.cxx \
	$(rootgmsrc)/solids/Polyhedra.cxx \
	$(rootgmsrc)/solids/SolidMap.cxx \
	$(rootgmsrc)/solids/Sphere.cxx \
	$(rootgmsrc)/solids/Torus.cxx \
	$(rootgmsrc)/solids/Trap.cxx \
	$(rootgmsrc)/solids/Trd.cxx \
	$(rootgmsrc)/solids/Tubs.cxx \
	$(rootgmsrc)/volumes/Factory.cxx \
	$(rootgmsrc)/volumes/Placement.cxx \
	$(rootgmsrc)/volumes/PlacementMap.cxx \
	$(rootgmsrc)/volumes/Volume.cxx \
	$(rootgmsrc)/volumes/VolumeMap.cxx

rootgminc=$(VGM_SOURCE)/packages/RootGM/include/RootGM

rootgmcomincdir = $(includedir)/RootGM/common
nodist_rootgmcominc_HEADERS = \
	$(rootgminc)/common/Units.h \
	$(rootgminc)/common/axis.h \
	$(rootgminc)/common/transform.h

rootgmmatincdir = $(includedir)/RootGM/materials
nodist_rootgmmatinc_HEADERS = \
	$(rootgminc)/materials/Element.h \
	$(rootgminc)/materials/ElementGeo.h \
	$(rootgminc)/materials/Isotope.h \
	$(rootgminc)/materials/Material.h \
	$(rootgminc)/materials/MaterialFactory.h \
	$(rootgminc)/materials/MaterialMap.h \
	$(rootgminc)/materials/Medium.h

rootgmsolincdir = $(includedir)/RootGM/solids
nodist_rootgmsolinc_HEADERS = \
	$(rootgminc)/solids/BooleanSolid.h \
	$(rootgminc)/solids/Box.h \
	$(rootgminc)/solids/Cons.h \
	$(rootgminc)/solids/Ctubs.h \
	$(rootgminc)/solids/EllipticalTube.h \
	$(rootgminc)/solids/Para.h \
	$(rootgminc)/solids/Polycone.h \
	$(rootgminc)/solids/Polyhedra.h \
	$(rootgminc)/solids/SolidMap.h \
	$(rootgminc)/solids/Sphere.h \
	$(rootgminc)/solids/Torus.h \
	$(rootgminc)/solids/Trap.h \
	$(rootgminc)/solids/Trd.h \
	$(rootgminc)/solids/Tubs.h


rootgmvolincdir = $(includedir)/RootGM/volumes
nodist_rootgmvolinc_HEADERS = \
	$(rootgminc)/volumes/Factory.h \
	$(rootgminc)/volumes/Placement.h \
	$(rootgminc)/volumes/PlacementMap.h \
	$(rootgminc)/volumes/Volume.h \
	$(rootgminc)/volumes/VolumeMap.h
