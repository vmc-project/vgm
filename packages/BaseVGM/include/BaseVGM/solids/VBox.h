// $Id$
/// \ingroup BaseVGM_solids
//
/// \class BaseVGM::VBox
///
/// The ABC for box solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_BOX_H
#define BASE_VGM_V_BOX_H

#include <iostream>

#include "VGM/solids/IBox.h"

namespace BaseVGM {

  class VBox : public virtual VGM::IBox
  {
    public:
      VBox();
      virtual ~VBox();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };
  
}  

// inline functions

inline VGM::SolidType 
BaseVGM::VBox::Type() const { return VGM::kBox; }

#endif //BASE_VGM_V_BOX_H
