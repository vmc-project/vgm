// $Id$
//
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test primary generator action
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "TstPrimaryGeneratorAction.hh"
#include "TstParameters.hh"

TstPrimaryGeneratorAction::TstPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0)
{
  fParticleGun = new G4ParticleGun(1);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  fParticleGun->SetParticleDefinition(
                   particleTable->FindParticle("geantino"));
  fParticleGun->SetParticleEnergy(1.0*GeV);
  fParticleGun->SetParticlePosition(
                   G4ThreeVector(0.0, 0.0, - TstParameters::WorldLength()));
}

TstPrimaryGeneratorAction::~TstPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void TstPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.0, 0.0, 1.0));
  fParticleGun->GeneratePrimaryVertex(event);
}


