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

#---Process examples subdirectories --------------------------------------------
 
#---Install examples sources ---------------------------------------------------
if(WITH_GEANT4)
  if (NOT IS_DIRECTORY ${VGM_SOURCE_DIR}/examples/E01/N03)
    execute_process(
      COMMAND ${VGM_SOURCE_DIR}/examples/install_sources.sh                  
      OUTPUT_VARIABLE INSTALL_SOURCES_OUTPUT
      OUTPUT_STRIP_TRAILING_WHITESPACE
      TIMEOUT 2)
    message(STATUS ${INSTALL_SOURCES_OUTPUT}) 
  else()
    message(STATUS "Examples sources are already installed") 
  endif()  
endif()  
      
#---Add examples subdirectories ------------------------------------------------
if(WITH_GEANT4 AND WITH_ROOT)
  add_subdirectory(E01)
  add_subdirectory(E02)
endif()
if(WITH_GEANT4)
  add_subdirectory(E03)
endif()
if(WITH_ROOT)
  add_subdirectory(E04)
endif()
