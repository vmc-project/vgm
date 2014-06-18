// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_volumes
//
/// \class RootGM::VolumeMap
///
/// The map between VGM and Root volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_VOLUME_MAP_H
#define ROOT_GM_VOLUME_MAP_H

#include <map>

class TGeoVolume;

namespace VGM {
  class IVolume;
}

namespace RootGM {

  class VolumeMap;

  class VolumeMap 
  {
    public:
      typedef std::map<VGM::IVolume*, TGeoVolume*>  RootVolumeMap;
      typedef RootVolumeMap::const_iterator         RootVolumeMapCIterator;

      typedef std::map<TGeoVolume*, VGM::IVolume*>  VgmVolumeMap;
      typedef VgmVolumeMap::const_iterator          VgmVolumeMapCIterator;

    public:
      VolumeMap();
      virtual ~VolumeMap();

      // static access methods
      static VolumeMap* Instance(); 

      // methods
      void  AddVolume(VGM::IVolume*, TGeoVolume*); 
      void  Print() const;

      // get methods
      TGeoVolume*   GetVolume(VGM::IVolume* iVolume) const;
      VGM::IVolume* GetVolume(TGeoVolume* rootVolume) const;

    private:
      VolumeMap(const VolumeMap&);

      // static data members
      static VolumeMap*  fgInstance;
  
      // data members
      RootVolumeMap  fRootVolumes;
      VgmVolumeMap   fVgmVolumes;
  };
  
}

#endif //ROOT_GM_VOLUME_MAP_H
