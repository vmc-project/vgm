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
/// \class Geant4GM::VolumeMap
///
/// The map between VGM and Geant4 volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_VOLUME_MAP_H
#define GEANT4_GM_VOLUME_MAP_H

#include <map>
#include <vector>

class G4LogicalVolume;

namespace VGM {
class IVolume;
}

namespace Geant4GM {

class VolumeMap;

class VolumeMap
{
 public:
  typedef std::map<VGM::IVolume*, G4LogicalVolume*> G4VolumeMap;
  typedef std::map<G4LogicalVolume*, VGM::IVolume*> VgmVolumeMap;
  typedef std::map<G4LogicalVolume*, std::vector<G4LogicalVolume*>> G4ParamVolumesMap;

 public:
  VolumeMap();
  virtual ~VolumeMap();

  // static access methods
  static VolumeMap* Instance();

  // methods
  void AddVolume(VGM::IVolume*, G4LogicalVolume*);
  void AddParamVolume(G4LogicalVolume*, const std::vector<G4LogicalVolume*>&);
  void Print() const;

  // get methods
  G4LogicalVolume* GetVolume(VGM::IVolume* iVolume) const;
  VGM::IVolume* GetVolume(G4LogicalVolume* lv) const;
  const std::vector<G4LogicalVolume*>& GetParamVolumes(G4LogicalVolume* lv) const;

 private:
  VolumeMap(const VolumeMap&);

  // static data members
  static VolumeMap* fgInstance;

  // data members
  G4VolumeMap fG4Volumes;
  VgmVolumeMap fVgmVolumes;
  G4ParamVolumesMap fG4ParamVolumes;
  std::vector<G4LogicalVolume*> fDummyVector;
};

} // namespace Geant4GM

#endif // GEANT4_GM_VOLUME_MAP_H
