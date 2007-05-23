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
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test primary generator action
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TST_PRIMARY_GENERATOR_ACTION_H
#define TST_PRIMARY_GENERATOR_ACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "TstPrimaryGeneratorActionMessenger.hh"

class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;

class TstPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    enum GunType {
      kGun,
      kGPS
    };  

  public:
    TstPrimaryGeneratorAction();
    virtual ~TstPrimaryGeneratorAction();
    
    // set method
    void SetGunType(GunType gunType);

  public:
    void GeneratePrimaries(G4Event* event);

  private:
    TstPrimaryGeneratorActionMessenger fMessenger;
    GunType                   fGunType;
    G4ParticleGun*            fParticleGun;
    G4GeneralParticleSource*  fGPSGun;
};

// inline functions

inline void TstPrimaryGeneratorAction::SetGunType(TstPrimaryGeneratorAction::GunType gunType)
{  fGunType = gunType; }

#endif //TST_PRIMARY_GENERATOR_ACTION_H


