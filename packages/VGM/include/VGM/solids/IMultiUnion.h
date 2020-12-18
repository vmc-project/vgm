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
/// \class VGM::IMultiUnion
///
/// The VGM interface to Boolean solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MULTI_UNION_H
#define VGM_I_MULTI_UNION_H

#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IMultiUnion : public virtual ISolid
{
 public:
  virtual ~IMultiUnion() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the number of constituent solids
  virtual int NofSolids() const = 0;
  ///
  /// Return the i-th constituent solid
  virtual ISolid* ConstituentSolid(int index) const = 0;
  ///
  /// Return the displacement of the ith constituent solid
  virtual Transform Transformation(int index) const = 0;
  ///
  /// Return true if the solid has to be first
  /// reflected before being placed
  virtual bool ToBeReflected() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IMultiUnion& solid);

#endif // VGM_I_MULTI_UNION_H
