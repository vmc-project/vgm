# $Id$
# --------------------------------------------------------------
# GNUmakefile for particles library.  Gabriele Cosmo, 4/4/97.
# --------------------------------------------------------------

name := RootGM

# Added for reading INTYLIBS (needed on MacOS)
include $(VGM_INSTALL)/config/architecture.gmk
include $(VGM_INSTALL)/config/root.gmk

SUBDIRS = common materials solids volumes
SUBLIBS = RootGM_common RootGM_materials RootGM_solids RootGM_volumes 

ifndef VGM_INSTALL
  VGM_INSTALL = ../..
endif

include $(VGM_INSTALL)/config/globlib.gmk
