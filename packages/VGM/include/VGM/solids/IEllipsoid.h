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
/// \class VGM::IEllipsoid
///
/// The VGM interface to ellipsoid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ELLIPSOID_H
#define VGM_I_ELLIPSOID_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IEllipsoid : public virtual ISolid
{
 public:
  virtual ~IEllipsoid() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the semi-axis of the ellipse along x in mm
  virtual double XSemiAxis() const = 0;
  ///
  /// Return the semi-axis of the ellipse along y in mm
  virtual double YSemiAxis() const = 0;
  ///
  /// Return the semi-axis of the ellipse along z in mm
  virtual double ZSemiAxis() const = 0;
  ///
  /// Return the z bottom cut in mm
  virtual double ZBottomCut() const = 0;
  ///
  /// Return the z top cut in mm
  virtual double ZTopCut() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};
} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IEllipsoid& box);

#endif // VGM_I_ELLIPSOID_H
