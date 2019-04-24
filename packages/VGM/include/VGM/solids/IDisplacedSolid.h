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
/// \class VGM::IDisplacedSolid
///
/// The VGM interface to displaced solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_DISPLACED_SOLID_H
#define VGM_I_DISPLACED_SOLID_H

#include "VGM/common/Transform.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

class IDisplacedSolid : public virtual ISolid
{
 public:
  virtual ~IDisplacedSolid() {}

  // methods

  virtual SolidType Type() const = 0;
  virtual std::string Name() const = 0;

  ///
  /// Return the constituent solid
  virtual ISolid* ConstituentSolid() const = 0;
  ///
  /// Return the 3D displacement of
  /// the constituent solid
  virtual Transform Displacement() const = 0;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const = 0;
};

} // namespace VGM

std::ostream& operator<<(std::ostream& out, const VGM::IDisplacedSolid& solid);

#endif // VGM_I_BOOLEAN_SOLID_H
