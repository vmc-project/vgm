#!/bin/sh
# $Id$

# -----------------------------------------------------------------------
# The test script of the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova
# All rights reserved.
#
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

echo "### Runing TEST1 suite ..."
./test1_suite.sh

echo
echo "### Runing TEST2 suite ..."
./test2_suite.sh

echo
echo "### Runing TEST3 suite ..."
./test3_suite.sh
