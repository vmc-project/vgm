// $Id$
//
// Class VBooleanSolid
// --------------------
// The ABC for Boolean solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_BOOLEAN_SOLID_H
#define BASE_VGM_V_BOOLEAN_SOLID_H

#include <iostream>

#include "VGM/solids/IBooleanSolid.h"

namespace BaseVGM {

  std::string BooleanTypeName(VGM::BooleanType typeId);

  class VBooleanSolid : public virtual VGM::IBooleanSolid
  {
    public:
      VBooleanSolid();
      virtual ~VBooleanSolid();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VBooleanSolid::Type() const { return VGM::kBoolean; }

#endif // BASE_VGM_V_BOOLEAN_SOLID_H
