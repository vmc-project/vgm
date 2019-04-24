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
// VGM::IIsotope output stream
// ----------------------------
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IIsotope.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IIsotope& isotope)
{
  out << "Isotope: "
      << "\"" << isotope.Name() << "\"  "
      << "  Z = " << isotope.Z() << "  N = " << isotope.N()
      << "  A = " << isotope.A() << " g/mole";

  return out;
}
