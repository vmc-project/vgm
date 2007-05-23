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
/// Singleton access function.

  if (!fgInstance) new Geant4GM::PlacementMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::PlacementMap::PlacementMap()
  : fG4Placements(),
    fVgmPlacements()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::PlacementMap::PlacementMap(const PlacementMap&)
{
/// Protected copy constructor
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
/// Add the specified pair in the map

  fG4Placements[iPlacement] = g4Placement;
  fVgmPlacements[g4Placement] = iPlacement;
}  

//_____________________________________________________________________________
G4VPhysicalVolume* 
Geant4GM::PlacementMap::GetPlacement(VGM::IPlacement* iPlacement) const
{
/// Find the G4 physical volume corresponding to a specified VGM placement

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
/// Find the VGM placement corresponding to a specified G4 physical volume

  VgmPlacementMapCIterator i = fVgmPlacements.find(pv);
  if (i != fVgmPlacements.end()) 
    return (*i).second;
  else                 
    return 0;
}
