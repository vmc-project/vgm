//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// Id: ExN03DetectorConstruction.hh,v 1.6 2003/09/15 15:38:14 maire Exp 
// GEANT4 tag Name: geant4-06-00-patch-01 
//
// $Id$
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN03DetectorConstruction_h
#define ExN03DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN03DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    ExN03DetectorConstruction();
   ~ExN03DetectorConstruction();

  public:
     
     G4VPhysicalVolume* Construct();
     const G4LogicalVolume* GetAbsorber()   {return logicAbsorber;};
     const G4LogicalVolume* GetGap()        {return logicGap;};

  private:
     G4LogicalVolume*  FindVolume(const G4String& name) const;

     G4LogicalVolume*   logicWorld;    //pointer to the logical World
     G4LogicalVolume*   logicCalor;    //pointer to the logical Calor
     G4LogicalVolume*   logicLayer;    //pointer to the logical Layer
     G4LogicalVolume*   logicAbsorber; //pointer to the logical Absorber
     G4LogicalVolume*   logicGap;      //pointer to the logical Gap
};

#endif

