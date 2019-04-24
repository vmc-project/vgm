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
#include "RootGM/materials/IsotopeMap.h"

#include "TGeoElement.h"

#include <math.h>

//_____________________________________________________________________________
RootGM::Isotope::Isotope(const std::string& name, int z, int n, double a)
  : VGM::IIsotope(),
    fIsotope(
      new TGeoIsotope(name.data(), z, n, a / RootGM::Units::AtomicWeight()))
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
RootGM::Isotope::Isotope(TGeoIsotope* tgeoIsotope)
  : VGM::IIsotope(), fIsotope(tgeoIsotope)
{
  /// Standard constructor to define Isotope from the G4 object

  // Register Isotope in the map
  IsotopeMap::Instance()->AddIsotope(this, fIsotope);
}

//_____________________________________________________________________________
RootGM::Isotope::~Isotope()
{
  //
}

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Isotope::Name() const { return fIsotope->GetName(); }

//_____________________________________________________________________________
int RootGM::Isotope::Z() const { return fIsotope->GetZ(); }

//_____________________________________________________________________________
int RootGM::Isotope::N() const { return fIsotope->GetN(); }

//_____________________________________________________________________________
double RootGM::Isotope::A() const
{
  return fIsotope->GetA() * RootGM::Units::AtomicWeight();
}
