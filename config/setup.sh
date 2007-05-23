# $Id$

# -----------------------------------------------------------------------
# The script for environment setting for the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# The default environment setting for VGM
#
# by I. Hrivnacova, IPN Orsay

# Path to VGM directory
#
export VGM_INSTALL=$HOME/vgm

# Architecture dependent setting
#
SYSTEM=`uname`

if [ "$SYSTEM" = "Linux" ]; then
  export VGM_SYSTEM=Linux-g++
  export LD_LIBRARY_PATH=$VGM_INSTALL/lib/$VGM_SYSTEM:$LD_LIBRARY_PATH
fi

if [ "$SYSTEM" = "SunOS" ]; then
  export VGM_SYSTEM=SUN-CC5
  export LD_LIBRARY_PATH=$VGM_INSTALL/lib/$VGM_SYSTEM:$LD_LIBRARY_PATH
fi

if [ "$SYSTEM" = "OSF1" ]; then
  export VGM_SYSTEM=DEC-cxx
  export LD_LIBRARY_PATH=$VGM_INSTALL/lib/$VGM_SYSTEM:$LD_LIBRARY_PATH
fi

if [ "$SYSTEM" = "HP-UX" ]; then
  export VGM_SYSTEM="HP-aCC"
  export SHLIB_PATH=$VGM_INSTALL/lib/$VGM_SYSTEM:$SHLIB_PATH
fi  
