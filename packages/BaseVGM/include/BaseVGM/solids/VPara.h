// $Id$
/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VPara
///
/// The ABC for para solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_PARA_H
#define BASE_VGM_V_PARA_H

#include <iostream>

#include "VGM/solids/IPara.h"

namespace BaseVGM {

  class VPara : public virtual VGM::IPara
  {
    public:
      VPara();
      virtual ~VPara();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VPara::Type() const { return VGM::kPara; }

#endif //BASE_VGM_V_PARA_H
