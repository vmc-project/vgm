# $Id$
#
# ------------------------------------------------------------------------------
# The configuration file for CMake build for Virtual Geometry Model
# Copyright (C) 2012, 2014 Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)

set(CMAKE_MODULE_PATH 
    ${VGM_DIR}/Modules
    ${CMAKE_MODULE_PATH}) 

#--- Required VGM package  -----------------------------------------------------
find_package(VGM REQUIRED)

#---Add examples subdirectories ------------------------------------------------
if(VGM_WITH_GEANT4 AND VGM_WITH_ROOT)
  add_subdirectory(E01)
  add_subdirectory(E02)
endif()
if(VGM_WITH_GEANT4)
  add_subdirectory(E03)
endif()
if(VGM_WITH_ROOT)
  add_subdirectory(E04)
endif()
