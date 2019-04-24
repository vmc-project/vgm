// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_common
//
/// BaseVGM utilities
///
/// Utility functions
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_AXIS_H
#define ROOT_GM_AXIS_H

#include "VGM/common/Axis.h"

class TGeoMatrix;
class TGeoPatternFinder;

namespace RootGM {

// Root -> VGM
//
VGM::Axis Axis(const TGeoPatternFinder* finder);

// VGM -> Root
//
int Axis(VGM::Axis axis);
double AxisUnit(VGM::Axis axis);
} // namespace RootGM

#endif // ROOT_GM_AXIS_H
