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
// Class Cons
// ---------------
// VGM implementation for Root cons solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Cons.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoShape.h"
#include "TGeoCone.h"

//_____________________________________________________________________________
RootGM::Cons::Cons(const std::string& name,
                   double rin1, double rout1, double rin2, double rout2,
	           double hz, double sphi, double dphi)
  : VGM::ISolid(),
    VGM::ICons(),
    BaseVGM::VCons(),
    fCons(new TGeoConeSeg(name.data(),
			  hz         / RootGM::Units::Length(),
                          rin1       / RootGM::Units::Length(),
			  rout1      / RootGM::Units::Length(),
			  rin2       / RootGM::Units::Length(),
			  rout2      / RootGM::Units::Length(),
			  sphi       / RootGM::Units::Angle(),
			 (sphi+dphi) / RootGM::Units::Angle()))
{
/// Standard constructor to define cons from parameters
/// \param rin1 inside radius at -hz in mm
/// \param rout1 outside radius at -hz in mm
/// \param rin2 inside radius at +hz in mm
/// \param rout2 outside radius at +hz in mm
/// \param hz half-length along the z axis in mm
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg

  RootGM::SolidMap::Instance()->AddSolid(this, fCons);
}


//_____________________________________________________________________________
RootGM::Cons::Cons(TGeoCone* cons)
  : VGM::ISolid(),
    VGM::ICons(),
    BaseVGM::VCons(),
    fCons(cons)
{
/// Standard constructor to define cons from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fCons);
}

//_____________________________________________________________________________
RootGM::Cons::Cons()
  : VGM::ISolid(),
    VGM::ICons(),
    BaseVGM::VCons()
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Cons::Cons(const Cons& rhs)
  : VGM::ISolid(rhs),
    VGM::ICons(rhs),
    BaseVGM::VCons(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Cons::~Cons() {
//
}

//_____________________________________________________________________________
std::string RootGM::Cons::Name() const
{
  return fCons->GetName();
}

//_____________________________________________________________________________
double RootGM::Cons::InnerRadiusMinusZ() const
{
  return fCons->GetRmin1() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Cons::OuterRadiusMinusZ() const
{
  return fCons->GetRmax1() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Cons::InnerRadiusPlusZ() const
{
  return fCons->GetRmin2() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Cons::OuterRadiusPlusZ() const
{
  return fCons->GetRmax2() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Cons::ZHalfLength() const
{
  return fCons->GetDz() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double RootGM::Cons::StartPhi() const
{
  if (fCons->TestShapeBit(TGeoShape::kGeoConeSeg))
    return ((TGeoConeSeg*)fCons)->GetPhi1() * RootGM::Units::Angle();
  else
    return 0. * RootGM::Units::Angle();
}

//_____________________________________________________________________________
double RootGM::Cons::DeltaPhi() const
{
  if (fCons->TestShapeBit(TGeoShape::kGeoConeSeg)) {
    return (  ((TGeoConeSeg*)fCons)->GetPhi2()
            - ((TGeoConeSeg*)fCons)->GetPhi1() ) * RootGM::Units::Angle();
  }
  else
    return 360. * RootGM::Units::Angle();
}
