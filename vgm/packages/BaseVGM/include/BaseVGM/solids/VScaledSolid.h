// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2017, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VScaledSolid
///
/// The ABC for Scaled solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_SCALED_SOLID_H
#define BASE_VGM_V_SCALED_SOLID_H

#include "VGM/solids/IScaledSolid.h"

#include <iostream>

namespace BaseVGM {

  class VScaledSolid : public virtual VGM::IScaledSolid
  {
    public:
      VScaledSolid();
      virtual ~VScaledSolid();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VScaledSolid::Type() const { return VGM::kScaled; }

#endif // BASE_VGM_V_SCALED_SOLID_H
