// $Id$
//
// Enum Axis
// -----------
// VGM Axis enumeration.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_AXIS_H
#define VGM_AXIS_H

// Define axes for function params etc.
// X/Y/ZAxis = Normal Catesian axes
// Rho = Radial axis in cylindrical polar
// Radial3D = Radial axis in spherical polar
// Phi = Phi axis in cylindrical polar
// kUndefined = Not defined axis
// (taken from Geant4)

namespace VGM {
  enum Axis {
    kXAxis,
    kYAxis,
    kZAxis,
    kRho,
    kRadial3D,
    kPhi,
    kSphTheta,
    kUnknownAxis
  };
}

#endif //VGM_AXIS_H
