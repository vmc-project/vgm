// $Id$
//
// Class VTorus
// ---------------
// The ABC for torus solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TORUS_H
#define BASE_VGM_V_TORUS_H

#include <iostream>

#include "VGM/solids/ITorus.h"

namespace BaseVGM {

  class VTorus : public virtual VGM::ITorus
  {
    public:
      VTorus();
      virtual ~VTorus();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VTorus::Type() const { return VGM::kTorus; }

#endif //BASE_VGM_V_TORUS_H
