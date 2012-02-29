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

# - Try to find G4ROOT
# Once done this will define
#
#  G4ROOT_FOUND       - If G4ROOT is found
#  G4ROOT_INCLUDE_DIR - the G4ROOT include directory
#  G4ROOT_LIBRARIES   - The libraries needed to use G4ROOT
#  G4ROOT_LIBRARY_DIR - PATH to the library directory 

message(STATUS "Looking for G4ROOT ...")

find_path(G4ROOT_INCLUDE_DIR NAMES TG4RootNavigator.h PATHS
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
  ${G4ROOT_DIR}/lib/tgt_${G4ROOT_ARCH}
)

if (G4ROOT_INCLUDE_DIR AND G4ROOT_LIBRARY_DIR)
  set(G4ROOT_FOUND TRUE)
endif (G4ROOT_INCLUDE_DIR AND G4ROOT_LIBRARY_DIR)

if (G4ROOT_FOUND)
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${G4ROOT_LIBRARY_DIR})
  set(G4ROOT_LIBRARIES "-L${G4ROOT_LIBRARY_DIR} -lG4ROOT")
  if (NOT G4ROOT_FIND_QUIETLY)
    message(STATUS "Found G4ROOT in ${G4ROOT_LIBRARY_DIR}")
  endif (NOT G4ROOT_FIND_QUIETLY)
else (G4ROOT_FOUND)
  if (G4ROOT_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for G4ROOT... - Not found")
  endif (G4ROOT_FIND_REQUIRED)
endif (G4ROOT_FOUND)

# Make variables changeble to the advanced user
mark_as_advanced(G4ROOT_INCLUDE_DIR G4ROOT_LIBRARY_DIR G4ROOT_LIBRARIES)

