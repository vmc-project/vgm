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
// Class Hype
// -----------
// VGM implementation for Root hyperboloid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Hype.h"
#include "RootGM/common/Units.h"
#include "RootGM/solids/SolidMap.h"

#include "TGeoHype.h"
#include "TGeoShape.h"

//_____________________________________________________________________________
RootGM::Hype::Hype(const std::string& name, double r1, double r2,
  double stereo1, double stereo2, double hz)
  : VGM::ISolid(),
    VGM::IHype(),
    BaseVGM::VHype(),
    fHype(new TGeoHype(name.data(), r1 / RootGM::Units::Length(),
      stereo1 / RootGM::Units::Angle(), r2 / RootGM::Units::Length(),
      stereo2 / RootGM::Units::Angle(), hz / RootGM::Units::Length()))
{
  /// Standard constructor to define hyperboloid from parameters
  /// \param r1 radius of the inner hyperbolic surface in mm
  /// \param r2 radius of the outer hyperbolic surface in mm
  /// \param stereo1 stereo angle for the inner hyperbolic surface in deg
  /// \param stereo2 stereo angle for the outer hyperbolic surface in deg
  /// \param hz half-length along the z axis in mm

  RootGM::SolidMap::Instance()->AddSolid(this, fHype);
}

//_____________________________________________________________________________
RootGM::Hype::Hype(TGeoHype* hype)
  : VGM::ISolid(), VGM::IHype(), BaseVGM::VHype(), fHype(hype)
{
  /// Standard constructor to define hyperboloid from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fHype);
}

//_____________________________________________________________________________
RootGM::Hype::Hype() : VGM::ISolid(), VGM::IHype(), BaseVGM::VHype()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Hype::Hype(const Hype& rhs)
  : VGM::ISolid(rhs), VGM::IHype(rhs), BaseVGM::VHype(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Hype::~Hype()
{
  //
}

//_____________________________________________________________________________
std::string RootGM::Hype::Name() const { return fHype->GetName(); }

//_____________________________________________________________________________
double RootGM::Hype::InnerRadius() const
{
  return fHype->GetRmin() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Hype::InnerStereoAngle() const
{
  return fHype->GetStIn() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Hype::OuterRadius() const
{
  return fHype->GetRmax() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Hype::OuterStereoAngle() const
{
  return fHype->GetStOut() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Hype::ZHalfLength() const
{
  return fHype->GetDz() * RootGM::Units::Length();
}
