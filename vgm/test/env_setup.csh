# $Id$
# The environment setting for the VGM test G4 application 
#
# by I. Hrivnacova, IPN Orsay

setenv G4WORKDIR ${VGM_INSTALL}/test
setenv PATH ${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
setenv LD_LIBRARY_PATH ${G4WORKDIR}/tmp/${G4SYSTEM}/vgm_test:${LD_LIBRARY_PATH}
setenv LD_LIBRARY_PATH ${VGM_INSTALL}/lib/${VGM_SYSTEM}:${LD_LIBRARY_PATH}

rehash

