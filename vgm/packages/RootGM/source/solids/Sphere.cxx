// $Id$
//
// Class Sphere
// ---------------
// VGM implementation for Root sphere solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Sphere.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Sphere::Sphere(const std::string& name, 
                       double rin, double rout, 
		       double sphi, double dphi, 
	               double stheta, double dtheta)
  : BaseVGM::VSphere(),
    fSphere(new TGeoSphere(name.data(), 
                           rin              / RootGM::Units::Length(), 
			   rout             / RootGM::Units::Length(), 
			   stheta           / RootGM::Units::Angle(), 
			   (stheta + dtheta)/ RootGM::Units::Angle(),
			   sphi             / RootGM::Units::Angle(), 
			   (sphi + dphi)    / RootGM::Units::Angle()))
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fSphere); 
}


//_____________________________________________________________________________
RootGM::Sphere::Sphere(TGeoSphere* sphere)
  : BaseVGM::VSphere(),
    fSphere(sphere)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fSphere); 
}

//_____________________________________________________________________________
RootGM::Sphere::~Sphere() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Sphere::Name() const
{
  return fSphere->GetName();
}  
  
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
