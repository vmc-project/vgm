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
/// \class BaseVGM::VPolycone
///
/// The ABC for polycone solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_POLYCONE_H
#define BASE_VGM_V_POLYCONE_H

#include "VGM/solids/IPolycone.h"

#include <iostream>

namespace BaseVGM {

class VPolycone : public virtual VGM::IPolycone
{
 public:
  VPolycone();
  virtual ~VPolycone();

  // methods
  virtual VGM::SolidType Type() const;

  // streaming
  virtual std::ostream& Put(std::ostream& out) const;
};

} // namespace BaseVGM

// inline functions

inline VGM::SolidType BaseVGM::VPolycone::Type() const
{
  return VGM::kPolycone;
}

#endif // BASE_VGM_V_POLYCONE_H
