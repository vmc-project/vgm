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
// Class TstPrimaryGeneratorActionMessenger
// ----------------------------------------
// The test primary generator action messenger
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "TstPrimaryGeneratorActionMessenger.hh"
#include "TstPrimaryGeneratorAction.hh"

#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>

//_____________________________________________________________________________
TstPrimaryGeneratorActionMessenger::TstPrimaryGeneratorActionMessenger(
                             TstPrimaryGeneratorAction* primaryGeneratorAction)
  : G4UImessenger(),
    fPrimaryGeneratorAction(primaryGeneratorAction),
    fDirectory(0),
    fSetGunTypeCmd(0)
{
//
  fDirectory = new G4UIdirectory("/tstGenerator/");
  fDirectory->SetGuidance("TstPrimaryGeneratorAction control commands.");

  fSetGunTypeCmd = new G4UIcmdWithAString("/tstGenerator/gunType", this);
  fSetGunTypeCmd->SetGuidance("Select gun type: Gun GPS");
  fSetGunTypeCmd->SetParameterName("gunType", false);
  fSetGunTypeCmd->SetCandidates("Gun GPS");
  fSetGunTypeCmd->AvailableForStates(G4State_PreInit, G4State_Init, G4State_Idle);
}

//_____________________________________________________________________________
TstPrimaryGeneratorActionMessenger::~TstPrimaryGeneratorActionMessenger() {
//
  delete fDirectory;
  delete fSetGunTypeCmd;
}

//
// public methods
//

//_____________________________________________________________________________
void TstPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command,
       G4String newValue)
{
/// Apply command to the associated object.

  if(command == fSetGunTypeCmd) {
    if ( newValue == G4String("Gun") ) {
      fPrimaryGeneratorAction->SetGunType(TstPrimaryGeneratorAction::kGun);
    }
    else if ( newValue == G4String("GPS") ) {
      fPrimaryGeneratorAction->SetGunType(TstPrimaryGeneratorAction::kGPS);
    }
  }
}
