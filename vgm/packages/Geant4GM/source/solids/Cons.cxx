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

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Cons.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Cons::Cons(const std::string& name, 
                     double rin1, double rout1, double rin2, double rout2,
	             double hz, double sphi, double dphi)
  : BaseVGM::VCons(),
    fIsReflected(false),
    fCons( new G4Cons(name, 
                      rin1  / ClhepVGM::Units::Length(), 
		      rout1 / ClhepVGM::Units::Length(), 
		      rin2  / ClhepVGM::Units::Length(), 
		      rout2 / ClhepVGM::Units::Length(), 
		      hz    / ClhepVGM::Units::Length(), 
		      sphi  / ClhepVGM::Units::Angle(), 
		      dphi  / ClhepVGM::Units::Angle()))
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
    return fCons->GetInnerRadiusMinusZ() * ClhepVGM::Units::Length();
  else  
    return fCons->GetInnerRadiusPlusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::OuterRadiusMinusZ() const
{
  if (!fIsReflected)
    return fCons->GetOuterRadiusMinusZ() * ClhepVGM::Units::Length();
  else  
    return fCons->GetOuterRadiusPlusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::InnerRadiusPlusZ() const
{
  if (!fIsReflected)
    return fCons->GetInnerRadiusPlusZ() * ClhepVGM::Units::Length();
  else  
    return fCons->GetInnerRadiusMinusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::OuterRadiusPlusZ() const
{
  if (!fIsReflected)
    return fCons->GetOuterRadiusPlusZ() * ClhepVGM::Units::Length();
  else  
    return fCons->GetOuterRadiusMinusZ() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::ZHalfLength() const
{
  return fCons->GetZHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::StartPhi() const
{
  return fCons->GetStartPhiAngle() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Cons::DeltaPhi() const
{
  return fCons->GetDeltaPhiAngle() * ClhepVGM::Units::Angle();
}  
