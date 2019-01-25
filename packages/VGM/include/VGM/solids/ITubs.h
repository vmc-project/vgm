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
/// \class VGM::ITubs
///
/// The VGM interface to tubs solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TUBS_H
#define VGM_I_TUBS_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class ITubs : public virtual ISolid
  {
    public:
      virtual ~ITubs() {}

      // methods

      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      ///
		      /// Return the inside radius in mm
      virtual double InnerRadius() const = 0;
		      ///
		      /// Return the outside radius in mm
      virtual double OuterRadius() const = 0;
		      ///
		      /// Return the half-length along the z axis in m
      virtual double ZHalfLength() const = 0;
		      ///
		      /// Return the starting angle of the segment in deg
      virtual double StartPhi() const = 0;
		      ///
		      /// Return the opening angle of the segment in deg
      virtual double DeltaPhi() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::ITubs& tubs);

#endif //VGM_I_TUBS_H
