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

#---Geant4GM -------------------------------------------------------------------

#---Include directories---------------------------------------------------------
include_directories(                     
  ${CLHEP_INCLUDE_DIRS}
  ${Geant4_INCLUDE_DIRS} 
  ${VGM_SOURCE_DIR}/packages/VGM/include 
  ${VGM_SOURCE_DIR}/packages/ClhepVGM/include 
  ${VGM_SOURCE_DIR}/packages/BaseVGM/include 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#---Add library-----------------------------------------------------------------
file(GLOB sources source/*/*.cxx)
add_library(Geant4GM ${sources})
target_link_libraries(Geant4GM BaseVGM ClhepVGM)

#----Installation---------------------------------------------------------------
install(DIRECTORY include/ DESTINATION include  PATTERN ".svn" EXCLUDE)
install(TARGETS Geant4GM EXPORT VGMTargets DESTINATION lib)
