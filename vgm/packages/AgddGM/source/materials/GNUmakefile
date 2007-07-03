# $Id: GNUmakefile,v 1.4 2007/05/23 10:31:14 ivana Exp $

# -----------------------------------------------------------------------
# The makefile for a sub-package of the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# Based on Geant4 makefiles

name := AgddGM_materials

ifndef VGM_INSTALL
  VGM_INSTALL = ../../../..
endif

include $(VGM_INSTALL)/config/architecture.gmk

CPPFLAGS += -I$(VGM_BASE)/VGM/include
CPPFLAGS += -I$(VGM_BASE)/ClhepVGM/include
CPPFLAGS += -I$(VGM_BASE)/BaseVGM/include
CPPFLAGS += -I$(VGM_BASE)/AgddGM/include

include $(VGM_INSTALL)/config/agdd.gmk

include $(VGM_INSTALL)/config/common.gmk

.PHONY: global
 
global: lib

