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
/// \class BaseVGM::VArb8
///
/// The ABC for Arb8 solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_ARB8_H
#define BASE_VGM_V_ARB8_H

#include "VGM/solids/IArb8.h"

#include <iostream>

namespace BaseVGM {

  class VArb8 : public virtual VGM::IArb8
  {
    public:
      VArb8();
      virtual ~VArb8();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VArb8::Type() const { return VGM::kArb8; }

#endif //BASE_VGM_V_ARB8_H
