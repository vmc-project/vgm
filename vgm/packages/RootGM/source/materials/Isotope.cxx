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
// Class Isotope
// ---------------
// VGM implementations for Root Isotope.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/Isotope.h"
#include "RootGM/common/Units.h"

#include <math.h>

//_____________________________________________________________________________
RootGM::Isotope::Isotope(const std::string& name,
                         int z, int n, double a) 
  : VGM::IIsotope(),
    fName(name),
    fZ(z),
    fN(n),
    fA(a)    			       			  
{
/// Standard constructor to define Isotope from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol its symbol
/// \param z the effective atomic number
/// \param a the effective mass of a mole in g/mole 

}
			   
//_____________________________________________________________________________
RootGM::Isotope::Isotope(const Isotope& rhs) 
  : VGM::IIsotope(rhs), 
    fName(rhs.fName),
    fZ(rhs.fZ),
    fN(rhs.fN),
    fA(rhs.fA)    			       			  
{
/// Copy constructor
}

//_____________________________________________________________________________
RootGM::Isotope::Isotope() 
  : VGM::IIsotope(), 
    fName("Undefined"),
    fZ(0),
    fN(0),
    fA(0)    			       			  
{
/// Default constructor
}  

//_____________________________________________________________________________
RootGM::Isotope::~Isotope() {
//
}

//
// operators
//

//_____________________________________________________________________________
RootGM::Isotope& 
RootGM::Isotope::operator = (const Isotope& rhs) 
{
/// Assignment operator
 
  // check assignment to self
  if ( this == &rhs ) return *this;

  // assignment operator
  fName= rhs.fName;
  fZ = rhs.fZ;
  fN = rhs.fN;
  fA = rhs.fA;
  
  return *this; 
}  

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Isotope::Name() const
{
  return fName;
}  

//_____________________________________________________________________________
int  RootGM::Isotope::Z() const    
{
  return fZ;
}

//_____________________________________________________________________________
int  RootGM::Isotope::N() const    
{
  return fN;
}

//_____________________________________________________________________________
double  RootGM::Isotope::A() const    
{
  return fA * RootGM::Units::AtomicWeight();
}

