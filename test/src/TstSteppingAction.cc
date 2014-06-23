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
// The test Stepping action.
// It kills looping tracks, after they reach predefined number of steps.
//
// Author: Ivana Hrivnacova; IPN Orsay

 
#include "TstSteppingAction.hh"

#include "G4Track.hh"
#include "G4ios.hh"
 
const G4int TstSteppingAction::fgkMaxStepNumber = 1000;

TstSteppingAction::TstSteppingAction()
{}

TstSteppingAction::~TstSteppingAction()
{}

void TstSteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* track = step->GetTrack();  
  G4int stepNumber = track->GetCurrentStepNumber();

  // stop track if maximum number of steps has been reached
  // 
  if ( stepNumber ==  fgkMaxStepNumber) {    
    G4cerr << "MaxStepNumber (" << fgkMaxStepNumber
           << ") has been reached. Stopping track ..." << G4endl;

    track->SetTrackStatus(fStopAndKill); 
  }    
}
