// $Id$
//
// Class IBox
// ---------------
// The VGM interface to box solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_BOX_H
#define VGM_I_BOX_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class IBox : public virtual ISolid
  {
    public:
      virtual ~IBox() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double XHalfLength() const = 0;
      virtual double YHalfLength() const = 0;
      virtual double ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };
}  

std::ostream& operator << (std::ostream& out, const VGM::IBox& box);

#endif //VGM_I_BOX_H
