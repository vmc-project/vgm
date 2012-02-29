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

#---Example E04 ----------------------------------------------------------------

# Create executable  "rootgeom"

message(STATUS "Configuring Example E04")  

#----------------------------------------------------------------------------
# Includes
#
include_directories(
   ${CLHEP_INCLUDE_DIR} 
   ${ROOT_INCLUDE_DIR} 
   ${VGM_SOURCE_DIR}/packages/VGM/include
   ${VGM_SOURCE_DIR}/packages/BaseVGM/include 
   ${VGM_SOURCE_DIR}/packages/XmlVGM/include
   ${VGM_SOURCE_DIR}/packages/RootGM/include
)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources N03/src/*.cc)
file(GLOB headers N03/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(rootgeom rootgeom.cxx)
target_link_libraries(rootgeom ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} RootGM BaseVGM ClhepVGM XmlVGM)

#----------------------------------------------------------------------------
# Copy all test scripts and macros to the build directory.
#

# macros
file(GLOB macros *.C)
foreach(_macropath ${macros})
  get_filename_component(_macro ${_macropath} NAME)
  # message(STATUS "Macro in list ${_macro}")
  configure_file(
    ${PROJECT_SOURCE_DIR}/examples/E04/${_macro}
    ${PROJECT_BINARY_DIR}/examples/E04/${_macro}
    COPYONLY
  )
endforeach()

#----Installation-----------------------------------------------------------------
install(TARGETS rootgeom DESTINATION bin)
