// $Id$
//
// Class Para
// ---------------
// VGM implementation for Geant4 para solid.
// If reflected, the parameters are changed as follows:
//    dx, dy, dz  -->  dx', dy', dz'
//    alpha -> alpha'
//    theta -> theta' = PI - theta
//    phi -> phi'
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Para.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Para::Para(const std::string& name,
                     double dx, double dy, double dz,
	             double alpha, double theta, double phi)
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara(),
    fIsReflected(false),
    fPara( new G4Para(name, 
                      dx    / ClhepVGM::Units::Length(), 
		      dy    / ClhepVGM::Units::Length(), 
		      dz    / ClhepVGM::Units::Length(), 
		      alpha / ClhepVGM::Units::Angle(), 
		      theta / ClhepVGM::Units::Angle(), 
		      phi   / ClhepVGM::Units::Angle()) )
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fPara); 
}


//_____________________________________________________________________________
Geant4GM::Para::Para(G4Para* para, 
                     G4ReflectedSolid* reflPara)
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara(),
    fIsReflected(false),
    fPara(para)
{    
  if (reflPara) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflPara);
  }
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, para); 
}

//_____________________________________________________________________________
Geant4GM::Para::Para() 
  : VGM::ISolid(),
    VGM::IPara(),
    BaseVGM::VPara() 
{
//
}

//_____________________________________________________________________________
Geant4GM::Para::Para(const Para& rhs) 
  : VGM::ISolid(rhs),
    VGM::IPara(rhs),
    BaseVGM::VPara(rhs) 
{
//
}

//_____________________________________________________________________________
Geant4GM::Para::~Para() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Para::Name() const
{
  return fPara->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Para::XHalfLength() const
{
  return fPara->GetXHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Para::YHalfLength() const
{
  return fPara->GetYHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Para::ZHalfLength() const
{
  return fPara->GetZHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Para::Alpha() const
{
  return atan(fPara->GetTanAlpha()) * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Para::Theta() const
{
  if (!fIsReflected)
    return fPara->GetSymAxis().theta() * ClhepVGM::Units::Angle();
  else
    return (M_PI - fPara->GetSymAxis().theta()) * ClhepVGM::Units::Angle();;
}  

//_____________________________________________________________________________
double Geant4GM::Para::Phi() const
{
  return fPara->GetSymAxis().phi() * ClhepVGM::Units::Angle();
}  


