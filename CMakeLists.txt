# $Id$
#
# ------------------------------------------------------------------------------
# The configuration file for CMake build for Virtual Geometry Model
# Copyright (C) 2012, Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# ------------------------------------------------------------------------------

# The CMake build for Virtual Geometry Model is a result of a merge 
# of the CMake configuration files kindly provided 
# by Florian Uhlig, GSI and Pere Mato, CERN.

#---CMake required version -----------------------------------------------------
cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

#---Project VGM ----------------------------------------------------------------
#
project(VGM)

#---CMake Module Path-----------------------------------------------------------
set(CMAKE_MODULE_PATH 
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}) 

#---Options---------------------------------------------------------------------
option(WITH_GEANT4       "Build Geant4 dependent subpackage (Geant4GM)" ON)
option(WITH_ROOT         "Build Root dependent subpackage(RootGM)" ON)
option(WITH_TEST         "Build test" ON)
option(WITH_G4ROOT       "Build test with G4Root" OFF)
option(WITH_XERCESC      "Build test with XercesC" OFF)
option(WITH_EXAMPLES     "Build examples" OFF)
option(BUILD_SHARED_LIBS "Build the dynamic libraries" ON)  

#---Find required packages------------------------------------------------------

# Geant4
if(WITH_GEANT4)
  set(Geant4_DIR "" CACHE PATH "Directory where Geant4Config.cmake is installed")
  set(GEANT4_DIR "" CACHE PATH "Directory where Geant4 is installed")
  set(GEANT4_INC_DIR "" CACHE PATH "Alternative directory for Geant4 includes")
  set(GEANT4_LIB_DIR "" CACHE PATH "Alternative directory for Geant4 libraries")
  set(GEANT4_SYSTEM "" CACHE PATH "Geant4 platform specification")
  option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
  if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
  else()
    find_package(Geant4 REQUIRED)
  endif()
  include(${Geant4_USE_FILE})
endif()

# CLHEP
set(CLHEP_DIR "" CACHE PATH "Directory where CLHEP is installed")
set(CLHEP_INC_DIR "" CACHE PATH "Alternative directory for CLHEP includes")
set(CLHEP_LIB_DIR "" CACHE PATH "Alternative directory for CLHEP libraries")
find_package(CLHEP REQUIRED)

# ROOT
if(WITH_ROOT)
  set(ROOT_DIR "" CACHE PATH "Directory where ROOT is installed")
  set(ROOT_INC_DIR "" CACHE PATH "Alternative directory for ROOT includes")
  set(ROOT_LIB_DIR "" CACHE PATH "Alternative directory for ROOT libraries")
  find_package(ROOT REQUIRED)
endif()

# Test
# (Required if Geant4 was built with GDML)
if(WITH_TEST)

  # Xerces-C
  if (WITH_XERCESC)
    set(XERCESC_DIR "" CACHE PATH "Directory where Xerces-C is installed")
    set(XERCESC_LIB_DIR "" CACHE PATH "Alternative directory for Xerces-C libraries")
    find_package(XercesC REQUIRED)
  endif(WITH_XERCESC)

  # G4Root
  if (WITH_ROOT AND WITH_G4ROOT)
      set(G4ROOT_DIR "" CACHE PATH "Directory where G4ROOT is installed")
      set(G4ROOT_INC_DIR "" CACHE PATH "Alternative directory for G4ROOT includes")
      set(G4ROOT_LIB_DIR "" CACHE PATH "Alternative directory for G4ROOT libraries")
      set(G4ROOT_ARCH "" CACHE PATH "G4ROOT platform specification")
  endif(WITH_ROOT AND WITH_G4ROOT)

endif(WITH_TEST)

#---Add required packages-------------------------------------------------------
add_subdirectory(packages)
if(WITH_TEST)
   add_subdirectory(test)
endif()
if(WITH_EXAMPLES)
   add_subdirectory(examples)
endif()


