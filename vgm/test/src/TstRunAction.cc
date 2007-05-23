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
// Class TstRunAction
// ----------------------------------------
// The test run action
//
// Author: Ivana Hrivnacova; IPN Orsay

// Make this appear first!
#include "G4Timer.hh"

#include "TstRunAction.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

#include <iomanip>

TstRunAction::TstRunAction()
{
  timer = new G4Timer;
}

TstRunAction::~TstRunAction()
{
  delete timer;
}

void TstRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  timer->Start();
  timer2.Start(true);
}

void TstRunAction::EndOfRunAction(const G4Run* aRun)
{
  timer->Stop();
  timer2.Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *timer << G4endl;
  G4cout << std::setprecision(3)
         << "Execution time:"
         << " R: " << timer2.RealTime() << " s "
         << " C: " << timer2.RealTime() << " s " << G4endl;
}

