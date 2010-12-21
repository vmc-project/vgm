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
# with all supported packages
#
# by I. Hrivnacova, IPN Orsay


./configure --prefix=/work/projects/vgm/autoconf/vgm_built \
            --with-xerces=/usr \
            --with-clhep=/work/packages/clhep/2.1.0.1 \
            --with-geant4=/work/projects/vgm/new/geant4 \
            --with-root=/work/projects/vgm/new/root
