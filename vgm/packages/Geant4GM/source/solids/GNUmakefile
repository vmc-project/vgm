# $Id$
# Based on G4 makefiles

name := Geant4GM_solids

ifndef VGM_INSTALL
  VGM_INSTALL = ../../../..
endif

include $(VGM_INSTALL)/config/architecture.gmk

CPPFLAGS += -I$(VGM_BASE)/VGM/include
CPPFLAGS += -I$(VGM_BASE)/ClhepVGM/include
CPPFLAGS += -I$(VGM_BASE)/BaseVGM/include
CPPFLAGS += -I$(VGM_BASE)/Geant4GM/include

include $(VGM_INSTALL)/config/geant4.gmk

include $(VGM_INSTALL)/config/common.gmk

.PHONY: global
 
global: lib

