// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_volumes
//
/// \class BaseVGM::VVolume
///
/// The abstract base class for volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_VOLUME_H
#define BASE_VGM_V_VOLUME_H

#include "VGM/volumes/IVolume.h"

#include <string>
#include <vector>

namespace VGM {
  class ISolid;
  class IPlacement;
}

namespace BaseVGM {

  class VVolume : public virtual VGM::IVolume
  {
    public:
      VVolume(VGM::ISolid* solid);
      virtual ~VVolume();

      // methods
      virtual std::string   Name() const = 0;
      virtual std::string   MaterialName() const = 0;
      virtual std::string   MediumName() const = 0;

      virtual VGM::ISolid*      Solid() const;
      virtual int               NofDaughters() const;
      virtual VGM::IPlacement*  Daughter(int i) const;

      virtual void  AddDaughter(VGM::IPlacement* daughter);

      virtual void  ResetSolid(VGM::ISolid* solid);

    protected:
      VVolume();
      VVolume(const VVolume& rhs);

    private:
      VGM::ISolid*  fSolid;
      std::vector<VGM::IPlacement*>  fDaughters;
  };

}

#endif //BASE_VGM_V_VOLUME_H
