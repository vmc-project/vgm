// $Id$
//
// Class Element
// ---------------
// VGM implementation for Geant4 element.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4Element.hh"

#include "ClhepVGM/Units.h"

#include "Geant4GM/materials/Element.h"
#include "Geant4GM/materials/ElementMap.h"

//_____________________________________________________________________________
Geant4GM::Element::Element(const std::string& name, 
                           const std::string& symbol,      
                           double z, double a) 
  : VGM::IElement(),
    fElement( new G4Element(name, symbol, z, 
                            a / ClhepVGM::Units::AtomicWeight()) )    			       			  
{
  // Create element if 

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
Geant4GM::Element::Element(G4Element* element)
  : VGM::IElement(),
    fElement(element)
{
//
  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
Geant4GM::Element::~Element() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string Geant4GM::Element::Name() const
{
  return fElement->GetName();
}  

//_____________________________________________________________________________
std::string Geant4GM::Element::Symbol() const
{
  return fElement->GetSymbol();
}  

//_____________________________________________________________________________
double  Geant4GM::Element::Z() const    
{
  return fElement->GetZ();
}

//_____________________________________________________________________________
double  Geant4GM::Element::N() const    
{
  return fElement->GetN();
}

//_____________________________________________________________________________
double  Geant4GM::Element::A() const    
{
  return fElement->GetA() * ClhepVGM::Units::AtomicWeight();
}

