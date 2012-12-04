# $Id$

# -----------------------------------------------------------------------
# The script for the Virtual Geometry Model test
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# An example of configure options for building VGM
# with all supported packages with CLHEP, expat embedded in Geant4
# (available since Geant4 9.5)
#
# by I. Hrivnacova, IPN Orsay


./configure --prefix=/work/projects/vgm/new/autoconf/vgm_build \
            --with-xerces=/usr \
            --with-clhep=no \
            --with-geant4=/work/projects/vgm/new/geant4 \
            --with-root=/work/projects/vgm/new/root

