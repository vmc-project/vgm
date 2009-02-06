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
/// \class BaseVGM::VDisplacedSolid
///
/// The ABC for displaced solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_DISPLACED_SOLID_H
#define BASE_VGM_V_DISPLACED_SOLID_H

#include "VGM/solids/IDisplacedSolid.h"

#include <iostream>

namespace BaseVGM {

  class VDisplacedSolid : public virtual VGM::IDisplacedSolid
  {
    public:
      VDisplacedSolid();
      virtual ~VDisplacedSolid();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VDisplacedSolid::Type() const { return VGM::kDisplaced; }

#endif // BASE_VGM_V_BOOLEAN_SOLID_H
