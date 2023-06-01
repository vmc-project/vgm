// $Id$

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstGeometryViaGeant4
// -------------------------------
// Class for building geometry via Geant4
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iomanip>
#include <math.h>

#include "G4AssemblyVolume.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4CutTubs.hh"
#include "G4DisplacedSolid.hh"
#include "G4Element.hh"
#include "G4Ellipsoid.hh"
#include "G4EllipticalTube.hh"
#include "G4ExtrudedSolid.hh"
#include "G4Hype.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4MultiUnion.hh"
#include "G4NistManager.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4Para.hh"
#include "G4Paraboloid.hh"
#include "G4PhysicalConstants.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4QuadrangularFacet.hh"
#include "G4ReflectionFactory.hh"
#include "G4ReplicatedSlice.hh"
#include "G4RotationMatrix.hh"
#include "G4ScaledSolid.hh"
#include "G4Sphere.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4TessellatedSolid.hh"
#include "G4Torus.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4TriangularFacet.hh"
#include "G4Tubs.hh"
#include "G4TwoVector.hh"
#include "G4UnionSolid.hh"
#include "G4VPVParameterisation.hh"
#include "G4VSolid.hh"

#include "TstGeometryViaGeant4.hh"

#include <math.h>
#include <utility>

using CLHEP::Hep3Vector;
using CLHEP::HepRotation;

//_____________________________________________________________________________
TstGeometryViaGeant4::TstGeometryViaGeant4() : TstVGeometry(), fBasicMaterial(0)
{
  //
}

//_____________________________________________________________________________
TstGeometryViaGeant4::~TstGeometryViaGeant4() {}

