// $Id$
//
// Class Element
// ---------------
// VGM implementations for Root element.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <math.h>

#include "TGeoElement.h"
#include "TGeoElement.h"

#include "RootGM/materials/Element.h"
#include "RootGM/materials/ElementMap.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::Element::Element(const std::string& name, 
                         const std::string& symbol,      
                         double z, double a) 
  : VGM::IElement(),
    fElement(0)    			       			  
{
/// Standard constructor to define element from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol its symbol
/// \param z the effective atomic number
/// \param a the effective mass of a mole in g/mole 

  // Use Root element table to create Root element
  // (to get it registered here)
  TGeoElementTable::Instance()
    ->AddElement(symbol.data(),
                 name.data(),
		 (int)z,
		 a /RootGM::Units::AtomicWeight()); 
  fElement = TGeoElementTable::Instance()->FindElement(symbol.data());

  // Register element in the map
  RootGM::ElementMap::Instance()->AddElement(this, fElement); 
}
			   
//_____________________________________________________________________________
RootGM::Element::Element(TGeoElement* element)
  : VGM::IElement(),
    fElement(element)
{
/// Standard constructor to define element from the Root object

  // Register element in the map
  RootGM::ElementMap::Instance()->AddElement(this, fElement); 
}
			   
			   
//_____________________________________________________________________________
RootGM::Element::Element() 
  : VGM::IElement() 
{
/// Protected default constructor
}  

//_____________________________________________________________________________
RootGM::Element::Element(const Element& rhs) 
  : VGM::IElement(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Element::~Element() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Element::Name() const
{
  return fElement->GetTitle();
}  

//_____________________________________________________________________________
std::string RootGM::Element::Symbol() const
{
  return fElement->GetName();
}  

//_____________________________________________________________________________
double  RootGM::Element::Z() const    
{
  return fElement->Z();
}

//_____________________________________________________________________________
double  RootGM::Element::N() const    
{
  return fElement->A();
}

//_____________________________________________________________________________
double  RootGM::Element::A() const    
{
  return fElement->A() * RootGM::Units::AtomicWeight();
}

