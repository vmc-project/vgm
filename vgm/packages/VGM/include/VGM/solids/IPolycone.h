// $Id$
//
// Class IPolycone
// ---------------
// The VGM interface to polycone solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_POLYCONE_H
#define VGM_I_POLYCONE_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class IPolycone : public virtual ISolid
  {
    public:
      virtual ~IPolycone() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double  StartPhi() const = 0;
      virtual double  DeltaPhi() const = 0;
      virtual int     NofZPlanes() const = 0;
      virtual double* ZValues() const = 0;
      virtual double* InnerRadiusValues() const = 0;
      virtual double* OuterRadiusValues() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IPolycone& polycone);

#endif //VGM_I_POLYCONE_H
