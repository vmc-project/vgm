// $Id$
//
// Class Trap
// ---------------
// VGM implementation for Root trap solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Trap.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Trap::Trap(const std::string& name, 
                   double hz, double theta, double phi,
                   double dy1, double dx1, double dx2, double alpha1, 
                   double dy2, double dx3, double dx4, double alpha2 )
  : BaseVGM::VTrap(),
    fTrap(new TGeoTrap(name.data(), 
                       hz     / RootGM::Units::Length(), 
		       theta  / RootGM::Units::Angle(), 
		       phi    / RootGM::Units::Angle(),
                       dy1    / RootGM::Units::Length(), 
		       dx1    / RootGM::Units::Length(), 
		       dx2    / RootGM::Units::Length(), 
		       alpha1 / RootGM::Units::Angle(), 
		       dy2    / RootGM::Units::Length(), 
		       dx3    / RootGM::Units::Length(), 
		       dx4    / RootGM::Units::Length(), 
		       alpha2 / RootGM::Units::Angle()))
{
// 
  RootGM::SolidMap::Instance()->AddSolid(this, fTrap); 
}


//_____________________________________________________________________________
RootGM::Trap::Trap(TGeoTrap* trap)
  : BaseVGM::VTrap(),
    fTrap(trap)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fTrap); 
}

//_____________________________________________________________________________
RootGM::Trap::~Trap() {
//
}    

//_____________________________________________________________________________
std::string RootGM::Trap::Name() const
{
  return fTrap->GetName();
}  
  
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

