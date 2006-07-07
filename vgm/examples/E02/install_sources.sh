#!/bin/sh
#
# Script for installation of sources for E02 examples

CURDIR=`pwd`

# E02
#
echo "... Installing E02 sources"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp N03Example.root N03
cp GNUmakefile N03
cp ExN03DetectorConstruction.hh N03/include
cp ExN03DetectorConstruction.cc N03/src
cp ExN03PrimaryGeneratorAction.cc N03/src
cp ExN03SteppingAction.cc N03/src
rm N03/include/ExN03DetectorMessenger.hh
rm N03/src/ExN03DetectorMessenger.cc

cd $CURDIR
