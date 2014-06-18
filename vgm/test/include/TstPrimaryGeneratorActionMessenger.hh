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
 
#ifndef TST_PRIMARY_GENERATOR_ACTION_MESSENGER_H
#define TST_PRIMARY_GENERATOR_ACTION_MESSENGER_H 

#include <G4UImessenger.hh>
#include <globals.hh>

class TstPrimaryGeneratorAction;

class G4UIdirectory;
class G4UIcmdWithAString;

class TstPrimaryGeneratorActionMessenger: public G4UImessenger
{
  public:
    TstPrimaryGeneratorActionMessenger(
       TstPrimaryGeneratorAction* primaryGeneratorAction);
    virtual ~TstPrimaryGeneratorActionMessenger();
   
    // methods 
    virtual void SetNewValue(G4UIcommand* command, G4String string);
    
  private:
    TstPrimaryGeneratorActionMessenger();
    TstPrimaryGeneratorActionMessenger(
       const TstPrimaryGeneratorActionMessenger& right);
    TstPrimaryGeneratorActionMessenger& operator=(
       const TstPrimaryGeneratorActionMessenger& right);

    // data members
    TstPrimaryGeneratorAction*  fPrimaryGeneratorAction; //associated class 
    G4UIdirectory*       fDirectory;         //command directory
    G4UIcmdWithAString*  fSetGunTypeCmd;     //command: /tstGenerator/gunType
};

#endif //TST_PRIMARY_GENERATOR_ACTION_MESSENGER_H
