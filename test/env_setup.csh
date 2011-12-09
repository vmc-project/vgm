# $Id$

# -----------------------------------------------------------------------
# The script for environment setting for the Virtual Geometry Model test
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# The environment setting for the VGM test G4 application 
#
# by I. Hrivnacova, IPN Orsay

# set Geant4 environment for building example via GNU Make 
source "`geant4-config --prefix`"/share/Geant4-"`geant4-config --version`"/geant4make/geant4make.csh         

setenv G4WORKDIR ${VGM_INSTALL}/test
setenv PATH ${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
setenv LD_LIBRARY_PATH ${G4WORKDIR}/tmp/${G4SYSTEM}/vgm_test:${LD_LIBRARY_PATH}
setenv LD_LIBRARY_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${LD_LIBRARY_PATH}

rehash

