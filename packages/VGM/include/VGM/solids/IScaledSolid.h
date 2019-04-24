// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2017, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::IScaledSolid
///
/// The VGM interface to Boolean solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_SCALED_SOLID_H
#define VGM_I_SCALED_SOLID_H

#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IScaledSolid : public virtual ISolid
{
 public:
  virtual ~IScaledSolid() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the constituent solid
  virtual ISolid* ConstituentSolid() const = 0;
  ///
  /// Return the 3D scale
  virtual Transform Scale() const = 0;

  /// Return true if the solid has to be first
  /// reflected before being placed
  virtual bool ToBeReflected() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IScaledSolid& solid);

#endif // VGM_I_BOOLEAN_SOLID_H
