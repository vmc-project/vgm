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

#---Process packages subdirectories --------------------------------------------
      
add_subdirectory(VGM)
add_subdirectory(ClhepVGM)
add_subdirectory(BaseVGM)
add_subdirectory(XmlVGM)
if(WITH_GEANT4)
  add_subdirectory(Geant4GM)
endif()
if(WITH_ROOT)
  add_subdirectory(RootGM)
endif()

