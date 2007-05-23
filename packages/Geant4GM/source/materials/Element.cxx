// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

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
#include "Geant4GM/materials/Isotope.h"
#include "Geant4GM/materials/IsotopeMap.h"

//_____________________________________________________________________________
Geant4GM::Element::Element(const std::string& name, 
                           const std::string& symbol,      
                           double z, double a) 
  : VGM::IElement(),
    fElement( new G4Element(name, symbol, z, 
                            a / ClhepVGM::Units::AtomicWeight()) )    			       			  
{
/// Standard constructor to define element from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol its symbol
/// \param z the effective atomic number
/// \param a the effective mass of a mole in g/mole 

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
Geant4GM::Element::Element(const std::string& name, 
                           const std::string& symbol,      
                           const VGM::IsotopeVector& isotopes,
                           const VGM::RelAbundanceVector& relAbundances) 
  : VGM::IElement(),
    fElement(0)    			       			  
{
/// Standard constructor to define element from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol  its symbol
/// \param isotopes  the vector if isotopes
/// \param relAbundances  the vector of relative abundances of isotopes

  if ( ! isotopes.size() ) {
    std::cerr << "    Geant4GM::Element::Element: " << std::endl; 
    std::cerr << "    No isotopes defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (isotopes.size() != relAbundances.size()) {
    std::cerr << "    Geant4GM::Element::Element: " << std::endl; 
    std::cerr << "    Isotopes size and relAbundances size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  // Create element
  fElement = new G4Element(name, symbol, isotopes.size());
  
  // Add isotopes
  for ( unsigned int i=0; i<isotopes.size(); i++ ) {
    G4Isotope* g4Isotope 
      = IsotopeMap::Instance()->GetIsotope(isotopes[i]);
    fElement->AddIsotope(g4Isotope, relAbundances[i]);    
  }

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
Geant4GM::Element::Element(G4Element* element)
  : VGM::IElement(),
    fElement(element)
{
/// Standard constructor to define element from the G4 object

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
Geant4GM::Element::Element() 
  : VGM::IElement() 
{
/// Protected default constructor
}  

//_____________________________________________________________________________
Geant4GM::Element::Element(const Element& rhs) 
  : VGM::IElement(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Element::~Element() {
//
}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::Element::CheckIndex(int i) const
{
  if ( i < 0 || i >= NofIsotopes()) {  
    std::cerr << "    Geant4GM::Element::CheckIndex: " << std::endl;
    std::cerr << "    Index of isotope outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
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

//_____________________________________________________________________________
int Geant4GM::Element::NofIsotopes() const 
{
  return fElement->GetNumberOfIsotopes();
}

//_____________________________________________________________________________
VGM::IIsotope*  Geant4GM::Element::Isotope(int i) const
{
  CheckIndex(i);

  const G4Isotope* g4Isotope = fElement->GetIsotope(i);
  return IsotopeMap::Instance()->GetIsotope(const_cast<G4Isotope*>(g4Isotope));
}  

//_____________________________________________________________________________
double  Geant4GM::Element::RelAbundance(int i) const 
{
  CheckIndex(i);

  return fElement->GetRelativeAbundanceVector()[i];
}  



