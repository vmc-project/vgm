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
/// \class BaseVGM::VBox
///
/// The ABC for box solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_BOX_H
#define BASE_VGM_V_BOX_H

#include <iostream>

#include "VGM/solids/IBox.h"

namespace BaseVGM {

  class VBox : public virtual VGM::IBox
  {
    public:
      VBox();
      virtual ~VBox();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VBox::Type() const { return VGM::kBox; }

#endif //BASE_VGM_V_BOX_H
