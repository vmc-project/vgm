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
// Class Tubs
// ---------------
// VGM implementation for Root tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Tubs.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoTube.h"

//_____________________________________________________________________________
RootGM::Tubs::Tubs(const std::string& name, 
                   double rin, double rout, double hz,
		   double sphi, double dphi)
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs(),
    fTubs(new TGeoTubeSeg(name.data(), 
                          rin         / RootGM::Units::Length(), 
			  rout        / RootGM::Units::Length(), 
			  hz          / RootGM::Units::Length(), 
			  sphi        / RootGM::Units::Angle(), 
			  (sphi+dphi) / RootGM::Units::Angle()))
{
/// Standard constructor to define tubs from parameters
/// \param rin inside radius in mm 
/// \param rout outside radius in mm 
/// \param hz half-length along the z axis in mm 
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg

  RootGM::SolidMap::Instance()->AddSolid(this, fTubs); 
}


//_____________________________________________________________________________
RootGM::Tubs::Tubs(TGeoTube* tubs)
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs(),
    fTubs(tubs)
{    
/// Standard constructor to define tubs from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fTubs); 
}

//_____________________________________________________________________________
RootGM::Tubs::Tubs() 
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Tubs::Tubs(const Tubs& rhs) 
  : VGM::ISolid(rhs),
    VGM::ITubs(rhs),
    BaseVGM::VTubs(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Tubs::~Tubs() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Tubs::Name() const
{
  return fTubs->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Tubs::InnerRadius() const
{
  return fTubs->GetRmin() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Tubs::OuterRadius() const
{
  return fTubs->GetRmax() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Tubs::ZHalfLength() const
{
  return fTubs->GetDz() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Tubs::StartPhi() const
{
  if (fTubs->TestShapeBit(TGeoShape::kGeoTubeSeg)) 
    return ((TGeoTubeSeg*)fTubs)->GetPhi1() * RootGM::Units::Angle();
  else    
    return 0. * RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Tubs::DeltaPhi() const
{
  if (fTubs->TestShapeBit(TGeoShape::kGeoTubeSeg)) {
    return (  ((TGeoTubeSeg*)fTubs)->GetPhi2() 
            - ((TGeoTubeSeg*)fTubs)->GetPhi1() ) * RootGM::Units::Angle();
  }
  else
    return 360. * RootGM::Units::Angle();	    
}  
