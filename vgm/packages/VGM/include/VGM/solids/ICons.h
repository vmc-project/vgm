// $Id$
//
// Class ICons
// ---------------
// The VGM interface to cons solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_CONS_H
#define VGM_I_CONS_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class ICons : public virtual ISolid
  {
    public:
      virtual ~ICons() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double InnerRadiusMinusZ() const = 0;
      virtual double OuterRadiusMinusZ() const = 0;
      virtual double InnerRadiusPlusZ() const = 0;
      virtual double OuterRadiusPlusZ() const = 0;
      virtual double ZHalfLength() const = 0;
      virtual double StartPhi() const = 0;
      virtual double DeltaPhi() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };
  
}  

std::ostream& operator << (std::ostream& out, const VGM::ICons& cons);

#endif //VGM_I_CONS_H
