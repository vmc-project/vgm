// $Id$
/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VTrap
///
/// The ABC for trap solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TRAP_H
#define BASE_VGM_V_TRAP_H

#include <iostream>

#include "VGM/solids/ITrap.h"

namespace BaseVGM {

  class VTrap : public virtual VGM::ITrap
  {
    public:
      VTrap();
      virtual ~VTrap();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VTrap::Type() const { return VGM::kTrap; }

#endif //BASE_VGM_V_TRAP_H
