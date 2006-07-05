#!/bin/sh
#
# Script for installation for E02 examples

CURDIR=`pwd`

# E02
#
echo "... Installing E02"
cp -r ${G4INSTALL}/examples/novice/N03 .
cp N03Example.root N03
cp GNUmakefile N03
cp ExN03DetectorConstruction.hh N03/include
cp ExN03DetectorConstruction.cc N03/src
cp ExN03PrimaryGeneratorAction.cc N03/src
cp ExN03SteppingAction.cc N03/src
rm N03/include/ExN03DetectorMessenger.hh
rm N03/src/ExN03DetectorMessenger.cc
. env_setup.sh
cd N03
gmake
echo "... Installing E02 finished"

cd $CURDIR
