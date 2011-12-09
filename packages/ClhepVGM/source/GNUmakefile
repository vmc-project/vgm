# $Id$

# -----------------------------------------------------------------------
# The makefile for a package of the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# Based on Geant4 makefiles

name := ClhepVGM

ifndef VGM_INSTALL
  VGM_INSTALL = ../../..
endif

include $(VGM_INSTALL)/config/architecture.gmk

# CLHEP with Geant4
ifeq ($(CLHEP_BASE_DIR),)
  include $(VGM_INSTALL)/config/geant4.gmk
endif

CPPFLAGS += -I$(VGM_BASE)/VGM/include
CPPFLAGS += -I$(VGM_BASE)/ClhepVGM/include

include $(VGM_INSTALL)/config/common.gmk

.PHONY: global
 
global: lib

