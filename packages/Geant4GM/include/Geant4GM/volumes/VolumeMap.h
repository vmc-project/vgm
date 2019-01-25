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

class G4LogicalVolume;

namespace VGM {
  class IVolume;
}

namespace Geant4GM {

  class VolumeMap;

  class VolumeMap
  {
    public:
      typedef std::map<VGM::IVolume*, G4LogicalVolume*>  G4VolumeMap;
      typedef G4VolumeMap::const_iterator                G4VolumeMapCIterator;

      typedef std::map<G4LogicalVolume*, VGM::IVolume*>  VgmVolumeMap;
      typedef VgmVolumeMap::const_iterator               VgmVolumeMapCIterator;

    public:
      VolumeMap();
      virtual ~VolumeMap();

      // static access methods
      static VolumeMap* Instance();

      // methods
      void  AddVolume(VGM::IVolume*, G4LogicalVolume*);
      void  Print() const;

      // get methods
      G4LogicalVolume* GetVolume(VGM::IVolume* iVolume) const;
      VGM::IVolume*    GetVolume(G4LogicalVolume* lv) const;

    private:
      VolumeMap(const VolumeMap&);

      // static data members
      static VolumeMap*  fgInstance;

      // data members
      G4VolumeMap   fG4Volumes;
      VgmVolumeMap  fVgmVolumes;
  };

}

#endif //GEANT4_GM_VOLUME_MAP_H
