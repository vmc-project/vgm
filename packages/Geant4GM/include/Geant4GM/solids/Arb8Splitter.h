// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

#ifndef GEANT4_GM_ARB8_SPLITTER_H
#define GEANT4_GM_ARB8_SPLITTER_H

#include "VGM/common/TwoVector.h"

#include <vector>

namespace Geant4GM {

/// Parameters of two G4GenericTrap-compatible pieces obtained by cutting an
/// Arb8 with a plane perpendicular to Z.
struct Arb8Split
{
  double fraction = 0.;
  double lowerHalfLength = 0.;
  double lowerZOffset = 0.;
  std::vector<VGM::TwoVector> lowerVertices;
  double upperHalfLength = 0.;
  double upperZOffset = 0.;
  std::vector<VGM::TwoVector> upperVertices;
};

enum class Arb8SplitResult
{
  kSuccess,
  kNoSplitNeeded,
  kInvalidInput,
  kCannotSplitInTwo
};

/// Split an Arb8 whose corresponding end edges form angles greater than 90
/// degrees into two pieces accepted by G4GenericTrap.
///
/// The input vertices follow the Arb8 convention: vertices 0..3 belong to
/// -halfLength and vertices 4..7 to +halfLength. The Z offsets in the result
/// refer to the coordinate system of the original Arb8. The function returns
/// kCannotSplitInTwo if no single common Z section works for all four faces.
Arb8SplitResult SplitArb8ForGenericTrap(double halfLength,
  const std::vector<VGM::TwoVector>& vertices, Arb8Split& split);

} // namespace Geant4GM

#endif // GEANT4_GM_ARB8_SPLITTER_H
