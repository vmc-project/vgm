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
/// \class BaseVGM::VEllipticalTube
///
/// The ABC for elliptical tube solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_ELLIPTICAL_TUBE_H
#define BASE_VGM_V_ELLIPTICAL_TUBE_H

#include "VGM/solids/IEllipticalTube.h"

#include <iostream>

namespace BaseVGM {
 
  class VEllipticalTube : public virtual VGM::IEllipticalTube
  {
    public:
      VEllipticalTube();
      virtual ~VEllipticalTube();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VEllipticalTube::Type() const { return VGM::kEltu; }

#endif //BASE_VGM_V_ELLIPTICAL_TUBE_H
