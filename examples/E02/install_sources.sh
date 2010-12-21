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
# Script for installation of sources for E02 examples

CURDIR=`pwd`

# E02
#
echo "... Installing E02 sources"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp N03Example.root N03
cp GNUmakefile N03
cp DetectorConstruction.cc N03/src
#cp ExN03PrimaryGeneratorAction.cc N03/src
#cp ExN03SteppingAction.cc N03/src
#rm N03/include/ExN03DetectorMessenger.hh
#rm N03/src/ExN03DetectorMessenger.cc

cd $CURDIR
