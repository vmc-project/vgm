# ------------------------------------------------------------------------------
# The configuration file for CMake build for Virtual Geometry Model
# Copyright (C) 2014, Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# ------------------------------------------------------------------------------
#
# $Id$
#
# Configuration file for CMake build for VGM packages.
#
# I. Hrivnacova, 04/06/2014

#-- Geant4 (optional) ----------------------------------------------------------
if(WITH_GEANT4)
  option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
  if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
  else()
    find_package(Geant4 REQUIRED)
  endif()
  include(${Geant4_USE_FILE})
endif()

#-- CLHEP (required) -----------------------------------------------------------
find_package(CLHEP REQUIRED)

#-- ROOT (optional) ------------------------------------------------------------
if(WITH_ROOT)
  find_package(ROOT REQUIRED)
endif()

#-- Optional packages used in test ---------------------------------------------
if(WITH_TEST)
  # G4Root
  if (WITH_ROOT AND WITH_G4ROOT)
    find_package(G4Root REQUIRED)      
  endif(WITH_ROOT AND WITH_G4ROOT)

endif(WITH_TEST)

