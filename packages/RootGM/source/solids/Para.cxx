// $Id$
//
// Class Para
// ---------------
// VGM implementation for Root para solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Para.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Para::Para(const std::string& name,
                   double dx, double dy, double dz,
	           double alpha, double theta, double phi)
  : BaseVGM::VPara(),
    fPara(new TGeoPara(name.data(), 
                       dx    / RootGM::Units::Length(), 
		       dy    / RootGM::Units::Length(), 
		       dz    / RootGM::Units::Length(), 
		       alpha / RootGM::Units::Angle(), 
		       theta / RootGM::Units::Angle(), 
		       phi   / RootGM::Units::Angle()))
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fPara); 
}


//_____________________________________________________________________________
RootGM::Para::Para(TGeoPara* para)
  : BaseVGM::VPara(),
    fPara(para)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fPara); 
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


