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
// Class Torus
// ---------------
// VGM implementation for Root torus solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Torus.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoTorus.h"

//_____________________________________________________________________________
RootGM::Torus::Torus(const std::string& name,
                     double rin, double rout, double rax,
		     double sphi, double dphi)
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus(),
    fTorus(new TGeoTorus(name.data(),
                         rax  / RootGM::Units::Length(),
		         rin  / RootGM::Units::Length(),
		         rout / RootGM::Units::Length(),
		         sphi / RootGM::Units::Angle(),
		         dphi / RootGM::Units::Angle()))
{
/// Standard constructor to define torus from parameters
/// \param rin inside radius of the torus in mm
/// \param rout outside radius of the torus in mm
/// \param rax axial (swept) radius of the torus in mm
/// \param sphi starting angle of the segment in deg
///	   (with 0 being the +x axis)
/// \param dphi opening angle of the segment in deg

  RootGM::SolidMap::Instance()->AddSolid(this, fTorus);
}


//_____________________________________________________________________________
RootGM::Torus::Torus(TGeoTorus* torus)
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus(),
    fTorus(torus)
{
/// Standard constructor to define torus from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fTorus);
}

//_____________________________________________________________________________
RootGM::Torus::Torus()
  : VGM::ISolid(),
    VGM::ITorus(),
    BaseVGM::VTorus()
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Torus::Torus(const Torus& rhs)
  : VGM::ISolid(rhs),
    VGM::ITorus(rhs),
    BaseVGM::VTorus(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Torus::~Torus() {
//
}

//_____________________________________________________________________________
std::string RootGM::Torus::Name() const
{
  return fTorus->GetName();
}

//_____________________________________________________________________________
double RootGM::Torus::InnerRadius() const
{
  return fTorus->GetRmin() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Torus::OuterRadius() const
{
  return fTorus->GetRmax() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Torus::AxialRadius() const
{
  return fTorus->GetR() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Torus::StartPhi() const
{
  return fTorus->GetPhi1() * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Torus::DeltaPhi() const
{
  return fTorus->GetDphi() * RootGM::Units::Angle();
}
