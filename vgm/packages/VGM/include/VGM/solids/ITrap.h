// $Id$
//
// Class ITrap
// ---------------
// The VGM interface to trap solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TRAP_H
#define VGM_I_TRAP_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class ITrap : public virtual ISolid
  {
    public:
      virtual ~ITrap() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double ZHalfLength() const = 0;
      virtual double Theta() const = 0;
      virtual double Phi() const = 0;
      virtual double YHalfLengthMinusZ() const = 0;
      virtual double XHalfLengthMinusZMinusY() const = 0;
      virtual double XHalfLengthMinusZPlusY() const = 0;
      virtual double AlphaMinusZ() const = 0;
      virtual double YHalfLengthPlusZ() const = 0;
      virtual double XHalfLengthPlusZMinusY() const = 0;
      virtual double XHalfLengthPlusZPlusY() const = 0;
      virtual double AlphaPlusZ() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };
  
}  

std::ostream& operator << (std::ostream& out, const VGM::ITrap& trap);

#endif //VGM_I_TRAP_H
