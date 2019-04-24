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
// Class Sphere
// ---------------
// VGM implementation for Root sphere solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Sphere.h"
#include "RootGM/common/Units.h"
#include "RootGM/solids/SolidMap.h"

#include "TGeoSphere.h"

//_____________________________________________________________________________
RootGM::Sphere::Sphere(const std::string& name, double rin, double rout,
  double sphi, double dphi, double stheta, double dtheta)
  : VGM::ISolid(),
    VGM::ISphere(),
    BaseVGM::VSphere(),
    fSphere(new TGeoSphere(name.data(), rin / RootGM::Units::Length(),
      rout / RootGM::Units::Length(), stheta / RootGM::Units::Angle(),
      (stheta + dtheta) / RootGM::Units::Angle(), sphi / RootGM::Units::Angle(),
      (sphi + dphi) / RootGM::Units::Angle()))
{
  /// Standard constructor to define sphere from parameters
  /// \param rin inside radius of the shell in mm
  /// \param rout outside radius of the shell in mm
  /// \param sphi starting azimuthal angle of the segment in deg
  /// \param dphi opening azimuthal angle of the segment in deg
  /// \param stheta starting polar angle of the segment in deg
  /// \param dtheta opening polar angle of the segment in deg

  RootGM::SolidMap::Instance()->AddSolid(this, fSphere);
}

//_____________________________________________________________________________
RootGM::Sphere::Sphere(TGeoSphere* sphere)
  : VGM::ISolid(), VGM::ISphere(), BaseVGM::VSphere(), fSphere(sphere)
{
  /// Standard constructor to define sphere from G4 object

  RootGM::SolidMap::Instance()->AddSolid(this, fSphere);
}

//_____________________________________________________________________________
RootGM::Sphere::Sphere() : VGM::ISolid(), VGM::ISphere(), BaseVGM::VSphere()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Sphere::Sphere(const Sphere& rhs)
  : VGM::ISolid(rhs), VGM::ISphere(rhs), BaseVGM::VSphere(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Sphere::~Sphere()
{
  //
}

//_____________________________________________________________________________
std::string RootGM::Sphere::Name() const { return fSphere->GetName(); }

//_____________________________________________________________________________
double RootGM::Sphere::InnerRadius() const
{
  return fSphere->GetRmin() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Sphere::OuterRadius() const
{
  return fSphere->GetRmax() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Sphere::StartPhi() const
{
  return fSphere->GetPhi1() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Sphere::DeltaPhi() const
{
  return (fSphere->GetPhi2() - fSphere->GetPhi1()) * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Sphere::StartTheta() const
{
  return fSphere->GetTheta1() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Sphere::DeltaTheta() const
{
  return (fSphere->GetTheta2() - fSphere->GetTheta1()) * RootGM::Units::Angle();
}
