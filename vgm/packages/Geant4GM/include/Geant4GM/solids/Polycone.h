// $Id$
//
// Class Polycone
// -----------------
// VGM implementation for Geant4 polycone solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_POLYCONE_H
#define GEANT4_GM_POLYCONE_H

#include <string>

#include "G4Polycone.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VPolycone.h"

namespace Geant4GM {

  class Polycone : public BaseVGM::VPolycone
  {
    public:
      Polycone(const std::string& name, 
               double sphi, double dphi, int nofZplanes,
               double* z, double* rin, double* rout);
      Polycone(G4Polycone* polycone, 
               G4ReflectedSolid* reflPolycone = 0);
      virtual ~Polycone();

      // methods
      virtual std::string Name() const;
      virtual double  StartPhi() const;
      virtual double  DeltaPhi() const;
      virtual int     NofZPlanes() const;
      virtual double* ZValues() const;
      virtual double* InnerRadiusValues() const;
      virtual double* OuterRadiusValues() const;

    protected:
      Polycone() : BaseVGM::VPolycone() {}
      Polycone(const Polycone& rhs) : BaseVGM::VPolycone(rhs) {}

    private:
      void CreateBuffers();

      static const int fgkMaxNofZPlanes;
      static double*   fgZBuffer;
      static double*   fgRinBuffer;
      static double*   fgRoutBuffer;

      bool        fIsReflected;
      double*     fZValuesRefl;
      G4Polycone* fPolycone;
  };

}

#endif //GEANT4_GM_POLYCONE_H
