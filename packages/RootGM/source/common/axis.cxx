// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// RootGM utilities
// --------------
// Utility functions
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/common/axis.h"
#include "RootGM/common/Units.h"

#include "TGeoMatrix.h"
#include "TGeoPatternFinder.h"

#include <float.h>
#include <iostream>

//
// Root -> VGM
//

//_____________________________________________________________________________
VGM::Axis RootGM::Axis(const TGeoPatternFinder* finder)
{
  // Checks the finder concrete type and returns the division axis.
  // ---

  const TGeoPatternX* finderX = dynamic_cast<const TGeoPatternX*>(finder);
  if (finderX) return VGM::kXAxis;

  const TGeoPatternY* finderY = dynamic_cast<const TGeoPatternY*>(finder);
  if (finderY) return VGM::kYAxis;

  const TGeoPatternZ* finderZ = dynamic_cast<const TGeoPatternZ*>(finder);
  if (finderZ) return VGM::kZAxis;

  const TGeoPatternParaX* finderParaX =
    dynamic_cast<const TGeoPatternParaX*>(finder);
  if (finderParaX) return VGM::kXAxis;

  const TGeoPatternParaY* finderParaY =
    dynamic_cast<const TGeoPatternParaY*>(finder);
  if (finderParaY) return VGM::kYAxis;

  const TGeoPatternParaZ* finderParaZ =
    dynamic_cast<const TGeoPatternParaZ*>(finder);
  if (finderParaZ) return VGM::kZAxis;

  const TGeoPatternTrapZ* finderTrapZ =
    dynamic_cast<const TGeoPatternTrapZ*>(finder);
  if (finderTrapZ) return VGM::kZAxis;

  const TGeoPatternCylR* finderR = dynamic_cast<const TGeoPatternCylR*>(finder);
  if (finderR) return VGM::kRho;

  const TGeoPatternCylPhi* finderPhi =
    dynamic_cast<const TGeoPatternCylPhi*>(finder);
  if (finderPhi) return VGM::kPhi;

  const TGeoPatternSphR* finderSphR =
    dynamic_cast<const TGeoPatternSphR*>(finder);
  if (finderSphR) return VGM::kRadial3D;

  const TGeoPatternSphPhi* finderSphPhi =
    dynamic_cast<const TGeoPatternSphPhi*>(finder);
  if (finderSphPhi) return VGM::kPhi;

  const TGeoPatternSphTheta* finderSphTheta =
    dynamic_cast<const TGeoPatternSphTheta*>(finder);
  if (finderSphTheta) return VGM::kSphTheta;

  // Not supported shapes:
  // Honeycomb

  return VGM::kUnknownAxis;
}

//
// VGM -> Root
//

//_____________________________________________________________________________
int RootGM::Axis(VGM::Axis axis)
{
  // Converts VGM axis enum to Root axis number.
  // ---

  switch (axis) {
    case VGM::kXAxis:
      return 1;
    case VGM::kYAxis:
      return 2;
    case VGM::kZAxis:
      return 3;
    case VGM::kRho:
      return 1;
    case VGM::kPhi:
      return 2;
    case VGM::kSphTheta:
      return 3;
    case VGM::kRadial3D:
      return 1;
    case VGM::kUnknownAxis:
      return 0;
  }

  return 0;
}

//_____________________________________________________________________________
double RootGM::AxisUnit(VGM::Axis axis)
{
  switch (axis) {
    case VGM::kXAxis:
      return RootGM::Units::Length();
      break;
    case VGM::kYAxis:
      return RootGM::Units::Length();
      break;
    case VGM::kZAxis:
      return RootGM::Units::Length();
      break;
    case VGM::kRho:
      return RootGM::Units::Length();
      break;
    case VGM::kRadial3D:
      return RootGM::Units::Length();
      break;
    case VGM::kPhi:
      return RootGM::Units::Angle();
      break;
    case VGM::kUnknownAxis:
      return 0;
      break;
    default:
      return 0;
      break;
  }
}
