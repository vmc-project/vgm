// $Id$
//
// Class Trap
// ---------------
// VGM implementation for Geant4 trap solid.
// If reflected, the parameters are changed as follows:
//    dy1, dx1, dx2  -->  dy2', dx3', dx4'
//    alpha1         -->  alpha2'
//    dy2, dx3, dx4  -->  dy1', dx1', dx2'
//    alpha2         -->  alpha1'
//    hz             -->  hz' 
//    theta          -->  theta'
//    phi            -->  phi'
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Trap.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Trap::Trap(const std::string& name, 
                     double hz, double theta, double phi,
                     double dy1, double dx1, double dx2, double alpha1, 
                     double dy2, double dx3, double dx4, double alpha2)
  : BaseVGM::VTrap(),
    fIsReflected(false),
    fTrap(new G4Trap(name, hz, theta, phi,
                     dy1, dx1, dx2, alpha1, dy2, dx3, dx4, alpha2))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fTrap); 
}


//_____________________________________________________________________________
Geant4GM::Trap::Trap(G4Trap* trap, 
                     G4ReflectedSolid* reflTrap)
  : BaseVGM::VTrap(),
    fIsReflected(false),
    fTrap(trap)
{    
  if (reflTrap) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTrap);
  }  
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, trap);
}

//_____________________________________________________________________________
Geant4GM::Trap::~Trap() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Trap::Name() const
{
  return fTrap->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Trap::ZHalfLength() const
{
  return fTrap->GetZHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::Theta() const
{
  //std::cout << "inc1 in VMC: " 
  //          << atan(fTrap->GetSymAxis().x()/fTrap->GetSymAxis().z()) / deg 
  //	      << std::endl; 
  if (!fIsReflected)
    return fTrap->GetSymAxis().theta();
  else   
    return - fTrap->GetSymAxis().theta();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::Phi() const
{
  //std::cout << "inc1 in VMC: " 
  //          << atan(fTrap->GetSymAxis().y()/fTrap->GetSymAxis().z()) / deg 
  //	      << std::endl; 
  if (!fIsReflected)
    return fTrap->GetSymAxis().phi();
  else  
    return -fTrap->GetSymAxis().phi();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::YHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrap->GetYHalfLength1();
  else   
    return fTrap->GetYHalfLength2();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthMinusZMinusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength1();
  else   
    return fTrap->GetXHalfLength3();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthMinusZPlusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength2();
  else   
    return fTrap->GetXHalfLength4();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::AlphaMinusZ() const
{
  if (!fIsReflected)
    return atan(fTrap->GetTanAlpha1());
  else   
    return atan(fTrap->GetTanAlpha2());
}  

//_____________________________________________________________________________
double Geant4GM::Trap::YHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrap->GetYHalfLength2();
  else   
    return fTrap->GetYHalfLength1();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthPlusZMinusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength3();
  else   
    return fTrap->GetXHalfLength1();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthPlusZPlusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength4();
  else   
    return fTrap->GetXHalfLength2();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::AlphaPlusZ() const
{
  if (!fIsReflected)
    return atan(fTrap->GetTanAlpha2());
  else   
    return atan(fTrap->GetTanAlpha1());
}  

