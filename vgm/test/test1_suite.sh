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

for inputType in VGM AGDD Geant4 Root
do
  for inputFactory in AGDD Geant4 Root
  do
    for outputFactory in None Geant4 Root
    do
      for selectedTest in Solids Placements Reflections Assemblies1 Assemblies2 BooleanSolids2 
      #for selectedTest in Placements 
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
 	    if [ $inputType != "VGM" -a "$outputFactory" = "None" ]
	    then
	      DUMMY=0
	    else 
  	      if [ "$inputFactory" = "$outputFactory" ]
	      then
  	        DUMMY=0
	      else 
                echo "Testing configuration: $inputType $inputFactory $outputFactory $selectedTest"
	        vgm_test $inputType $inputFactory $outputFactory $NOXML $selectedTest $NOVIS debug \
	          > $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest.out"   \
	          2> $OUTDIR/"$inputType.$inputFactory.$outputFactory.$selectedTest.err"
              fi      
            fi
	  fi    
        fi
      done 	
    done
  done  
done  
