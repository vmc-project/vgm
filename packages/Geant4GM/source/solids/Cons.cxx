// $Id$
//
// Class Cons
// ---------------
// VGM implementation for Geant4 cons solid.
// If reflected, the parameters are changed as follows:
//    rin1, rout1  -->  rin2', rout2'
//    rin2, rout2  -->  rin1', rout1'
//    hz           -->  hz' 
//    sphi, dphi   -->  sphi', dphi' 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Cons.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Cons::Cons(const std::string& name, 
                     double rin1, double rout1, double rin2, double rout2,
	             double hz, double sphi, double dphi)
  : BaseVGM::VCons(),
    fIsReflected(false),
    fCons(new G4Cons(name, rin1, rout1, rin2, rout2, hz, sphi, dphi))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fCons); 
}


//_____________________________________________________________________________
Geant4GM::Cons::Cons(G4Cons* cons, 
                     G4ReflectedSolid* reflCons)
  : BaseVGM::VCons(),
    fIsReflected(false),
    fCons(cons)
{    
  if (reflCons) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflCons); 
  }  
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, cons); 
      
}

//_____________________________________________________________________________
Geant4GM::Cons::~Cons() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Cons::Name() const
{
  return fCons->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Cons::InnerRadiusMinusZ() const
{
  if (!fIsReflected)
    return fCons->GetInnerRadiusMinusZ();
  else  
    return fCons->GetInnerRadiusPlusZ();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::OuterRadiusMinusZ() const
{
  if (!fIsReflected)
    return fCons->GetOuterRadiusMinusZ();
  else  
    return fCons->GetOuterRadiusPlusZ();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::InnerRadiusPlusZ() const
{
  if (!fIsReflected)
    return fCons->GetInnerRadiusPlusZ();
  else  
    return fCons->GetInnerRadiusMinusZ();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::OuterRadiusPlusZ() const
{
  if (!fIsReflected)
    return fCons->GetOuterRadiusPlusZ();
  else  
    return fCons->GetOuterRadiusMinusZ();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::ZHalfLength() const
{
  return fCons->GetZHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::StartPhi() const
{
  return fCons->GetStartPhiAngle();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::DeltaPhi() const
{
  return fCons->GetDeltaPhiAngle();
}  
