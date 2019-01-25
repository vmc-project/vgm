// $Id$

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_common
//
/// \class VGM::Transform
///
/// VGM typedef for 3D transformation
/// represented by std::vector<double>:
///   - std::vector<double>[0]   translation X in mm
///   - std::vector<double>[1]   translation Y in mm
///   - std::vector<double>[2]   translation Z in mm
///   - std::vector<double>[3]   axis angle X in degree
///   - std::vector<double>[4]   axis angle Y in degree
///   - std::vector<double>[5]   axis angle Z in degree
///   - std::vector<double>[6]   reflection info:
///   -                              0  - no reflection
///   -                              1. - reflection in Z
///
/// Using GDML convention for axis angles definition.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_TRANSFORM_H
#define VGM_TRANSFORM_H

#include <vector>
#include <iostream>

namespace VGM {

  typedef std::vector<double>  Transform;

  enum TransformVector {
    kDx,
    kDy,
    kDz,
    kAngleX,
    kAngleY,
    kAngleZ,
    kReflZ,
    kSize
  };

}

std::ostream& operator << (std::ostream& out, const VGM::Transform& transform);

#endif //VGM_TRANSFORM_H
