// $Id$
/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::EllipticalTube
///
/// VGM implementation for Geant4 elliptical tube solid.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ELLIPTICAL_TUBE_H
#define GEANT4_GM_ELLIPTICAL_TUBE_H

#include <string>

#include "G4EllipticalTube.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VEllipticalTube.h"

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
