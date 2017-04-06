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
/// \class VGM::ISolid
/// 
/// The VGM interface to solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_SOLID_H
#define VGM_I_SOLID_H

#include <string>
#include <iostream>

namespace VGM {

  enum SolidType {
    kArb8,
    kBox,
    kCons,
    kCtubs,
    kEllipsoid,
    kEltu,
    kExtruded,
    kHype,
    kPara,
    kParaboloid,
    kPolycone,
    kPolyhedra,
    kSphere,
    kTessellated,
    kTorus,
    kTrap,
    kTrd,
    kTubs,
    kBoolean,
    kDisplaced,
    kScaled,
    kUnknownSolid
  };
  
  std::string SolidTypeName(VGM::SolidType typeId);

  class ISolid
  {
    public:
      virtual ~ISolid() {}
    
      // methods
			     /// 
                             /// Return the type of this solid
      virtual SolidType     Type() const = 0;
			     /// 
                             /// Return the name of this solid
      virtual std::string   Name() const = 0;
    
      // streaming
                            /// Put the printing of the solid parameters
			    /// in the out stream
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::ISolid& solid);

#endif //VGM_I_SOLID_H
