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

# - Try to find CLHEP
# Once done this will define
#
#  CLHEP_FOUND        - If CLHEP is found
#  CLHEP_INCLUDE_DIR  - the CLHEP include directory
#  CLHEP_LIBRARIES    - the libraries needed to use CLHEP
#  CLHEP_LIBRARY_DIR  - PATH to the library directory 
#  CLHEP_LIBRARY_NAME - the CLHEP library name 


message(STATUS "Looking for CLHEP ...")

find_path(CLHEP_INCLUDE_DIR NAMES CLHEP/Evaluator/Evaluator.h PATHS
  ${CLHEP_INC_DIR}
  ${CLHEP_DIR}/include
  ${Geant4_INCLUDE_DIR}
  ${GEANT4_INCLUDE_DIR}
  $ENV{CLHEP_BASE_DIR}/include
)

# CLHEP library external to Geant4 
find_path(CLHEP_LIBRARY_DIR NAMES libCLHEP.so libCLHEP.dylib PATHS
  ${CLHEP_LIB_DIR}
  ${CLHEP_DIR}/lib
  $ENV{CLHEP_BASE_DIR}/lib
)
if (CLHEP_LIBRARY_DIR)
  set(CLHEP_LIBRARY_NAME CLHEP)
endif()    

# CLHEP library within Geant4 
if (NOT CLHEP_LIBRARY_DIR)
  find_path(CLHEP_LIBRARY_DIR NAMES libG4clhep.so libG4clhep.dylib PATHS
    ${Geant4_DIR}/..
    ${GEANT4_LIBRARY_DIR}
  )
  if (CLHEP_LIBRARY_DIR)
    set(CLHEP_LIBRARY_NAME G4clhep)
  endif(CLHEP_LIBRARY_DIR)
endif()    
   
if (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)
  set(CLHEP_FOUND TRUE)
endif (CLHEP_INCLUDE_DIR AND CLHEP_LIBRARY_DIR)

if (CLHEP_FOUND)
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${CLHEP_LIBRARY_DIR})
  set(CLHEP_LIBRARIES "-L${CLHEP_LIBRARY_DIR} -l${CLHEP_LIBRARY_NAME}")
  if (NOT CLHEP_FIND_QUIETLY)
    message(STATUS "Found ${CLHEP_LIBRARY_NAME} in ${CLHEP_LIBRARY_DIR}")
  endif (NOT CLHEP_FIND_QUIETLY)
else (CLHEP_FOUND)
  if (CLHEP_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for CLHEP... - Not found")
  endif (CLHEP_FIND_REQUIRED)
endif (CLHEP_FOUND)

# Make variables changeble to the advanced user
mark_as_advanced(CLHEP_INCLUDE_DIR CLHEP_LIBRARY_DIR CLHEP_LIBRARIES)

