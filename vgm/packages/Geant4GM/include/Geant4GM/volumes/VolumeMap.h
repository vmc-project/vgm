// $Id$
//
// Class VolumeMap
// ------------------
// The map between VGM and Geant4 volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_VOLUME_MAP_H
#define GEANT4_GM_VOLUME_MAP_H

#include <map>

#include "G4LogicalVolume.hh"

#include "VGM/volumes/IVolume.h"

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
      VolumeMap(const VolumeMap&) {}

      // static data members
      static VolumeMap*  fgInstance;
  
      // data members
      G4VolumeMap   fG4Volumes;
      VgmVolumeMap  fVgmVolumes;
  };

}

#endif //GEANT4_GM_VOLUME_MAP_H
