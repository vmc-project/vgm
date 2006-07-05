#!/bin/sh
#
# Script for installation for E03 examples

CURDIR=`pwd`

echo "... Installing E03"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp GNUmakefile N03
cp ExN03DetectorConstruction.cc N03/src
. env_setup.sh
cd N03
gmake
echo "... Installing E03 finished"

cd $CURDIR
