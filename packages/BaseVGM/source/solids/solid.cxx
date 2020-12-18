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
// VGM::ISolid output stream and utility function
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/ISolid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ISolid& solid)
{
  out << VGM::SolidTypeName(solid.Type()) << "  \"" << solid.Name() << "\"";
  return solid.Put(out);
}

//_____________________________________________________________________________
std::string VGM::SolidTypeName(VGM::SolidType typeId)
{
  // Returns the solid type name for specified typeId
  switch (typeId) {
    case kArb8:
      return "Arb8";
      break;
    case kBox:
      return "Box";
      break;
    case kCons:
      return "Cons";
      break;
    case kCtubs:
      return "Ctubs";
      break;
    case kEllipsoid:
      return "Ellipsoid";
      break;
    case kEltu:
      return "Eltu";
      break;
    case kExtruded:
      return "Extruded";
      break;
    case kHype:
      return "Hype";
      break;
    case kPara:
      return "Para";
      break;
    case kParaboloid:
      return "Paraboloid";
      break;
    case kPolycone:
      return "Polycone";
      break;
    case kPolyhedra:
      return "Polygone";
      break;
    case kSphere:
      return "Sphere";
      break;
    case kTorus:
      return "Torus";
      break;
    case kTrap:
      return "Trap";
      break;
    case kTrd:
      return "Trd";
      break;
    case kTubs:
      return "Tubs";
      break;
    case kBoolean:
      return "Boolean";
      break;
    case kDisplaced:
      return "Displaced";
      break;
    case kMultiUnion:
      return "MultiUnion";
      break;
    case kScaled:
      return "Scaled";
      break;
    case kUnknownSolid:
      return "Unknown";
      break;
    default:
      return "Undefined";
      break;
  };
}
