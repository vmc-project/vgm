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

project(vgm_examples)

set(CMAKE_MODULE_PATH
    ${VGM_DIR}/Modules
    ${CMAKE_MODULE_PATH})

if (NOT VGM_WITH_EXAMPLES)
   # Build examples outside VGM project
   #--- Required VGM package  -----------------------------------------------------
   find_package(VGM REQUIRED)

   #----------------------------------------------------------------------------
   # Find ROOT package
   find_package(ROOT REQUIRED)

   #----------------------------------------------------------------------------
   # Find Geant4 package, activating all available UI and Vis drivers by default
   # You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
   # to build a batch mode only executable
   #
   option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
   if(WITH_GEANT4_UIVIS)
     find_package(Geant4 REQUIRED ui_all vis_all)
   else()
     find_package(Geant4 REQUIRED)
   endif()
   
   #----------------------------------------------------------------------------
   # Setup Geant4 include directories and compile definitions
   # Setup include directory for this project
   #
   include(${Geant4_USE_FILE})

else()
   # Build examples outside VGM project
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
if(VGM_WITH_GEANT4 AND Geant4_FOUND AND VGM_WITH_ROOT AND ROOT_FOUND)
  add_subdirectory(E01)
  add_subdirectory(E02)
endif()
if(VGM_WITH_GEANT4 AND Geant4_FOUND)
  add_subdirectory(E03)
endif()
if(VGM_WITH_ROOT AND ROOT_FOUND)
  add_subdirectory(E04)
endif()
