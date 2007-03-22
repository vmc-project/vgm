// $Id$
//
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test primary generator action
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "TstPrimaryGeneratorAction.hh"

TstPrimaryGeneratorAction::TstPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    fMessenger(this),
    fGunType(kGPS),
    fParticleGun(0),
    fGPSGun(0)
{
  fParticleGun = new G4ParticleGun(1);
  fGPSGun = new G4GeneralParticleSource();
}

TstPrimaryGeneratorAction::~TstPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGPSGun;
}

void TstPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
  switch ( fGunType ) {
    case kGun:
     fParticleGun->GeneratePrimaryVertex(event);
     break;
    case kGPS:
     fGPSGun->GeneratePrimaryVertex(event);
     break;
  }   
}


