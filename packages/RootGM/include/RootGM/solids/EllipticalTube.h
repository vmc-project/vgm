// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM:: EllipticalTube
///
/// VGM implementation for Root elliptical tube solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELLIPTICAL_TUBE_H
#define ROOT_GM_ELLIPTICAL_TUBE_H

#include "BaseVGM/solids/VEllipticalTube.h"

#include <string>

class TGeoEltu;

namespace RootGM {

  class EllipticalTube : public BaseVGM::VEllipticalTube
  {
    public:
      EllipticalTube(const std::string& name, 
                     double dx, double dy, double hz);
      EllipticalTube(TGeoEltu* tubs);
      virtual ~EllipticalTube();

      // methods
      virtual std::string Name() const;
      virtual double Dx() const;
      virtual double Dy() const;
      virtual double ZHalfLength() const;

    protected:
      EllipticalTube();
      EllipticalTube(const EllipticalTube& rhs);

    private:
      TGeoEltu* fEllipticalTube;
  };

}

#endif //ROOT_GM_ELLIPTICAL_TUBE_H
