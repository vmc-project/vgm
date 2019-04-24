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
// Class Trap
// ---------------
// VGM implementation for Root trap solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Trap.h"
#include "RootGM/common/Units.h"
#include "RootGM/solids/SolidMap.h"

#include "TGeoArb8.h"

//_____________________________________________________________________________
RootGM::Trap::Trap(const std::string& name, double hz, double theta, double phi,
  double dy1, double dx1, double dx2, double alpha1, double dy2, double dx3,
  double dx4, double alpha2)
  : VGM::ISolid(),
    VGM::ITrap(),
    BaseVGM::VTrap(),
    fTrap(new TGeoTrap(name.data(), hz / RootGM::Units::Length(),
      theta / RootGM::Units::Angle(), phi / RootGM::Units::Angle(),
      dy1 / RootGM::Units::Length(), dx1 / RootGM::Units::Length(),
      dx2 / RootGM::Units::Length(), alpha1 / RootGM::Units::Angle(),
      dy2 / RootGM::Units::Length(), dx3 / RootGM::Units::Length(),
      dx4 / RootGM::Units::Length(), alpha2 / RootGM::Units::Angle()))
{
  /// Standard constructor to define trap from parameters
  /// ( Note that of the 11 parameters described below, only 9
  ///   are really independent)
  /// \param hz half-length along the z axis in mm
  /// \param theta polar angle of the line joining the centres
  ///	   of the faces at -hz and +hz in deg
  /// \param phi azimuthal angle of the line joining the centres
  ///	   of the faces at -hz and +hz in deg
  /// \param dy1 half-length along y of the face at -hz in mm
  /// \param dx1 half-length along x of the side at -hy
  ///	   of the face at -hz in mm
  /// \param dx2 half-length along x of the side at +hy
  ///	   of the face at +hz in mm
  /// \param alpha1  angle with respect to the y axis from the
  ///	   centre of the side at -hy to the centre at +hy
  ///	   of the face at -hz
  /// \param dy2 half-length along y of the face at +hz in mm
  /// \param dx3 half-length along x of the side at -hy
  ///	   of the face at +hz in mm
  /// \param dx4 half-length along x of the side at +hy
  ///	   of the face at +hz in mm
  /// \param alpha2  angle with respect to the y axis from the
  ///	   centre of the side at -hy to the centre at +hy
  ///	   of the face at +hz

  RootGM::SolidMap::Instance()->AddSolid(this, fTrap);
}

//_____________________________________________________________________________
RootGM::Trap::Trap(TGeoTrap* trap)
  : VGM::ISolid(), VGM::ITrap(), BaseVGM::VTrap(), fTrap(trap)
{
  /// Standard constructor to define trap from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fTrap);
}

//_____________________________________________________________________________
RootGM::Trap::Trap() : VGM::ISolid(), VGM::ITrap(), BaseVGM::VTrap()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Trap::Trap(const Trap& rhs)
  : VGM::ISolid(rhs), VGM::ITrap(rhs), BaseVGM::VTrap(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Trap::~Trap()
{
  //
}

//_____________________________________________________________________________
std::string RootGM::Trap::Name() const { return fTrap->GetName(); }

//_____________________________________________________________________________
double RootGM::Trap::ZHalfLength() const
{
  return fTrap->GetDZ() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::Theta() const
{
  return fTrap->GetTheta() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Trap::Phi() const
{
  return fTrap->GetPhi() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Trap::YHalfLengthMinusZ() const
{
  return fTrap->GetH1() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::XHalfLengthMinusZMinusY() const
{
  return fTrap->GetBl1() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::XHalfLengthMinusZPlusY() const
{
  return fTrap->GetTl1() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::AlphaMinusZ() const
{
  return fTrap->GetAlpha1() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Trap::YHalfLengthPlusZ() const
{
  return fTrap->GetH2() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::XHalfLengthPlusZMinusY() const
{
  return fTrap->GetBl2() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::XHalfLengthPlusZPlusY() const
{
  return fTrap->GetTl2() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Trap::AlphaPlusZ() const
{
  return fTrap->GetAlpha2() * RootGM::Units::Angle();
}
