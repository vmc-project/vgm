// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Test vgm_arb8_twist_test
// ------------------------
// An Arb8 with non-planar sides cannot be built from planar facets, so it is
// converted to a G4GenericTrap.  That solid accepts a twist of at most 90
// degrees on a lateral face, which not every Root Arb8 respects.
//
// The test converts two twisted shapes and compares, point by point, what Root
// and Geant4 consider to be inside them:
//
//   arbAlice      the beam pipe support of the ALICE geometry, twisted by 17
//                 degrees, with all eight vertices distinct
//   arbCollapsed  two bottom vertices collapsed, twisted by 39 degrees
//
// and checks that a shape beyond the single-G4GenericTrap limit is split into
// two G4GenericTrap solids:
//
//   arbSteep      two top vertices collapsed, twisted by 104 degrees
//
// It also checks a convex Arb8 for which different lateral faces require
// incompatible split positions, so no division into only two GenericTraps is
// possible.
//
// Needs no run manager and returns a non-zero code on failure.

#include "Geant4GM/solids/Arb8.h"
#include "Geant4GM/solids/Arb8Splitter.h"
#include "Geant4GM/volumes/Factory.h"
#include "RootGM/volumes/Factory.h"

#include "TGeoArb8.h"
#include "TGeoManager.h"
#include "TGeoMedium.h"
#include "TGeoVolume.h"

#include "G4GenericTrap.hh"
#include "G4MultiUnion.hh"
#include "G4SolidStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace {

/// Half-length in z and the eight (x,y) vertices of one Arb8, in cm.
struct Shape
{
  const char* fName;
  double fDz;
  double fVertices[8][2];
};

// The two ARB8 solids of the ALICE beam pipe support; this one is ARB8Out.
const Shape kAlice = { "arbAlice", 7.675,
  { { 3.316, 4.3 }, { 0.7025, -4.3 }, { -0.7025, -4.3 }, { -3.316, 4.3 },
    { 1.3, -1.7 }, { 1.3, -4.3 }, { -1.3, -4.3 }, { -1.3, -1.7 } } };

// vertices 0 and 1 collapsed: the first lateral face is a triangle
const Shape kCollapsed = { "arbCollapsed", 75.,
  { { 45., -15. }, { 45., -15. }, { -30., -75. }, { 15., -15. },
    { 45., -15. }, { 0., -75. }, { -30., -75. }, { 15., -15. } } };

// vertices 4 and 5 collapsed: twisted by more than Geant4 can represent
const Shape kSteep = { "arbSteep", 75.,
  { { 45., -15. }, { 0., -75. }, { -30., -75. }, { 15., -15. },
    { 0., -75. }, { 0., -75. }, { -30., -75. }, { 15., -15. } } };

// Both end faces and every interpolated cross-section are convex, but the
// permitted split intervals of lateral faces 1 and 3 do not overlap:
// approximately [0.2891, 0.9554] and [0.0842, 0.2723], respectively.
const Shape kCannotSplitInTwo = { "arbCannotSplitInTwo", 1.,
  { { -0.4307636622, 0.2231118424 },
    { -0.1447443560, 0.2962323240 },
    { 4.7352057379, -1.0445794352 },
    { -0.0675924807, -0.2728480420 },
    { 0.0607942928, 0.1081316842 },
    { 0.9940584508, 0.1184766124 },
    { 0.3162721535, -1.4566513801 },
    { -3.2320871703, -0.2667477443 } } };

std::vector<VGM::TwoVector> Vertices(const Shape& shape)
{
  std::vector<VGM::TwoVector> vertices;
  for (int i = 0; i < 8; ++i)
    vertices.push_back(VGM::TwoVector(shape.fVertices[i][0], shape.fVertices[i][1]));
  return vertices;
}

