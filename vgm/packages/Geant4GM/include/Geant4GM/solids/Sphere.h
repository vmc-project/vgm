// $Id$
//
// Class Sphere
// ----------------
// VGM implementation for Geant4 sphere solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_SPHERE_H
#define GEANT4_GM_SPHERE_H

#include <string>

#include "G4Sphere.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VSphere.h"

namespace Geant4GM {

  class Sphere : public BaseVGM::VSphere
  {
    public:
      Sphere(const std::string& name, 
             double rin, double rout, double sphi, double dphi, 
	     double stheta, double dtheta);
      Sphere(G4Sphere* sphere, 
             G4ReflectedSolid* reflSphere = 0);
      virtual ~Sphere();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;
      virtual double StartTheta() const;
      virtual double DeltaTheta() const;

    protected:
      Sphere();
      Sphere(const Sphere& rhs);

    private:
      bool      fIsReflected;
      G4Sphere* fSphere;
  };

}

#endif //GEANT4_GM_SPHERE_H
