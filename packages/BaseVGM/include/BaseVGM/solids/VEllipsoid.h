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
/// \class BaseVGM::VEllipsoid
///
/// The ABC for ellipsoid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_ELLIPSOID_H
#define BASE_VGM_V_ELLIPSOID_H

#include "VGM/solids/IEllipsoid.h"

#include <iostream>

namespace BaseVGM {

class VEllipsoid : public virtual VGM::IEllipsoid
{
 public:
  VEllipsoid();
  virtual ~VEllipsoid();

  // methods
  virtual VGM::SolidType Type() const;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const;
};

} // namespace BaseVGM

// inline functions

inline VGM::SolidType BaseVGM::VEllipsoid::Type() const
{
  return VGM::kEllipsoid;
}

#endif // BASE_VGM_V_ELLIPSOID_H
