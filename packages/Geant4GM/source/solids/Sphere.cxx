// $Id$
//
// Class Sphere
// ---------------
// VGM implementation for Geant4 tubs solid.
// If reflected, the parameters are changed as follows:
//    rin, rout  --> rin', rout'
//    sphi, dphi --> sphi', dphi' 
//    stheta     --> PI - stheta' 
//    dtheta     --> dtheta'
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Sphere.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Sphere::Sphere(const std::string& name, 
                         double rin, double rout, double sphi, double dphi, 
	                 double stheta, double dtheta)
  : BaseVGM::VSphere(),
    fIsReflected(false),
    fSphere(new G4Sphere(name, rin, rout, sphi, dphi, stheta, dtheta))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fSphere); 
}


//_____________________________________________________________________________
Geant4GM::Sphere::Sphere(G4Sphere* sphere, 
                         G4ReflectedSolid* reflSphere)
  : BaseVGM::VSphere(),
    fIsReflected(false),
    fSphere(sphere)
{    
  if (reflSphere) { 
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflSphere);
  }   
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, sphere); 
}

//_____________________________________________________________________________
Geant4GM::Sphere::~Sphere() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Sphere::Name() const
{
  return fSphere->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Sphere::InnerRadius() const
{
  return fSphere->GetInsideRadius();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::OuterRadius() const
{
  return fSphere->GetOuterRadius();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::StartPhi() const
{
  return fSphere->GetStartPhiAngle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::DeltaPhi() const
{
  return fSphere->GetDeltaPhiAngle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::StartTheta() const
{
  if (!fIsReflected)
    return fSphere->GetStartThetaAngle();
  else   
    return M_PI - fSphere->GetDeltaThetaAngle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::DeltaTheta() const
{
  return fSphere->GetDeltaThetaAngle();
}  
