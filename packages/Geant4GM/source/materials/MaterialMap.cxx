// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class MaterialMap
// ------------------
// The map between VGM and G4 materials.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"

#include "Geant4GM/materials/MaterialMap.h"

Geant4GM::MaterialMap*  Geant4GM::MaterialMap::fgInstance = 0;

#include "G4Material.hh"

//_____________________________________________________________________________
Geant4GM::MaterialMap* 
Geant4GM::MaterialMap::Instance()
{ 
/// Singleton access function.

  if (!fgInstance) new MaterialMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::MaterialMap::MaterialMap()
  : fG4Materials(),
    fVgmMaterials()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::MaterialMap::MaterialMap(const MaterialMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::MaterialMap::~MaterialMap() 
{
//
  fgInstance = 0;
}    

//
// public methods
//

//_____________________________________________________________________________
void  Geant4GM::MaterialMap::AddMaterial(VGM::IMaterial* iMaterial, 
                                         G4Material* g4Material)
{
/// Adds the specified pair in the maps.

  fG4Materials[iMaterial] = g4Material;
  fVgmMaterials[g4Material] = iMaterial;
}  

//_____________________________________________________________________________
void  Geant4GM::MaterialMap::Print() const
{
/// Print all materials in  the maps.

  std::cout << "G4 Materials Map: " << std::endl; 

  int counter = 0;
  G4MaterialMapCIterator i;
  for (i = fG4Materials.begin(); i != fG4Materials.end(); i++) {
    VGM::IMaterial* iMaterial = (*i).first;
    G4Material* g4Material = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmMaterial " << iMaterial << " " << iMaterial->Name()
              << "  g4Material " << g4Material << " " << g4Material->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
G4Material* 
Geant4GM::MaterialMap::GetMaterial(VGM::IMaterial* iMaterial) const
{
/// Find the G4 material corresponding to a specified VGM material.

  G4MaterialMapCIterator i = fG4Materials.find(iMaterial);
  if (i != fG4Materials.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialMap::GetMaterial(G4Material* g4Material) const
{
/// Find the VGM material corresponding to a specified G4 material.

  VgmMaterialMapCIterator i = fVgmMaterials.find(g4Material);
  if (i != fVgmMaterials.end()) 
    return (*i).second;
  else                 
    return 0;
}
