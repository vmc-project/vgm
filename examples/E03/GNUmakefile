# $Id$

# -----------------------------------------------------------------------
# The makefile for the Virtual Geometry Model example
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# --------------------------------------------------------------
# Based on Geant4 makefiles
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := exampleN03
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

# VGM
CPPFLAGS  += -I$(VGM_INSTALL)/packages/VGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/XmlVGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/BaseVGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/Geant4GM/include
CPPFLAGS += -I$(VGM_INSTALL)/include
EXTRALIBS += -L$(VGM_INSTALL)/lib/$(VGM_SYSTEM)
EXTRALIBS += -lGeant4GM -lBaseVGM -lXmlVGM -lClhepVGM

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

