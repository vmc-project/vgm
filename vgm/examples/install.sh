#!/bin/sh

# -----------------------------------------------------------------------
# The script for installation for the Virtual Geometry Model examples
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation for all examples

CURDIR=`pwd`

cd E01
./install.sh

cd $CURDIR/E02
./install.sh

cd $CURDIR/E03
./install.sh

cd $CURDIR/E04
./install.sh

cd $CURDIR
