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
# VGM test for XML output
#
# by I. Hrivnacova, IPN Orsay

LOGDIR=log
OUTDIR=$LOGDIR/test2
NOVIS="noVis"
NOXML="noXML"

# When running on Mac with SIP enabled, the DYLD_LIBRARY_PATH must be defined
# via another env variable
RUN_ENV=""
if [[ $LD_LIBRARY_PATH} ]]
then
  RUN_ENV="env DYLD_LIBRARY_PATH=${LD_LIBRARY_PATH} "
fi
EXE="$RUN_ENV vgm_test"

for outputXML in AGDD GDML
do
  # file extension
  if [ $outputXML = "AGDD" ]; then
     EXT="agdd"
  fi
  if [ $outputXML = "GDML" ]; then
     EXT="gdml"
  fi

  # create output directory
  if [ ! -d $OUTDIR/$EXT ]
  then
    mkdir -p $OUTDIR/$EXT
  fi

  for inputType in VGM Geant4 Root
  do
    for inputFactory in Geant4 Root
    do
      for selectedTest in Solids Placements Placements2 Placements3 Reflections Assemblies1 Assemblies2 BooleanSolids2 DisplacedSolids1 DisplacedSolids2 MultiUnion
      do
        DOIT="1"

        # exclude wrong combinations
        if [ $inputType != "VGM"  -a $inputFactory != $inputType ];  then DOIT="0";  fi

        # exclude non existing tests
        if [ $inputType  = "VGM"  -a $selectedTest  = "Assemblies1" ]; then DOIT="0";  fi
        if [ $inputType  = "VGM"  -a $selectedTest  = "Assemblies2" ]; then DOIT="0";  fi
        if [ $inputType  = "Root" -a $selectedTest  = "DisplacedSolids2" ]; then DOIT="0";  fi
        if [ $inputType != "Geant4"  -a $selectedTest = "Placements3" ]; then DOIT="0";  fi

        if [ $DOIT = "1" ]; then
          # run test
          echo "Testing configuration: $inputType $inputFactory $outputXML $selectedTest"
  	      $EXE $inputType $inputFactory "None" $outputXML $selectedTest $NOVIS \
	           > /dev/null 2> /dev/null
	        # copy file to output dir
	        mv *.$EXT  $OUTDIR/$EXT
        fi
      done
    done
  done
done
