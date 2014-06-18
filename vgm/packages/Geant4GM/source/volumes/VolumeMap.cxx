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
// Class VolumeMap
// ------------------
// The map between VGM and Geant4 volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/volumes/IVolume.h"

#include "Geant4GM/volumes/VolumeMap.h"

#include "G4LogicalVolume.hh"

Geant4GM::VolumeMap*  Geant4GM::VolumeMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::VolumeMap* 
Geant4GM::VolumeMap::Instance()
{ 
/// Singleton access function

  if (!fgInstance) new Geant4GM::VolumeMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::VolumeMap::VolumeMap()
  : fG4Volumes(),
    fVgmVolumes()
{
/// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::VolumeMap::VolumeMap(const VolumeMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::VolumeMap::~VolumeMap() 
{
//

  fgInstance = 0;
}    

//_____________________________________________________________________________
void  Geant4GM::VolumeMap::AddVolume(VGM::IVolume* iVolume, 
                                     G4LogicalVolume* g4Volume)
{
/// Add the specified pair in the map

  fG4Volumes[iVolume] = g4Volume;
  fVgmVolumes[g4Volume] = iVolume;
}  

//_____________________________________________________________________________
void  Geant4GM::VolumeMap::Print() const
{
/// Print all volumes in  the map

  std::cout << "Geant4 Volumes Map: " << std::endl; 

  int counter = 0;
  G4VolumeMapCIterator i;
  for (i = fG4Volumes.begin(); i != fG4Volumes.end(); i++) {
    VGM::IVolume* iVolume = (*i).first;
    G4LogicalVolume* lv = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmVolume " << iVolume << " " << iVolume->Name()
              << "  LV " << lv << " " << lv->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
G4LogicalVolume* 
Geant4GM::VolumeMap::GetVolume(VGM::IVolume* iVolume) const
{
/// Find the G4 logical volume corresponding to a specified VGM volume

  G4VolumeMapCIterator i = fG4Volumes.find(iVolume);
  if (i != fG4Volumes.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IVolume* 
Geant4GM::VolumeMap::GetVolume(G4LogicalVolume* lv) const
{
/// Find the VGM volume corresponding to a specified  G4 logical volume

  VgmVolumeMapCIterator i = fVgmVolumes.find(lv);
  if (i != fVgmVolumes.end()) 
    return (*i).second;
  else                 
    return 0;
}
