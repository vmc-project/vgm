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
// Class VTrap
// ---------------
// The ABC for trap solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VTrap.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITrap& trap)
{
  const VGM::ISolid& trapSolid = trap;
  out << trapSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VTrap::VTrap()
  : VGM::ITrap()
{
/// Default constructor
}


//_____________________________________________________________________________
BaseVGM::VTrap::~VTrap() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTrap::Put(std::ostream& out) const
{
  out << "  hz = "     << ZHalfLength()                << "mm"
      << "  theta = "  << Theta()                      << "deg"
      << "  phi = "    << Phi()                        << "deg"
      << "  hy1 = "    << YHalfLengthMinusZ()          << "mm"
      << "  hx1 = "    << XHalfLengthMinusZMinusY()    << "mm"
      << "  hx2 = "    << XHalfLengthMinusZPlusY()     << "mm"
      << "  alpha1 = " << AlphaMinusZ()                << "deg"
      << "  hy2 = "    << YHalfLengthPlusZ()           << "mm"
      << "  hx3 = "    << XHalfLengthPlusZMinusY()     << "mm"
      << "  hx4 = "    << XHalfLengthPlusZPlusY()      << "mm"
      << "  alpha2 = " << AlphaPlusZ()                 << "deg";
  return out;
}

