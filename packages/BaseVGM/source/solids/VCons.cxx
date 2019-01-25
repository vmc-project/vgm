// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VCons
// ---------------
// The ABC for cons solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VCons.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ICons& cons)
{
  const VGM::ISolid& consSolid = cons;
  out << consSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VCons::VCons()
  : VGM::ICons()
{
/// Default constructor
}


//_____________________________________________________________________________
BaseVGM::VCons::~VCons() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VCons::Put(std::ostream& out) const
{
  out << "  rin1 = "  << InnerRadiusMinusZ() << "mm"
      << "  rout1 = " << OuterRadiusMinusZ() << "mm"
      << "  rin2 = "  << InnerRadiusPlusZ()  << "mm"
      << "  rout2 = " << OuterRadiusPlusZ()  << "mm"
      << "  hz = "    << ZHalfLength()       << "mm"
      << "  sphi = "  << StartPhi()          << "deg"
      << "  dphi = "  << DeltaPhi()          << "deg";
  return out;
}

