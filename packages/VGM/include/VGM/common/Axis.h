// $Id$
/// \ingroup VGM_common
//
/// \class VGM::Axis
///
/// VGM Axis enumeration.
/// Define axes for function params etc
/// (in Geant4 convention):
///   - X/Y/ZAxis   Normal Catesian axes
///   - Rho         Radial axis in cylindrical polar
///   - Radial3D    Radial axis in spherical polar
///   - Phi         Phi axis in cylindrical polar
///   - kUndefined  Not defined axis
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_AXIS_H
#define VGM_AXIS_H

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
