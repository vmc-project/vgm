// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Element
// ---------------
// VGM implementations for Root element.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/Element.h"
#include "RootGM/materials/ElementMap.h"
#include "RootGM/materials/Isotope.h"
#include "RootGM/materials/IsotopeMap.h"
#include "RootGM/common/Units.h"

#include "TGeoElement.h"
#include "TGeoManager.h"

#include <math.h>
#include <cstdlib>

//_____________________________________________________________________________
RootGM::Element::Element(const std::string& name, 
                         const std::string& symbol,      
                         double z, double a) 
  : VGM::IElement(),
    fElement( new TGeoElement(name.data(), symbol.data(), z, 
                              a / RootGM::Units::AtomicWeight()) )    			       			  
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
RootGM::Element::Element(const std::string& name, 
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
    std::cerr << "    RootGM::Element::Element: " << std::endl; 
    std::cerr << "    No isotopes defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (isotopes.size() != relAbundances.size()) {
    std::cerr << "    RootGM::Element::Element: " << std::endl; 
    std::cerr << "    Isotopes size and relAbundances size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
    
  // Create element
  fElement = new TGeoElement(name.data(), symbol.data(), isotopes.size());
  
  // Add isotopes
  for ( unsigned int i=0; i<isotopes.size(); i++ ) {
    TGeoIsotope* tgeoIsotope 
      = IsotopeMap::Instance()->GetIsotope(isotopes[i]);
    fElement->AddIsotope(tgeoIsotope, relAbundances[i]);    
  }

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
RootGM::Element::Element(TGeoElement* geoElement) 
  : VGM::IElement(),
    fElement(geoElement)    			       			  
{
/// Standard constructor to define element from TGeoElement 
/// \param geoElement  TGeoElement

  // Register element in the map
  ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
RootGM::Element::~Element() {
//
}

//
// private functions
//

//_____________________________________________________________________________
void RootGM::Element::CheckIndex(int i) const
{
  if ( i < 0 || i >= NofIsotopes()) {  
    std::cerr << "    RootGM::Element::CheckIndex: " << std::endl;
    std::cerr << "    Index of isotope outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Element::Name() const
{
  return fElement->GetName();
}  

//_____________________________________________________________________________
std::string RootGM::Element::Symbol() const
{
  return fElement->GetTitle();
}  

//_____________________________________________________________________________
double  RootGM::Element::Z() const    
{
  return fElement->Z();
}

//_____________________________________________________________________________
double  RootGM::Element::N() const    
{
  return fElement->N();
}

//_____________________________________________________________________________
double  RootGM::Element::A() const    
{
  return fElement->A() * RootGM::Units::AtomicWeight();
}

//_____________________________________________________________________________
int RootGM::Element::NofIsotopes() const 
{
  return fElement->GetNisotopes();
}

//_____________________________________________________________________________
VGM::IIsotope*  RootGM::Element::Isotope(int i) const
{
  CheckIndex(i);

  TGeoIsotope* tgeoIsotope = fElement->GetIsotope(i);
  return IsotopeMap::Instance()->GetIsotope(tgeoIsotope);
}  

//_____________________________________________________________________________
double  RootGM::Element::RelAbundance(int i) const 
{
  CheckIndex(i);

  return fElement->GetRelativeAbundance(i);
}  

