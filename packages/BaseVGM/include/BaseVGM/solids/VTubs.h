// $Id$
/// \ingroup BaseVGM_solids
///
/// \class BaseVGM::VTubs
///
/// The ABC for tubs solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TUBS_H
#define BASE_VGM_V_TUBS_H

#include <iostream>

#include "VGM/solids/ITubs.h"

namespace BaseVGM {
 
  class VTubs : public virtual VGM::ITubs
  {
    public:
      VTubs();
      virtual ~VTubs();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VTubs::Type() const { return VGM::kTubs; }

#endif //BASE_VGM_V_TUBS_H
