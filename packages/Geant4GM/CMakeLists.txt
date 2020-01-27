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

#----------------------------------------------------------------------------
# Define installed names
#
set(_library_name Geant4GM)

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
add_library(${_library_name} ${sources})
set(_dependencies BaseVGM ClhepVGM ${Geant4_LIBRARIES} ${CLHEP_LIBRARIES})
target_link_libraries(${_library_name} ${_dependencies})
set_target_properties(${_library_name} PROPERTIES INTERFACE_LINK_LIBRARIES "${_dependencies}")
target_include_directories(${_library_name} INTERFACE $<INSTALL_INTERFACE:include/${_library_name}>)

#----Installation---------------------------------------------------------------
install(DIRECTORY include/ DESTINATION include)
install(TARGETS ${_library_name} EXPORT VGMTargets DESTINATION ${CMAKE_INSTALL_LIBDIR})
