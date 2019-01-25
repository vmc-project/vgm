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
/// \class BaseVGM::VPara
///
/// The ABC for para solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_PARA_H
#define BASE_VGM_V_PARA_H

#include "VGM/solids/IPara.h"

#include <iostream>

namespace BaseVGM {

  class VPara : public virtual VGM::IPara
  {
    public:
      VPara();
      virtual ~VPara();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType
BaseVGM::VPara::Type() const { return VGM::kPara; }

#endif //BASE_VGM_V_PARA_H