TGeoVolume* CreateVolume(const Shape& shape, TGeoMedium* medium)
{
  TGeoArb8* arb = new TGeoArb8((std::string(shape.fName) + "S").c_str(), shape.fDz);
  for (int i = 0; i < 8; ++i)
    arb->SetVertex(i, shape.fVertices[i][0], shape.fVertices[i][1]);
  return new TGeoVolume(shape.fName, arb, medium);
}

/// Compare what Root and Geant4 consider inside, over a grid covering the shape.
/// Points within \em tolerance of either boundary are skipped: the two surfaces
/// are the same surface, and a point sitting on it belongs to neither answer.
bool CompareContains(const Shape& shape)
{
  TGeoShape* rootShape = gGeoManager->GetVolume(shape.fName)->GetShape();
  G4VSolid* g4Solid = G4SolidStore::GetInstance()->GetSolid(
    std::string(shape.fName) + "S", false);
  if (!g4Solid) {
    std::cerr << "FAILED  " << shape.fName << ": no Geant4 solid" << std::endl;
    return false;
  }
  const bool splitExpected =
    Geant4GM::Arb8::MaxTwistAngle(Vertices(shape)) > 90.;
  const bool typeMatches = splitExpected
                             ? dynamic_cast<G4MultiUnion*>(g4Solid) != nullptr
                             : dynamic_cast<G4GenericTrap*>(g4Solid) != nullptr;
  if (!typeMatches) {
    std::cerr << "FAILED  " << shape.fName << ": converted to "
              << g4Solid->GetEntityType() << ", expected "
              << (splitExpected ? "G4MultiUnion" : "G4GenericTrap")
              << std::endl;
    return false;
  }

  double extent = shape.fDz;
  for (int i = 0; i < 8; ++i)
    for (int k = 0; k < 2; ++k)
      extent = std::max(extent, std::abs(shape.fVertices[i][k]));

  const int n = 40;
  const double tolerance = 1.e-3 * extent;
  int inside = 0, mismatch = 0, skipped = 0;

  for (int ix = 0; ix < n; ++ix) {
    for (int iy = 0; iy < n; ++iy) {
      for (int iz = 0; iz < n; ++iz) {
        double point[3] = { extent * (2. * (ix + 0.5) / n - 1.),
                            extent * (2. * (iy + 0.5) / n - 1.),
                            shape.fDz * (2. * (iz + 0.5) / n - 1.) };
        bool inRoot = rootShape->Contains(point);
        if (rootShape->Safety(point, inRoot) < tolerance) {
          ++skipped;
          continue;
        }
        G4ThreeVector g4Point(point[0] * cm, point[1] * cm, point[2] * cm);
        EInside where = g4Solid->Inside(g4Point);
        if (where == kSurface) {
          ++skipped;
          continue;
        }
        if (inRoot) ++inside;
        if (inRoot != (where == kInside)) ++mismatch;
      }
    }
  }

  const bool ok = (mismatch == 0) && (inside > 0);
  std::cout << (ok ? "OK      " : "FAILED  ") << shape.fName << ": " << inside
            << " points inside, " << mismatch << " disagreements, " << skipped
            << " on the surface" << std::endl;
  return ok;
}

bool CheckMaxTwist(const Shape& shape, double expected)
{
  const double twist = Geant4GM::Arb8::MaxTwistAngle(Vertices(shape));
  const bool ok = std::abs(twist - expected) < 1.e-3;
  std::cout << (ok ? "OK      " : "FAILED  ") << shape.fName << ": twisted by "
            << twist << " degrees, expected " << expected << std::endl;
  return ok;
}

