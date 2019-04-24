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
// Class VArb8
// ---------------------
// The ABC for Arb8 solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VArb8.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IArb8& arb8)
{
  const VGM::ISolid& Arb8 = arb8;
  out << Arb8;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VArb8::VArb8() : VGM::IArb8()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VArb8::~VArb8()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VArb8::Put(std::ostream& out) const
{
  out << std::endl;
  out << NofVertices() << " vertices:" << std::endl;
  for (int i = 0; i < NofVertices(); i++) {
    out << "  (" << Vertex(i).first << ", " << Vertex(i).second << ")";
  }
  out << " mm" << std::endl;
  out << "  twist angles:";
  for (int i = 0; i < 4; i++) {
    out << "  " << TwistAngle(i);
  }
  out << " rad" << std::endl;
  out << "  hz = " << ZHalfLength() << "mm" << std::endl;

  return out;
}
