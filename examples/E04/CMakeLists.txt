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

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.8.3 FATAL_ERROR)
project(E04)

#----------------------------------------------------------------------------
# Set path to Find modules in VGM
#
set(CMAKE_MODULE_PATH 
    ${VGM_DIR}/Modules
    ${CMAKE_MODULE_PATH}) 

#----------------------------------------------------------------------------
# Find VGM package
if (NOT VGM_FOUND)
  find_package(VGM REQUIRED)
endif()

#----------------------------------------------------------------------------
# Find ROOT package
find_package(ROOT REQUIRED)

#----------------------------------------------------------------------------
# Includes
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${ROOT_INCLUDE_DIRS}
                    ${VGM_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Add the executable, and link it to the VGM libraries
#
add_executable(exampleE04 rootgeom.cxx)
target_link_libraries(exampleE04 ${VGM_ROOT_LIBRARIES} ${ROOT_LIBRARIES})
#VGM Libraries can be used also explicitly
#target_link_libraries(exampleE04 RootGM ClhepVGM BaseVGM XmlVGM ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all test scripts and macros to the build directory.
#
set(E04_SCRIPTS
  rootgeom.C
)

foreach(_script ${E04_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----Installation-----------------------------------------------------------------
install(TARGETS exampleE04 DESTINATION bin)
