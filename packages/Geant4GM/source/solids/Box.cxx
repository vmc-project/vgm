// $Id$
//
// Class Box
// ---------------
// VGM implementation for Geant4 box solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Box.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Box::Box(const std::string& name, 
                   double hx, double hy, double hz)
  : BaseVGM::VBox(),
    fBox(new G4Box(name, hx, hy, hz))
{
// 
  Geant4GM::SolidMap::Instance()->AddSolid(this, fBox); 
}


//_____________________________________________________________________________
Geant4GM::Box::Box(G4Box* box, 
                   G4ReflectedSolid* reflBox)
  : BaseVGM::VBox(),
    fBox(box)
{    
  if (reflBox)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflBox);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, box);
}

//_____________________________________________________________________________
Geant4GM::Box::~Box() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Box::Name() const
{
  return fBox->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Box::XHalfLength() const
{
  return fBox->GetXHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Box::YHalfLength() const
{
  return fBox->GetYHalfLength();
}  

//_____________________________________________________________________________
double Geant4GM::Box::ZHalfLength() const
{
  return fBox->GetZHalfLength();
}  