bool CheckGenericTrapConstructor(const Shape& shape)
{
  std::vector<G4TwoVector> vertices;
  for (int i = 0; i < 8; ++i) {
    vertices.push_back(G4TwoVector(
      shape.fVertices[i][0] * cm, shape.fVertices[i][1] * cm));
  }

  G4GenericTrap* genericTrap =
    new G4GenericTrap("arbImportedS", shape.fDz * cm, vertices);
  Geant4GM::Arb8* imported = new Geant4GM::Arb8(genericTrap);

  bool ok = imported->Name() == "arbImportedS" &&
            std::abs(imported->ZHalfLength() - shape.fDz * cm) < 1.e-9;
  for (int i = 0; i < 8; ++i) {
    const VGM::TwoVector vertex = imported->Vertex(i);
    ok &= std::abs(vertex.first - shape.fVertices[i][0] * cm) < 1.e-9;
    ok &= std::abs(vertex.second - shape.fVertices[i][1] * cm) < 1.e-9;
  }

  std::cout << (ok ? "OK      " : "FAILED  ")
            << "G4GenericTrap import constructor" << std::endl;
  return ok;
}

bool CheckNonCentralSplit()
{
  // For differently sized end faces, z=0 need not be a valid split plane.
  std::vector<VGM::TwoVector> vertices = { { -0.5, -0.5 }, { -0.5, 0.5 },
    { 0.5, 0.5 }, { 0.5, -0.5 } };
  const double angle = 100. * M_PI / 180.;
  const double cosine = std::cos(angle);
  const double sine = std::sin(angle);
  for (int i = 0; i < 4; ++i) {
    const double x = vertices[i].first;
    const double y = vertices[i].second;
    vertices.push_back(VGM::TwoVector(
      10. * (cosine * x - sine * y), 10. * (sine * x + cosine * y)));
  }

  Geant4GM::Arb8Split split;
  const auto result = Geant4GM::SplitArb8ForGenericTrap(10., vertices, split);
  const bool ok = result == Geant4GM::Arb8SplitResult::kSuccess &&
                  split.fraction < 0.5 &&
                  Geant4GM::Arb8::MaxTwistAngle(split.lowerVertices) < 90. &&
                  Geant4GM::Arb8::MaxTwistAngle(split.upperVertices) < 90.;
  std::cout << (ok ? "OK      " : "FAILED  ")
            << "non-central split at fraction " << split.fraction << std::endl;
  return ok;
}

bool CheckCannotSplitInTwo()
{
  Geant4GM::Arb8Split split;
  const auto result = Geant4GM::SplitArb8ForGenericTrap(
    kCannotSplitInTwo.fDz, Vertices(kCannotSplitInTwo), split);
  const bool ok =
    result == Geant4GM::Arb8SplitResult::kCannotSplitInTwo;
  std::cout << (ok ? "OK      " : "FAILED  ")
            << kCannotSplitInTwo.fName
            << ": incompatible lateral-face split intervals" << std::endl;
  return ok;
}

} // namespace

int main()
{
  bool ok = true;

  // Check the twist calculation before constructing the solids.
  ok &= CheckMaxTwist(kAlice, 16.9038);
  ok &= CheckMaxTwist(kCollapsed, 38.6598);
  ok &= CheckMaxTwist(kSteep, 104.0362);
  ok &= CheckGenericTrapConstructor(kAlice);
  ok &= CheckNonCentralSplit();
  ok &= CheckCannotSplitInTwo();

  new TGeoManager("arb8Twist", "twisted Arb8 solids");
  TGeoMedium* medium = new TGeoMedium("medium", 1, new TGeoMaterial("material", 26.98, 13., 2.7));
  TGeoVolume* world = gGeoManager->MakeBox("world", medium, 200., 200., 200.);
  gGeoManager->SetTopVolume(world);
  world->AddNode(CreateVolume(kAlice, medium), 1, gGeoIdentity);
  world->AddNode(CreateVolume(kCollapsed, medium), 1, gGeoIdentity);
  world->AddNode(CreateVolume(kSteep, medium), 1, gGeoIdentity);
  gGeoManager->CloseGeometry();

  RootGM::Factory rootFactory;
  rootFactory.Import(gGeoManager->GetTopNode());
  Geant4GM::Factory g4Factory;
  rootFactory.Export(&g4Factory);

  ok &= CompareContains(kAlice);
  ok &= CompareContains(kCollapsed);
  ok &= CompareContains(kSteep);

  return ok ? 0 : 1;
}
