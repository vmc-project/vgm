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
// Class TstPhysicsList
// --------------------
// The test physics list - defines only geantino and transportation
// process
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef TST_PHYSICS_LIST_H
#define TST_PHYSICS_LIST_H

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class TstPhysicsList: public G4VUserPhysicsList
{
  public:
    TstPhysicsList();
    virtual ~TstPhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();
};

#endif //G_TST_PHYSICS_LIST_H







