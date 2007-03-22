//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id$
// GEANT4 tag $Name$
//

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

