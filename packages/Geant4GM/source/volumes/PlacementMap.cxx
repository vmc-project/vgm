// $Id$
//
// Class PlacementMap
// ---------------------
// The map between VGM and Geant4 placements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/volumes/PlacementMap.h"

Geant4GM::PlacementMap*  Geant4GM::PlacementMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::PlacementMap* 
Geant4GM::PlacementMap::Instance()
{ 
// Singleton access function.
// ---

  if (!fgInstance) new Geant4GM::PlacementMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::PlacementMap::PlacementMap()
  : fG4Placements(),
    fVgmPlacements()
{
//  
  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::PlacementMap::~PlacementMap() 
{
//
  fgInstance = 0;
}    

//_____________________________________________________________________________
void  Geant4GM::PlacementMap::AddPlacement(VGM::IPlacement* iPlacement, 
                                           G4VPhysicalVolume* g4Placement)
{
// Adds the specified pair in the map.
// ---

  fG4Placements[iPlacement] = g4Placement;
  fVgmPlacements[g4Placement] = iPlacement;
}  

//_____________________________________________________________________________
G4VPhysicalVolume* 
Geant4GM::PlacementMap::GetPlacement(VGM::IPlacement* iPlacement) const
{
// Finds the G4 physical volume corresponding to a specified VGM placement.
// ---

  G4PlacementMapCIterator i = fG4Placements.find(iPlacement);
  if (i != fG4Placements.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IPlacement* 
Geant4GM::PlacementMap::GetPlacement(G4VPhysicalVolume* pv) const
{
// Finds the G4 physical volume corresponding to a specified VGM placement.
// ---

  VgmPlacementMapCIterator i = fVgmPlacements.find(pv);
  if (i != fVgmPlacements.end()) 
    return (*i).second;
  else                 
    return 0;
}
