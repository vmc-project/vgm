# $Id$
# Based on G4 makefiles

name := XmlVGM

ifndef VGM_INSTALL
  VGM_INSTALL = ../../..
endif

include $(VGM_INSTALL)/config/architecture.gmk

CPPFLAGS += -I$(VGM_BASE)/VGM/include
CPPFLAGS += -I$(VGM_BASE)/XmlVGM/include

include $(VGM_INSTALL)/config/common.gmk

.PHONY: global
 
global: lib

