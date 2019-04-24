// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

// BaseVGM utilities
// --------------
// Utility functions
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/common/Axis.h"
#include "VGM/common/Transform.h"

#include "BaseVGM/common/utilities.h"

#include <iostream>
#include <math.h>

//_____________________________________________________________________________
void BaseVGM::DebugInfo()
{
  //
  std::cout << "VGM info:   ";
}

//_____________________________________________________________________________
double BaseVGM::Round(double x)
{
  /// Replacement for round(double) function from math.h
  /// which is not available on all platforms (gcc 2.95.x, Windows)

  double t;
  if (x >= 0.0) {
    t = ceil(x);
    if (t - x > 0.5) t -= 1.0;
    return t;
  }
  else {
    t = ceil(-x);
    if (t + x > 0.5) t -= 1.0;
    return -t;
  }
}

//_____________________________________________________________________________
std::string VGM::AxisTypeName(VGM::Axis typeId)
{
  // Returns the axis type name for specified typeId
  switch (typeId) {
    case kXAxis:
      return "X";
      break;
    case kYAxis:
      return "Y";
      break;
    case kZAxis:
      return "Z";
      break;
    case kRho:
      return "Rho";
      break;
    case kRadial3D:
      return "Radial3D";
      break;
    case kPhi:
      return "Phi";
      break;
    case kSphTheta:
      return "SphTheta";
      break;
    case kUnknownAxis:
      return "Unknown";
      break;
    default:
      return "Undefined";
      break;
  };
}

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::Transform& transform)
{
  out << "( " << transform[VGM::kDx] << ", " << transform[VGM::kDy] << ", "
      << transform[VGM::kDz] << ")mm ( " << transform[VGM::kAngleX] << ", "
      << transform[VGM::kAngleY] << ", " << transform[VGM::kAngleZ] << ")deg ";

  if (BaseVGM::Round(transform[6]) == 0)
    out << " noReflZ";
  else
    out << " reflZ";

  return out;
}
