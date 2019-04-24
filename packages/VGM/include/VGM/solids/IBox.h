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
/// \class VGM::IBox
///
/// The VGM interface to box solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_BOX_H
#define VGM_I_BOX_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IBox : public virtual ISolid
{
 public:
  virtual ~IBox() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the half-length along the x axis in mm
  virtual double XHalfLength() const = 0;
  ///
  /// Return the half-length along the y axis in mm
  virtual double YHalfLength() const = 0;
  ///
  /// Return the half-length along the z axis in mm
  virtual double ZHalfLength() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};
} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IBox& box);

#endif // VGM_I_BOX_H
