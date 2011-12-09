#!/bin/sh
# $Id$

# -----------------------------------------------------------------------
# The script for installation for the Virtual Geometry Model examples
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation for E04 examples

CURDIR=`pwd`

echo "... Installing E04"

if [ ! "$CLHEP_BASE_DIR" = "" ]; then  
  LINK_CLHEP="-L$CLHEP_BASE_DIR/lib -lCLHEP"
else
  if [ ! "$G4LIB" = "" ]; then  
    LINK_CLHEP="-L$G4LIB/$G4SYSTEM -lG4clhep"
  else  
    LINK_CLHEP=`geant4-config --libs`
  fi
fi  
   
g++ -I$ROOTSYS/include \
    -I$VGM_INSTALL/packages/VGM/include \
    -I$VGM_INSTALL/packages/BaseVGM/include \
    -I$VGM_INSTALL/packages/RootGM/include \
    -I$VGM_INSTALL/packages/XmlVGM/include \
    -I$CLHEP_BASE_DIR/include \
    -L$VGM_INSTALL/lib/$VGM_SYSTEM -lRootGM -lBaseVGM -lXmlVGM -lClhepVGM \
    $LINK_CLHEP \
    `root-config --glibs` -lGeomPainter -lGeom rootgeom.cxx \
    -o rootgeom

echo "... Installing E04 finished"

cd $CURDIR
