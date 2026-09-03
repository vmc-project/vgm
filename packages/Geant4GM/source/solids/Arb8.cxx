// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Arb8
// --------------------
// VGM implementation for Geant4 Arb8 solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Arb8.h"
#include "Geant4GM/solids/SolidMap.h"

#include "ClhepVGM/Units.h"

#include "G4GenericTrap.hh"
#include "G4QuadrangularFacet.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"

#include <iostream>

const int Geant4GM::Arb8::fgkNofVertices = 8;
const double Geant4GM::Arb8::fgkTolerance = 1E-3;
// The largest twist G4GenericTrap accepts on a lateral face, in degrees.
const double Geant4GM::Arb8::fgkMaxTwistAngle = 90.;

//_____________________________________________________________________________
double Geant4GM::Arb8::TwistAngleOfFace(
  const std::vector<VGM::TwoVector>& vertices, int index)
{
  /// Returns the angle, in radians, between the projections on the xy plane of
  /// the two edges of the lateral face \em index.
  /// A face with an edge collapsed to a point is a triangle and so is planar,
  /// whatever the other edge does; its angle is reported as zero.

  int nv = fgkNofVertices / 2;
  int i = index % nv;
  int j = (index + 1) % nv;

  double dx1 = vertices[j].first - vertices[i].first;
  double dy1 = vertices[j].second - vertices[i].second;
  double dx2 = vertices[nv + j].first - vertices[nv + i].first;
  double dy2 = vertices[nv + j].second - vertices[nv + i].second;

  if ((dx1 == 0 && dy1 == 0) || (dx2 == 0 && dy2 == 0)) return 0.;

  return atan2(dx1 * dy2 - dy1 * dx2, dx1 * dx2 + dy1 * dy2);
}

//_____________________________________________________________________________
double Geant4GM::Arb8::MaxTwistAngle(
  const std::vector<VGM::TwoVector>& vertices)
{
  /// Returns the largest twist of the four lateral faces, in degrees.
  /// This is the quantity G4GenericTrap limits to 90 degrees, so it says
  /// whether a twisted Arb8 can be converted to Geant4 at all.

  double maxAngle = 0.;
  for (int i = 0; i < 4; i++) {
    double angle = fabs(TwistAngleOfFace(vertices, i)) * 180. / M_PI;
    if (angle > maxAngle) maxAngle = angle;
  }
  return maxAngle;
}

//_____________________________________________________________________________
bool Geant4GM::Arb8::IsTwisted(std::vector<VGM::TwoVector> vertices)
{
  /// From TgeoArb8.
  /// Computes tangents of twist angles (angles between projections on XY plane
  /// of corresponding -dz +dz edges).

  bool twisted = false;
  double dx1, dy1, dx2, dy2;
  int nv = fgkNofVertices / 2;
  for (int i = 0; i < 4; i++) {

    dx1 = vertices[(i + 1) % nv].first - vertices[i].first;
    dy1 = vertices[(i + 1) % nv].second - vertices[i].second;
    if (dx1 == 0 && dy1 == 0) continue;

    dx2 = vertices[nv + (i + 1) % nv].first - vertices[nv + i].first;
    dy2 = vertices[nv + (i + 1) % nv].second - vertices[nv + i].second;
    if (dx2 == 0 && dy2 == 0) continue;

    if (fabs(dy1 * dx2 - dx1 * dy2) < fgkTolerance) continue;

    twisted = true;
  }
  return twisted;
}

