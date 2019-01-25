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
// Class VDisplacedSolid
// --------------------
// The ABC for displaced solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"
#include "BaseVGM/solids/VDisplacedSolid.h"

#include <math.h>

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IDisplacedSolid& solid)
{
  const VGM::ISolid& displacedSolid = solid;
  out << displacedSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VDisplacedSolid::VDisplacedSolid()
  : VGM::IDisplacedSolid()
{
/// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VDisplacedSolid::~VDisplacedSolid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VDisplacedSolid::Put(std::ostream& out) const
{
  out << "  Const. = \"" << ConstituentSolid()->Name() << "\""
      << "  Displacement = ( "
      << Displacement()[VGM::kDx] << ", "
      << Displacement()[VGM::kDy]  << ", "
      << Displacement()[VGM::kDz]
      << ")mm ( "
      << Displacement()[VGM::kAngleX] << ", "
      << Displacement()[VGM::kAngleY] << ", "
      << Displacement()[VGM::kAngleZ]
      << ")deg ";

  if ( Round(Displacement()[6]) == 0 )
    out << "  noReflZ";
  else
    out << "  reflZ";

  return out;
}

