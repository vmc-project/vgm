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
// Class GTstPhysicsList
// --------------------
// The test physics list - defines only geantino and transportation
// process
//
// Author: Ivana Hrivnacova; IPN Orsay


#include "TstPhysicsList.hh"
#include "G4ParticleTypes.hh"


//_____________________________________________________________________________
TstPhysicsList::TstPhysicsList() 
  : G4VUserPhysicsList()
{
//
}

//_____________________________________________________________________________
TstPhysicsList::~TstPhysicsList()
{
//
}

//_____________________________________________________________________________
void TstPhysicsList::ConstructParticle() 
{
// Construct geantino only
// ---

  G4Geantino::GeantinoDefinition();
}

//_____________________________________________________________________________
void TstPhysicsList::ConstructProcess()
{
// Define transportation process
// ---

  AddTransportation();
}

//_____________________________________________________________________________
void TstPhysicsList::SetCuts()
{
  // Suppress error messages even in case e/gamma/proton do not exist            
  G4int temp = GetVerboseLevel();                                                SetVerboseLevel(0);                                                           
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(temp);  
}