//_____________________________________________________________________________
Geant4GM::Arb8::Arb8(
  const std::string& name, double hz, std::vector<VGM::TwoVector> vertices)
  : VGM::ISolid(),
    VGM::IArb8(),
    BaseVGM::VArb8(),
    fHz(hz),
    fVertices(vertices),
    fTessellatedSolid(0),
    fSolid(0)
{
  /// Standard constructor to define Arb8 from parameters
  /// \param hz half-length along the z axis in mm
  /// \param vertices vector of (x,y) coordinates of vertices
  /// - first four points are the (x,y)
  ///   coordinates of the vertices sitting on the -dz plane;
  /// - last four points are the (x,y)
  ///   coordinates of the vertices sitting on the +dz plane;
  ///
  /// The order of defining the vertices of an arb8 is the following:
  /// - point 0 is connected with points 1,3,4
  /// - point 1 is connected with points 0,2,5
  /// - point 2 is connected with points 1,3,6
  /// - point 3 is connected with points 0,2,7
  /// - point 4 is connected with points 0,5,7
  /// - point 5 is connected with points 1,4,6
  /// - point 6 is connected with points 2,5,7
  /// - point 7 is connected with points 3,4,6
  ///
  /// Points can be identical in order to create shapes with less than
  /// vertices.

  // A twisted arb8 has non-planar sides, so it cannot be built from planar
  // facets.  G4GenericTrap is the same shape and handles the twist itself.
  if (IsTwisted(vertices)) {
    double maxTwist = MaxTwistAngle(vertices);
    if (maxTwist > fgkMaxTwistAngle) {
      std::cerr << "+++ Error  +++" << std::endl;
      std::cerr << "    Arb8 \"" << name << "\" has a lateral face twisted by "
                << maxTwist << " degrees." << std::endl;
      std::cerr << "    G4GenericTrap accepts at most " << fgkMaxTwistAngle
                << " degrees, so this solid has no Geant4 equivalent."
                << std::endl;
      exit(1);
    }

    std::vector<G4TwoVector> g4Vertices;
    for (G4int i = 0; i < fgkNofVertices; i++)
      g4Vertices.push_back(G4TwoVector(vertices[i].first / ClhepVGM::Units::Length(),
        vertices[i].second / ClhepVGM::Units::Length()));

    fSolid = new G4GenericTrap(name, hz / ClhepVGM::Units::Length(), g4Vertices);
    Geant4GM::SolidMap::Instance()->AddSolid(this, fSolid);
    return;
  }

  // 3D vertices
  G4int nv = fgkNofVertices / 2;
  std::vector<G4ThreeVector> downVertices;
  for (G4int i = 0; i < nv; i++)
    downVertices.push_back(
      G4ThreeVector(vertices[i].first / ClhepVGM::Units::Length(),
        vertices[i].second / ClhepVGM::Units::Length(),
        -hz / ClhepVGM::Units::Length()));

  std::vector<G4ThreeVector> upVertices;
  for (G4int i = nv; i < 2 * nv; i++)
    upVertices.push_back(
      G4ThreeVector(vertices[i].first / ClhepVGM::Units::Length(),
        vertices[i].second / ClhepVGM::Units::Length(),
        hz / ClhepVGM::Units::Length()));

  // Reorder vertices if they are not ordered anti-clock wise
  G4ThreeVector cross = (downVertices[1] - downVertices[0])
                          .cross(downVertices[2] - downVertices[1]);
  if (cross.z() > 0.0) {
    ReorderVertices(downVertices);
    ReorderVertices(upVertices);
  }

  fTessellatedSolid = new G4TessellatedSolid(name);

  G4VFacet* facet = 0;
  facet = MakeDownFacet(downVertices, 0, 1, 2);
  if (facet) fTessellatedSolid->AddFacet(facet);

  facet = MakeDownFacet(downVertices, 0, 2, 3);
  if (facet) fTessellatedSolid->AddFacet(facet);

  facet = MakeUpFacet(upVertices, 0, 2, 1);
  if (facet) fTessellatedSolid->AddFacet(facet);

  facet = MakeUpFacet(upVertices, 0, 3, 2);
  if (facet) fTessellatedSolid->AddFacet(facet);

  // The quadrangular sides
  for (G4int i = 0; i < nv; ++i) {
    G4int j = (i + 1) % nv;
    facet = MakeSideFacet(
      downVertices[j], downVertices[i], upVertices[i], upVertices[j]);

    if (facet) fTessellatedSolid->AddFacet(facet);
  }

  fTessellatedSolid->SetSolidClosed(true);

  // G4cout << "Arb8 solid " <<  Name() <<  G4endl;
  // G4cout << *fTessellatedSolid << G4endl;

  fSolid = fTessellatedSolid;
  Geant4GM::SolidMap::Instance()->AddSolid(this, fSolid);
}

