// $Id$
/// \ingroup VGM_solids
///
/// \class VGM::ISphere
/// 
/// The VGM interface to sphere solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_SPHERE_H
#define VGM_I_SPHERE_H

#include <iostream>

#include "VGM/solids/ISolid.h"

namespace VGM {

  class ISphere : public virtual ISolid
  {
    public:
      virtual ~ISphere() {}

      // methods
      
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

 		      ///
		      /// Return the inside radius of the shell in mm
      virtual double InnerRadius() const = 0;
		      ///
		      /// Return the outside radius of the shell in mm
      virtual double OuterRadius() const = 0;
		      ///
		      /// Return the starting azimuthal angle of the segment in deg
      virtual double StartPhi() const = 0;
		      ///
		      /// Return the opening azimuthal angle of the segment in deg
      virtual double DeltaPhi() const = 0;
		      ///
		      /// Return the starting polar angle of the segment in deg
      virtual double StartTheta() const = 0;
		      ///
		      /// Return the opening polar angle of the segment in deg
      virtual double DeltaTheta() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::ISphere& sphere);

#endif //VGM_I_SPHERE_H
