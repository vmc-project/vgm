// $Id$
//
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test primary generator action
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TST_PARAMETERS_H
#define TST_PARAMETERS_H

#include "globals.hh"

class TstParameters
{
  public:
    virtual ~TstParameters();

    static TstParameters* Instance(); 

    static G4double WorldLength() { return fgkWorldLength; }

  private:
    TstParameters();

    static TstParameters* fgInstance;
    static G4double  fgkWorldLength;
};

#endif //TST_PARAMETERS_H


