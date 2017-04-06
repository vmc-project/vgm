// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::Ellipsoid
///
/// VGM implementation for Geant4 ellipsoid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ELLIPSOID_H
#define GEANT4_GM_ELLIPSOID_H

#include "BaseVGM/solids/VEllipsoid.h"

#include <string>

class G4Ellipsoid;
class G4ReflectedSolid;

namespace Geant4GM {

  class Ellipsoid : public BaseVGM::VEllipsoid
  {
    public:
      Ellipsoid(const std::string& name, 
          double dx, double dy, double dz, double zBottomCut, double zTopCut);
      Ellipsoid(G4Ellipsoid* ellipsoid, 
          G4ReflectedSolid* reflEllipsoid = 0);
      virtual ~Ellipsoid();

      // methods
      virtual std::string Name() const;
      virtual double XSemiAxis() const;
      virtual double YSemiAxis() const;
      virtual double ZSemiAxis() const;
      virtual double ZBottomCut() const;
      virtual double ZTopCut() const;

    protected:
      Ellipsoid();
      Ellipsoid(const Ellipsoid& rhs);

    private:
      G4Ellipsoid* fEllipsoid;
  };

}

#endif //GEANT4_GM_ELLIPSOID_H
