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
// Class SolidMap
// ------------------
// The map between VGM and Geant4 solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/ISolid.h"

#include "Geant4GM/solids/SolidMap.h"

#include "G4VSolid.hh"

Geant4GM::SolidMap* Geant4GM::SolidMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::SolidMap* Geant4GM::SolidMap::Instance()
{
  /// Singleton access function.

  if (!fgInstance) new Geant4GM::SolidMap();

  return fgInstance;
}

//_____________________________________________________________________________
Geant4GM::SolidMap::SolidMap() : fG4Solids(), fVgmSolids()
{
  /// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::SolidMap::SolidMap(const SolidMap&)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::SolidMap::~SolidMap()
{
  //
  fgInstance = 0;
}

//_____________________________________________________________________________
void Geant4GM::SolidMap::AddSolid(VGM::ISolid* iSolid, G4VSolid* g4Solid)
{
  /// Add the specified pair in the map

  fG4Solids[iSolid] = g4Solid;
  fVgmSolids[g4Solid] = iSolid;
}

//_____________________________________________________________________________
G4VSolid* Geant4GM::SolidMap::GetSolid(VGM::ISolid* iSolid) const
{
  /// Find the G4 solid corresponding to a specified VGM solid

  G4SolidMapCIterator i = fG4Solids.find(iSolid);
  if (i != fG4Solids.end())
    return (*i).second;
  else
    return 0;
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::SolidMap::GetSolid(G4VSolid* solid) const
{
  /// Find the VGM solid corresponding to a specified G4 solid

  VgmSolidMapCIterator i = fVgmSolids.find(solid);
  if (i != fVgmSolids.end())
    return (*i).second;
  else
    return 0;
}
