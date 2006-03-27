# $Id$
# --------------------------------------------------------------
# GNUmakefile for particles library.  Gabriele Cosmo, 4/4/97.
# --------------------------------------------------------------

name := Geant4GM

# Added for reading INTYLIBS (needed on MacOS)
include $(VGM_INSTALL)/config/architecture.gmk
include $(VGM_INSTALL)/config/geant4.gmk

SUBDIRS = materials solids volumes
SUBLIBS = Geant4GM_materials Geant4GM_solids Geant4GM_volumes

ifndef VGM_INSTALL
  VGM_INSTALL = ../..
endif

include $(VGM_INSTALL)/config/globlib.gmk
