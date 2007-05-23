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
/// \class BaseVGM::VSphere
///
/// The ABC for sphere solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_SPHERE_H
#define BASE_VGM_V_SPHERE_H

#include <iostream>

#include "VGM/solids/ISphere.h"

namespace BaseVGM {

  class VSphere : public virtual VGM::ISphere
  {
    public:
      VSphere();
      virtual ~VSphere();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VSphere::Type() const { return VGM::kSphere; }

#endif //BASE_VGM_V_SPHERE_H
