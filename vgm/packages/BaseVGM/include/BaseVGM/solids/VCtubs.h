// $Id$
/// \ingroup BaseVGM_solids
///
/// \class BaseVGM::VCtubs
///
/// The ABC for cut tubs solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_CTUBS_H
#define BASE_VGM_V_CTUBS_H

#include <iostream>

#include "VGM/solids/ICtubs.h"

namespace BaseVGM {
 
  class VCtubs : public virtual VGM::ICtubs
  {
    public:
      VCtubs();
      virtual ~VCtubs();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VCtubs::Type() const { return VGM::kCtubs; }

#endif //BASE_VGM_V_CTUBS_H
