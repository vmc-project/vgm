// $Id$
//
// Class Tubs
// ---------------
// VGM implementation for Geant4 tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TUBS_H
#define GEANT4_GM_TUBS_H

#include <string>

#include "G4Tubs.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VTubs.h"

namespace Geant4GM {

  class Tubs : public BaseVGM::VTubs
  {
    public:
      Tubs(const std::string& name, 
              double rin, double rout, double hz, 
	      double sphi, double dphi);
      Tubs(G4Tubs* tubs, 
              G4ReflectedSolid* reflTubs = 0);
      virtual ~Tubs();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Tubs() : BaseVGM::VTubs() {}
      Tubs(const Tubs& rhs) : BaseVGM::VTubs(rhs) {}

    private:
      G4Tubs* fTubs;
  };

}

#endif //GEANT4_GM_TUBS_H
