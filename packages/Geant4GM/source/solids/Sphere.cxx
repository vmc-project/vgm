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

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Sphere.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Sphere::Sphere(const std::string& name, 
                         double rin, double rout, double sphi, double dphi, 
	                 double stheta, double dtheta)
  : BaseVGM::VSphere(),
    fIsReflected(false),
    fSphere( new G4Sphere(name, 
                          rin    / ClhepVGM::Units::Length(), 
			  rout   / ClhepVGM::Units::Length(), 
			  sphi   / ClhepVGM::Units::Angle(), 
			  dphi   / ClhepVGM::Units::Angle(), 
			  stheta / ClhepVGM::Units::Angle(), 
			  dtheta / ClhepVGM::Units::Angle()))
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
  return fSphere->GetInsideRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::OuterRadius() const
{
  return fSphere->GetOuterRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::StartPhi() const
{
  return fSphere->GetStartPhiAngle() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::DeltaPhi() const
{
  return fSphere->GetDeltaPhiAngle() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::StartTheta() const
{
  if (!fIsReflected)
    return fSphere->GetStartThetaAngle() * ClhepVGM::Units::Angle();
  else   
    return (M_PI - fSphere->GetDeltaThetaAngle()) * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Sphere::DeltaTheta() const
{
  return fSphere->GetDeltaThetaAngle() * ClhepVGM::Units::Angle();
}  
