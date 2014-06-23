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
/// \class BaseVGM::VTubs
///
/// The ABC for tubs solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TUBS_H
#define BASE_VGM_V_TUBS_H

#include "VGM/solids/ITubs.h"

#include <iostream>

namespace BaseVGM {
 
  class VTubs : public virtual VGM::ITubs
  {
    public:
      VTubs();
      virtual ~VTubs();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VTubs::Type() const { return VGM::kTubs; }

#endif //BASE_VGM_V_TUBS_H
