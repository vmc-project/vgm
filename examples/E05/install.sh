#!/bin/sh
# $Id: install.sh 544 2007-05-23 10:39:11Z ivana $

# -----------------------------------------------------------------------
# The script for installation for the Virtual Geometry Model examples
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation for E05 example

CURDIR=`pwd`

echo "... Installing E05"

g++ -I$AGDD_INSTALL/include \
    -I$ROOTSYS/include \
    -I$VGM_INSTALL/packages/VGM/include \
    -I$VGM_INSTALL/packages/BaseVGM/include \
    -I$VGM_INSTALL/packages/AgddGM/include \
    -I$VGM_INSTALL/packages/RootGM/include \
    -I$CLHEP_BASE_DIR/include \
    -L$VGM_INSTALL/lib/$VGM_SYSTEM -lAgddGM -lRootGM -lBaseVGM -lClhepVGM \
    -L$CLHEP_BASE_DIR/lib -lCLHEP \
    -L${AGDD_INSTALL}/lib -lagdd \
    -L${XERCESC_INSTALL}/lib -lxerces-c \
    `root-config --glibs` -lGeomPainter -lGeom agdd2root.cxx \
    -o agdd2root

echo "... Installing E05 finished"

cd $CURDIR
