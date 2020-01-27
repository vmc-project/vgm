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

#---BaseVGM --------------------------------------------------------------------

#----------------------------------------------------------------------------
# Define installed names
#
set(_library_name BaseVGM)

#---Include directories---------------------------------------------------------
include_directories(
  ${VGM_SOURCE_DIR}/packages/VGM/include
  ${VGM_SOURCE_DIR}/packages/ClhepVGM/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#---Add library-----------------------------------------------------------------
file(GLOB sources source/*/*.cxx)
add_library(${_library_name} ${sources})
target_include_directories(${_library_name} INTERFACE $<INSTALL_INTERFACE:include/${_library_name}>)

#----Installation---------------------------------------------------------------
install(DIRECTORY include/ DESTINATION include)
install(TARGETS ${_library_name} EXPORT VGMTargets DESTINATION ${CMAKE_INSTALL_LIBDIR})
