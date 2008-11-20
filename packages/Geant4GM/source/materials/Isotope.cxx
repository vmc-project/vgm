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
// Class Isotope
// ---------------
// VGM implementation for Geant4 isotope.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/materials/Isotope.h"
#include "Geant4GM/materials/IsotopeMap.h"

#include "G4Isotope.hh"

//_____________________________________________________________________________
Geant4GM::Isotope::Isotope(const std::string& name, 
                           int z, int n, double a) 
  : VGM::IIsotope(),
    fIsotope( new G4Isotope(name, z, n, 
                            a / ClhepVGM::Units::AtomicWeight()) )    			       			  
{
/// Standard constructor to define Isotope from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param z the atomic number
/// \param n the number of nucleons
/// \param a the mass of a mole in g/mole 

  // Register Isotope in the map
  IsotopeMap::Instance()->AddIsotope(this, fIsotope); 
}
			   
//_____________________________________________________________________________
Geant4GM::Isotope::Isotope(G4Isotope* Isotope)
  : VGM::IIsotope(),
    fIsotope(Isotope)
{
/// Standard constructor to define Isotope from the G4 object

  // Register Isotope in the map
  IsotopeMap::Instance()->AddIsotope(this, fIsotope); 
}
			   
//_____________________________________________________________________________
Geant4GM::Isotope::Isotope() 
  : VGM::IIsotope() 
{
/// Protected default constructor
}  

//_____________________________________________________________________________
Geant4GM::Isotope::Isotope(const Isotope& rhs) 
  : VGM::IIsotope(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Isotope::~Isotope() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string Geant4GM::Isotope::Name() const
{
  return fIsotope->GetName();
}  

//_____________________________________________________________________________
int  Geant4GM::Isotope::Z() const    
{
  return fIsotope->GetZ();
}

//_____________________________________________________________________________
int  Geant4GM::Isotope::N() const    
{
  return fIsotope->GetN();
}

//_____________________________________________________________________________
double  Geant4GM::Isotope::A() const    
{
  return fIsotope->GetA() * ClhepVGM::Units::AtomicWeight();
}

