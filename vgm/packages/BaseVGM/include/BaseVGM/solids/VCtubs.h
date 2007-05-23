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
///
/// \class BaseVGM::VCtubs
///
/// The ABC for cut tubs solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_CTUBS_H
#define BASE_VGM_V_CTUBS_H

#include <iostream>

#include "VGM/solids/ICtubs.h"

namespace BaseVGM {
 
  class VCtubs : public virtual VGM::ICtubs
  {
    public:
      VCtubs();
      virtual ~VCtubs();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VCtubs::Type() const { return VGM::kCtubs; }

#endif //BASE_VGM_V_CTUBS_H
