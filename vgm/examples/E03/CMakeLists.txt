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

#---Example E03 ----------------------------------------------------------------

# Create executable  "exampleE03"

message(STATUS "Configuring Example E03")  

#----------------------------------------------------------------------------
# Includes
#
include_directories(
   ${CLHEP_INCLUDE_DIR} 
   ${GEANT4_INCLUDE_DIR} 
   ${VGM_SOURCE_DIR}/packages/VGM/include
   ${VGM_SOURCE_DIR}/packages/BaseVGM/include 
   ${VGM_SOURCE_DIR}/packages/XmlVGM/include
   ${VGM_SOURCE_DIR}/packages/Geant4GM/include
   ${VGM_SOURCE_DIR}/examples/E03/N03/include
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
add_executable(exampleE03 N03/exampleN03.cc ${sources} ${headers})
target_link_libraries(exampleE03 ${CLHEP_LIBRARIES} ${XERCES_LIBRARIES} ${GEANT4_LIBRARIES} Geant4GM BaseVGM ClhepVGM XmlVGM)

#----------------------------------------------------------------------------
# Copy all test scripts and macros to the build directory.
#

# macros
file(GLOB macros N03/*.mac)
foreach(_macropath ${macros})
  get_filename_component(_macro ${_macropath} NAME)
  # message(STATUS "Macro in list ${_macro}")
  configure_file(
    ${PROJECT_SOURCE_DIR}/examples/E03/N03/${_macro}
    ${PROJECT_BINARY_DIR}/examples/E03/N03/${_macro}
    COPYONLY
  )
endforeach()

#----Installation-----------------------------------------------------------------
install(TARGETS exampleE03 DESTINATION bin)
