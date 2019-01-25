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
/// \class RootGM::Volume
///
/// VGM implementation for Root volume.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_VOLUME_H
#define ROOT_GM_VOLUME_H

#include "BaseVGM/volumes/VVolume.h"

#include <string>

class TGeoVolume;

namespace VGM {
  class ISolid;
}

namespace RootGM {

  class Volume : public BaseVGM::VVolume
  {
    public:
      Volume(const std::string& name,
             VGM::ISolid* solid,
             const std::string& mediumName );
      Volume(VGM::ISolid* solid,
             TGeoVolume* volume);
      virtual ~Volume();

      // methods
      virtual std::string  Name() const;
      virtual std::string  MaterialName() const;
      virtual std::string  MediumName() const;

      void ResetVolume(TGeoVolume* rootVolume);

    protected:
      Volume();
      Volume(const Volume& rhs);

    private:
      TGeoVolume* fGeoVolume;
  };

}

#endif //ROOT_GM_VOLUME_H
