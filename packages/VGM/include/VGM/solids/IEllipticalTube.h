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
/// \class VGM::IEllipticalTube
///
/// The VGM interface to elliptical tube solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ELLIPTICAL_TUBE_H
#define VGM_I_ELLIPTICAL_TUBE_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IEllipticalTube : public virtual ISolid
{
 public:
  virtual ~IEllipticalTube() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the semi-axis of the ellipse along x in mm
  virtual double Dx() const = 0;
  ///
  /// Return the semi-axis of the ellipse along y in mm
  virtual double Dy() const = 0;
  ///
  /// Return the half-length along the z axis in mm
  virtual double ZHalfLength() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IEllipticalTube& eltu);

#endif // VGM_I_ELLIPTICAL_TUBE_H
