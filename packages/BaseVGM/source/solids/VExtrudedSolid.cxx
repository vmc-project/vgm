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
// Class VExtrudedSolid
// ---------------------
// The ABC for ExtrudedSolid solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VExtrudedSolid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IExtrudedSolid& xtru)
{
  const VGM::ISolid& xtruSolid = xtru;
  out << xtruSolid;
  return out;
}

//_____________________________________________________________________________
BaseVGM::VExtrudedSolid::VExtrudedSolid() : VGM::IExtrudedSolid()
{
  /// Default constructor
}

//_____________________________________________________________________________
BaseVGM::VExtrudedSolid::~VExtrudedSolid()
{
  //
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VExtrudedSolid::Put(std::ostream& out) const
{
  out << std::endl;
  out << "Polygon,  " << NofVertices() << " vertices:" << std::endl;
  for (int i = 0; i < NofVertices(); i++) {
    out << "  (" << Vertex(i).first << ", " << Vertex(i).second << ")";
  }
  out << " mm" << std::endl;

  out << "Planes:" << std::endl;
  for (int i = 0; i < NofZSections(); i++) {
    out << "  z = " << ZPosition(i) << " mm  "
        << "  x0 = " << Offset(i).first << " mm  "
        << "  y0 = " << Offset(i).second << " mm  "
        << "  scale= " << Scale(i) << std::endl;
  }

  return out;
}
