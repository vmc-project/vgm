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
// Class VMultiUnion
// --------------------
// The ABC for Boolean solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VMultiUnion.h"
#include "BaseVGM/common/utilities.h"

#include <math.h>

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IMultiUnion& boolean)
{
  const VGM::ISolid& MultiUnion = boolean;
  out << MultiUnion;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VMultiUnion::VMultiUnion() : VGM::IMultiUnion()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VMultiUnion::~VMultiUnion()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VMultiUnion::Put(std::ostream& out) const
{
  for (int i = 0; i < NofSolids(); ++i) {
    out << i << "th constituent = " << *ConstituentSolid(i) << std::endl
        << "  Displacement translation (object):  ( "
        << Transformation(i)[VGM::kDx] << ",  " << Transformation(i)[VGM::kDy]
        << ",  " << Transformation(i)[VGM::kDz] << ") mm " << std::endl
        << "  Displacement rotation (object):  ("
        << Transformation(i)[VGM::kAngleX] << ",  "
        << Transformation(i)[VGM::kAngleY] << ",  "
        << Transformation(i)[VGM::kAngleZ] << ") deg  ";
    if (Round(Transformation(i)[6]) == 0)
      out << "  no reflectionZ";
    else
      out << "  reflectionZ";
  }
  return out;
}
