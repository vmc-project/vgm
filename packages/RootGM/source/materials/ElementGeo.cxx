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
// Class ElementGeo
// -----------------
// VGM implementations for Root element using TGeoElement.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <math.h>

#include "TGeoElement.h"
#include "TGeoManager.h"

#include "RootGM/materials/ElementGeo.h"
#include "RootGM/common/Units.h"

//_____________________________________________________________________________
RootGM::ElementGeo::ElementGeo(TGeoElement* geoElement) 
  : VGM::IElement(),
    fElement(geoElement)    			       			  
{
/// Standard constructor to define element from TGeoElement 
/// \param geoElement  TGeoElement

}
			   
//_____________________________________________________________________________
RootGM::ElementGeo::~ElementGeo() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::ElementGeo::Name() const
{
  return fElement->GetTitle();
}  

//_____________________________________________________________________________
std::string RootGM::ElementGeo::Symbol() const
{
  return fElement->GetName();
}  

//_____________________________________________________________________________
double  RootGM::ElementGeo::Z() const    
{
  return fElement->Z();
}

//_____________________________________________________________________________
double  RootGM::ElementGeo::N() const    
{
  return fElement->A();
}

//_____________________________________________________________________________
double  RootGM::ElementGeo::A() const    
{
  return fElement->A() * RootGM::Units::AtomicWeight();
}

//_____________________________________________________________________________
int RootGM::ElementGeo::NofIsotopes() const 
{
  return 0;
}

//_____________________________________________________________________________
VGM::IIsotope*  RootGM::ElementGeo::Isotope(int /*i*/) const
{
  std::cerr << "    RootGM::Element::Isotope: " << std::endl;
  std::cerr << "    Element has no istopes defined." << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);

  return 0;
}  

//_____________________________________________________________________________
double  RootGM::ElementGeo::RelAbundance(int /*i*/) const 
{
  std::cerr << "    RootGM::Element::Isotope: " << std::endl;
  std::cerr << "    Element has no istopes defined." << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);

  return 0;
}  


