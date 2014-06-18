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
/// \class BaseVGM::VTrd
///
/// The ABC for trd solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TRD_H
#define BASE_VGM_V_TRD_H

#include "VGM/solids/ITrd.h"

#include <iostream>

namespace BaseVGM {

  class VTrd : public virtual VGM::ITrd
  {
    public:
      VTrd();
      virtual ~VTrd();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VTrd::Type() const { return VGM::kTrd; }

#endif //BASE_VGM_V_TRD_H
