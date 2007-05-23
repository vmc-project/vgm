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
// Class PlacementMap
// ---------------------
// The map between VGM and Root placements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/volumes/PlacementMap.h"

RootGM::PlacementMap*  RootGM::PlacementMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::PlacementMap* 
RootGM::PlacementMap::Instance()
{ 
/// Singleton access function.

  if (!fgInstance) new RootGM::PlacementMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
RootGM::PlacementMap::PlacementMap()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::PlacementMap::PlacementMap(const PlacementMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::PlacementMap::~PlacementMap() 
{
//
  fgInstance = 0;
}  

//
// public methods
//  

//_____________________________________________________________________________
void  RootGM::PlacementMap::AddPlacement(VGM::IPlacement* iPlacement, 
                                         TGeoNode* rtPlacement)
{
/// Add the specified pair in the map

  fPlacements[iPlacement] = rtPlacement;
}  

//_____________________________________________________________________________
TGeoNode* 
RootGM::PlacementMap::GetPlacement(VGM::IPlacement* iPlacement) const
{
/// Find the Root node corresponding to a specified VGM placement.

  RootPlacementMapCIterator i = fPlacements.find(iPlacement);
  if (i != fPlacements.end()) 
    return (*i).second;
  else                 
    return 0;
}
