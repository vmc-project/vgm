# $Id$

# -----------------------------------------------------------------------
# The script for environment setting for the Virtual Geometry Model example
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# The environment setting for the E01 example 
#
# by I. Hrivnacova, IPN Orsay

# set Geant4 environment for building example via GNU Make 
if [ ! "`which geant4-config 2> /dev/null`" = "" ]; then
  . "`geant4-config --prefix`"/share/Geant4-"`geant4-config --version`"/geant4make/geant4make.sh 
fi

export G4WORKDIR=`pwd`/N03
export PATH=${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
export LD_LIBRARY_PATH=${G4WORKDIR}/tmp/${G4SYSTEM}/exampleN03:${LD_LIBRARY_PATH}
