// $Id$
//
// Class Cons
// ---------------
// VGM implementation for Geant4 cons solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_CONS_H
#define GEANT4_GM_CONS_H

#include <string>

#include "G4Cons.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VCons.h"

namespace Geant4GM {

  class Cons : public BaseVGM::VCons
  {
    public:
      Cons(const std::string& name, 
           double rin1, double rout1, double rin2, double rout2,
	   double hz, double sphi, double dphi);
      Cons(G4Cons* cons, 
           G4ReflectedSolid* reflCons = 0);
      virtual ~Cons();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadiusMinusZ() const ;
      virtual double OuterRadiusMinusZ() const;
      virtual double InnerRadiusPlusZ() const;
      virtual double OuterRadiusPlusZ() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Cons() : BaseVGM::VCons() {}
      Cons(const Cons& rhs) : BaseVGM::VCons(rhs) {}
 
    private:
      bool    fIsReflected;
      G4Cons* fCons;
  };

}

#endif //GEANT4_GM_CONS_H
