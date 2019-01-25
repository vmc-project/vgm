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
// Class Element
// ---------------
// VGM implementations for Root element which is not represented via TGeoElement
/// object in Root geometry.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/ElementNonGeo.h"
#include "RootGM/materials/Isotope.h"
#include "RootGM/common/Units.h"

#include "TGeoElement.h"
#include "TGeoManager.h"

#include <math.h>
#include <cstdlib>

//_____________________________________________________________________________
RootGM::ElementNonGeo::ElementNonGeo(const std::string& name,
                         const std::string& symbol,
                         double z, double a)
  : VGM::IElement(),
    fName(name),
    fSymbol(symbol),
    fZ(z),
    fN(a),
    fA(a)
{
/// Standard constructor to define element from parameters
/// \param name its name
///	   (must be unique in the factory)
/// \param symbol its symbol
/// \param z the effective atomic number
/// \param a the effective mass of a mole in g/mole

}

//_____________________________________________________________________________
RootGM::ElementNonGeo::~ElementNonGeo() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::ElementNonGeo::Name() const
{
  return fName;
}

//_____________________________________________________________________________
std::string RootGM::ElementNonGeo::Symbol() const
{
  return fSymbol;
}

//_____________________________________________________________________________
double  RootGM::ElementNonGeo::Z() const
{
  return fZ;
}

//_____________________________________________________________________________
double  RootGM::ElementNonGeo::N() const
{
  return fN;
}

//_____________________________________________________________________________
double  RootGM::ElementNonGeo::A() const
{
  return fA * RootGM::Units::AtomicWeight();
}

//_____________________________________________________________________________
int RootGM::ElementNonGeo::NofIsotopes() const
{
  return 0;
}

//_____________________________________________________________________________
VGM::IIsotope*  RootGM::ElementNonGeo::Isotope(int /*i*/) const
{
  return 0;
}

//_____________________________________________________________________________
double  RootGM::ElementNonGeo::RelAbundance(int /*i*/) const
{
  return 0;
}

