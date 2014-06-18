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
// Class Para
// ---------------
// VGM implementation for Root para solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Para.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoPara.h"

//_____________________________________________________________________________
RootGM::Para::Para(const std::string& name,
                   double dx, double dy, double dz,
	           double alpha, double theta, double phi)
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara(),
    fPara(new TGeoPara(name.data(), 
                       dx    / RootGM::Units::Length(), 
		       dy    / RootGM::Units::Length(), 
		       dz    / RootGM::Units::Length(), 
		       alpha / RootGM::Units::Angle(), 
		       theta / RootGM::Units::Angle(), 
		       phi   / RootGM::Units::Angle()))
{
/// Standard constructor to define para from parameters
/// \param dx half-length along the x axis in mm
/// \param dy half-length along the y axis in mm
/// \param dz half-length along the z axis in mm
/// \param alpha angle formed by the y axis and by the plane
///	   joining the centre of the faces parallel to the
///	   z-x plane at -hy and +hy in deg
/// \param theta polar angle of the line joining the centres
///	   of the faces at -hz and +hz in deg
/// \param phi azimuthal angle of the line joining the centres
///	   of the faces at -hz and +hz in deg

  RootGM::SolidMap::Instance()->AddSolid(this, fPara); 
}


//_____________________________________________________________________________
RootGM::Para::Para(TGeoPara* para)
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara(),
    fPara(para)
{    
/// Standard constructor to define para from G4 object

  RootGM::SolidMap::Instance()->AddSolid(this, fPara); 
}

//_____________________________________________________________________________
RootGM::Para::Para() 
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Para::Para(const Para& rhs) 
  : VGM::ISolid(rhs),
    VGM::IPara(rhs),
    BaseVGM::VPara(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Para::~Para() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Para::Name() const
{
  return fPara->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Para::XHalfLength() const
{
  return fPara->GetX() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Para::YHalfLength() const
{
  return fPara->GetY() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Para::ZHalfLength() const
{
  return fPara->GetZ() * RootGM::Units::Length();
}  

//_____________________________________________________________________________
double RootGM::Para::Alpha() const
{
  return fPara->GetAlpha() * RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Para::Theta() const
{
  return fPara->GetTheta() * RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Para::Phi() const
{
  return fPara->GetPhi() * RootGM::Units::Angle();
}  


