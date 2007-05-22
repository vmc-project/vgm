# $Id$

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} ${GEANT4_INCLUDE} \
         -I$(VGM_SOURCE)/packages/VGM/include \
         -I$(VGM_SOURCE)/packages/BaseVGM/include \
         -I$(VGM_SOURCE)/packages/ClhepVGM/include \
         -I$(VGM_SOURCE)/packages/Geant4GM/include 

geant4gmsrc=$(VGM_SOURCE)/packages/Geant4GM/source

lib_LTLIBRARIES = libGeant4GM.la

nodist_libGeant4GM_la_SOURCES =                        \
	$(geant4gmsrc)/materials/Element.cxx \
	$(geant4gmsrc)/materials/ElementMap.cxx \
	$(geant4gmsrc)/materials/Isotope.cxx \
	$(geant4gmsrc)/materials/IsotopeMap.cxx \
	$(geant4gmsrc)/materials/Material.cxx \
	$(geant4gmsrc)/materials/MaterialFactory.cxx \
	$(geant4gmsrc)/materials/MaterialMap.cxx \
	$(geant4gmsrc)/materials/Medium.cxx \
	$(geant4gmsrc)/solids/BooleanSolid.cxx \
	$(geant4gmsrc)/solids/Box.cxx \
	$(geant4gmsrc)/solids/Cons.cxx \
	$(geant4gmsrc)/solids/Ctubs.cxx \
	$(geant4gmsrc)/solids/EllipticalTube.cxx \
	$(geant4gmsrc)/solids/Para.cxx \
	$(geant4gmsrc)/solids/Polycone.cxx \
	$(geant4gmsrc)/solids/Polyhedra.cxx \
	$(geant4gmsrc)/solids/SolidMap.cxx \
	$(geant4gmsrc)/solids/Sphere.cxx \
	$(geant4gmsrc)/solids/Torus.cxx \
	$(geant4gmsrc)/solids/Trap.cxx \
	$(geant4gmsrc)/solids/Trd.cxx \
	$(geant4gmsrc)/solids/Tubs.cxx \
	$(geant4gmsrc)/volumes/Factory.cxx \
	$(geant4gmsrc)/volumes/Placement.cxx \
	$(geant4gmsrc)/volumes/PlacementMap.cxx \
	$(geant4gmsrc)/volumes/Volume.cxx \
	$(geant4gmsrc)/volumes/VolumeMap.cxx

geant4gminc=$(VGM_SOURCE)/packages/Geant4GM/include/Geant4GM

geant4gmmatincdir = $(includedir)/Geant4GM/materials
nodist_geant4gmmatinc_HEADERS = \
	$(geant4gminc)/materials/Element.h \
	$(geant4gminc)/materials/ElementMap.h \
	$(geant4gminc)/materials/Isotope.h \
	$(geant4gminc)/materials/IsotopeMap.h \
	$(geant4gminc)/materials/Material.h \
	$(geant4gminc)/materials/MaterialFactory.h \
	$(geant4gminc)/materials/MaterialMap.h \
	$(geant4gminc)/materials/Medium.h


geant4gmsolincdir = $(includedir)/Geant4GM/solids
nodist_geant4gmsolinc_HEADERS = \
	$(geant4gminc)/solids/BooleanSolid.h \
	$(geant4gminc)/solids/Box.h \
	$(geant4gminc)/solids/Cons.h \
	$(geant4gminc)/solids/Ctubs.h \
	$(geant4gminc)/solids/EllipticalTube.h \
	$(geant4gminc)/solids/Para.h \
	$(geant4gminc)/solids/Polycone.h \
	$(geant4gminc)/solids/Polyhedra.h \
	$(geant4gminc)/solids/SolidMap.h \
	$(geant4gminc)/solids/Sphere.h \
	$(geant4gminc)/solids/Torus.h \
	$(geant4gminc)/solids/Trap.h \
	$(geant4gminc)/solids/Trd.h \
	$(geant4gminc)/solids/Tubs.h

geant4gmvolincdir = $(includedir)/Geant4GM/volumes
nodist_geant4gmvolinc_HEADERS = \
	$(geant4gminc)/volumes/Factory.h \
	$(geant4gminc)/volumes/Placement.h \
	$(geant4gminc)/volumes/PlacementMap.h \
	$(geant4gminc)/volumes/Volume.h \
	$(geant4gminc)/volumes/VolumeMap.h

