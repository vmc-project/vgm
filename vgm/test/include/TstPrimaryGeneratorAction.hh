// $Id$
//
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test primary generator action
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TST_PRIMARY_GENERATOR_ACTION_H
#define TST_PRIMARY_GENERATOR_ACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class TstPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TstPrimaryGeneratorAction();
    virtual ~TstPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* event);

  private:
    G4ParticleGun*  fParticleGun;
};

#endif //TST_PRIMARY_GENERATOR_ACTION_H


