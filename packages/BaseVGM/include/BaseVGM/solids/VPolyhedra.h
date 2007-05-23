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
/// \class BaseVGM::VPolyhedra
///
/// The ABC for polyhedra solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_POLYHEDRA_H
#define BASE_VGM_V_POLYHEDRA_H

#include <iostream>

#include "VGM/solids/IPolyhedra.h"

namespace BaseVGM {

  class VPolyhedra : public virtual VGM::IPolyhedra
  {
    public:
      VPolyhedra();
      virtual ~VPolyhedra();

      // methods
      virtual VGM::SolidType Type() const;

      double ConvertRadiusFactor() const;
             // converts radius of the sides to radius of the corners:
	     // r_corners = r_sides/factor

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VPolyhedra::Type() const { return VGM::kPolyhedra; }

#endif //BASE_VGM_V_POLYHEDRA_H
