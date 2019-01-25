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
// Class VEllipsoid
// ---------------
// The interface to ellipsoid solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VEllipsoid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IEllipsoid& ellipsoid)
{
  const VGM::ISolid& ellipsoidSolid = ellipsoid;
  out << ellipsoidSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VEllipsoid::VEllipsoid()
  : VGM::IEllipsoid()
{
/// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VEllipsoid::~VEllipsoid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VEllipsoid::Put(std::ostream& out) const
{
  out << "  dx = " << XSemiAxis() << "mm"
      << "  dy = " << YSemiAxis() << "mm"
      << "  dz = " << ZSemiAxis() << "mm"
      << "  zBottomCut = " << ZBottomCut() << "mm"
      << "  ZTopCut = " << ZTopCut() << "mm";
  return out;
}

