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

# The CMake build for Virtual Geometry Model is a result of a merge 
# of the CMake configuration files kindly provided 
# by Florian Uhlig, GSI and Pere Mato, CERN.

# - Try to find G4ROOT
# Once done this will define
#
#  G4ROOT_FOUND        - If G4ROOT is found
#  G4ROOT_INCLUDE_DIRS - the G4ROOT include directoris
#  G4ROOT_LIBRARIES    - the libraries needed to use G4ROOT

#message(STATUS "Looking for G4ROOT ...")

set(G4ROOT_DIR "" CACHE PATH "Directory where G4ROOT is installed")
set(G4ROOT_INC_DIR "" CACHE PATH "Alternative directory for G4ROOT includes")
set(G4ROOT_LIB_DIR "" CACHE PATH "Alternative directory for G4ROOT libraries")
set(G4ROOT_ARCH "" CACHE PATH "G4ROOT platform specification")

# First search for Geant4VMCConfig.cmake on the path defined via user setting 
# Geant4VMC_DIR

if(EXISTS ${Geant4VMC_DIR}/Geant4VMCConfig.cmake)
  include(${Geant4VMC_DIR}/Geant4VMCConfig.cmake)
  if (Geant4VMC_USE_G4ROOT)
    set(G4ROOT_INCLUDE_DIRS ${Geant4VMC_INCLUDE_DIRS})
    set(G4ROOT_LIBRARIES ${Geant4VMC_LIBRARIES})
    set(G4ROOT_FOUND TRUE)
    message(STATUS "Found G4Root in Geant4VMC CMake configuration in ${Geant4VMC_DIR}")
    return()
  endif(Geant4VMC_USE_G4ROOT)
endif()


find_path(G4ROOT_INCLUDE_DIRS NAMES TG4RootNavigator.h PATHS
  ${G4ROOT_INC_DIR}
  ${G4ROOT_DIR}/include/g4root
)

if (NOT G4ROOT_ARCH)
  if(ROOT_CONFIG_EXECUTABLE)
    execute_process(
      COMMAND ${ROOT_CONFIG_EXECUTABLE} --arch 
      OUTPUT_VARIABLE G4ROOT_ARCH 
      OUTPUT_STRIP_TRAILING_WHITESPACE)
   endif()
endif()      

find_path(G4ROOT_LIBRARY_DIR NAMES libg4root.so libg4root.dylib PATHS
  ${G4ROOT_LIB_DIR}
  ${G4ROOT_DIR}/lib
  ${G4ROOT_DIR}/lib/tgt_${G4ROOT_ARCH}
)

if (G4ROOT_INCLUDE_DIRS AND G4ROOT_LIBRARY_DIR)
  set(G4ROOT_FOUND TRUE)
endif (G4ROOT_INCLUDE_DIRS AND G4ROOT_LIBRARY_DIR)

if (G4ROOT_FOUND)
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${G4ROOT_LIBRARY_DIR})
  set(G4ROOT_LIBRARIES "-L${G4ROOT_LIBRARY_DIR} -lg4root")
  if (NOT G4ROOT_FIND_QUIETLY)
    message(STATUS "Found G4ROOT in ${G4ROOT_LIBRARY_DIR}")
  endif (NOT G4ROOT_FIND_QUIETLY)
else (G4ROOT_FOUND)
  if (G4ROOT_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for G4ROOT... - Not found")
  endif (G4ROOT_FIND_REQUIRED)
endif (G4ROOT_FOUND)

# Make variables changeble to the advanced user
mark_as_advanced(G4ROOT_INCLUDE_DIRS)
mark_as_advanced(G4ROOT_LIBRARIES)
mark_as_advanced(G4ROOT_LIBRARY_DIR)

