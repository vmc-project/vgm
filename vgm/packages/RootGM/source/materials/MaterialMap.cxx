// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class MaterialMap
// ------------------
// The map between VGM and Root materials.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/MaterialMap.h"

RootGM::MaterialMap*  RootGM::MaterialMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::MaterialMap* RootGM::MaterialMap::Instance()
{ 
/// Singleton access function

  if (!fgInstance) new RootGM::MaterialMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
RootGM::MaterialMap::MaterialMap()
  : fRootMaterials(),
    fVgmMaterials()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::MaterialMap::MaterialMap(const MaterialMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::MaterialMap::~MaterialMap() 
{
//
  fgInstance = 0;
}    

//
// public methods
//

//_____________________________________________________________________________
void  RootGM::MaterialMap::AddMaterial(VGM::IMaterial* iMaterial, 
                                       TGeoMaterial* rootMaterial)
{
/// Add the specified pair in the maps

  fRootMaterials[iMaterial] = rootMaterial;
  fVgmMaterials[rootMaterial] = iMaterial;
}  

//_____________________________________________________________________________
void  RootGM::MaterialMap::Print() const
{
/// Prints all materials in the maps

  std::cout << "Root Materials Map: " << std::endl; 

  int counter = 0;
  RootMaterialMapCIterator i;
  for (i = fRootMaterials.begin(); i != fRootMaterials.end(); i++) {
    VGM::IMaterial* iMaterial = (*i).first;
    TGeoMaterial* rootMaterial = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmMaterial " << iMaterial << " " << iMaterial->Name()
              << "  rootMaterial " << rootMaterial << " " << rootMaterial->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
TGeoMaterial* 
RootGM::MaterialMap::GetMaterial(VGM::IMaterial* iMaterial) const
{
/// Find the Root material corresponding to a specified VGM material

  RootMaterialMapCIterator i = fRootMaterials.find(iMaterial);
  if (i != fRootMaterials.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IMaterial* 
RootGM::MaterialMap::GetMaterial(TGeoMaterial* rootMaterial) const
{
/// Finds the VGM material corresponding to a specified Root material

  VgmMaterialMapCIterator i = fVgmMaterials.find(rootMaterial);
  if (i != fVgmMaterials.end()) 
    return (*i).second;
  else                 
    return 0;
}
