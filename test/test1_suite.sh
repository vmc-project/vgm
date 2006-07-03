#!/bin/sh 
# $Id$
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
      done 	
    done
  done  
done  
