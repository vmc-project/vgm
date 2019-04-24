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
/// \class BaseVGM::VBooleanSolid
///
/// The ABC for Boolean solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_BOOLEAN_SOLID_H
#define BASE_VGM_V_BOOLEAN_SOLID_H

#include "VGM/solids/IBooleanSolid.h"

#include <iostream>

namespace BaseVGM {

std::string BooleanTypeName(VGM::BooleanType typeId);

class VBooleanSolid : public virtual VGM::IBooleanSolid
{
 public:
  VBooleanSolid();
  virtual ~VBooleanSolid();

  // methods
  virtual VGM::SolidType Type() const;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const;
};

} // namespace BaseVGM

// inline functions

inline VGM::SolidType BaseVGM::VBooleanSolid::Type() const
{
  return VGM::kBoolean;
}

#endif // BASE_VGM_V_BOOLEAN_SOLID_H
