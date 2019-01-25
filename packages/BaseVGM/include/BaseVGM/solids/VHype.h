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
/// \class BaseVGM::VHype
///
/// The ABC for hyperboloid solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_HYPE_H
#define BASE_VGM_V_HYPE_H

#include "VGM/solids/IHype.h"

#include <iostream>

namespace BaseVGM {

  class VHype : public virtual VGM::IHype
  {
    public:
      VHype();
      virtual ~VHype();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType
BaseVGM::VHype::Type() const { return VGM::kHype; }

#endif //BASE_VGM_V_HYPE_H
