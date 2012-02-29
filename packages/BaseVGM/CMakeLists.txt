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
      
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#---Add library-----------------------------------------------------------------
file(GLOB sources source/*/*.cxx)
add_library(BaseVGM SHARED ${sources})

#----Installation---------------------------------------------------------------
install(DIRECTORY include/ DESTINATION include  PATTERN ".svn" EXCLUDE)
install(TARGETS BaseVGM DESTINATION lib)
