#!/bin/sh
#
# Script for installation for E01 examples

CURDIR=`pwd`

echo "... Installing E01"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp GNUmakefile N03
cp ExN03DetectorConstruction.cc N03/src
. env_setup.sh
cd N03
gmake
echo "... Installing E01 finished"

cd $CURDIR
