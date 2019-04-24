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
if (NOT VGM_WITH_EXAMPLES)
   find_package(VGM REQUIRED)
else()
   # define includes and VGM_LIBRARIES explicitly
   include_directories(
      ${VGM_SOURCE_DIR}/packages/VGM/include
      ${VGM_SOURCE_DIR}/packages/ClhepVGM/include
      ${VGM_SOURCE_DIR}/packages/BaseVGM/include
      ${VGM_SOURCE_DIR}/packages/XmlVGM/include)
   set(VGM_LIBRARIES BaseVGM;XmlVGM;ClhepVGM)
   if (VGM_WITH_GEANT4)
      include_directories(${VGM_SOURCE_DIR}/packages/Geant4GM/include)
      set(VGM_LIBRARIES "${VGM_LIBRARIES};Geant4GM")
      set(VGM_GEANT4_LIBRARIES Geant4GM;ClhepVGM;BaseVGM;XmlVGM)
   endif()
   if(VGM_WITH_ROOT)
      include_directories(${VGM_SOURCE_DIR}/packages/RootGM/include)
      set(VGM_LIBRARIES "${VGM_LIBRARIES};RootGM")
      set(VGM_ROOT_LIBRARIES RootGM;ClhepVGM;BaseVGM;XmlVGM)
   endif()
   set(VGM_FOUND ON)
endif()

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
