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
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN03DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

// VGM demo
#include "Geant4GM/volumes/Factory.h"
#include "RootGM/volumes/Factory.h"
#include "TGeoManager.h"
// end VGM demo


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN03DetectorConstruction::ExN03DetectorConstruction()
  : logicWorld(0),
    logicCalor(0),
    logicLayer(0),
    logicAbsorber(0),
    logicGap (0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN03DetectorConstruction::~ExN03DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  // ---------------------------------------------------------------------------
  // VGM demo 
  //

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume*  
ExN03DetectorConstruction::FindVolume(const G4String& name) const
{
  G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();
  
  for (G4int i=0; i<G4int(lvStore->size()); i++) {
    G4LogicalVolume* lv = (*lvStore)[i];
    if (lv->GetName() == name) return lv;
  }

  G4String text = "ExN03DetectorConstruction:: FindVolume:\n"; 
  text = text + "    Logical volume " + name + " does not exist.";
  std::cerr << text << G4endl;
  return 0;
}  	       	         

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ExN03DetectorConstruction::Construct()
{
  // 
  // Import geometry from Root
  //

  // Import geometry from the root file
  new TGeoManager("N03", "Geant4 novice example N03");
  gGeoManager->Import("N03Example.root");

  // Import geometry from Root to VGM
  RootGM::Factory rtFactory;
  rtFactory.SetDebug(1);
  rtFactory.Import(gGeoManager->GetTopNode());

  // Export VGM geometry to Geant4
  //
  Geant4GM::Factory g4Factory;
  g4Factory.SetDebug(1);
  rtFactory.Export(&g4Factory);
  G4VPhysicalVolume* world = g4Factory.World();

  // Get volumes from logical volume store by name
  logicCalor = FindVolume("Calorimeter");
  logicLayer = FindVolume("Layer");
  logicAbsorber = FindVolume("Lead");
  logicGap = FindVolume("liquidArgon");
  
  // Visualization attributes
  //
  logicWorld = world->GetLogicalVolume();
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
  G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  simpleBoxVisAtt->SetVisibility(true);
  if (logicCalor)    logicCalor->SetVisAttributes(simpleBoxVisAtt);
  if (logicLayer)    logicLayer->SetVisAttributes(simpleBoxVisAtt);
  if (logicAbsorber) logicAbsorber->SetVisAttributes(simpleBoxVisAtt);
  if (logicGap)      logicGap->SetVisAttributes(simpleBoxVisAtt);
  
  return world;
}

  //
  // end VGM demo
  //---------------------------------------------------------------------------
