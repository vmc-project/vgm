# $Id$
# The default environment setting for VGM
#
# by I. Hrivnacova, IPN Orsay

# Path to VGM directory
#
setenv VGM_INSTALL ${HOME}/vgm

# Architecture dependent setting
#
set SYSTEM = `uname`

if ( $SYSTEM == "Linux" ) then
  setenv VGM_SYSTEM "Linux-g++"
  setenv LD_LIBRARY_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${LD_LIBRARY_PATH}
endif

if ( $SYSTEM == "SunOS" ) then
  setenv VGM_SYSTEM "SUN-CC5"
  setenv LD_LIBRARY_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${LD_LIBRARY_PATH}
endif 

if ( $SYSTEM == "OSF1" ) then
  setenv VGM_SYSTEM "DEC-cxx"
  setenv LD_LIBRARY_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${LD_LIBRARY_PATH}
endif 

if ( $SYSTEM == "HP-UX" ) then
  setenv VGM_SYSTEM "HP-aCC"
  setenv SHLIB_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${SHLIB_PATH}
endif 
