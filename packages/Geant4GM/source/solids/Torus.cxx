// $Id$
//
// Class Torus
// ---------------
// VGM implementation for Geant4 torus solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Torus.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Torus::Torus(const std::string& name, 
                       double rin, double rout, double rax, 
		       double sphi, double dphi)
  : BaseVGM::VTorus(),
    fTorus( new G4Torus(name, 
                        rin  / ClhepVGM::Units::Length(), 
			rout / ClhepVGM::Units::Length(), 
			rax  / ClhepVGM::Units::Length(), 
			sphi / ClhepVGM::Units::Angle(), 
			dphi / ClhepVGM::Units::Angle()) )
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fTorus); 
}


//_____________________________________________________________________________
Geant4GM::Torus::Torus(G4Torus* torus, 
                       G4ReflectedSolid* reflTorus)
  : BaseVGM::VTorus(),
    fTorus(torus)
{    
  if (reflTorus)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTorus);
  else  
    Geant4GM::SolidMap::Instance()->AddSolid(this, torus);
}

//_____________________________________________________________________________
Geant4GM::Torus::~Torus() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Torus::Name() const
{
  return fTorus->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Torus::InnerRadius() const
{
  return fTorus->GetRmin() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::OuterRadius() const
{
  return fTorus->GetRmax() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::AxialRadius() const
{
  return fTorus->GetRtor() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::StartPhi() const
{
  return fTorus->GetSPhi() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Torus::DeltaPhi() const
{
  return fTorus->GetDPhi() * ClhepVGM::Units::Angle();
}  
