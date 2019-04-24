// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_volumes
//
/// \class Geant4GM::Volume
///
/// VGM implementation for Geant4 volume.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_VOLUME_H
#define GEANT4_GM_VOLUME_H

#include "BaseVGM/volumes/VVolume.h"

#include <string>

class G4LogicalVolume;

namespace VGM {
class ISolid;
}

namespace Geant4GM {

class Volume : public BaseVGM::VVolume
{
 public:
  Volume(const std::string& name, VGM::ISolid* solid,
    const std::string& materialName, const std::string& mediumName);
  Volume(
    VGM::ISolid* solid, G4LogicalVolume* lv, const std::string& mediumName);
  virtual ~Volume();

  // methods
  virtual std::string Name() const;
  virtual std::string MaterialName() const;
  virtual std::string MediumName() const;

  virtual void ResetSolid(VGM::ISolid* solid);

 protected:
  Volume();
  Volume(const Volume& rhs);

 private:
  G4LogicalVolume* fLogicalVolume;
  std::string fMediumName;
};

} // namespace Geant4GM

#endif // GEANT4_GM_VOLUME_H
