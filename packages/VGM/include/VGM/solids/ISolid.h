// $Id$
//
// Class ISolid
// ---------------
// The VGM interface to solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_SOLID_H
#define VGM_I_SOLID_H

#include <string>
#include <iostream>

namespace VGM {

  enum SolidType {
    kBox,
    kCons,
    kPara,
    kPolycone,
    kPolyhedra,
    kSphere,
    kTorus,
    kTrap,
    kTrd,
    kTubs,
    kBoolean,
    kUnknownSolid
  };
  
  std::string SolidTypeName(VGM::SolidType typeId);

  class ISolid
  {
    public:
      virtual ~ISolid() {}
    
      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;
    
      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::ISolid& solid);

#endif //VGM_I_SOLID_H
