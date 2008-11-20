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
/// \class BaseVGM::VTorus
///
/// The ABC for torus solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TORUS_H
#define BASE_VGM_V_TORUS_H

#include "VGM/solids/ITorus.h"

#include <iostream>

namespace BaseVGM {

  class VTorus : public virtual VGM::ITorus
  {
    public:
      VTorus();
      virtual ~VTorus();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VTorus::Type() const { return VGM::kTorus; }

#endif //BASE_VGM_V_TORUS_H
