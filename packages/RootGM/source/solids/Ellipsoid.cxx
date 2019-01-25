// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Ellipsoid
// ---------------
// VGM implementation for Root elliptical tube solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Ellipsoid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoMatrix.h"
#include "TGeoBBox.h"
#include "TGeoSphere.h"
#include "TGeoScaledShape.h"
#include "TGeoBoolNode.h"
#include "TGeoCompositeShape.h"

//_____________________________________________________________________________
RootGM::Ellipsoid::Ellipsoid(const std::string& name,
                             double dx, double dy, double dz,
                             double zBottomCut, double zTopCut)
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid(),
    fEllipsoid(0),
    fDx(dx),
    fDy(dy),
    fDz(dz),
    fZBottomCut(zBottomCut),
    fZTopCut(zTopCut)
{
/// Standard constructor to define elliptical tube from parameters
/// \param dx the semi-axis of the ellipse along x in mm
/// \param dy the semi-axis of the ellipse along y in mm
/// \param dz the semi-axis of the ellipse along z in mm
/// \param zBottomCut bottom cut in z in mm
/// \param zTopCut top cut in z in mm

  // First create a sphere with rmin = 0, rmax = dx
  TGeoSphere* sphere
    = new TGeoSphere("sphere", 0., dx / RootGM::Units::Length());

  // The scale to trasform sphere in ellipsoid
  TGeoScale* scale
    = new TGeoScale(1.0, dy/dx, dz/dx);

  // The ellipsoid without z-cuts
  TGeoScaledShape* scaledShape
    = new TGeoScaledShape("scaledSphere", sphere, scale);

  if ( zBottomCut == 0. &&  zTopCut == 0. ) {
    fEllipsoid = scaledShape;
    fEllipsoid->SetName(name.data());
  }
  else {
    // adjust cut parameters if they are not consistent
    if ( zBottomCut == 0. || zBottomCut > dz ) zBottomCut = -dz;
    if ( zTopCut == 0. || zTopCut < zBottomCut ) zTopCut = dz;

    // The composite shape applying z cuts
    Double_t origin[3];
    origin[0] = 0.;
    origin[1] = 0.;
    origin[2] = 0.5*(zBottomCut+zTopCut) / RootGM::Units::Length();
    TGeoBBox* cutBox
      = new TGeoBBox("cutBox",
                      2. * dx / RootGM::Units::Length(),
                      2. * dy / RootGM::Units::Length(),
                      0.5 * (zTopCut-zBottomCut) / RootGM::Units::Length(),
                      origin);

    TGeoBoolNode* boolNode
      = new TGeoIntersection(scaledShape, cutBox);

    fEllipsoid
      = new TGeoCompositeShape(name.data(), boolNode);
  }

  RootGM::SolidMap::Instance()->AddSolid(this, fEllipsoid);
}

//_____________________________________________________________________________
RootGM::Ellipsoid::Ellipsoid(TGeoScaledShape* scaledShape)
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid(),
    fEllipsoid(scaledShape),
    fDx(0.),
    fDy(0.),
    fDz(0.),
    fZBottomCut(0.),
    fZTopCut(0.)

{
/// Create ellipsoid from Root scaled sphere.
/// The rmin, theta and phi parameters are ignored.

  TGeoSphere* sphere = dynamic_cast<TGeoSphere*>(scaledShape->GetShape());
  const Double_t* scale = scaledShape->GetScale()->GetScale();

  Double_t rmax = sphere->GetRmax();
  Double_t sx = scale[0];
  Double_t sy = scale[1];
  Double_t sz = scale[2];

  fDx = rmax * sx * RootGM::Units::Length();
  fDy = rmax * sy * RootGM::Units::Length();
  fDz = rmax * sz * RootGM::Units::Length();

  RootGM::SolidMap::Instance()->AddSolid(this, fEllipsoid);
}

//_____________________________________________________________________________
RootGM::Ellipsoid::Ellipsoid()
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid()
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Ellipsoid::Ellipsoid(const Ellipsoid& rhs)
  : VGM::ISolid(rhs),
    VGM::IEllipsoid(rhs),
    BaseVGM::VEllipsoid(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Ellipsoid::~Ellipsoid() {
//
}

//_____________________________________________________________________________
std::string RootGM::Ellipsoid::Name() const
{
  return fEllipsoid->GetName();
}

//_____________________________________________________________________________
double RootGM::Ellipsoid::XSemiAxis() const
{
  return fDx;
}

//_____________________________________________________________________________
double RootGM::Ellipsoid::YSemiAxis() const
{
  return fDy;
}

//_____________________________________________________________________________
double RootGM::Ellipsoid::ZSemiAxis() const
{
  return fDz;
}

//_____________________________________________________________________________
double RootGM::Ellipsoid::ZBottomCut() const
{
  return fZBottomCut;
}

//_____________________________________________________________________________
double RootGM::Ellipsoid::ZTopCut() const
{
  return fZTopCut;
}
