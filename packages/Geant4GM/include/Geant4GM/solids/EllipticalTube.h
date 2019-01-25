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
/// \class Geant4GM::EllipticalTube
///
/// VGM implementation for Geant4 elliptical tube solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ELLIPTICAL_TUBE_H
#define GEANT4_GM_ELLIPTICAL_TUBE_H

#include "BaseVGM/solids/VEllipticalTube.h"

#include <string>

class G4EllipticalTube;
class G4ReflectedSolid;

namespace Geant4GM {

  class EllipticalTube : public BaseVGM::VEllipticalTube
  {
    public:
      EllipticalTube(const std::string& name,
                     double dx, double dy, double hz);
      EllipticalTube(G4EllipticalTube* eltu,
                     G4ReflectedSolid* reflEltu = 0);
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
      G4EllipticalTube* fEllipticalTube;
  };

}

#endif //GEANT4_GM_ELLIPTICAL_TUBE_H
