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

#include "Geant4GM/solids/Para.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Para::Para(const std::string& name,
                     double dx, double dy, double dz,
	             double alpha, double theta, double phi)
  : BaseVGM::VPara(),
    fIsReflected(false),
    fPara(new G4Para(name, dx, dy, dz, alpha, theta, phi))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fPara); 
}


//_____________________________________________________________________________
Geant4GM::Para::Para(G4Para* para, 
                     G4ReflectedSolid* reflPara)
  : BaseVGM::VPara(),
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
  return fPara->GetXHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Para::YHalfLength() const
{
  return fPara->GetYHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Para::ZHalfLength() const
{
  return fPara->GetZHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Para::Alpha() const
{
  return atan(fPara->GetTanAlpha());
}  

//_____________________________________________________________________________
double Geant4GM::Para::Theta() const
{
  if (!fIsReflected)
    return fPara->GetSymAxis().theta();
  else
    return M_PI - fPara->GetSymAxis().theta();
}  

//_____________________________________________________________________________
double Geant4GM::Para::Phi() const
{
  return fPara->GetSymAxis().phi();
}  


