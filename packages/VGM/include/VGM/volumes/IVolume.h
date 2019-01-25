// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_volumes
//
/// \class VGM::IVolume
///
/// The VGM interface to volumes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_VOLUME_H
#define VGM_I_VOLUME_H

#include <string>
#include <iostream>

namespace VGM {

  class ISolid;
  class IPlacement;

  class IVolume
  {
    public:
      virtual ~IVolume() {}

      // methods
      			    ///
                            /// Return the name of this volume
      virtual std::string  Name() const = 0;
			    ///
                            /// Return the name of the associated material
      virtual std::string  MaterialName() const = 0;
			    ///
                            /// Return the name of the associated medium
      virtual std::string  MediumName() const = 0;

			    ///
                            /// Return the associated solid
      virtual ISolid*      Solid() const = 0;
			    ///
			    /// Return the number of volume daughters
      virtual int          NofDaughters() const = 0;
			    ///
                            /// Return the i-th daughter
      virtual IPlacement*  Daughter(int i) const = 0;
			    ///
                            /// Add the specified daughter
      virtual void  AddDaughter(VGM::IPlacement* daughter) = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::IVolume& volume);

#endif //VGM_I_VOLUME_H
