// $Id$
//
// Class SolidMap
// ------------------
// The map between VGM and Geant4 solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/SolidMap.h"

Geant4GM::SolidMap*  Geant4GM::SolidMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::SolidMap* 
Geant4GM::SolidMap::Instance()
{ 
// Singleton access function.
// ---

  if (!fgInstance) new Geant4GM::SolidMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::SolidMap::SolidMap()
  : fG4Solids(),
    fVgmSolids()
{
//  
  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::SolidMap::~SolidMap() 
{
//
  fgInstance = 0;
}    

//_____________________________________________________________________________
void  Geant4GM::SolidMap::AddSolid(VGM::ISolid* iSolid,     
                                   G4VSolid* g4Solid)
{
// Adds the specified pair in the map.
// ---

  fG4Solids[iSolid] = g4Solid;
  fVgmSolids[g4Solid] = iSolid;
}  

//_____________________________________________________________________________
G4VSolid* 
Geant4GM::SolidMap::GetSolid(VGM::ISolid* iSolid) const
{
// Finds the G4 solid corresponding to a specified VGM solid.
// ---

  G4SolidMapCIterator i = fG4Solids.find(iSolid);
  if (i != fG4Solids.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::ISolid* 
Geant4GM::SolidMap::GetSolid(G4VSolid* solid) const
{
// Finds the G4 logical volume corresponding to a specified VGM volume.
// ---

  VgmSolidMapCIterator i = fVgmSolids.find(solid);
  if (i != fVgmSolids.end()) 
    return (*i).second;
  else                 
    return 0;
}
