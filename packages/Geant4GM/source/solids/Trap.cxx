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

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Trap.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Trap::Trap(const std::string& name, 
                     double hz, double theta, double phi,
                     double dy1, double dx1, double dx2, double alpha1, 
                     double dy2, double dx3, double dx4, double alpha2)
  : VGM::ISolid(),
    VGM::ITrap(),
    BaseVGM::VTrap(),
    fIsReflected(false),
    fTrap(new G4Trap(name, 
                     hz     / ClhepVGM::Units::Length(), 
		     theta  / ClhepVGM::Units::Angle(), 
		     phi    / ClhepVGM::Units::Angle(),
                     dy1    / ClhepVGM::Units::Length(), 
		     dx1    / ClhepVGM::Units::Length(), 
		     dx2    / ClhepVGM::Units::Length(), 
		     alpha1 / ClhepVGM::Units::Angle(), 
		     dy2    / ClhepVGM::Units::Length(), 
		     dx3    / ClhepVGM::Units::Length(), 
		     dx4    / ClhepVGM::Units::Length(), 
		     alpha2 / ClhepVGM::Units::Angle()) )
{
/// Standard constructor to define trap from parameters
/// ( Note that of the 11 parameters described below, only 9 
///   are really independent)
/// \param hz half-length along the z axis in mm
/// \param theta polar angle of the line joining the centres
///	   of the faces at -hz and +hz in deg
/// \param phi azimuthal angle of the line joining the centres
///	   of the faces at -hz and +hz in deg
/// \param dy1 half-length along y of the face at -hz in mm
/// \param dx1 half-length along x of the side at -hy 
///	   of the face at -hz in mm
/// \param dx2 half-length along x of the side at +hy
///	   of the face at +hz in mm
/// \param alpha1  angle with respect to the y axis from the 
///	   centre of the side at -hy to the centre at +hy
///	   of the face at -hz
/// \param dy2 half-length along y of the face at +hz in mm
/// \param dx3 half-length along x of the side at -hy 
///	   of the face at +hz in mm
/// \param dx4 half-length along x of the side at +hy
///	   of the face at +hz in mm
/// \param alpha1  angle with respect to the y axis from the 
///	   centre of the side at -hy to the centre at +hy
///	   of the face at +hz


  Geant4GM::SolidMap::Instance()->AddSolid(this, fTrap); 
}


//_____________________________________________________________________________
Geant4GM::Trap::Trap(G4Trap* trap, 
                     G4ReflectedSolid* reflTrap)
  : VGM::ISolid(),
    VGM::ITrap(),
    BaseVGM::VTrap(),
    fIsReflected(false),
    fTrap(trap)
{    
/// Standard constructor to define trap from G4 object

  if (reflTrap) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTrap);
  }  
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, trap);
}

//_____________________________________________________________________________
Geant4GM::Trap::Trap() 
  : VGM::ISolid(),
    VGM::ITrap(),
    BaseVGM::VTrap() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Trap::Trap(const Trap& rhs) 
  : VGM::ISolid(rhs),
    VGM::ITrap(rhs),
    BaseVGM::VTrap(rhs) 
{
/// Protected copy constructor
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
  return fTrap->GetZHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::Theta() const
{
  //std::cout << "inc1 in VMC: " 
  //          << atan(fTrap->GetSymAxis().x()/fTrap->GetSymAxis().z()) / deg 
  //	      << std::endl; 
  if (!fIsReflected)
    return fTrap->GetSymAxis().theta() * ClhepVGM::Units::Angle();
  else   
    return - fTrap->GetSymAxis().theta() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::Phi() const
{
  //std::cout << "inc1 in VMC: " 
  //          << atan(fTrap->GetSymAxis().y()/fTrap->GetSymAxis().z()) / deg 
  //	      << std::endl; 
  if (!fIsReflected)
    return fTrap->GetSymAxis().phi() * ClhepVGM::Units::Angle();
  else  
    return -fTrap->GetSymAxis().phi() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::YHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrap->GetYHalfLength1() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetYHalfLength2() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthMinusZMinusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength1() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetXHalfLength3() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthMinusZPlusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength2() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetXHalfLength4() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::AlphaMinusZ() const
{
  if (!fIsReflected)
    return atan(fTrap->GetTanAlpha1()) * ClhepVGM::Units::Angle();
  else   
    return atan(fTrap->GetTanAlpha2()) * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::YHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrap->GetYHalfLength2() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetYHalfLength1() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthPlusZMinusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength3() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetXHalfLength1() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::XHalfLengthPlusZPlusY() const
{
  if (!fIsReflected)
    return fTrap->GetXHalfLength4() * ClhepVGM::Units::Length();
  else   
    return fTrap->GetXHalfLength2() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Trap::AlphaPlusZ() const
{
  if (!fIsReflected)
    return atan(fTrap->GetTanAlpha2()) * ClhepVGM::Units::Angle();
  else   
    return atan(fTrap->GetTanAlpha1()) * ClhepVGM::Units::Angle();
}  