//
// private methods
//

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateWorld(
  G4double x, G4double y, G4double z)
{
  // Create world volume
  // ---

  // Get material from G4
  if (!fBasicMaterial) fBasicMaterial = G4Material::GetMaterial("Basic");

  G4VSolid* worldS = new G4Box("worldS", x, y, z);

  return new G4LogicalVolume(worldS, fBasicMaterial, "world");
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateNewSolid()
{
  // Create a new solid
  // ---

  return CreateCtubs(0, 360. * deg);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateBox()
{
  return new G4Box("boxS", 20. * cm, 60. * cm, 50. * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateCons(G4double sphi, G4double dphi)
{
  return new G4Cons(
    "consS", 10. * cm, 40. * cm, 20. * cm, 60. * cm, 50 * cm, sphi, dphi);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateEllipsoid()
{
  return new G4Ellipsoid(
    "ellipsiodS", 10. * cm, 20. * cm, 50 * cm, -10. * cm, 40. * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateEllipticalTube()
{
  return new G4EllipticalTube("eltuS", 20. * cm, 30. * cm, 50 * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateExtrudedSolid1()
{
  std::vector<G4TwoVector> polygon;
  polygon.push_back(G4TwoVector(-30. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(-30. * cm, 30. * cm));
  polygon.push_back(G4TwoVector(30. * cm, 30. * cm));
  polygon.push_back(G4TwoVector(30. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(15. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(15. * cm, 15. * cm));
  polygon.push_back(G4TwoVector(-15. * cm, 15. * cm));
  polygon.push_back(G4TwoVector(-15. * cm, -30. * cm));

  std::vector<G4ExtrudedSolid::ZSection> zsections;
  zsections.push_back(G4ExtrudedSolid::ZSection(
    -40. * cm, G4TwoVector(-20. * cm, 10. * cm), 1.5));
  zsections.push_back(
    G4ExtrudedSolid::ZSection(10. * cm, G4TwoVector(0. * cm, 0. * cm), 0.5));
  zsections.push_back(
    G4ExtrudedSolid::ZSection(15. * cm, G4TwoVector(0. * cm, 0. * cm), 0.7));
  zsections.push_back(
    G4ExtrudedSolid::ZSection(40. * cm, G4TwoVector(20. * cm, 20. * cm), 0.9));

  return new G4ExtrudedSolid("Xtru1S", polygon, zsections);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateExtrudedSolid2()
{

  std::vector<G4TwoVector> polygon;
  polygon.push_back(G4TwoVector(-30. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(-30. * cm, 30. * cm));
  polygon.push_back(G4TwoVector(30. * cm, 30. * cm));
  polygon.push_back(G4TwoVector(30. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(15. * cm, -30. * cm));
  polygon.push_back(G4TwoVector(15. * cm, 15. * cm));
  polygon.push_back(G4TwoVector(-15. * cm, 15. * cm));
  polygon.push_back(G4TwoVector(-15. * cm, -30. * cm));

  std::vector<G4ExtrudedSolid::ZSection> zsections1;
  zsections1.push_back(G4ExtrudedSolid::ZSection(
    -40. * cm, G4TwoVector(-20. * cm, 10. * cm), 1.5));
  zsections1.push_back(
    G4ExtrudedSolid::ZSection(10. * cm, G4TwoVector(0. * cm, 0. * cm), 0.5));

  G4ExtrudedSolid* xtruS1 = new G4ExtrudedSolid("XtruS1", polygon, zsections1);

  std::vector<G4ExtrudedSolid::ZSection> zsections2;
  zsections2.push_back(
    G4ExtrudedSolid::ZSection(10. * cm, G4TwoVector(0. * cm, 0. * cm), 0.7));
  zsections2.push_back(
    G4ExtrudedSolid::ZSection(40. * cm, G4TwoVector(20. * cm, 20. * cm), 0.9));

  G4ExtrudedSolid* xtruS2 = new G4ExtrudedSolid("XtruS2", polygon, zsections2);

  return new G4UnionSolid("xtru2S", xtruS1, xtruS2, 0, G4ThreeVector());
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateHype()
{
  return new G4Hype(
    "hypeS", 20. * cm, 30. * cm, 30.0 * deg, 40.0 * deg, 50. * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreatePara()
{
  return new G4Para(
    "paraS", 40. * cm, 60. * cm, 50. * cm, 30. * deg, 30. * deg, 30. * deg);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateParaboloid()
{
  return new G4Paraboloid("paraboloidS", 50. * cm, 20. * cm, 45. * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreatePolycone(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50. * cm;
  rin[0] = 10. * cm;
  rout[0] = 50. * cm;

  z[1] = 10. * cm;
  rin[1] = 20. * cm;
  rout[1] = 30. * cm;

  z[2] = 40. * cm;
  rin[2] = 30. * cm;
  rout[2] = 60. * cm;

  return new G4Polycone("pconeS", sphi, dphi, nofPlanes, z, rin, rout);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreatePolyhedra(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofSides = 4;
  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50. * cm;
  rin[0] = 10. * cm;
  rout[0] = 40. * cm;

  z[1] = 10. * cm;
  rin[1] = 20. * cm;
  rout[1] = 30. * cm;

  z[2] = 40. * cm;
  rin[2] = 30. * cm;
  rout[2] = 50. * cm;

  return new G4Polyhedra(
    "phedraS", sphi, dphi, nofSides, nofPlanes, z, rin, rout);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateSphere(G4double sphi, G4double dphi)
{
  return new G4Sphere(
    "sphereS", 20. * cm, 60. * cm, sphi, dphi, sphi / 2., dphi / 2.);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateTessellatedSolid()
{
  // First declare a tessellated solid
  //
  G4TessellatedSolid* tessellatedS = new G4TessellatedSolid("tessellatedS");

  G4double targetSize = 50 * cm;
  G4TriangularFacet* facet1 =
    new G4TriangularFacet(G4ThreeVector(-targetSize, -targetSize, 0.0),
      G4ThreeVector(+targetSize, -targetSize, 0.0),
      G4ThreeVector(0.0, 0.0, +targetSize), ABSOLUTE);

  G4TriangularFacet* facet2 =
    new G4TriangularFacet(G4ThreeVector(+targetSize, -targetSize, 0.0),
      G4ThreeVector(+targetSize, +targetSize, 0.0),
      G4ThreeVector(0.0, 0.0, +targetSize), ABSOLUTE);

  G4TriangularFacet* facet3 =
    new G4TriangularFacet(G4ThreeVector(+targetSize, +targetSize, 0.0),
      G4ThreeVector(-targetSize, +targetSize, 0.0),
      G4ThreeVector(0.0, 0.0, +targetSize), ABSOLUTE);

  G4TriangularFacet* facet4 =
    new G4TriangularFacet(G4ThreeVector(-targetSize, +targetSize, 0.0),
      G4ThreeVector(-targetSize, -targetSize, 0.0),
      G4ThreeVector(0.0, 0.0, +targetSize), ABSOLUTE);

  G4QuadrangularFacet* facet5 =
    new G4QuadrangularFacet(G4ThreeVector(-targetSize, -targetSize, 0.0),
      G4ThreeVector(-targetSize, +targetSize, 0.0),
      G4ThreeVector(+targetSize, +targetSize, 0.0),
      G4ThreeVector(+targetSize, -targetSize, 0.0), ABSOLUTE);

  tessellatedS->AddFacet((G4VFacet*)facet1);
  tessellatedS->AddFacet((G4VFacet*)facet2);
  tessellatedS->AddFacet((G4VFacet*)facet3);
  tessellatedS->AddFacet((G4VFacet*)facet4);
  tessellatedS->AddFacet((G4VFacet*)facet5);
  tessellatedS->SetSolidClosed(true);

  return tessellatedS;
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateTorus(G4double sphi, G4double dphi)
{
  return new G4Torus("torusS", 20. * cm, 30. * cm, 40. * cm, sphi, dphi);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateTrap()
{
  return new G4Trap("trapS", 30. * cm, 25. * deg, 35. * deg, 20. * cm, 10. * cm,
    15. * cm, 0. * deg, 20. * cm, 10. * cm, 15. * cm, 0. * deg);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateTrd()
{
  return new G4Trd("trdS", 20. * cm, 30 * cm, 40. * cm, 50. * cm, 50. * cm);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateTubs(G4double sphi, G4double dphi)
{
  return new G4Tubs("tubsS", 20. * cm, 40 * cm, 50. * cm, sphi, dphi);
}

//_____________________________________________________________________________
G4VSolid* TstGeometryViaGeant4::CreateCtubs(
  G4double /*sphi*/, G4double /*dphi*/)
{
  return new G4CutTubs("ctubsS", 20. * cm, 30. * cm, 60.49 * cm, 330. * deg,
    280. * deg, G4ThreeVector(0.00, 0.64, -0.77),
    G4ThreeVector(0.00, 0.09, 0.87));
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateVolume(
  G4VSolid* solid, G4bool scale)
{
  HepGeom::Scale3D scale3D(0.8, 0.5, 0.25);

  // Remove "S" from solid name
  G4String name = solid->GetName();
  if (name.find("S") != std::string::npos) {
    name.erase(name.find("S"), 1);
  }

  G4VSolid* finalSolid = solid;
  if (scale) finalSolid = new G4ScaledSolid(solid->GetName(), solid, scale3D);

  return new G4LogicalVolume(finalSolid, fBasicMaterial, name);
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::PlaceSolids(G4LogicalVolume* mother,
  G4bool fullPhi, G4bool reflect, G4bool scale, G4double zpos)
{

  G4double sphi = 0. * deg;
  G4double dphi = 360. * deg;
  if (!fullPhi) {
    sphi = 45. * deg;
    dphi = 90. * deg;
  }

  G4int counter = 0;
  G4double x0 = -5.0 * m;
  G4double dx = 1.5 * m;
  G4double dy = 1.5 * m;

  HepGeom::ReflectZ3D reflect3D;
  HepGeom::Scale3D scale3D(0.8, 0.5, 0.25);

  // Box
  //
  G4VSolid* box = CreateBox();
  G4LogicalVolume* boxV = CreateVolume(box, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, -dy, zpos), boxV,
    "box", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "box",
      boxV, mother, false, 0);
  }

  // Cons
  //
  G4VSolid* cons = CreateCons(sphi, dphi);
  G4LogicalVolume* consV = CreateVolume(cons, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), consV,
    "cons", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "cons",
      consV, mother, false, 0);
  }

  // Elliptical tube
  //
  G4VSolid* eltu = CreateEllipticalTube();
  G4LogicalVolume* eltuV = CreateVolume(eltu, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    eltuV, "eltu", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "eltu",
      eltuV, mother, false, 0);
  }

  // Para
  //
  G4VSolid* para = CreatePara();
  G4LogicalVolume* paraV = CreateVolume(para, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), paraV,
    "para", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "para",
      paraV, mother, false, 0);
  }

  // Polycone
  //
  G4VSolid* pcone = CreatePolycone(sphi, dphi);
  G4LogicalVolume* pconeV = CreateVolume(pcone, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    pconeV, "pcone", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "pcone",
      pconeV, mother, false, 0);
  }

  // Polyhedra
  //
  G4VSolid* phedra = CreatePolyhedra(sphi, dphi);
  G4LogicalVolume* phedraV = CreateVolume(phedra, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), phedraV,
    "phedra", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "phedra",
      phedraV, mother, false, 0);
  }

  // Sphere
  //
  G4VSolid* sphere = CreateSphere(sphi, dphi);
  G4LogicalVolume* sphereV = CreateVolume(sphere, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    sphereV, "sphere", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "sphere",
      sphereV, mother, false, 0);
  }

  // Torus
  //
  G4VSolid* torus = CreateTorus(sphi, dphi);
  G4LogicalVolume* torusV = CreateVolume(torus, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), torusV,
    "torus", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "torus",
      torusV, mother, false, 0);
  }

  // Trap
  //
  G4VSolid* trap = CreateTrap();
  G4LogicalVolume* trapV = CreateVolume(trap, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    trapV, "trap", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "trap",
      trapV, mother, false, 0);
  }

  // Trd
  //
  G4VSolid* trd = CreateTrd();
  G4LogicalVolume* trdV = CreateVolume(trd, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), trdV,
    "trd", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "trd",
      trdV, mother, false, 0);
  }

  // Tubs
  //
  G4VSolid* tubs = CreateTubs(sphi, dphi);
  G4LogicalVolume* tubsV = CreateVolume(tubs, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    tubsV, "tubs", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "tubs",
      tubsV, mother, false, 0);
  }

  // CTubs
  //
  G4VSolid* ctubs = CreateCtubs(sphi, dphi);
  G4LogicalVolume* ctubsV = CreateVolume(ctubs, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), ctubsV,
    "ctubs", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "ctubs",
      ctubsV, mother, false, 0);
  }

  // Xtru1
  //
  G4VSolid* xtru1 = CreateExtrudedSolid1();
  G4LogicalVolume* xtru1V = CreateVolume(xtru1, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    xtru1V, "xtru1", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "xtru1",
      xtru1V, mother, false, 0);
  }

  // Xtru2
  //
  G4bool scaleDisabled = false;
  // ROOT breaks when we want to scale Boolean solid (to be reported)
  G4VSolid* xtru2 = CreateExtrudedSolid2();
  G4LogicalVolume* xtru2V = CreateVolume(xtru2, scaleDisabled);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos), xtru2V,
    "xtru2", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D, "xtru2",
      xtru2V, mother, false, 0);
  }

  // Hype
  //
  G4VSolid* hype = CreateHype();
  G4LogicalVolume* hypeV = CreateVolume(hype, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos),
    hypeV, "hype", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D, "hype",
      hypeV, mother, false, 0);
  }

  // Paraboloid
  //
  G4VSolid* paraboloid = CreateParaboloid();
  G4LogicalVolume* paraboloidV = CreateVolume(paraboloid, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos),
    paraboloidV, "paraboloid", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
      "paraboloid", paraboloidV, mother, false, 0);
  }

  // Tessellated
  G4VSolid* tessellated = CreateTessellatedSolid();
  G4LogicalVolume* tessellatedV = CreateVolume(tessellated, scale);
  new G4PVPlacement(HepGeom::Translate3D(x0 + (++counter) * dx, dy, zpos),
    tessellatedV, "tessellated", mother, false, 0);
  std::cout << "Tessellated position: " << x0 + counter * dx << ", " << dy
            << ", " << zpos << std::endl;

  if (reflect) {
    G4ReflectionFactory::Instance()->Place(
      HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
      "tesselled", tessellatedV, mother, false, 0);
  }

  return mother;
}

//_____________________________________________________________________________
void TstGeometryViaGeant4::PlaceExtraSolid(
  VGM::SolidType solidType, G4LogicalVolume* mother)
{

  // Arb8
  //
  G4LogicalVolume* lv = 0;
  G4String lvName;

  if (solidType == VGM::kEllipsoid) {
    lv = CreateVolume(CreateEllipsoid());
    lvName = "ellipsoid";
  }

  if (solidType == VGM::kTessellated) {
    lv = CreateVolume(CreateTessellatedSolid());
    lvName = "tessellated";
  }

  if (!lv) return;

  G4double zpos = 1.0 * m;
  HepGeom::ReflectZ3D reflect3D;

  new G4PVPlacement(
    HepGeom::Translate3D(0, 0, zpos), lv, lvName, mother, false, 0);

  G4ReflectionFactory::Instance()->Place(
    HepGeom::Translate3D(0, 0, -zpos) * reflect3D, lvName, lv, mother, false,
    0);
}

//
// public methods
//

//_____________________________________________________________________________
void TstGeometryViaGeant4::DefineMaterials()
{
  // simple material (Al)
  //
  G4double z, a, density, fractionmass;
  new G4Material(
    "Basic", z = 13., a = 26.98 * g / mole, density = 2.700 * g / cm3);

  // compound/mixture material
  //
  G4Element* N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g / mole);
  G4Element* O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g / mole);

  density = 1.290 * mg / cm3;
  G4Material* material2 = new G4Material("Air", density, 2);
  material2->AddElement(N, fractionmass = 0.7);
  material2->AddElement(O, fractionmass = 0.3);

  // material from predefined elements
  //
  G4NistManager* nistManager = G4NistManager::Instance();
  G4Element* H = nistManager->FindOrBuildElement(1);
  G4Element* C = nistManager->FindOrBuildElement(6);

  G4int natoms;
  density = 1.032 * g / cm3;
  G4Material* material3 = new G4Material("Scintillator", density, 2);
  material3->AddElement(C, natoms = 9);
  material3->AddElement(H, natoms = 10);

  // material using isotopes
  G4int iz, n, ncomponents;
  G4double abundance;
  G4Isotope* U5 =
    new G4Isotope("U235", iz = 92, n = 235, a = 235.01 * g / mole);
  G4Isotope* U8 =
    new G4Isotope("U238", iz = 92, n = 238, a = 238.03 * g / mole);
  G4Element* U = new G4Element("enriched Uranium", "U", ncomponents = 2);
  U->AddIsotope(U5, abundance = 90. * perCent);
  U->AddIsotope(U8, abundance = 10. * perCent);

  G4Material* material4 =
    new G4Material("Uranium", density = 13.61 * g / cm3, ncomponents = 1);
  material4->AddElement(U, 1);

  // vacuum
  //
  new G4Material("Vacuum", z = 1., a = 1.01 * g / mole,
    density = universe_mean_density, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);

  // simple material (Tungsten)  which caused problem in v3.03
  //
  new G4Material(
    "Tungsten", z = 74., a = 183.84 * g / mole, density = 19.25 * g / cm3);
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestSolids(G4bool fullPhi)
{

  G4LogicalVolume* worldV = CreateWorld(8.0 * m, 3. * m, 2. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  PlaceSolids(worldV, fullPhi, false, false, 0.);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestExtraSolid(VGM::SolidType solidType)
{

  G4LogicalVolume* worldV = CreateWorld(8.0 * m, 3. * m, 2. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  PlaceExtraSolid(solidType, worldV);

  return (void*)world;
}

#include "G4VisAttributes.hh"
//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestNewSolid()
{

  G4LogicalVolume* worldV = CreateWorld(2. * m, 2. * m, 2. * m);
  G4VPhysicalVolume* world = new G4PVPlacement(
    0, CLHEP::Hep3Vector(), worldV, worldV->GetName(), 0, false, 0);
  worldV->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4VSolid* solid = CreateNewSolid();
  G4LogicalVolume* solidV = CreateVolume(solid);

  if (solidV) {
    new G4PVPlacement(
      0, CLHEP::Hep3Vector(), solidV, solidV->GetName(), worldV, false, 0);
  }

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestNewSolid2()
{
  G4LogicalVolume* worldV = CreateWorld(2. * m, 2. * m, 2. * m);
  G4VPhysicalVolume* world = new G4PVPlacement(
    0, CLHEP::Hep3Vector(), worldV, worldV->GetName(), 0, false, 0);
  worldV->SetVisAttributes(G4VisAttributes::GetInvisible());

  std::cerr << "TstGeometryViaGeant4::TestNewSolid2: not yet implemented."
            << std::endl;
  exit(1);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestPlacements()
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld(6. * m, 1. * m, 6. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Get materials via names
  G4Material* air = G4Material::GetMaterial("Air");
  G4Material* scintillator = G4Material::GetMaterial("Scintillator");
  G4Material* uranium = G4Material::GetMaterial("Uranium");
  G4Material* vacuum = G4Material::GetMaterial("Vacuum");

  // Reset world material to vacuum
  worldV->SetMaterial(vacuum);

  // Big box A
  //
  G4VSolid* boxA = new G4Box("boxA", 20. * cm, 60. * cm, 50. * cm);
  G4LogicalVolume* volA = new G4LogicalVolume(boxA, air, "layerA");

  // Thick layer B (in A)
  //
  G4VSolid* boxB = new G4Box("boxB", 20. * cm, 10. * cm, 50. * cm);
  G4LogicalVolume* volB = new G4LogicalVolume(boxB, uranium, "layerB");

  // Thin layer C (in B)
  //
  G4VSolid* boxC = new G4Box("boxC", 20. * cm, 0.2 * cm, 50. * cm);
  G4LogicalVolume* volC = new G4LogicalVolume(boxC, scintillator, "layerC");

  // Place layers C
  //
  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0., 9.8 * cm, 0.), volC, "layerC", volB, false, 0);
  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0., -9.8 * cm, 0.), volC, "layerC", volB, false, 1);

  // Place layers B
  //
  // new G4PVDivision("layerB", volB, volA, kYAxis, 6, 20.*cm, 0.);
  // division in the whole mother

  new G4PVDivision("layerB", volB, volA, kYAxis, 3, 20. * cm, 60. * cm);
  // division with offeset

  // Placements of A in a circle
  //
  for (G4int i = 0; i < 24; i++) {

    G4double x0 = 5. * m;
    G4double y0 = 0. * m;
    G4double dphi = 15. * deg;

    G4double phi = dphi * (i + 1);
    G4double x = x0 * cos(phi);
    G4double z = x0 * sin(phi);

    CLHEP::HepRotation* rot = new CLHEP::HepRotation();
    rot->rotateY(phi);
    // !!! Different meaning of rotation in Geant4 than in Root, VGM

    new G4PVPlacement(
      rot, CLHEP::Hep3Vector(x, y0, z), volA, "layerA", worldV, false, i);
  }

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestPlacements2(G4bool /*bestMatch*/)
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld(2. * m, 1. * m, 4. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Get materials via names
  G4Material* air = G4Material::GetMaterial("Air");
  G4Material* scintillator = G4Material::GetMaterial("Scintillator");

  // Reset world material to air
  worldV->SetMaterial(air);

  // Divison 1 (defined via replica)
  //
  G4VSolid* box1A = new G4Box("box1A", 20. * cm, 60. * cm, 50. * cm);
  G4LogicalVolume* vol1A = new G4LogicalVolume(box1A, air, "vol1A");

  // Replica cell
  //
  G4VSolid* box1B = new G4Box("box1B", 20. * cm, 10. * cm, 50. * cm);
  G4LogicalVolume* vol1B = new G4LogicalVolume(box1B, scintillator, "vol1B");

  // Replica PV
  //
  // G4PVReplica(const G4String& pName,
  //                   G4LogicalVolume *pLogical,
  //                   G4LogicalVolume *pMother,
  //             const EAxis pAxis,
  //             const G4int nReplicas,
  //             const G4double width,
  //             const G4double offset=0);
  new G4PVDivision("vol1B", vol1B, vol1A, kYAxis, 6, 20. * cm, 0. * cm);
  // division with offeset

  // Replicated Slice
  //
  G4VSolid* box2A = new G4Box("box2A", 20. * cm, 60. * cm, 50. * cm);
  G4LogicalVolume* vol2A = new G4LogicalVolume(box2A, air, "vol2A");

  // Replicated Slice cell
  //
  G4VSolid* box2B = new G4Box("box2B", 20. * cm, 5. * cm, 50. * cm);
  G4LogicalVolume* vol2B = new G4LogicalVolume(box2B, scintillator, "vol2B");

  // Replicated slice
  //
  // G4ReplicatedSlice(const G4String& pName,
  //                         G4LogicalVolume* pLogical,
  //                         G4LogicalVolume* pMotherLogical,
  //                   const EAxis pAxis,
  //                   const G4int nReplicas,
  //                   const G4double width,
  //                   const G4double half_gap,
  //                   const G4double offset );
  new G4ReplicatedSlice(
    "vol2B", vol2B, vol2A, kYAxis, 6, 20. * cm, 4. * cm, 0.);

  // Division
  //
  G4VSolid* box3A = new G4Box("box3A", 20. * cm, 60. * cm, 50. * cm);
  G4LogicalVolume* vol3A = new G4LogicalVolume(box3A, air, "vol3A");

  // Division cell
  //
  G4VSolid* box3B = new G4Box("box3B", 20. * cm, 10. * cm, 50. * cm);
  G4LogicalVolume* vol3B = new G4LogicalVolume(box3B, scintillator, "vol3B");

  // Division
  //
  // G4PVDivision(const G4String& pName,
  //                    G4LogicalVolume* pLogical,
  //                    G4LogicalVolume* pMother,
  //              const EAxis pAxis,
  //              const G4int nReplicas,
  //              const G4double width,
  //              const G4double offset=0)
  new G4PVDivision("vol3B", vol3B, vol3A, kYAxis, 6, 20. * cm, 0. * cm);

  // Placements of A volumes along z axis
  //
  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0, 0, -2. * m), vol1A, "vol1A", worldV, false, 0);
  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0, 0, 0), vol2A, "vol2A", worldV, false, 1);
  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0, 0, 2. * m), vol3A, "vol3A", worldV, false, 2);

  return (void*)world;
}

