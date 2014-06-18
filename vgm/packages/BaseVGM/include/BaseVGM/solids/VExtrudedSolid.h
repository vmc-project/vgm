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
/// \class BaseVGM::VExtrudedSolid
///
/// The ABC for xtru solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_EXTRUDED_SOLID_H
#define BASE_VGM_V_EXTRUDED_SOLID_H

#include "VGM/solids/IExtrudedSolid.h"

#include <iostream>

namespace BaseVGM {

  class VExtrudedSolid : public virtual VGM::IExtrudedSolid
  {
    public:
      VExtrudedSolid();
      virtual ~VExtrudedSolid();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VExtrudedSolid::Type() const { return VGM::kExtruded; }

#endif //BASE_VGM_V_EXTRUDED_SOLID_H
