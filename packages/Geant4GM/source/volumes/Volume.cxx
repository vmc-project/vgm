// $Id$
//
// Class Volume
// ---------------
// VGM implementation for Geant4 volume.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4VSolid.hh"
#include "G4Material.hh"

#include "Geant4GM/volumes/Volume.h"
#include "Geant4GM/volumes/VolumeMap.h"
#include "Geant4GM/solids/SolidMap.h"

#include <iostream>

//_____________________________________________________________________________
Geant4GM::Volume::Volume(const std::string& name, 
                         VGM::ISolid* solid, 
                         const std::string& materialName) 
  : BaseVGM::VVolume(solid),
    fLogicalVolume(0) {
//

  // Get solid from the solid map
  G4VSolid* g4Solid = Geant4GM::SolidMap::Instance()->GetSolid(solid);
  
  // Get material from G4
  G4Material* g4Material = G4Material::GetMaterial(materialName);

  if (!g4Material) {
    std::cerr << "    Geant4GM::Volume::Volume:" << std::endl; 
    std::cerr << "    Material \"" << materialName << "\" not found." 
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);	      
  }	      
  
  // Create logical volume
  fLogicalVolume = new G4LogicalVolume(g4Solid, g4Material, name);

  // Register logical volume in the map
  Geant4GM::VolumeMap::Instance()->AddVolume(this, fLogicalVolume); 
}

//_____________________________________________________________________________
Geant4GM::Volume::Volume(VGM::ISolid* solid, 
                         G4LogicalVolume* lv)
  : BaseVGM::VVolume(solid),
    fLogicalVolume(lv)
{
  // Register logical volume in the map
  Geant4GM::VolumeMap::Instance()->AddVolume(this, fLogicalVolume); 
}  

//_____________________________________________________________________________
Geant4GM::Volume::~Volume() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string  Geant4GM::Volume::Name() const
{
//
  return fLogicalVolume->GetName();
}  

//_____________________________________________________________________________
std::string  Geant4GM::Volume::MaterialName() const
{
//
  return fLogicalVolume->GetMaterial()->GetName();
}
