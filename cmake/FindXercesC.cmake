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

# - Try to find XercesC library
# Once done this will define
#
#  XERCES_FOUND     - If Xerces-C is found
#  XERCES_LIBRARIES - The libraries needed to use XercesC
#

message(STATUS "Looking for XercesC library ...")

find_path(XERCES_LIBRARY_DIR NAMES libxerces-c.so libxerces-c.dylib PATHS
  ${XERCES_LIB_DIR}
  ${XERCES_DIR}/lib
  ${XERCES_DIR}/lib64
  /usr/lib64
  /usr/lib
)

if (XERCES_LIBRARY_DIR)
  set(XERCES_FOUND TRUE)
endif (XERCES_LIBRARY_DIR)

if (XERCES_FOUND)
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${XERCES_LIBRARY_DIR})
  set(XERCES_LIBRARIES "-L${XERCES_LIBRARY_DIR} -lxerces-c")
  if (NOT XERCES_FIND_QUIETLY)
    message(STATUS "Found XercesC library in ${XERCES_LIBRARY_DIR}")
  endif (NOT XERCES_FIND_QUIETLY)
else (XERCES_FOUND)
  if (XERCES_FIND_REQUIRED)
    message(FATAL_ERROR "Xerces-C required, but not found")
  endif (XERCES_FIND_REQUIRED)
endif (XERCES_FOUND)

# Make variables changeble to the advanced user
mark_as_advanced(XERCES_LIBRARY_DIR XERCES_LIBRARIES)

