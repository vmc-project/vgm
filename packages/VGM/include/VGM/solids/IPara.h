// $Id$
//
// Class IPara
// ---------------
// The VGM interface to para solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_PARA_H
#define VGM_I_PARA_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class IPara : public virtual ISolid
  {
    public:
      virtual ~IPara() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double XHalfLength() const = 0;
      virtual double YHalfLength() const = 0;
      virtual double ZHalfLength() const = 0;
      virtual double Alpha() const = 0;
      virtual double Theta() const = 0;
      virtual double Phi() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IPara& para);

#endif //VGM_I_PARA_H
