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
// Class Volume
// ---------------
// VGM implementation for Root volume.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/IDisplacedSolid.h"

#include "RootGM/solids/SolidMap.h"
#include "RootGM/volumes/Volume.h"
#include "RootGM/volumes/VolumeMap.h"

#include "TGeoManager.h"
#include "TGeoMedium.h"
#include "TGeoShape.h"

#include <iostream>

//_____________________________________________________________________________
RootGM::Volume::Volume(
  const std::string& name, VGM::ISolid* solid, const std::string& mediumName)
  : VGM::IVolume(), BaseVGM::VVolume(solid), fGeoVolume(0)
{
  /// Standard constructor to define a volume via parameters
  /// \param solid the associated solid
  /// \param mediumName the name of the associated medium

  // Get solid from the solid map
  // If displaced solid, get its constituent solid
  VGM::ISolid* constSolid = solid;
  while (constSolid->Type() == VGM::kDisplaced) {
    VGM::IDisplacedSolid* displacedSolid =
      dynamic_cast<VGM::IDisplacedSolid*>(constSolid);
    constSolid = displacedSolid->ConstituentSolid();
  }

  TGeoShape* geoSolid = RootGM::SolidMap::Instance()->GetSolid(constSolid);
  // Get medium from Root
  TGeoMedium* geoMedium = gGeoManager->GetMedium(mediumName.data());

  if (!geoMedium) {
    std::cerr << "+++ Warning  +++" << std::endl;
    std::cerr << "    RootGM::Volume::Volume:" << std::endl;
    std::cerr << "    Medium \"" << mediumName << "\" not found." << std::endl;
  }

  // Create logical volume
  fGeoVolume = new TGeoVolume(name.data(), geoSolid, geoMedium);

  // Register logical volume in the map
  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume);
}

//_____________________________________________________________________________
RootGM::Volume::Volume(VGM::ISolid* solid, TGeoVolume* volume)
  : VGM::IVolume(), BaseVGM::VVolume(solid), fGeoVolume(volume)
{
  /// Standard constructor to define a volume via Root object

  // Register logical volume in the map
  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume);
}

//_____________________________________________________________________________
RootGM::Volume::Volume() : VGM::IVolume(), BaseVGM::VVolume()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Volume::Volume(const Volume& rhs)
  : VGM::IVolume(rhs), BaseVGM::VVolume(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Volume::~Volume()
{
  //
}

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Volume::Name() const
{
  //
  return std::string(fGeoVolume->GetName());
}

//_____________________________________________________________________________
std::string RootGM::Volume::MaterialName() const
{
  //
  // Root volumes may not have medium
  //
  if (!fGeoVolume->GetMedium() ||
      (fGeoVolume->GetMedium() && !fGeoVolume->GetMedium()->GetMaterial()))
    return "None";

  return std::string(fGeoVolume->GetMedium()->GetMaterial()->GetName());
}

//_____________________________________________________________________________
std::string RootGM::Volume::MediumName() const
{
  //
  // Root volumes may not have medium
  //
  if (!fGeoVolume->GetMedium()) return "None";

  return std::string(fGeoVolume->GetMedium()->GetName());
}

//_____________________________________________________________________________
void RootGM::Volume::ResetVolume(TGeoVolume* volume)
{
  /// Reset the associated Root volume to the specified one

  TGeoVolume* oldVolume = fGeoVolume;

  fGeoVolume = volume;
  if (oldVolume) fGeoVolume->SetMedium(oldVolume->GetMedium());

  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume);
  // Check solid for this case
}
