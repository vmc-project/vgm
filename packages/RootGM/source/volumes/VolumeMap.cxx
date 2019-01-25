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
// Class VolumeMap
// ------------------
// The map between VGM and Root volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/volumes/IVolume.h"

#include "RootGM/volumes/VolumeMap.h"

#include "TGeoVolume.h"

RootGM::VolumeMap*  RootGM::VolumeMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::VolumeMap*
RootGM::VolumeMap::Instance()
{
/// Singleton access function

  if (!fgInstance) new RootGM::VolumeMap();

  return fgInstance;
}

//_____________________________________________________________________________
RootGM::VolumeMap::VolumeMap()
  : fRootVolumes(),
    fVgmVolumes()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::VolumeMap::VolumeMap(const VolumeMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::VolumeMap::~VolumeMap()
{
//
  fgInstance = 0;
}

//
// public methods
//

//_____________________________________________________________________________
void  RootGM::VolumeMap::AddVolume(VGM::IVolume* iVolume,
                                   TGeoVolume* rootVolume)
{
/// Add the specified pair in the maps

  fRootVolumes[iVolume] = rootVolume;
  fVgmVolumes[rootVolume] = iVolume;
}

//_____________________________________________________________________________
void  RootGM::VolumeMap::Print() const
{
/// Print all volumes in  the maps

  std::cout << "Root Volumes Map: " << std::endl;

  int counter = 0;
  RootVolumeMapCIterator i;
  for (i = fRootVolumes.begin(); i != fRootVolumes.end(); i++) {
    VGM::IVolume* iVolume = (*i).first;
    TGeoVolume* rootVolume = (*i).second;

    std::cout << "   "
              << counter++ << "th entry:"
	      << "  vgmVolume " << iVolume << " " << iVolume->Name()
              << "  rootVolume " << rootVolume << " " << rootVolume->GetName()
	      << std::endl;
  }
}

//_____________________________________________________________________________
TGeoVolume*
RootGM::VolumeMap::GetVolume(VGM::IVolume* iVolume) const
{
/// Find the Root volume corresponding to a specified VGM volume

  RootVolumeMapCIterator i = fRootVolumes.find(iVolume);
  if (i != fRootVolumes.end())
    return (*i).second;
  else
    return 0;
}

//_____________________________________________________________________________
VGM::IVolume*
RootGM::VolumeMap::GetVolume(TGeoVolume* rootVolume) const
{
/// Finds the VGM volume corresponding to a specified Root volume

  VgmVolumeMapCIterator i = fVgmVolumes.find(rootVolume);
  if (i != fVgmVolumes.end())
    return (*i).second;
  else
    return 0;
}
