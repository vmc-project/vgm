// $Id$
//
// Class ITubs
// ---------------
// The VGM interface to tubs solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TUBS_H
#define VGM_I_TUBS_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class ITubs : public virtual ISolid
  {
    public:
      virtual ~ITubs() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double InnerRadius() const = 0;
      virtual double OuterRadius() const = 0;
      virtual double ZHalfLength() const = 0;
      virtual double StartPhi() const = 0;
      virtual double DeltaPhi() const = 0;
  
      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::ITubs& box);

#endif //VGM_I_TUBS_H
