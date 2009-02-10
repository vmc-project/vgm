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
// Class Paraboloid
// -----------------
// VGM implementation for Root paraboloid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Paraboloid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoShape.h"
#include "TGeoParaboloid.h"

//_____________________________________________________________________________
RootGM::Paraboloid::Paraboloid(const std::string& name, 
                               double r1, double r2, double hz)
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid(),
    fParaboloid(new TGeoParaboloid(name.data(), 
                          r1 / RootGM::Units::Length(), 
			  r2 / RootGM::Units::Length(), 
			  hz / RootGM::Units::Length()))
{
/// Standard constructor to define paraboloid from parameters
/// \param r1 radius at -hz in mm
/// \param r2 radius at +hz in mm
/// \param hz half-length along the z axis in mm

  RootGM::SolidMap::Instance()->AddSolid(this, fParaboloid); 
}


//_____________________________________________________________________________
RootGM::Paraboloid::Paraboloid(TGeoParaboloid* paraboloid)
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid(),
    fParaboloid(paraboloid)
{    
/// Standard constructor to define paraboloid from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fParaboloid); 
}

//_____________________________________________________________________________
RootGM::Paraboloid::Paraboloid() 
  : VGM::ISolid(),
    VGM::IParaboloid(),
    BaseVGM::VParaboloid() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Paraboloid::Paraboloid(const Paraboloid& rhs) 
  : VGM::ISolid(rhs),
    VGM::IParaboloid(rhs),
    BaseVGM::VParaboloid(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Paraboloid::~Paraboloid() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Paraboloid::Name() const
{
  return fParaboloid->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Paraboloid::RadiusMinusZ() const
{
  return fParaboloid->GetRlo() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Paraboloid::RadiusPlusZ() const
{
  return fParaboloid->GetRhi() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Paraboloid::ZHalfLength() const
{
  return fParaboloid->GetDz() * RootGM::Units::Length();
}  
