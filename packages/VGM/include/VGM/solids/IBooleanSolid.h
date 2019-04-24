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
/// \class VGM::IBooleanSolid
///
/// The VGM interface to Boolean solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_BOOLEAN_SOLID_H
#define VGM_I_BOOLEAN_SOLID_H

#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

enum BooleanType
{
  kIntersection,
  kSubtraction,
  kUnion,
  kUnknownBoolean
};

std::string BooleanTypeName(BooleanType typeId);

class IBooleanSolid : public virtual ISolid
{
 public:
  virtual ~IBooleanSolid() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the Boolean type of this solid
  virtual BooleanType BoolType() const = 0;
  ///
  /// Return the first constituent solid
  virtual ISolid* ConstituentSolidA() const = 0;
  ///
  /// Return the second constituent solid
  virtual ISolid* ConstituentSolidB() const = 0;
  ///
  /// Return the 3D displacement of the second
  /// constituent solid with respect to the first one
  virtual Transform Displacement() const = 0;
  ///
  /// Return true if the solid has to be first
  /// reflected before being placed
  virtual bool ToBeReflected() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IBooleanSolid& solid);

#endif // VGM_I_BOOLEAN_SOLID_H
