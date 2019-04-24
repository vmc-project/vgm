// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2010 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class IsotopeMap
// ------------------
// The map between VGM and Root isotopes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IIsotope.h"

#include "RootGM/materials/IsotopeMap.h"

#include "TGeoElement.h"

RootGM::IsotopeMap* RootGM::IsotopeMap::fgInstance = 0;

//_____________________________________________________________________________
RootGM::IsotopeMap* RootGM::IsotopeMap::Instance()
{
  /// Singleton access function.

  if (!fgInstance) new IsotopeMap();

  return fgInstance;
}

//_____________________________________________________________________________
RootGM::IsotopeMap::IsotopeMap() : fTGeoIsotopes(), fVgmIsotopes()
{
  /// Standard default constructor

  fgInstance = this;
}

//_____________________________________________________________________________
RootGM::IsotopeMap::IsotopeMap(const IsotopeMap&)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::IsotopeMap::~IsotopeMap()
{
  //
  fgInstance = 0;
}

//
// public methods
//

//_____________________________________________________________________________
void RootGM::IsotopeMap::AddIsotope(
  VGM::IIsotope* iIsotope, TGeoIsotope* tgeoIsotope)
{
  /// Add the specified pair in the map

  fTGeoIsotopes[iIsotope] = tgeoIsotope;
  fVgmIsotopes[tgeoIsotope] = iIsotope;
}

//_____________________________________________________________________________
void RootGM::IsotopeMap::Print() const
{
  /// Print all Isotopes in the map

  std::cout << "Geant4 Isotopes Map: " << std::endl;

  int counter = 0;
  TGeoIsotopeMapCIterator i;
  for (i = fTGeoIsotopes.begin(); i != fTGeoIsotopes.end(); i++) {
    VGM::IIsotope* iIsotope = (*i).first;
    TGeoIsotope* tgeoIsotope = (*i).second;

    std::cout << "   " << counter++ << "th entry:"
              << "  vgmIsotope " << iIsotope << " " << iIsotope->Name()
              << "  tgeoIsotope " << tgeoIsotope << " "
              << tgeoIsotope->GetName() << std::endl;
  }
}

//_____________________________________________________________________________
TGeoIsotope* RootGM::IsotopeMap::GetIsotope(VGM::IIsotope* iIsotope) const
{
  /// Find the Root Isotope corresponding to a specified VGM Isotope

  TGeoIsotopeMapCIterator i = fTGeoIsotopes.find(iIsotope);
  if (i != fTGeoIsotopes.end())
    return (*i).second;
  else
    return 0;
}

//_____________________________________________________________________________
VGM::IIsotope* RootGM::IsotopeMap::GetIsotope(TGeoIsotope* tgeoIsotope) const
{
  /// Find the VGM Isotope corresponding to a specified Root Isotope

  VgmIsotopeMapCIterator i = fVgmIsotopes.find(tgeoIsotope);
  if (i != fVgmIsotopes.end())
    return (*i).second;
  else
    return 0;
}
