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
  set(CMAKE_CXX_STANDARD ${Geant4_CXX_STANDARD})
endif()

#-- ROOT (optional) ------------------------------------------------------------
if(WITH_ROOT)
  find_package(ROOT CONFIG COMPONENTS Geom REQUIRED)
  set(ROOT_DEPS ROOT::Core ROOT::Physics ROOT::Geom)
  if(NOT WITH_GEANT4)
    # use ROOT comilation flags if not taken from Geant4
    include(${ROOT_USE_FILE})
  endif()
endif()

#-- CLHEP (required) -----------------------------------------------------------
if(Geant4_builtin_clhep_FOUND)
  if(${Geant4_VERSION} VERSION_LESS "10.6")
     set(CLHEP_LIBRARIES G4clhep)
  else()
     set(CLHEP_LIBRARIES Geant4::G4clhep)
  endif()
else()
  find_package(CLHEP CONFIG REQUIRED)
  if(NOT WITH_GEANT4 AND NOT WITH_ROOT)
    # set c++11 standard explicitely if Geant4 and Root use files are not used
    # at it is the default for CLHEP build
    set(CMAKE_CXX_STANDARD 11)
  endif()

endif()

#-- Optional packages used in test ---------------------------------------------
if(WITH_TEST)
  # G4Root
  if (WITH_ROOT AND WITH_G4ROOT)

#-- VMC (required) ------------------------------------------------------------
    if(ROOT_vmc_FOUND)
      message(STATUS "Using VMC built with ROOT")
      set(VMC_LIBRARIES ROOT::VMC)
    else()
      find_package(VMC CONFIG REQUIRED)
       #  set(VMC_DEPS VMCLibrary)
      if(NOT VMC_FIND_QUIETLY)
        message(STATUS "Found VMC ${VMC_VERSION} in ${VMC_DIR}")
      endif()
    endif()
    find_package(G4Root REQUIRED)
  endif(WITH_ROOT AND WITH_G4ROOT)

endif(WITH_TEST)

