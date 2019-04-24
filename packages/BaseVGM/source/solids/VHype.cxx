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
// Class VHype
// ------------
// The ABC for hyperboloid solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VHype.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IHype& hype)
{
  const VGM::ISolid& hypeSolid = hype;
  out << hypeSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VHype::VHype() : VGM::IHype()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VHype::~VHype()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VHype::Put(std::ostream& out) const
{
  out << "  r1 = " << InnerRadius() << "mm"
      << "  stereo1 = " << InnerStereoAngle() << "deg"
      << "  r2 = " << OuterRadius() << "mm"
      << "  stereo1 = " << OuterStereoAngle() << "deg"
      << "  hz = " << ZHalfLength() << "mm";
  return out;
}
