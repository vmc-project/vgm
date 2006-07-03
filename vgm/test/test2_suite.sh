#!/bin/sh 
# $Id$
#
# VGM test for XML output 
#
# by I. Hrivnacova, IPN Orsay

LOGDIR=log
OUTDIR=$LOGDIR/test2
NOVIS="noVis"
NOXML="noXML"

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
 	  if [ $inputType = "VGM" -a "$selectedTest" = "Assemblies1" ]
	  then
	    DUMMY=0
	  else 
	    if [ $inputType = "VGM" -a "$selectedTest" = "Assemblies2" ]
	    then 
	      DUMMY=0
	    else 
              echo "Testing configuration: $inputType $inputFactory $outputXML $selectedTest"
	      vgm_test $inputType $inputFactory "None" $outputXML $selectedTest $NOVIS \
	        > /dev/null 2> /dev/null
  
	      # copy file to output dir
	      mv *.$EXT  $OUTDIR/$EXT
	    fi
	  fi    
        fi
      done 	
    done
  done  
done  
