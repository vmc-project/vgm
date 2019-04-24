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
// Class VTrd
// ---------------
// The ABC for trd solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VTrd.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITrd& trd)
{
  const VGM::ISolid& trdSolid = trd;
  out << trdSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VTrd::VTrd() : VGM::ITrd()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VTrd::~VTrd()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTrd::Put(std::ostream& out) const
{
  out << "  hx1 = " << XHalfLengthMinusZ() << "mm"
      << "  hx2 = " << XHalfLengthPlusZ() << "mm"
      << "  hy1 = " << YHalfLengthMinusZ() << "mm"
      << "  hy2 = " << YHalfLengthPlusZ() << "mm"
      << "  hz = " << ZHalfLength() << "mm";
  return out;
}
