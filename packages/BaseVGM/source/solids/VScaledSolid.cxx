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
// Class VScaledSolid
// --------------------
// The ABC for Scaled solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"
#include "BaseVGM/solids/VScaledSolid.h"

#include <math.h>

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IScaledSolid& scaled)
{
  const VGM::ISolid& scaledSolid = scaled;
  out << scaledSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VScaledSolid::VScaledSolid()
  : VGM::IScaledSolid()
{
/// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VScaledSolid::~VScaledSolid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VScaledSolid::Put(std::ostream& out) const
{
  out << "  "
      << "  Constituent = " << *ConstituentSolid() << std:: endl
      << "  Scale (object):  ( "
      << Scale()[VGM::kDx] << ",  "
      << Scale()[VGM::kDy] << ",  "
      << Scale()[VGM::kDz] << ") " << std:: endl;

  return out;
}
