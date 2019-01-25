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
/// \class VGM::IHype
///
/// The VGM interface to hyperboloid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_HYPE_H
#define VGM_I_HYPE_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class IHype : public virtual ISolid
  {
    public:
      virtual ~IHype() {}

      // methods

      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      ///
		      /// Return the inner radius in mm
      virtual double InnerRadius() const = 0;
		      ///
		      /// Return the inner stereo angle
      virtual double InnerStereoAngle() const = 0;
		      ///
		      /// Return the outer radius in mm
      virtual double OuterRadius() const = 0;
		      ///
		      /// Return the inner stereo angle
      virtual double OuterStereoAngle() const = 0;
		      ///
		      /// Return the half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::IHype& hype);

#endif //VGM_I_HYPE_H
