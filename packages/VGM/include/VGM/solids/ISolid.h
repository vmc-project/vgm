// $Id$
/// \ingroup VGM_solids
///
/// \class VGM::ISolid
/// 
/// The VGM interface to solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_SOLID_H
#define VGM_I_SOLID_H

#include <string>
#include <iostream>

namespace VGM {

  enum SolidType {
    kBox,
    kCons,
    kEltu,
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
