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
// Class VBox
// ---------------
// The interface to box solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VBox.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IBox& box)
{
  const VGM::ISolid& boxSolid = box;
  out << boxSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VBox::VBox() : VGM::IBox()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VBox::~VBox()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VBox::Put(std::ostream& out) const
{
  out << "  hx = " << XHalfLength() << "mm"
      << "  hy = " << YHalfLength() << "mm"
      << "  hz = " << ZHalfLength() << "mm";
  return out;
}
