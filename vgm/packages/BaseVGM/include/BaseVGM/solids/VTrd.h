// $Id$
/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VTrd
///
/// The ABC for trd solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_TRD_H
#define BASE_VGM_V_TRD_H

#include <iostream>

#include "VGM/solids/ITrd.h"

namespace BaseVGM {

  class VTrd : public virtual VGM::ITrd
  {
    public:
      VTrd();
      virtual ~VTrd();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VTrd::Type() const { return VGM::kTrd; }

#endif //BASE_VGM_V_TRD_H
