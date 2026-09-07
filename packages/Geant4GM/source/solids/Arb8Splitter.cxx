// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

#include "Geant4GM/solids/Arb8Splitter.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace {

struct Vector2
{
  double x;
  double y;
};

//_____________________________________________________________________________
Vector2 Edge(const std::vector<VGM::TwoVector>& vertices, int offset, int index)
{
  const int next = (index + 1) % 4;
  return { vertices[offset + next].first - vertices[offset + index].first,
    vertices[offset + next].second - vertices[offset + index].second };
}

//_____________________________________________________________________________
double Dot(const Vector2& lhs, const Vector2& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

} // namespace

//_____________________________________________________________________________
Geant4GM::Arb8SplitResult Geant4GM::SplitArb8ForGenericTrap(double halfLength,
  const std::vector<VGM::TwoVector>& vertices, Arb8Split& split)
{
  split = Arb8Split{};
  if (!(halfLength > 0.) || !std::isfinite(halfLength) ||
      vertices.size() != 8) {
    return Arb8SplitResult::kInvalidInput;
  }
  for (const auto& vertex : vertices) {
    if (!std::isfinite(vertex.first) || !std::isfinite(vertex.second)) {
      return Arb8SplitResult::kInvalidInput;
    }
  }

  // At fractional height t, corresponding end edges a and b interpolate as
  // m(t)=(1-t)*a+t*b. Both new traps satisfy the 90-degree restriction when
  // a.m(t)>=0 and m(t).b>=0. Intersect the permitted t intervals of all faces.
  double lowerBound = 0.;
  double upperBound = 1.;
  bool splitNeeded = false;
  for (int i = 0; i < 4; ++i) {
    const Vector2 bottom = Edge(vertices, 0, i);
    const Vector2 top = Edge(vertices, 4, i);
    const double bottom2 = Dot(bottom, bottom);
    const double top2 = Dot(top, top);

    // G4GenericTrap treats a face with a collapsed end edge as planar.
    if (bottom2 == 0. || top2 == 0.) continue;

    const double product = Dot(bottom, top);
    if (product >= 0.) continue;

    splitNeeded = true;
    lowerBound = std::max(lowerBound, -product / (top2 - product));
    upperBound = std::min(upperBound, bottom2 / (bottom2 - product));
  }

  if (!splitNeeded) return Arb8SplitResult::kNoSplitNeeded;

  // Avoid exactly 90 degrees: round-off in G4GenericTrap's acos() can turn a
  // boundary value into an angle just above its limit.
  const double margin = 64. * std::numeric_limits<double>::epsilon();
  if (!(upperBound - lowerBound > 2. * margin)) {
    return Arb8SplitResult::kCannotSplitInTwo;
  }

  double fraction = 0.5;
  if (fraction <= lowerBound + margin || fraction >= upperBound - margin) {
    fraction = 0.5 * (lowerBound + upperBound);
  }

  std::vector<VGM::TwoVector> middle;
  middle.reserve(4);
  for (int i = 0; i < 4; ++i) {
    middle.emplace_back(vertices[i].first + fraction * (vertices[i + 4].first -
                                                         vertices[i].first),
      vertices[i].second +
        fraction * (vertices[i + 4].second - vertices[i].second));
  }

  split.fraction = fraction;
  split.lowerHalfLength = halfLength * fraction;
  split.lowerZOffset = halfLength * (fraction - 1.);
  split.upperHalfLength = halfLength * (1. - fraction);
  split.upperZOffset = halfLength * fraction;

  split.lowerVertices.reserve(8);
  split.upperVertices.reserve(8);
  split.lowerVertices.insert(
    split.lowerVertices.end(), vertices.begin(), vertices.begin() + 4);
  split.lowerVertices.insert(
    split.lowerVertices.end(), middle.begin(), middle.end());
  split.upperVertices.insert(
    split.upperVertices.end(), middle.begin(), middle.end());
  split.upperVertices.insert(
    split.upperVertices.end(), vertices.begin() + 4, vertices.end());

  return Arb8SplitResult::kSuccess;
}
