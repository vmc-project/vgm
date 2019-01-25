// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::IParaboloid
///
/// The VGM interface to paraboloid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_PARABOLOID_H
#define VGM_I_PARABOLOID_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class IParaboloid : public virtual ISolid
  {
    public:
      virtual ~IParaboloid() {}

      // methods

      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      ///
		      /// Return the radius at -z in mm
      virtual double RadiusMinusZ() const = 0;
		      ///
		      /// Return the radius at +z in mm
      virtual double RadiusPlusZ() const = 0;
		      ///
		      /// Return the half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::IParaboloid& paraboloid);

#endif //VGM_I_PARABOLOID_H
