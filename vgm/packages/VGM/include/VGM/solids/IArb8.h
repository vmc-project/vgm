// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::IArb8
/// 
/// The VGM interface to Arb8 solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ARB8_H
#define VGM_I_ARB8_H

#include "VGM/common/TwoVector.h"
#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class IArb8 : public virtual ISolid
  {
    public:
      virtual ~IArb8() {}

      // methods

      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		           /// 
		           /// Return the number of vertices 
      virtual int        NofVertices() const = 0;
		           /// 
		           /// Return the index-th vertex 
      virtual TwoVector  Vertex(int index) const = 0;
		           ///
		           /// Return the half-length along the z axis in mm
      virtual double     ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IArb8& xtru);

#endif //VGM_I_ARB8_H
