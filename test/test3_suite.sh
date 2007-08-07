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

for inputType in VGM AGDD Geant4 Root
# Use the line below for performance tests (G4 navigator)/G4Root navigator)
# for inputType in Geant4 Root
do
  for inputFactory in AGDD Geant4 Root
  do
    for outputFactory in None Geant4
    # Use the line below for performance tests (G4 navigator)/G4Root navigator)
    # for outputFactory in None
    do
      for selectedTest in Solids Placements Reflections Assemblies1 Assemblies2 BooleanSolids1 BooleanSolids2
      do
        #
        # exclude wrong combinations
	# (could be done in a more intelligent way
	#  if we learn more shell scripting ...)   
	#
	if [ $inputType != "VGM" -a "$inputFactory" != "$inputType" ]
	then
	  DUMMY=0
	else 
 	  if [ $inputType = "VGM" -a "$inputFactory" = "AGDD" ]
	  then
	    DUMMY=0
	  else 
 	    if [ $inputType = "AGDD" -a "$inputFactory" = "AGDD" -a  "$outputFactory" = "None" ]
	    then
	      DUMMY=0
	    else 
  	      if [ "$inputFactory" = "$outputFactory" ]
	      then
  	        DUMMY=0
  	      else 
	        NAVIG=""
	        if [ $inputFactory = "Root" -a "$outputFactory" = "None" ]
	        then
                  NAVIG=rootNavig
                  echo "... Regenerating Root geometry file: $selectedTest"
	          vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS \
	            >& $OUTDIR/tmp.out
	        fi        
                echo "Testing configuration: $inputType $inputFactory $outputFactory $selectedTest $NAVIG"
	        vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS run $NAVIG \
	          >& $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest.out"
              fi                   
            fi    
          fi
        fi
      done 	
    done
  done  
done  

for inputType in AGDD
do
  for inputFactory in AGDD
  do
    for outputFactory in Root
    # Use the line below for performance tests (G4 navigator)/G4Root navigator)
    # for outputFactory in None
    do
      for selectedTest in Solids Placements Assemblies1 BooleanSolids1 BooleanSolids2
      do
 	NAVIG=rootNavig
        echo "... Regenerating Root geometry file: $selectedTest"
	vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS \
          >& $OUTDIR/tmp.out
        echo "Testing configuration: $inputType $inputFactory $outputFactory $selectedTest $NAVIG"
	vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS run $NAVIG \
	  >& $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest.out" 
      done 	
    done
  done  
done  

rm $OUTDIR/tmp.out
