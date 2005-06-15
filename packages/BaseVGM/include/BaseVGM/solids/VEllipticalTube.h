// $Id$
/// \ingroup BaseVGM_solids
///
/// \class BaseVGM::VEllipticalTube
///
/// The ABC for elliptical tube solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_ELLIPTICAL_TUBE_H
#define BASE_VGM_V_ELLIPTICAL_TUBE_H

#include <iostream>

#include "VGM/solids/IEllipticalTube.h"

namespace BaseVGM {
 
  class VEllipticalTube : public virtual VGM::IEllipticalTube
  {
    public:
      VEllipticalTube();
      virtual ~VEllipticalTube();

      // methods
      virtual VGM::SolidType Type() const;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const;
  };

}

// inline functions

inline VGM::SolidType 
BaseVGM::VEllipticalTube::Type() const { return VGM::kEltu; }

#endif //BASE_VGM_V_ELLIPTICAL_TUBE_H
