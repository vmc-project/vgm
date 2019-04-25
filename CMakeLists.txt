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

#---  Enforce an out-of-source builds before anything else ---------------------
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(STATUS "VGM requires an out-of-source build.")
    message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
    message(STATUS "CMakeCache.txt")
    message(STATUS "CMakeFiles")
    message(STATUS "Once these files are removed, create a separate directory")
    message(STATUS "and run CMake from there")
    message(FATAL_ERROR "in-source build detected")
endif()

#--- CMake required version ----------------------------------------------------
cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

# Required to be able to use non Apple Clang builds on macOS
cmake_policy(SET CMP0025 NEW)

#--- CMake Module Path----------------------------------------------------------
set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

#---Project VGM ----------------------------------------------------------------
#
project(VGM)
set(${PROJECT_NAME}_VERSION_MAJOR "4")
set(${PROJECT_NAME}_VERSION_MINOR "5")
set(${PROJECT_NAME}_VERSION_PATCH "0")
set(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})

#--- Default project build mode ------------------------------------------------
include(VGMBuildMode)

#--- Options -------------------------------------------------------------------
option(WITH_GEANT4       "Build Geant4 dependent subpackage (Geant4GM)" ON)
option(WITH_ROOT         "Build Root dependent subpackage(RootGM)" ON)
option(WITH_EXAMPLES     "Build examples" ON)
option(WITH_TEST         "Build test" OFF)
option(WITH_G4ROOT       "Build test with G4Root" OFF)
option(INSTALL_EXAMPLES  "Install examples" ON)
option(BUILD_SHARED_LIBS "Build the dynamic libraries" ON)

#--- Find required packages ----------------------------------------------------
include(VGMRequiredPackages)

#--- Utility to defined installation lib directory -----------------------------
include(VGMInstallLibDir)

#--- Add the packages sources --------------------------------------------------
add_subdirectory(packages)

#--- Build test ----------------------------------------------------------------
if(WITH_TEST)
   if (WITH_GEANT4 AND WITH_ROOT)
     add_subdirectory(test)
   else()
     message(STATUS "VGM test inactivated: requires both WITH_GEANT4 and WITH_ROOT set ON.")
   endif()
endif()

#--- Build examples ------------------------------------------------------------
if(WITH_EXAMPLES)
   set(VGM_WITH_GEANT4 ${WITH_GEANT4})
   set(VGM_WITH_ROOT ${WITH_ROOT})
   set(VGM_WITH_EXAMPLES ${WITH_EXAMPLES})
   add_subdirectory(examples)
endif()

#--- Build project configuration -----------------------------------------------
include(VGMBuildProject)
