# $Id$
# The environment setting for the E01 example 
#
# by I. Hrivnacova, IPN Orsay

export G4WORKDIR=`pwd`/N03
export PATH=${G4WORKDIR}/bin/${G4SYSTEM}:${PATH}
export LD_LIBRARY_PATH=${G4WORKDIR}/tmp/${G4SYSTEM}/exampleN03:${LD_LIBRARY_PATH}
