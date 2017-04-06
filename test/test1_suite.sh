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

#
# Full VGM test suite 
#
# by I. Hrivnacova, IPN Orsay

LOGDIR=log
OUTDIR=$LOGDIR/test1
NOVIS="noVis"
NOXML="noXML"
#NOVIS=""

if [ ! -d $OUTDIR ] 
then
  mkdir -p $OUTDIR 
fi

for inputType in VGM Geant4 Root
do
  for inputFactory in Geant4 Root
  do
    for outputFactory in None Geant4 Root
    do
      for selectedTest in Solids Placements Reflections ScaledSolids Assemblies1 Assemblies2 BooleanSolids2 DisplacedSolids1 DisplacedSolids2 
      #for selectedTest in Placements 
      do
        DOIT="1"

        # exclude wrong combinations
	if [ $inputType != "VGM" -a $inputFactory != $inputType ];  then DOIT="0"; fi 
 	if [ $inputType  = "VGM" -a $outputFactory = "None" ];      then DOIT="0"; fi 
  	if [ $inputFactory = $outputFactory ]; then DOIT="0";  fi 

        # exclude non existing tests
  	if [ $inputType  = "VGM"  -a $selectedTest  = "Assemblies1" ]; then DOIT="0";  fi 
  	if [ $inputType  = "VGM"  -a $selectedTest  = "Assemblies2" ]; then DOIT="0";  fi 
  	if [ $inputType  = "Root" -a $selectedTest  = "DisplacedSolids2" ]; then DOIT="0";  fi 

        if [ $DOIT = "1" ]; then
          # run test
          echo "Testing configuration: $inputType $inputFactory $outputFactory $selectedTest"
          vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS debug \
            >& $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest.out"
        fi    
      done 	
    done
  done  
done
