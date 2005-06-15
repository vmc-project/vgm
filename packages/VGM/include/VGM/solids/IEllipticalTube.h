// $Id$
/// \ingroup VGM_solids
///
/// \class VGM::IEllipticalTube
/// 
/// The VGM interface to elliptical tube solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_ELLIPTICAL_TUBE_H
#define VGM_I_ELLIPTICAL_TUBE_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class IEllipticalTube : public virtual ISolid
  {
    public:
      virtual ~IEllipticalTube() {}

      // methods
      
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      ///
		      /// Return the semi-axis of the ellipse along x in mm
      virtual double Dx() const = 0;
		      ///
		      /// Return the semi-axis of the ellipse along y in mm
      virtual double Dy() const = 0;
		      ///
		      /// Return the half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::IEllipticalTube& eltu);

#endif //VGM_I_ELLIPTICAL_TUBE_H
