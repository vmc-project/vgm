// $Id$
//
// Class Sphere
// ---------------
// VGM implementation for Root sphere solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_SPHERE_H
#define ROOT_GM_SPHERE_H

#include <string>

#include "TGeoSphere.h"

#include "BaseVGM/solids/VSphere.h"

namespace RootGM {

  class Sphere : public BaseVGM::VSphere
  {
    public:
      Sphere(const std::string& name, 
             double rin, double rout, double sphi, double dphi, 
	     double stheta, double dtheta);
      Sphere(TGeoSphere* sphere);
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
      Sphere() : BaseVGM::VSphere() {}
      Sphere(const Sphere& rhs) : BaseVGM::VSphere(rhs) {}

    private:
      TGeoSphere* fSphere;
  };

}

#endif //ROOT_GM_SPHERE_H
