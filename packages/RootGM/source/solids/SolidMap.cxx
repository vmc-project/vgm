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
// Class SolidMap
// ---------------
// The map between VGM and Root solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/ISolid.h"

#include "RootGM/solids/SolidMap.h"

#include "TGeoShape.h"

RootGM::SolidMap* RootGM::SolidMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::SolidMap* RootGM::SolidMap::Instance()
{
  /// Singleton access function

  if (!fgInstance) new RootGM::SolidMap();

  return fgInstance;
}

//_____________________________________________________________________________
RootGM::SolidMap::SolidMap() : fRootSolids(), fVgmSolids()
{
  /// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::SolidMap::SolidMap(const SolidMap&)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::SolidMap::~SolidMap()
{
  //
  fgInstance = 0;
}

//_____________________________________________________________________________
void RootGM::SolidMap::AddSolid(VGM::ISolid* iSolid, TGeoShape* rootSolid)
{
  /// Adds the specified pair in both maps

  fRootSolids[iSolid] = rootSolid;
  fVgmSolids[rootSolid] = iSolid;
}

//_____________________________________________________________________________
void RootGM::SolidMap::AddSolidInRootMapOnly(
  VGM::ISolid* iSolid, TGeoShape* rootSolid)
{
  /// Adds the specified pair in the Root map only

  fRootSolids[iSolid] = rootSolid;
}

//_____________________________________________________________________________
void RootGM::SolidMap::AddSolidInVGMMapOnly(
  VGM::ISolid* iSolid, TGeoShape* rootSolid)
{
  /// Adds the specified pair in the VGM map only

  fVgmSolids[rootSolid] = iSolid;
}

//_____________________________________________________________________________
TGeoShape* RootGM::SolidMap::GetSolid(VGM::ISolid* iSolid) const
{
  /// Find the Root solid corresponding to a specified VGM solid

  RootSolidMapCIterator i = fRootSolids.find(iSolid);
  if (i != fRootSolids.end())
    return (*i).second;
  else
    return 0;
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::SolidMap::GetSolid(TGeoShape* rootSolid) const
{
  /// Find the VGM solid corresponding to a specified Root solid

  VgmSolidMapCIterator i = fVgmSolids.find(rootSolid);
  if (i != fVgmSolids.end())
    return (*i).second;
  else
    return 0;
}
