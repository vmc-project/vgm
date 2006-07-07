#!/bin/sh
#
# Script for installation of sources for E01 examples

CURDIR=`pwd`

echo "... Installing E01 sources"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp GNUmakefile N03
cp ExN03DetectorConstruction.cc N03/src

cd $CURDIR
