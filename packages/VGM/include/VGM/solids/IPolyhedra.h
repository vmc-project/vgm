// $Id$
//
// Class IPolyhedra
// ---------------
// The VGM interface to polyhedra solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_POLYHEDRA_H
#define VGM_I_POLYHEDRA_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class IPolyhedra : public virtual ISolid
  {
    public:
      virtual ~IPolyhedra() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

      virtual double  StartPhi() const = 0;
      virtual double  DeltaPhi() const = 0;
      virtual int     NofSides() const = 0;
      virtual int     NofZPlanes() const = 0;
      virtual double* ZValues() const = 0;
      virtual double* InnerRadiusValues() const = 0;
      virtual double* OuterRadiusValues() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IPolyhedra& polyhedra);

#endif //VGM_I_POLYHEDRA_H
