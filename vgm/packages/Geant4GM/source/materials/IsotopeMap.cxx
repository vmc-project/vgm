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
// Class IsotopeMap
// ------------------
// The map between VGM and Geant4 isotopes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/materials/IsotopeMap.h"

Geant4GM::IsotopeMap*  Geant4GM::IsotopeMap::fgInstance = 0;

//_____________________________________________________________________________
Geant4GM::IsotopeMap* 
Geant4GM::IsotopeMap::Instance()
{ 
/// Singleton access function.

  if (!fgInstance) new IsotopeMap();
  
  return fgInstance;
}  

//_____________________________________________________________________________
Geant4GM::IsotopeMap::IsotopeMap()
  : fG4Isotopes(),
    fVgmIsotopes()
{
/// Standard default constructor
  
  fgInstance = this;
}

//_____________________________________________________________________________
Geant4GM::IsotopeMap::IsotopeMap(const IsotopeMap&)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::IsotopeMap::~IsotopeMap() 
{
//
  fgInstance = 0;
}    


//
// public methods
//

//_____________________________________________________________________________
void  Geant4GM::IsotopeMap::AddIsotope(VGM::IIsotope* iIsotope, 
                                       G4Isotope* g4Isotope)
{
/// Add the specified pair in the map

  fG4Isotopes[iIsotope] = g4Isotope;
  fVgmIsotopes[g4Isotope] = iIsotope;
}  

//_____________________________________________________________________________
void  Geant4GM::IsotopeMap::Print() const
{
/// Prints all Isotopes in the map

  std::cout << "Geant4 Isotopes Map: " << std::endl; 

  int counter = 0;
  G4IsotopeMapCIterator i;
  for (i = fG4Isotopes.begin(); i != fG4Isotopes.end(); i++) {
    VGM::IIsotope* iIsotope = (*i).first;
    G4Isotope* g4Isotope = (*i).second;
    
    std::cout << "   "
              << counter++ << "th entry:" 
	      << "  vgmIsotope " << iIsotope << " " << iIsotope->Name()
              << "  g4Isotope " << g4Isotope << " " << g4Isotope->GetName()
	      << std::endl;
  }
}  	       

//_____________________________________________________________________________
G4Isotope* 
Geant4GM::IsotopeMap::GetIsotope(VGM::IIsotope* iIsotope) const
{
/// Find the G4 Isotope corresponding to a specified VGM Isotope

  G4IsotopeMapCIterator i = fG4Isotopes.find(iIsotope);
  if (i != fG4Isotopes.end()) 
    return (*i).second;
  else                 
    return 0;
}

//_____________________________________________________________________________
VGM::IIsotope* 
Geant4GM::IsotopeMap::GetIsotope(G4Isotope* Isotope) const
{
/// Find the VGM Isotope corresponding to a specified G4 Isotope

  VgmIsotopeMapCIterator i = fVgmIsotopes.find(Isotope);
  if (i != fVgmIsotopes.end()) 
    return (*i).second;
  else                 
    return 0;
}
