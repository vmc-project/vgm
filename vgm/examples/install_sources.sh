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

SOURCE_DIR=`dirname $0`

$SOURCE_DIR/E01/install_sources.sh
$SOURCE_DIR/E02/install_sources.sh
$SOURCE_DIR/E03/install_sources.sh
