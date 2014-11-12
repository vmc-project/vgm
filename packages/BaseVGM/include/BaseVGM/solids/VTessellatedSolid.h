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
/// \class BaseVGM::VTessellatedSolid
///
/// The ABC for tessellated solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TESSELLATED_SOLID_H
#define BASE_VGM_V_TESSELLATED_SOLID_H

#include "VGM/solids/ITessellatedSolid.h"

#include <iostream>

namespace BaseVGM {

  class VTessellatedSolid : public virtual VGM::ITessellatedSolid
  {
    public:
      VTessellatedSolid();
      virtual ~VTessellatedSolid();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VTessellatedSolid::Type() const { return VGM::kTessellated; }

#endif //BASE_VGM_V_TESSELLATED_SOLID_H
