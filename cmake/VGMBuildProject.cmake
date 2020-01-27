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

# Set needed variables for the install tree
set(VGM_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/cmake)

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

install(EXPORT VGMTargets NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/VGM-${VGM_VERSION})
