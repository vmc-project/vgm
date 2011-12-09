#!/bin/sh
# $Id$

# -----------------------------------------------------------------------
# The script for environment setting for the Virtual Geometry Model example
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation of sources for E01 examples

CURDIR=`pwd`

# Find sources
echo "... Installing E01 sources"
DIR="`geant4-config --prefix`"/share/Geant4-"`geant4-config --version`"/examples/novice/N03
if [ ! -d ${DIR} ]; then 
  DIR=${G4INSTALL}/examples/novice/N03
fi
if [ ! -d ${DIR} ]; then 
  echo "... Example source not found in Geant4 installation"
  exit 1
fi    

# Copy sources
cp -r ${DIR} .
cp GNUmakefile N03
cp DetectorConstruction.cc N03/src

cd $CURDIR
