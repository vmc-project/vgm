// $Id$
//
// Class TstParameters
// -------------------
// The test parameters
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "TstParameters.hh"

TstParameters* TstParameters::fgInstance = 0;
G4double       TstParameters::fgkWorldLength = 10.*m;

//_____________________________________________________________________________
TstParameters* TstParameters::Instance()
{
  if (!fgInstance) 
    fgInstance = new TstParameters();
    
  return fgInstance;
}     

//_____________________________________________________________________________
TstParameters::TstParameters()
{
  fgInstance = this;
}

//_____________________________________________________________________________
TstParameters::~TstParameters()
{
  fgInstance = 0;
}
