// $Id$
//
// Class Tubs
// ---------------
// VGM implementation for Root tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Tubs.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Tubs::Tubs(const std::string& name, 
                   double rin, double rout, double hz,
		   double sphi, double dphi)
  : BaseVGM::VTubs(),
    fTubs(new TGeoTubeSeg(name.data(), 
                          rin         / RootGM::Units::Length(), 
			  rout        / RootGM::Units::Length(), 
			  hz          / RootGM::Units::Length(), 
			  sphi        / RootGM::Units::Angle(), 
			  (sphi+dphi) / RootGM::Units::Angle()))
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fTubs); 
}


//_____________________________________________________________________________
RootGM::Tubs::Tubs(TGeoTube* tubs)
  : BaseVGM::VTubs(),
    fTubs(tubs)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fTubs); 
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
