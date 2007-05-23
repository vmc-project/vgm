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
/// \class BaseVGM::VCons
///
/// The ABC for cons solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_CONS_H
#define BASE_VGM_V_CONS_H

#include <iostream>

#include "VGM/solids/ICons.h"

namespace BaseVGM {

  class VCons : public virtual VGM::ICons
  {
    public:
      VCons();
      virtual ~VCons();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VCons::Type() const { return VGM::kCons; }

#endif //BASE_VGM_V_CONS_H
