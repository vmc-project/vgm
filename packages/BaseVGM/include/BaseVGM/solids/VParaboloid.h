// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VParaboloid
///
/// The ABC for paraboloid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_PARABOLOID_H
#define BASE_VGM_V_PARABOLOID_H

#include "VGM/solids/IParaboloid.h"

#include <iostream>

namespace BaseVGM {

class VParaboloid : public virtual VGM::IParaboloid
{
 public:
  VParaboloid();
  virtual ~VParaboloid();

  // methods
  virtual VGM::SolidType Type() const;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const;
};

} // namespace BaseVGM

// inline functions

inline VGM::SolidType BaseVGM::VParaboloid::Type() const
{
  return VGM::kParaboloid;
}

#endif // BASE_VGM_V_PARABOLOID_H
