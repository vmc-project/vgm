// $Id$

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstSteppingAction
// -------------------------------
// The test Stepping action
//
// Author: Ivana Hrivnacova; IPN Orsay

 
#ifndef TST_STEPPING_ACTION_H
#define TST_STEPPING_ACTION_H

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Track;

class TstSteppingAction : public G4UserSteppingAction
{
  public:
    TstSteppingAction();
   ~TstSteppingAction();

    virtual void UserSteppingAction(const G4Step* step);

  private:
    static const G4int fgkMaxStepNumber;
};

#endif

    
