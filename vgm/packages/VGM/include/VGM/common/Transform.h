// $Id$
//
// Typedef Transform
// -------------------
// VGM typedef for 3D transformation
// represented by std::vector<double>:
//   std::vector<double>[0]   translation X in mm
//   std::vector<double>[1]   translation Y in mm
//   std::vector<double>[2]   translation Z in mm
//   std::vector<double>[3]   axis angle X in rad
//   std::vector<double>[4]   axis angle Y in rad
//   std::vector<double>[5]   axis angle Z in rad
//   std::vector<double>[6]   reflection info: 
//                                 0  - no reflection
//                                 1. - reflection in Z
//
// Using GDML convention for axis angles definition.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_TRANSFORM_H
#define VGM_TRANSFORM_H

#include <vector>

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

#endif //VGM_TRANSFORM_H
