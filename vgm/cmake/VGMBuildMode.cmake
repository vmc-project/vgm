# ------------------------------------------------------------------------------
# The configuration file for CMake build for Virtual Geometry Model
# Copyright (C) 2014, Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# ------------------------------------------------------------------------------

# Configuration file for CMake build for VGM packages
# which defines the default build mode if it has not been set
#
# I. Hrivnacova, 18/01/2017

#-------------------------------------------------------------------------------
# Make sure a default build type is used
#
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
       FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#-------------------------------------------------------------------------------
# Always use '@rpath' in install names of libraries.
#
set(CMAKE_MACOSX_RPATH 1)
