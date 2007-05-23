# $Id$

# -----------------------------------------------------------------------
# The makefile for a sub-package of the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# Based on Geant4 makefiles

name := RootGM_materials

ifndef VGM_INSTALL
  VGM_INSTALL = ../../../..
endif

include $(VGM_INSTALL)/config/architecture.gmk

CPPFLAGS += -I$(VGM_BASE)/VGM/include
CPPFLAGS += -I$(VGM_BASE)/BaseVGM/include
CPPFLAGS += -I$(VGM_BASE)/RootGM/include

include $(VGM_INSTALL)/config/root.gmk

include $(VGM_INSTALL)/config/common.gmk

.PHONY: global
 
global: lib

