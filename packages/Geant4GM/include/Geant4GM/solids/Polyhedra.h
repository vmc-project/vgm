// $Id$
//
// Class Polyhedra
// -------------------
// VGM implementation for Geant4 polyhedra solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_POLYHEDRA_H
#define GEANT4_GM_POLYHEDRA_H

#include <string>

#include "G4Polyhedra.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VPolyhedra.h"

namespace Geant4GM {

  class Polyhedra : public BaseVGM::VPolyhedra
  {
    public:
      Polyhedra(const std::string& name, 
                double sphi, double dphi, int nofSides, int nofZplanes,
                double* z, double* rin, double* rout);
      Polyhedra(G4Polyhedra* polyhedra, 
                G4ReflectedSolid* reflPolyhedra = 0);
      virtual ~Polyhedra();

      // methods
      virtual std::string Name() const;
      virtual double  StartPhi() const;
      virtual double  DeltaPhi() const;
      virtual int     NofSides() const;
      virtual int     NofZPlanes() const;
      virtual double* ZValues() const;
      virtual double* InnerRadiusValues() const;
      virtual double* OuterRadiusValues() const;

    protected:
      Polyhedra() : BaseVGM::VPolyhedra() {}
      Polyhedra(const Polyhedra& rhs) : BaseVGM::VPolyhedra(rhs) {}

    private:
      bool         fIsReflected;
      double*      fZValuesRefl;
      G4Polyhedra* fPolyhedra;
  };

}

#endif //GEANT4_GM_POLYHEDRA_H