//_____________________________________________________________________________
Geant4GM::Arb8::Arb8()
  : VGM::ISolid(),
    VGM::IArb8(),
    BaseVGM::VArb8(),
    fHz(0),
    fVertices(),
    fTessellatedSolid(0),
    fSolid(0)
{
  /// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Arb8::Arb8(const Arb8& rhs)
  : VGM::ISolid(rhs),
    VGM::IArb8(rhs),
    BaseVGM::VArb8(rhs),
    fHz(0),
    fVertices(),
    fTessellatedSolid(0),
    fSolid(0)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Arb8::~Arb8()
{
  //
}

//_____________________________________________________________________________
void Geant4GM::Arb8::ReorderVertices(std::vector<G4ThreeVector>& vertices)
{
  // Reorder the vector of vertices

  std::vector<G4ThreeVector> oldVertices(vertices);

  for (unsigned int i = 0; i < oldVertices.size(); ++i) {
    vertices[i] = oldVertices[oldVertices.size() - 1 - i];
  }
}

//_____________________________________________________________________________
G4VFacet* Geant4GM::Arb8::MakeDownFacet(
  std::vector<G4ThreeVector> fromVertices, int ind1, int ind2, int ind3) const
{
  // Create a triangular facet from the polygon points given by indices
  // forming the down side ( the normal goes in -z)

  // Do not create facet if 2 vertices are the same
  if (fromVertices[ind1] == fromVertices[ind2] ||
      fromVertices[ind2] == fromVertices[ind3] ||
      fromVertices[ind1] == fromVertices[ind3])
    return 0;

  std::vector<G4ThreeVector> vertices;
  vertices.push_back(fromVertices[ind1]);
  vertices.push_back(fromVertices[ind2]);
  vertices.push_back(fromVertices[ind3]);

  // first vertex most left
  //
  G4ThreeVector cross =
    (vertices[1] - vertices[0]).cross(vertices[2] - vertices[1]);

  if (cross.z() > 0.0) {
    // Should not happen, as vertices should have been reordered
    // at this stage
    std::cerr << "    Geant4GM::Arb8::MakeDownFacet:" << std::endl;
    std::cerr << "    Vertices in wrong order." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return new G4TriangularFacet(vertices[0], vertices[1], vertices[2], ABSOLUTE);
}

//_____________________________________________________________________________
G4VFacet* Geant4GM::Arb8::MakeUpFacet(
  std::vector<G4ThreeVector> fromVertices, int ind1, int ind2, int ind3) const
{
  // Creates a triangular facet from the polygon points given by indices
  // forming the upper side ( z>0 )

  // Do not create facet if 2 vertices are the same
  if (fromVertices[ind1] == fromVertices[ind2] ||
      fromVertices[ind2] == fromVertices[ind3] ||
      fromVertices[ind1] == fromVertices[ind3])
    return 0;

  std::vector<G4ThreeVector> vertices;
  vertices.push_back(fromVertices[ind1]);
  vertices.push_back(fromVertices[ind2]);
  vertices.push_back(fromVertices[ind3]);

  // first vertex most left
  //
  G4ThreeVector cross =
    (vertices[1] - vertices[0]).cross(vertices[2] - vertices[1]);

  if (cross.z() < 0.0) {
    // Should not happen, as vertices should have been reordered
    // at this stage
    std::cerr << "    Geant4GM::Arb8::MakeUpFacet:" << std::endl;
    std::cerr << "    Vertices in wrong order." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return new G4TriangularFacet(vertices[0], vertices[1], vertices[2], ABSOLUTE);
}

//_____________________________________________________________________________
G4VFacet* Geant4GM::Arb8::MakeSideFacet(G4ThreeVector downVertex0,
  G4ThreeVector downVertex1, G4ThreeVector upVertex1,
  G4ThreeVector upVertex0) const
{
  // Creates a triangular facet from the polygon points given by indices
  // forming the upper side ( z>0 )

  if (downVertex0 == downVertex1 && upVertex0 == upVertex1) return 0;

  if (downVertex0 == downVertex1)
    return new G4TriangularFacet(downVertex0, upVertex1, upVertex0, ABSOLUTE);

  if (upVertex0 == upVertex1)
    return new G4TriangularFacet(downVertex0, downVertex1, upVertex0, ABSOLUTE);

  return new G4QuadrangularFacet(
    downVertex0, downVertex1, upVertex1, upVertex0, ABSOLUTE);
}

//_____________________________________________________________________________
std::string Geant4GM::Arb8::Name() const
{
  return fSolid->GetName();
}

//_____________________________________________________________________________
int Geant4GM::Arb8::NofVertices() const { return fgkNofVertices; }

//_____________________________________________________________________________
VGM::TwoVector Geant4GM::Arb8::Vertex(int index) const
{
  if (index < 0 || index >= NofVertices()) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong vertex index: " << index << std::endl;
    exit(1);
  }

  return fVertices[index];
}

//_____________________________________________________________________________
double Geant4GM::Arb8::TwistAngle(int index) const
{
  if (index < 0 || index >= 4) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong twist angle index: " << index << std::endl;
    exit(1);
  }

  return TwistAngleOfFace(fVertices, index) * ClhepVGM::Units::Angle();
}

//_____________________________________________________________________________
double Geant4GM::Arb8::ZHalfLength() const { return fHz; }
