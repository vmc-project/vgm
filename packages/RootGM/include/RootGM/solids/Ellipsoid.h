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
/// \class RootGM::Ellipsoid
///
/// VGM implementation for Root ellipsoid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELLIPSOID_H
#define ROOT_GM_ELLIPSOID_H

#include "BaseVGM/solids/VEllipsoid.h"

#include <string>

class TGeoShape;
class TGeoScaledShape;

namespace RootGM {

class Ellipsoid : public BaseVGM::VEllipsoid
{
 public:
  Ellipsoid(const std::string& name, double dx, double dy, double dz,
    double zBottomCut, double zTopCut);
  Ellipsoid(TGeoScaledShape* scaledShape);
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
  TGeoShape* fEllipsoid;
  double fDx;
  double fDy;
  double fDz;
  double fZBottomCut;
  double fZTopCut;
};
} // namespace RootGM

#endif // ROOT_GM_BOX_H
