# $Id: Makefile.am,v 1.2 2007/05/23 14:24:48 ivana Exp $

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${AGDD_INCLUDE} \
         -I../../../packages/VGM/include \
         -I../../..//packages/BaseVGM/include \
         -I../../../packages/ClhepVGM/include \
         -I../../../packages/AgddGM/include 

agddgmsrc=../../../packages/AgddGM/source

lib_LTLIBRARIES = libAgddGM.la

libAgddGM_la_SOURCES =                        \
	$(agddgmsrc)/materials/Isotope.cxx \
	$(agddgmsrc)/materials/Element.cxx \
	$(agddgmsrc)/materials/Material.cxx \
	$(agddgmsrc)/materials/MaterialFactory.cxx \
	$(agddgmsrc)/solids/BooleanSolid.cxx \
	$(agddgmsrc)/solids/Box.cxx \
	$(agddgmsrc)/solids/Cons.cxx \
	$(agddgmsrc)/solids/Polycone.cxx \
	$(agddgmsrc)/solids/Sphere.cxx \
	$(agddgmsrc)/solids/Torus.cxx \
	$(agddgmsrc)/solids/Trap.cxx \
	$(agddgmsrc)/solids/Trd.cxx \
	$(agddgmsrc)/solids/Tubs.cxx \
	$(agddgmsrc)/volumes/Factory.cxx \
	$(agddgmsrc)/volumes/FactoryCreate.cxx \
	$(agddgmsrc)/volumes/FactoryImport.cxx \
	$(agddgmsrc)/volumes/Placement.cxx \
	$(agddgmsrc)/volumes/Volume.cxx

agddgminc=../../../packages/AgddGM/include/AgddGM

agddgmmatincdir = $(includedir)/AgddGM/materials
agddgmmatinc_HEADERS = \
	$(agddgminc)/materials/Element.h \
	$(agddgminc)/materials/Material.h \
	$(agddgminc)/materials/MaterialFactory.h

agddgmsolincdir = $(includedir)/AgddGM/solids
agddgmsolinc_HEADERS = \
	$(agddgminc)/solids/BooleanSolid.h \
	$(agddgminc)/solids/Box.h \
	$(agddgminc)/solids/Cons.h \
	$(agddgminc)/solids/Polycone.h \
	$(agddgminc)/solids/Sphere.h \
	$(agddgminc)/solids/Torus.h \
	$(agddgminc)/solids/Trap.h \
	$(agddgminc)/solids/Trd.h \
	$(agddgminc)/solids/Tubs.h


agddgmvolincdir = $(includedir)/AgddGM/volumes
agddgmvolinc_HEADERS = \
	$(agddgminc)/volumes/Factory.h \
	$(agddgminc)/volumes/Placement.h \
	$(agddgminc)/volumes/Volume.h
