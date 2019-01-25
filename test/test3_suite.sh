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
# VGM tracking test suite 
#
# by I. Hrivnacova, IPN Orsay

LOGDIR=log
OUTDIR=$LOGDIR/test3
NOVIS="noVis"
NOXML="noXML"

if [ ! -d $OUTDIR ] 
then
  mkdir -p $OUTDIR 
fi

for inputType in VGM Geant4 Root
# Use the line below for performance tests (G4 navigator)/G4Root navigator)
# for inputType in Geant4 Root
do
  for inputFactory in Geant4 Root
  do
    for outputFactory in None Geant4
    # Use the line below for performance tests (G4 navigator)/G4Root navigator)
    # for outputFactory in None
    do
      for selectedTest in Solids Placements Placements2 Reflections ScaledSolids Assemblies1 Assemblies2 BooleanSolids1 BooleanSolids2 DisplacedSolids1 DisplacedSolids2 BestMatch
      do
        DOIT="1"

        # exclude wrong combinations
        if [ $inputType != "VGM"  -a $inputFactory != $inputType ];  then DOIT="0"; fi
        if [ $inputFactory = $outputFactory ]; then DOIT="0";  fi

        # exclude non existing tests
        if [ $inputType = "VGM"  -a $selectedTest = "Assemblies1" ]; then DOIT="0";  fi
        if [ $inputType = "VGM"  -a $selectedTest = "Assemblies2" ]; then DOIT="0";  fi
        if [ $inputType = "Root" -a $selectedTest = "DisplacedSolids2" ]; then DOIT="0";  fi
        if [ $inputFactory != "Root" -a $outputFactory != "Root" -a $selectedTest = "BestMatch" ]; then DOIT="0";  fi

        if [ $DOIT = "1" ]; then
          # Placements2 test with bestMatch option
          OPTION=""
          if [ $selectedTest = "BestMatch" ]; then
            OPTION="bestMatch"
            selectedTest="Placements2"
          fi

          # generate Root geometry file for test with rootNavig
          NAVIG=""
          if [ $inputFactory = "Root" -a "$outputFactory" = "None" ]
          then
            NAVIG=rootNavig
            #echo "... Regenerating Root geometry file: $selectedTest"
            vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS $OPTION \
              >& $OUTDIR/tmp.out
          fi

          # run test
          vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS $OPTION run $NAVIG \
            >& $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest$OPTION.out"

        fi  	
      done 
    done
  done  
done  

rm $OUTDIR/tmp.out
