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
# Configuration file for CMake build for VGM packages
# which defines customised installation.
#
# I. Hrivnacova, 04/06/2014

# Find modules
foreach(_find_mod CLHEP Geant4 ROOT)
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/Find${_find_mod}.cmake
    ${PROJECT_BINARY_DIR}/Modules/Find${_find_mod}.cmake
    COPYONLY
  )
endforeach()

# Set needed variables for the install tree
set(VGM_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/cmake)

# Install the custom modules for the examples
install(DIRECTORY
  ${PROJECT_BINARY_DIR}/Modules/
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/VGM-${VGM_VERSION}/Modules
  COMPONENT Development
)

# Install examples
if(INSTALL_EXAMPLES)
  install(DIRECTORY
    ${PROJECT_SOURCE_DIR}/examples
    DESTINATION share/VGM-${VGM_VERSION}
  )
endif()

#
# Install the VGMConfig, VGMConfigVersion
#
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/VGMConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/VGMConfig.cmake" @ONLY)

configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/VGMConfigVersion.cmake.in"
  "${PROJECT_BINARY_DIR}/VGMConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/VGMConfig.cmake"
  "${PROJECT_BINARY_DIR}/VGMConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/VGM-${VGM_VERSION})

install(EXPORT VGMTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/VGM-${VGM_VERSION})
