// $Id$
//
// Class VPolycone
// ---------------
// The ABC for polycone solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_POLYCONE_H
#define BASE_VGM_V_POLYCONE_H

#include <iostream>

#include "VGM/solids/IPolycone.h"

namespace BaseVGM {

  class VPolycone : public virtual VGM::IPolycone
  {
    public:
      VPolycone();
      virtual ~VPolycone();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VPolycone::Type() const { return VGM::kPolycone; }

#endif //BASE_VGM_V_POLYCONE_H
