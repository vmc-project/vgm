# $Id$
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := vgm_test
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

CPPFLAGS += -I$(ROOTSYS)/include
EXTRALIBS = $(shell root-config --glibs) -lGeomPainter -lGeom

CPPFLAGS  += -I$(VGM_INSTALL)/packages/VGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/BaseVGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/Geant4GM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/RootGM/include
CPPFLAGS  += -I$(VGM_INSTALL)/packages/XmlVGM/include
EXTRALIBS += -L$(VGM_INSTALL)/lib/$(VGM_SYSTEM) -lGeant4GM -lRootGM  -lBaseVGM -lXmlVGM

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

