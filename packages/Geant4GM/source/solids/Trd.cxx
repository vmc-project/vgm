// $Id$
//
// Class Trd
// ---------------
// VGM implementation for Geant4 trd solid.
// If reflected, the parameters are changed as follows:
//    hx1, hy1  -->  hx2', hy2'
//    hx2, hy2  -->  hx1', hy1'
//    hz           -->  hz' 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Trd.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Trd::Trd(const std::string& name, 
                   double hx1, double hx2, double hy1, double hy2, double hz)
  : BaseVGM::VTrd(),
    fIsReflected(false),
    fTrd(new G4Trd(name, hx1, hx2, hy1, hy2, hz))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fTrd); 
}


//_____________________________________________________________________________
Geant4GM::Trd::Trd(G4Trd* trd, 
                   G4ReflectedSolid* reflTrd)
  : BaseVGM::VTrd(),
    fIsReflected(false),
    fTrd(trd)
{    
  if (reflTrd) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTrd);
  }   
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, trd); 
}

//_____________________________________________________________________________
Geant4GM::Trd::~Trd() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Trd::Name() const
{
  return fTrd->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Trd::XHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrd->GetXHalfLength1();
  else  
    return fTrd->GetXHalfLength2();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::XHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrd->GetXHalfLength2();
  else  
    return fTrd->GetXHalfLength1();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::YHalfLengthMinusZ() const
{
  if (!fIsReflected)
    return fTrd->GetYHalfLength1();
  else  
    return fTrd->GetYHalfLength2();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::YHalfLengthPlusZ() const
{
  if (!fIsReflected)
    return fTrd->GetYHalfLength2();
  else  
    return fTrd->GetYHalfLength1();
}  

//_____________________________________________________________________________
double Geant4GM::Trd::ZHalfLength() const
{
  return fTrd->GetZHalfLength();
}  