class Placements3Para : public G4VPVParameterisation
{
 public:
  Placements3Para(
    const std::vector<std::pair<G4ThreeVector, G4RotationMatrix*>>& Transforms,
    G4VSolid* Solid1 = nullptr, G4VSolid* Solid2 = nullptr, int StartSolid2 = 0,
    G4Material* Mat1 = G4Material::GetMaterial("Scintillator"),
    G4Material* Mat2 = G4Material::GetMaterial("Tungsten"))
    : mTransforms(Transforms),
      mSolid1(Solid1),
      mSolid2(Solid2),
      mStartSolid2(StartSolid2),
      mMat1(Mat1),
      mMat2(Mat2)
  {}

  virtual void ComputeTransformation(
    const G4int copyNo, G4VPhysicalVolume* physVol) const
  {
    physVol->SetTranslation(mTransforms.at(copyNo).first);
    physVol->SetRotation(mTransforms.at(copyNo).second);
  }

  virtual G4Material* ComputeMaterial(
    const G4int copyNo, G4VPhysicalVolume* physVol, const G4VTouchable*)
  {
    if (!mSolid1) {
      return G4VPVParameterisation::ComputeMaterial(copyNo, physVol);
    }
    if (!mSolid2) {
      physVol->GetLogicalVolume()->SetVisAttributes(red);
      return mMat1;
    }
    if (copyNo < mStartSolid2) {
      physVol->GetLogicalVolume()->SetVisAttributes(red);
      return mMat1;
    }
    physVol->GetLogicalVolume()->SetVisAttributes(blue);
    return mMat2;
  }

