// $Id$
/// \ingroup VGM_solids
///
/// \class VGM::IPara
/// 
/// The VGM interface to para solids.
///
/// Author: Ivana Hrivnacova; IPN Orsay

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

		      ///
		      /// Return half-length along the x axis in mm
      virtual double XHalfLength() const = 0;
		      ///
		      /// Return half-length along the y axis in mm
      virtual double YHalfLength() const = 0;
		      ///
		      /// Return half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;
		      ///
		      /// Return angle formed by the y axis and by the plane
		      /// joining the centre of the faces parallel to the
		      /// z-x plane at -hy and +hy in deg
      virtual double Alpha() const = 0;
		      ///
		      /// Return polar angle of the line joining the centres
		      /// of the faces at -hz and +hz in deg
      virtual double Theta() const = 0;
		      ///
		      /// Return azimuthal angle of the line joining the centres
 		      /// of the faces at -hz and +hz in deg
      virtual double Phi() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IPara& para);

#endif //VGM_I_PARA_H
