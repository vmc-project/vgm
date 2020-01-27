# $Id$

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(E02)

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
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS}
                    ${VGM_INCLUDE_DIRS})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(exampleE02 exampleB4a.cc ${sources} ${headers})
target_link_libraries(exampleE02 ${VGM_LIBRARIES} ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B4a. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(B4a_SCRIPTS
  exampleB4a.out
  exampleB4.in
  icons.mac
  gui.mac
  run.png
  init.mac
  init_vis.mac
  run1.mac
  run2.mac
  vis.mac
  )

foreach(_script ${B4a_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS exampleE02 DESTINATION bin)
