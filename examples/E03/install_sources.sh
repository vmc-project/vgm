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
# Script for installation of sources for E03 examples

CURDIR=`pwd`

echo "... Installing E03 sources"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp GNUmakefile N03
cp DetectorConstruction.cc N03/src

cd $CURDIR
