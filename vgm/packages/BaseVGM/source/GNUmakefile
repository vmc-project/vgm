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
# (GNUmakefile for particles library.  Gabriele Cosmo, 4/4/97 )

name := BaseVGM

SUBDIRS = common materials solids volumes
SUBLIBS = BaseVGM_common BaseVGM_materials BaseVGM_solids BaseVGM_volumes

ifndef VGM_INSTALL
  VGM_INSTALL = ../..
endif

include $(VGM_INSTALL)/config/globlib.gmk
