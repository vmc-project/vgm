// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::IPolycone
/// 
/// The VGM interface to polycone solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_POLYCONE_H
#define VGM_I_POLYCONE_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class IPolycone : public virtual ISolid
  {
    public:
      virtual ~IPolycone() {}

      // methods
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		       ///
		       /// Return starting phi angle of the segment in deg
      virtual double  StartPhi() const = 0;
		       ///
		       /// Return opening phi angle of the segment in deg
      virtual double  DeltaPhi() const = 0;
		       ///
		       /// Return number of planes perpendicular to the z axis
      virtual int     NofZPlanes() const = 0;
		       ///
		       /// Return the array of z positions of the planes in mm
      virtual double* ZValues() const = 0;
		       ///
		       /// Return the array of inner radius of the planes in mm
      virtual double* InnerRadiusValues() const = 0;
		       ///
		       /// Return the array of outer radius of the planes in mm
      virtual double* OuterRadiusValues() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}  

std::ostream& operator << (std::ostream& out, const VGM::IPolycone& polycone);

#endif //VGM_I_POLYCONE_H
