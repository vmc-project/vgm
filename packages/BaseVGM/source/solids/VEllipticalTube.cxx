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
// Class VEllipticalTube
// ---------------------
// The ABC for elliptical tube solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VEllipticalTube.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IEllipticalTube& eltu)
{
  const VGM::ISolid& eltuSolid = eltu;
  out << eltuSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VEllipticalTube::VEllipticalTube()
  : VGM::IEllipticalTube()
{
/// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VEllipticalTube::~VEllipticalTube() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VEllipticalTube::Put(std::ostream& out) const
{
  out << "  dx = "  << Dx()  << "mm"
      << "  dy = "  << Dy()  << "mm"
      << "  hz = "  << ZHalfLength()  << "mm";
  return out;
}