  virtual G4VSolid* ComputeSolid(const G4int copyNo, G4VPhysicalVolume* physVol)
  {
    if (!mSolid1) {
      return G4VPVParameterisation::ComputeSolid(copyNo, physVol);
    }
    if (!mSolid2) {
      return mSolid1;
    }
    if (copyNo < mStartSolid2) {
      return mSolid1;
    }
    return mSolid2;
  }

 private:
  std::vector<std::pair<G4ThreeVector, G4RotationMatrix*>> mTransforms;
  G4VSolid* mSolid1;
  G4VSolid* mSolid2;
  int mStartSolid2;
  G4Material* mMat1;
  G4Material* mMat2;
  G4VisAttributes* red = new G4VisAttributes(true, G4Colour(1.0, 0.0, 0.0));
  G4VisAttributes* blue = new G4VisAttributes(true, G4Colour(0.0, 0.0, 1.0));
};

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestPlacements3()
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld(2. * m, 1. * m, 4. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Reset world material to air and make invisible
  worldV->SetMaterial(G4Material::GetMaterial("Vacuum"));
  worldV->SetVisAttributes(G4VisAttributes::GetInvisible());

  // colours
  G4VisAttributes* yellow_50 =
    new G4VisAttributes(true, G4Colour(1.0, 0.91, 0.13, 0.3));
  G4VisAttributes* lightgreen =
    new G4VisAttributes(true, G4Colour(0.5, 1.0, 0.5));

  // build holding box for replication
  double HalfLengthHolding = 0.4 * m;
  G4Box* Holding = new G4Box(
    "Holding", HalfLengthHolding, HalfLengthHolding, HalfLengthHolding);
  G4LogicalVolume* HoldingLog = new G4LogicalVolume(
    Holding, G4Material::GetMaterial("Uranium"), "HoldingLog");
  HoldingLog->SetVisAttributes(yellow_50);
  new G4PVPlacement(0, CLHEP::Hep3Vector(0, 0, 0), HoldingLog,
    "HoldingLogPlacement", worldV, false, 0);

  // build box for first layer
  double HalfLenghtFirstLayer = HalfLengthHolding / 8.;
  std::vector<std::pair<G4ThreeVector, G4RotationMatrix*>> Transforms1;
  Transforms1.emplace_back(std::make_pair(
    G4ThreeVector(-0.5 * HalfLengthHolding, -0.5 * HalfLengthHolding, 0),
    nullptr));
  Transforms1.emplace_back(std::make_pair(
    G4ThreeVector(0.5 * HalfLengthHolding, -0.5 * HalfLengthHolding, 0),
    nullptr));
  Transforms1.emplace_back(std::make_pair(
    G4ThreeVector(-0.5 * HalfLengthHolding, 0.5 * HalfLengthHolding, 0),
    nullptr));
  Transforms1.emplace_back(std::make_pair(
    G4ThreeVector(0.5 * HalfLengthHolding, 0.5 * HalfLengthHolding, 0),
    nullptr));
  G4Box* FirstLayer = new G4Box("FirstLayer", HalfLenghtFirstLayer,
    HalfLenghtFirstLayer, HalfLengthHolding);
  G4LogicalVolume* FirstLayerLog = new G4LogicalVolume(
    FirstLayer, G4Material::GetMaterial("Air"), "FirstLayerLog");
  FirstLayerLog->SetVisAttributes(lightgreen);
  new G4PVParameterised("FirstLayerPara", FirstLayerLog, HoldingLog, kZAxis,
    Transforms1.size(), new Placements3Para(Transforms1));

  // build more complicated second layer
  double HalfLenghtSecondLayer = HalfLenghtFirstLayer / 8.;
  std::vector<std::pair<G4ThreeVector, G4RotationMatrix*>> Transforms2;
  Transforms2.emplace_back(std::make_pair(
    G4ThreeVector(-0.5 * HalfLenghtFirstLayer, -0.5 * HalfLenghtFirstLayer, 0),
    nullptr));
  Transforms2.emplace_back(std::make_pair(
    G4ThreeVector(0.5 * HalfLenghtFirstLayer, -0.5 * HalfLenghtFirstLayer, 0),
    nullptr));
  Transforms2.emplace_back(std::make_pair(
    G4ThreeVector(-0.5 * HalfLenghtFirstLayer, 0.5 * HalfLenghtFirstLayer, 0),
    nullptr));
  Transforms2.emplace_back(std::make_pair(
    G4ThreeVector(0.5 * HalfLenghtFirstLayer, 0.5 * HalfLenghtFirstLayer, 0),
    nullptr));
  G4Box* SecondLayer1 = new G4Box("SecondLayer1", HalfLenghtSecondLayer,
    HalfLenghtSecondLayer, HalfLengthHolding);
  G4Tubs* SecondLayer2 = new G4Tubs("SecondLayer1", 0, HalfLenghtSecondLayer,
    HalfLengthHolding, 0, 360 * CLHEP::deg);
  G4LogicalVolume* SecondLayerLog = new G4LogicalVolume(
    SecondLayer1, G4Material::GetMaterial("Vacuum"), "SecondLayerLog");
  new G4PVParameterised("SecondLayerPara", SecondLayerLog, FirstLayerLog,
    kZAxis, Transforms2.size(),
    new Placements3Para(Transforms2, SecondLayer1, SecondLayer2, 2));

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestReflections(G4bool fullPhi)
{

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(8.0 * m, 3. * m, 3. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  PlaceSolids(worldV, fullPhi, true, false, 1. * m);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestScaledSolids(G4bool fullPhi)
{

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(8.0 * m, 3. * m, 3. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  PlaceSolids(worldV, fullPhi, true, true, 1. * m);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestAssemblies()
{
  // Example for assemblies from Root tutorial

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(10. * m, 10. * m, 1. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, G4ThreeVector(), worldV, "world", 0, false, 0);

  // Make the elementary assembly of the whole structure
  //
  G4int ntooth = 5;
  G4double xplate = 25. * cm;
  G4double yplate = 50. * cm;
  G4double xtooth = 10. * cm;
  G4double ytooth = 0.5 * yplate / ntooth;
  G4double dshift = 2. * xplate + xtooth;
  G4double xt, yt;

  G4AssemblyVolume* tplate = new G4AssemblyVolume();

  // plate volume
  G4Box* plateS = new G4Box("plateS", xplate, yplate, 1. * cm);
  G4LogicalVolume* plateV =
    new G4LogicalVolume(plateS, fBasicMaterial, "PLATE");

  // tooth volume
  G4Box* toothS = new G4Box("toothS", xtooth, ytooth, 1. * cm);
  G4LogicalVolume* toothV =
    new G4LogicalVolume(toothS, fBasicMaterial, "TOOTH");

  // compose assembly
  G4ThreeVector pos0(0., 0., 0.);
  tplate->AddPlacedVolume(plateV, pos0, 0);
  for (G4int i = 0; i < ntooth; i++) {
    xt = xplate + xtooth;
    yt = -yplate + (4 * i + 1) * ytooth;
    G4ThreeVector pos1(xt, yt, 0);
    tplate->AddPlacedVolume(toothV, pos1, 0);

    xt = -xplate - xtooth;
    yt = -yplate + (4 * i + 3) * ytooth;
    G4ThreeVector pos2(xt, yt, 0);
    tplate->AddPlacedVolume(toothV, pos2, 0);
  }

  /*
    // simple placement in the world
    G4RotationMatrix* rotv = 0;
    G4ThreeVector posv;
    tplate->MakeImprint(worldV, posv, rotv);
  */

  G4RotationMatrix* rot1 = new G4RotationMatrix();
  rot1->rotateX(90. * deg);
  G4RotationMatrix* rot;
  G4AssemblyVolume* cell = new G4AssemblyVolume();
  // Make a hexagone cell out of 6 toothplates. These can zip togeather
  // without generating overlaps (they are self-contained)
  for (G4int i2 = 0; i2 < 6; i2++) {
    G4double phi = 60. * i2 * deg;
    G4double xp = dshift * sin(phi);
    G4double yp = -dshift * cos(phi);
    rot = new G4RotationMatrix(*rot1);
    rot->rotateZ(phi);
    G4ThreeVector pos(xp, yp, 0.);
    cell->AddPlacedAssembly(tplate, pos, rot);
  }
  /*
    // simple placement in the world
    G4RotationMatrix* rotv = 0;
    G4ThreeVector posv;
    cell->MakeImprint(worldV, posv, rotv);
    return (void*) world;
  */
  // Make a row as an assembly of cells, then combine rows in a honeycomb
  // structure. This again works without any need to define rows as
  // "overlapping"
  G4AssemblyVolume* row = new G4AssemblyVolume();
  G4int ncells = 5;
  for (G4int i3 = 0; i3 < ncells; i3++) {
    G4double ycell = (2 * i3 + 1) * (dshift + 10. * cm);
    G4ThreeVector pos1(0., ycell, 0.);
    row->AddPlacedAssembly(cell, pos1, 0);
    G4ThreeVector pos2(0., -ycell, 0.);
    row->AddPlacedAssembly(cell, pos2, 0);
  }
  /*
    // simple placement in the world
    G4RotationMatrix* rotv = 0;
    G4ThreeVector posv;
    row->MakeImprint(worldV, posv, rotv);
    return (void*) world;
  */
  G4double dxrow = 3. * (dshift + 10. * cm) * tan(30. * deg);
  G4double dyrow = dshift + 10. * cm;
  G4int nrows = 5;
  for (G4int i4 = 0; i4 < nrows; i4++) {
    G4double xrow = 0.5 * (2 * i4 + 1) * dxrow;
    G4double yrow = 0.5 * dyrow;
    if ((i4 % 2) == 0) yrow = -yrow;
    G4ThreeVector pos1(xrow, yrow, 0.);
    row->MakeImprint(worldV, pos1, 0);
    G4ThreeVector pos2(-xrow, -yrow, 0.);
    row->MakeImprint(worldV, pos2, 0);
  }

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestAssemblies2()
{
  // Example for assemblies with reflections

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(2. * m, 2. * m, 1. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, G4ThreeVector(), worldV, "world", 0, false, 0);

  // Assembly
  //
  G4AssemblyVolume* assembly = new G4AssemblyVolume();

  // Cons volume
  G4VSolid* consS = new G4Cons(
    "consS", 10. * cm, 40. * cm, 20. * cm, 60. * cm, 50 * cm, 0., 360. * deg);

  G4LogicalVolume* consV = new G4LogicalVolume(consS, fBasicMaterial, "CONS");

  // Transformations
  //
  HepGeom::Transform3D transform1 =
    HepGeom::Translate3D(110. * cm, 0., 0.) * HepGeom::RotateY3D(90. * deg);

  HepGeom::Transform3D transform2 = HepGeom::ReflectX3D() *
                                    HepGeom::Translate3D(110. * cm, 0., 0.) *
                                    HepGeom::RotateY3D(90. * deg);

  HepGeom::Transform3D transform3 =
    HepGeom::Translate3D(0., 110. * cm, 0.) * HepGeom::RotateX3D(-90. * deg);

  HepGeom::Transform3D transform4 = HepGeom::ReflectY3D() *
                                    HepGeom::Translate3D(0., 110. * cm, 0.) *
                                    HepGeom::RotateX3D(-90. * deg);
  /*
    // Simple placement
    G4ReflectionFactory::Instance()
      ->Place( transform1, "cons", consV, worldV, false, 0);
    G4ReflectionFactory::Instance()
      ->Place( transform2, "cons", consV, worldV, false, 0);
    G4ReflectionFactory::Instance()
      ->Place( transform3, "cons", consV, worldV, false, 0);
    G4ReflectionFactory::Instance()
      ->Place( transform4, "cons", consV, worldV, false, 0);

  */
  // Place via assembly
  assembly->AddPlacedVolume(consV, transform1);
  assembly->AddPlacedVolume(consV, transform2);
  assembly->AddPlacedVolume(consV, transform3);
  assembly->AddPlacedVolume(consV, transform4);

  // Make imprint
  G4RotationMatrix* rotv = 0;
  G4ThreeVector posv;
  assembly->MakeImprint(worldV, posv, rotv);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids1()
{
  // Only translation in solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4. * m, 1. * m, 4. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Create solids
  G4VSolid* solid1 = new G4Box("boxS", 50. * cm, 50. * cm, 50. * cm);

  G4VSolid* solid2 = new G4Cons(
    "consS", 10. * cm, 30. * cm, 20. * cm, 40. * cm, 100. * cm, 0., 360. * deg);

  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1 =
    new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25 * m, 0., -2. * m), volume1,
    "solid1", worldV, false, 0);

  G4LogicalVolume* volume2 =
    new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, CLHEP::Hep3Vector(1.25 * m, 0., -2. * m), volume2,
    "solid2", worldV, false, 0);

  // Intersection
  //
  G4VSolid* intersectionS =
    new G4IntersectionSolid("intersection_solid1_solid2_S", solid1, solid2, 0,
      CLHEP::Hep3Vector(20. * cm, 0., 0.));
  G4LogicalVolume* intersectionV = new G4LogicalVolume(
    intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(-2.5 * m, 0., 2. * m), intersectionV,
    "intersection_solid1_solid2", worldV, false, 0);

  // Subtraction
  //
  G4VSolid* subtractionS = new G4SubtractionSolid("subtraction_solid1_solid2_S",
    solid1, solid2, 0, CLHEP::Hep3Vector(20. * cm, 0., 0.));
  G4LogicalVolume* subtractionV = new G4LogicalVolume(
    subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., 2. * m), subtractionV,
    "subtraction_solid1_solid2", worldV, false, 0);

  // Union
  //
  G4VSolid* unionS = new G4UnionSolid("union_solid1_solid2_S", solid1, solid2,
    0, CLHEP::Hep3Vector(20. * cm, 0., 0.));
  G4LogicalVolume* unionV =
    new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(2.5 * m, 0., 2. * m), unionV,
    "union_solid1_solid2", worldV, false, 0);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids2()
{
  // Translation + rotation in solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4. * m, 1. * m, 4. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Create solids
  G4VSolid* solid1 = new G4Box("boxS", 50. * cm, 50. * cm, 50. * cm);

  G4VSolid* solid2 = new G4Cons(
    "consS", 10. * cm, 30. * cm, 20. * cm, 40. * cm, 100. * cm, 0., 360. * deg);

  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1 =
    new G4LogicalVolume(solid1, fBasicMaterial, "solid1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25 * m, 0., -2. * m), volume1,
    "solid1", worldV, false, 0);

  G4LogicalVolume* volume2 =
    new G4LogicalVolume(solid2, fBasicMaterial, "solid2");
  new G4PVPlacement(0, CLHEP::Hep3Vector(1.25 * m, 0., -2. * m), volume2,
    "solid2", worldV, false, 0);

  // Define displacement transformations
  //

  // Rotate solid1
  CLHEP::HepRotation* rot1 = new CLHEP::HepRotation();
  rot1->rotateY(-45. * deg);

  // Rotate + translate solid2
  //
  CLHEP::HepRotation* rot2 = new CLHEP::HepRotation();
  rot2->rotateY(45. * deg);
  rot2->rotateX(-30. * deg);
  CLHEP::Hep3Vector tr2 = CLHEP::Hep3Vector(20. * cm, 0., 0.);

  // Intersection
  //
  G4VSolid* intersectionS = new G4IntersectionSolid(
    "intersection_solid1_solid2_S", solid1, solid2, rot2, tr2);
  G4LogicalVolume* intersectionV = new G4LogicalVolume(
    intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector(-2.5 * m, 0., 2. * m),
    intersectionV, "intersection_solid1_solid2", worldV, false, 0);

  // Subtraction
  //
  G4VSolid* subtractionS = new G4SubtractionSolid(
    "subtraction_solid1_solid2_S", solid1, solid2, rot2, tr2);
  G4LogicalVolume* subtractionV = new G4LogicalVolume(
    subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector(0., 0., 2. * m), subtractionV,
    "subtraction_solid1_solid2", worldV, false, 0);

  // Union
  //
  G4VSolid* unionS =
    new G4UnionSolid("union_solid1_solid2_S", solid1, solid2, rot2, tr2);
  G4LogicalVolume* unionV =
    new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector(2.5 * m, 0., 2. * m), unionV,
    "union_solid1_solid2", worldV, false, 0);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids3()
{
  // Translation + reflection in solid displacement

  G4cout << "Reflections are not allowed in Boolean solids in Geant4."
         << G4endl;
  exit(1);
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestDisplacedSolids1()
{
  // Test solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(60. * cm, 60. * cm, 160. * cm);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Create solids

  // Normal solid
  //
  G4VSolid* solid1 = new G4Box("boxS1", 50. * cm, 50. * cm, 50. * cm);

  G4LogicalVolume* volume1 =
    new G4LogicalVolume(solid1, fBasicMaterial, "volume1");

  // Chained displaced solids
  //
  G4VSolid* solid2 = new G4Box("boxS2", 50. * cm, 50. * cm, 50. * cm);

  G4DisplacedSolid* solid2A =
    new G4DisplacedSolid("boxS2A", solid2, 0, G4ThreeVector(0., 0., 50. * cm));

  G4DisplacedSolid* solid2B =
    new G4DisplacedSolid("boxS2B", solid2A, 0, G4ThreeVector(0., 0., 50. * cm));

  G4DisplacedSolid* solid2C =
    new G4DisplacedSolid("boxS2C", solid2B, 0, G4ThreeVector(0., 0., 50. * cm));

  G4LogicalVolume* volume2C =
    new G4LogicalVolume(solid2C, fBasicMaterial, "volume2C");

  // Daughter to be placed in displaced solid
  //
  G4VSolid* solid3 = new G4Box("boxS3", 20. * cm, 20. * cm, 20. * cm);

  G4LogicalVolume* volume3 =
    new G4LogicalVolume(solid3, fBasicMaterial, "volume3");

  // Daughter to be placed in normal solid
  //
  G4VSolid* solid4 = new G4Box("boxS4", 20. * cm, 20. * cm, 10. * cm);

  G4LogicalVolume* volume4 =
    new G4LogicalVolume(solid4, fBasicMaterial, "volume4");

  // Daughter with displaced solid to be placed in displaced solid
  //
  G4VSolid* solid5 = new G4Box("boxS5", 20. * cm, 20. * cm, 5. * cm);

  G4VSolid* solid5A =
    new G4DisplacedSolid("boxS5A", solid5, G4ThreeVector(0., 0., 40. * cm));

  G4LogicalVolume* volume5A =
    new G4LogicalVolume(solid5A, fBasicMaterial, "volume3");

  // Make placements
  //
  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., -100. * cm), volume1,
    "volume1", worldV, false, 1);

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., -100. * cm), volume2C,
    "volume2C", worldV, false, 2);

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., 150. * cm), volume3, "volume3",
    volume2C, false, 1);

  new G4PVPlacement(0, CLHEP::Hep3Vector(0. * cm, 0. * cm, 0.), volume4,
    "volume4", volume1, false, 1);

  new G4PVPlacement(0, CLHEP::Hep3Vector(0. * cm, 0. * cm, 150. * cm), volume5A,
    "volume5A", volume2C, false, 2);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestDisplacedSolids2()
{
  // Test BooleanSolids2 where displacement is defined via
  // Displaced solid

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4. * m, 1. * m, 4. * m);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Create solids
  G4VSolid* solid1 = new G4Box("boxS", 50. * cm, 50. * cm, 50. * cm);

  G4VSolid* solid2 = new G4Cons(
    "consS", 10. * cm, 30. * cm, 20. * cm, 40. * cm, 100. * cm, 0., 360. * deg);

  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1 =
    new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25 * m, 0., -2. * m), volume1,
    "solid1", worldV, false, 0);

  G4LogicalVolume* volume2 =
    new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, CLHEP::Hep3Vector(1.25 * m, 0., -2. * m), volume2,
    "solid2", worldV, false, 0);

  // Rotate solid1
  //
  CLHEP::HepRotation* rot1 = new CLHEP::HepRotation();
  rot1->rotateY(-45. * deg);
  CLHEP::Hep3Vector tr1 = CLHEP::Hep3Vector();

  // Rotate + translate solid2
  //
  CLHEP::HepRotation* rot2 = new CLHEP::HepRotation();
  // rot2->rotateY( 45.*deg);
  rot2->rotateX(-30. * deg);
  CLHEP::Hep3Vector tr2 = CLHEP::Hep3Vector(20. * cm, 0., 0.);

  // Displaced solids
  //
  G4DisplacedSolid* dsolid1 = new G4DisplacedSolid("dboxS", solid1, rot1, tr1);

  G4DisplacedSolid* dsolid2 = new G4DisplacedSolid("dconsS", solid2, rot2, tr2);

  // Intersection
  //
  G4VSolid* intersectionS = new G4IntersectionSolid(
    "intersection_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, CLHEP::Hep3Vector());
  G4LogicalVolume* intersectionV = new G4LogicalVolume(
    intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(-2.5 * m, 0., 2. * m), intersectionV,
    "intersection_solid1_solid2", worldV, false, 0);

  // Subtraction
  //
  G4VSolid* subtractionS = new G4SubtractionSolid(
    "subtraction_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, CLHEP::Hep3Vector());
  G4LogicalVolume* subtractionV = new G4LogicalVolume(
    subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., 2. * m), subtractionV,
    "subtraction_solid1_solid2", worldV, false, 0);

  // Union
  //
  G4VSolid* unionS = new G4UnionSolid(
    "union_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, CLHEP::Hep3Vector());
  G4LogicalVolume* unionV =
    new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(2.5 * m, 0., 2. * m), unionV,
    "union_solid1_solid2", worldV, false, 0);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestMultiUnion()
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld(60. * cm, 60. * cm, 160. * cm);
  G4VPhysicalVolume* world =
    new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0);

  // Define two -G4Box- shapes
  G4Box* box1 = new G4Box("Box1", 5. * cm, 5. * cm, 10. * cm);
  G4Box* box2 = new G4Box("Box2", 5. * cm, 5. * cm, 10. * cm);

  // Define displacements for the shapes
  G4RotationMatrix rotation = G4RotationMatrix();
  G4ThreeVector position1 = G4ThreeVector(0., 0., 0. * cm);
  G4ThreeVector position2 = G4ThreeVector(0., 3. * cm, 10. * cm);
  G4Transform3D tr1 = G4Transform3D(rotation, position1);
  G4Transform3D tr2 = G4Transform3D(rotation, position2);

  // Initialise a MultiUnion structure
  G4MultiUnion* multiUnion = new G4MultiUnion("boxesUnion");

  // Add the shapes to the structure
  multiUnion->AddNode(*box1, tr1);
  multiUnion->AddNode(*box2, tr2);

  // Cons shape (for testing reflection)
  // G4Cons* cons = new G4Cons(
  //   "consS", 1.*cm, 4.*cm, 2.*cm, 6.*cm, 10.*cm, 0., 360.*deg);
  // HepGeom::ReflectZ3D reflect3D;
  // multiUnion->AddNode(*cons, reflect3D);

  // Finally close the structure
  multiUnion->Voxelize();

  // Associate it to a logical volume as a normal solid
  G4LogicalVolume* multiUnionV =
    new G4LogicalVolume(multiUnion, fBasicMaterial, "boxesUnion");

  new G4PVPlacement(
    0, CLHEP::Hep3Vector(0, 0, 0), multiUnionV, "boxesUnion", worldV, false, 0);

  return (void*)world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestSpecial()
{
  // Geometry defined via external user code

  /*
    MyDetectorConstruction* myDetector = new MyDetectorConstruction();

    G4VPhysicalVolume* world = myDetector->Construct();

    return (void*) world;
  */

  return 0;
}
