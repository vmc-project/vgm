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
// Class Ctubs
// ---------------
// VGM implementation for Root cut tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Ctubs.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Ctubs::Ctubs(const std::string& name, 
                   double rin, double rout, double hz,
		   double sphi, double dphi,
	           double nxlow, double nylow, double nzlow,
	           double nxhigh, double nyhigh, double nzhigh)
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs(),
    fCtubs(new TGeoCtub(name.data(), 
                        rin         / RootGM::Units::Length(), 
			rout        / RootGM::Units::Length(), 
			hz          / RootGM::Units::Length(), 
			sphi        / RootGM::Units::Angle(), 
			(sphi+dphi) / RootGM::Units::Angle(),
			nxlow       / RootGM::Units::Length(),
			nylow       / RootGM::Units::Length(),
			nzlow       / RootGM::Units::Length(),
			nxhigh      / RootGM::Units::Length(),
			nyhigh      / RootGM::Units::Length(),
			nzhigh      / RootGM::Units::Length()))
{
/// Standard constructor to define tubs from parameters
/// \param rin inside radius in mm 
/// \param rout outside radius in mm 
/// \param hz half-length along the z axis in mm 
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg
/// \param nxlow X-component of the normal unit vector to the cut plane in -z
/// \param nylow Y-component of the normal unit vector to the cut plane in -z
/// \param nzlow Z-component of the normal unit vector to the cut plane in -z
/// \param nxhigh X-component of the normal unit vector to the cut plane in +z
/// \param nyhigh Y-component of the normal unit vector to the cut plane in +z
/// \param nzhigh Z-component of the normal unit vector to the cut plane in +z


  RootGM::SolidMap::Instance()->AddSolid(this, fCtubs); 
}


//_____________________________________________________________________________
RootGM::Ctubs::Ctubs(TGeoCtub* tubs)
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs(),
    fCtubs(tubs)
{    
/// Standard constructor to define tubs from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fCtubs); 
}

//_____________________________________________________________________________
RootGM::Ctubs::Ctubs() 
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Ctubs::Ctubs(const Ctubs& rhs) 
  : VGM::ISolid(rhs),
    VGM::ICtubs(rhs),
    BaseVGM::VCtubs(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Ctubs::~Ctubs() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Ctubs::Name() const
{
  return fCtubs->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Ctubs::InnerRadius() const
{
  return fCtubs->GetRmin() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::OuterRadius() const
{
  return fCtubs->GetRmax() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::ZHalfLength() const
{
  return fCtubs->GetDz() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::StartPhi() const
{
  if (fCtubs->TestShapeBit(TGeoShape::kGeoTubeSeg)) 
    return ((TGeoTubeSeg*)fCtubs)->GetPhi1() * RootGM::Units::Angle();
  else    
    return 0. * RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::DeltaPhi() const
{
  if (fCtubs->TestShapeBit(TGeoShape::kGeoTubeSeg)) {
    return (  ((TGeoTubeSeg*)fCtubs)->GetPhi2() 
            - ((TGeoTubeSeg*)fCtubs)->GetPhi1() ) * RootGM::Units::Angle();
  }
  else
    return 360. * RootGM::Units::Angle();	    
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NxLow() const
{
  return fCtubs->GetNlow()[0] * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NyLow() const
{
  return fCtubs->GetNlow()[1] * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NzLow() const
{
  return fCtubs->GetNlow()[2] * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NxHigh() const
{
  return fCtubs->GetNhigh()[0] * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NyHigh() const
{
  return fCtubs->GetNhigh()[1] * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Ctubs::NzHigh() const
{
  return fCtubs->GetNhigh()[2] * RootGM::Units::Length();
}  

