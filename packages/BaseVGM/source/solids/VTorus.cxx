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
// Class VTorus
// ---------------
// The ABC for torus solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VTorus.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITorus& torus)
{
  const VGM::ISolid& torusSolid = torus;
  out << torusSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VTorus::VTorus() : VGM::ITorus()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VTorus::~VTorus()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTorus::Put(std::ostream& out) const
{
  out << "  rin = " << InnerRadius() << "mm"
      << "  rout = " << OuterRadius() << "mm"
      << "  rtor = " << AxialRadius() << "mm"
      << "  sphi = " << StartPhi() << "deg"
      << "  dphi = " << DeltaPhi() << "deg";
  return out;
}
