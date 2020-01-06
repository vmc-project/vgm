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
// Class TstGeometryViaVGM
// -------------------------------
// Class for building geometry vis VGM
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"

#include "ClhepVGM/Units.h"
#include "ClhepVGM/transform.h"

#include "TstGeometryViaVGM.hh"

using namespace VGM;

using CLHEP::atmosphere;
using CLHEP::cm;
using CLHEP::cm3;
using CLHEP::deg;
using CLHEP::g;
using CLHEP::hep_pascal;
using CLHEP::kelvin;
using CLHEP::m;
using CLHEP::mg;
using CLHEP::mole;

//_____________________________________________________________________________
TstGeometryViaVGM::TstGeometryViaVGM(IFactory* factory)
  : TstVGeometry(),
    fFactory(factory),
    fCm(ClhepVGM::Units::Length(cm)),
    fDeg(ClhepVGM::Units::Angle(deg)),
    fGcm3(ClhepVGM::Units::MassDensity(g / cm3)),
    fGmole(ClhepVGM::Units::AtomicWeight(g / mole)),
    fKelvin(ClhepVGM::Units::Temperature(kelvin)),
    fAtm(ClhepVGM::Units::Pressure(atmosphere))
{
  //
}

//_____________________________________________________________________________
TstGeometryViaVGM::~TstGeometryViaVGM() {}

//
// private methods
//

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateWorld(
  double x, double y, double z, const std::string& materialName)
{
  // Create world volume
  // ---

  ISolid* worldS = fFactory->CreateBox("worldS", x, y, z);

  return fFactory->CreateVolume("world", worldS, materialName);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateNewSolid()
{
  return CreateCtubs(0, 360 * fDeg);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateArb8()
{
  std::vector<VGM::TwoVector> vertices;
  vertices.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  vertices.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));

  return fFactory->CreateArb8("arb8S", 75. * fCm, vertices);
}

//_____________________________________________________________________________
void TstGeometryViaVGM::CreateArb8Solids(std::vector<VGM::IVolume*>& volumes)
{
  // 1 down vertex: 0=1=2=3
  std::vector<VGM::TwoVector> vertices1;
  vertices1.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices1.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices1.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices1.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices1.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices1.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices1.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices1.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  ISolid* arbS1 = fFactory->CreateArb8("arbS1", 75. * fCm, vertices1);
  volumes.push_back(fFactory->CreateVolume("arb1", arbS1, "Basic"));

  // 2 down vertices: 0=1 2=3
  std::vector<VGM::TwoVector> vertices2;
  vertices2.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices2.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices2.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  ISolid* arbS2 = fFactory->CreateArb8("arbS2", 75. * fCm, vertices2);
  volumes.push_back(fFactory->CreateVolume("arb2", arbS2, "Basic"));

  // 1 up vertex: 4=5=6=7
  std::vector<VGM::TwoVector> vertices3;
  vertices3.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices3.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices3.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices3.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  vertices3.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices3.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices3.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices3.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  ISolid* arbS3 = fFactory->CreateArb8("arbS3", 75. * fCm, vertices3);
  volumes.push_back(fFactory->CreateVolume("arb3", arbS3, "Basic"));

  // 2 up vertices: 4=5 6=7
  std::vector<VGM::TwoVector> vertices4;
  vertices4.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices4.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices4.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices4.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  vertices4.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices4.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices4.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices4.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  ISolid* arbS4 = fFactory->CreateArb8("arbS4", 75. * fCm, vertices4);
  volumes.push_back(fFactory->CreateVolume("arb4", arbS4, "Basic"));

  // 1 down vertex: 0=1=2=3
  // 3 up vertices: 4=5
  std::vector<VGM::TwoVector> vertices5;
  vertices5.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices5.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices5.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices5.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices5.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices5.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices5.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices5.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices5.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  ISolid* arbS5 = fFactory->CreateArb8("arbS5", 75. * fCm, vertices5);
  volumes.push_back(fFactory->CreateVolume("arb5", arbS5, "Basic"));

  // 3 down vertices: 0=1
  // 1 up vertex: 4=5=6=7
  std::vector<VGM::TwoVector> vertices6;
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices6.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices6.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  ISolid* arbS6 = fFactory->CreateArb8("arbS6", 75. * fCm, vertices6);
  volumes.push_back(fFactory->CreateVolume("arb6", arbS6, "Basic"));

  // all up & down vertices different
  std::vector<VGM::TwoVector> vertices7;
  vertices7.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices7.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices7.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices7.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  vertices7.push_back(VGM::TwoVector(45. * fCm, -15. * fCm));
  vertices7.push_back(VGM::TwoVector(0. * fCm, -75. * fCm));
  vertices7.push_back(VGM::TwoVector(-30. * fCm, -75. * fCm));
  vertices7.push_back(VGM::TwoVector(15. * fCm, -15. * fCm));
  ISolid* arbS7 = fFactory->CreateArb8("arbS7", 75. * fCm, vertices7);
  volumes.push_back(fFactory->CreateVolume("arb7", arbS7, "Basic"));

  /*
    // 3 down vertices: 0=1 (twisted )
    std::vector<VGM::TwoVector> vertices8;
    vertices8.push_back(VGM::TwoVector( 45.*fCm, -15.*fCm));
    vertices8.push_back(VGM::TwoVector( 45.*fCm, -15.*fCm));
    vertices8.push_back(VGM::TwoVector(-30.*fCm, -75.*fCm));
    vertices8.push_back(VGM::TwoVector( 15.*fCm, -15.*fCm));
    vertices8.push_back(VGM::TwoVector( 45.*fCm, -15.*fCm));
    vertices8.push_back(VGM::TwoVector(  0.*fCm, -75.*fCm));
    vertices8.push_back(VGM::TwoVector(-30.*fCm, -75.*fCm));
    vertices8.push_back(VGM::TwoVector( 15.*fCm, -15.*fCm));
    ISolid* arbS8 = fFactory->CreateArb8("arbS8", 75.*fCm, vertices8);
    volumes.push_back(fFactory->CreateVolume("arb8", arbS8, "Basic"));

    // 3 up vertices: 4=5 (twisted )
    std::vector<VGM::TwoVector> vertices9;
    vertices9.push_back(VGM::TwoVector( 45.*fCm, -15.*fCm));
    vertices9.push_back(VGM::TwoVector(  0.*fCm, -75.*fCm));
    vertices9.push_back(VGM::TwoVector(-30.*fCm, -75.*fCm));
    vertices9.push_back(VGM::TwoVector( 15.*fCm, -15.*fCm));
    vertices9.push_back(VGM::TwoVector(  0.*fCm, -75.*fCm));
    vertices9.push_back(VGM::TwoVector(  0.*fCm, -75.*fCm));
    vertices9.push_back(VGM::TwoVector(-30.*fCm, -75.*fCm));
    vertices9.push_back(VGM::TwoVector( 15.*fCm, -15.*fCm));
    ISolid* arbS9 = fFactory->CreateArb8("arbS9", 75.*fCm, vertices9);
    volumes.push_back(fFactory->CreateVolume("arb9", arbS9, "Basic"));
  */
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateBox()
{
  return fFactory->CreateBox("boxS", 20. * fCm, 60. * fCm, 50. * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateCons(double sphi, double dphi)
{
  return fFactory->CreateCons(
    "consS", 10. * fCm, 40. * fCm, 20. * fCm, 60. * fCm, 50 * fCm, sphi, dphi);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateEllipsoid()
{
  return fFactory->CreateEllipsoid(
    "ellipsoidS", 10. * fCm, 20. * fCm, 50 * fCm, -10. * fCm, 60. * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateEllipticalTube()
{
  return fFactory->CreateEllipticalTube(
    "eltuS", 20. * fCm, 30. * fCm, 50 * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateExtrudedSolid1()
{
  std::vector<VGM::TwoVector> polygon;
  polygon.push_back(VGM::TwoVector(-30. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(-30. * fCm, 30. * fCm));
  polygon.push_back(VGM::TwoVector(30. * fCm, 30. * fCm));
  polygon.push_back(VGM::TwoVector(30. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(15. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(15. * fCm, 15. * fCm));
  polygon.push_back(VGM::TwoVector(-15. * fCm, 15. * fCm));
  polygon.push_back(VGM::TwoVector(-15. * fCm, -30. * fCm));

  double array1[] = { -40. * cm, -20. * cm, 10. * cm, 1.5 };
  double array2[] = { 10. * cm, 0. * cm, 0. * cm, 0.5 };
  double array3[] = { 15. * cm, 0. * cm, 0. * cm, 0.7 };
  double array4[] = { 40. * cm, 20. * cm, 20. * cm, 0.9 };

  std::vector<std::vector<double> > zsections;
  zsections.push_back(std::vector<double>(array1, array1 + 4));
  zsections.push_back(std::vector<double>(array2, array2 + 4));
  zsections.push_back(std::vector<double>(array3, array3 + 4));
  zsections.push_back(std::vector<double>(array4, array4 + 4));

  return fFactory->CreateExtrudedSolid("xtru1S", polygon, zsections);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateExtrudedSolid2()
{
  std::vector<VGM::TwoVector> polygon;
  polygon.push_back(VGM::TwoVector(-30. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(-30. * fCm, 30. * fCm));
  polygon.push_back(VGM::TwoVector(30. * fCm, 30. * fCm));
  polygon.push_back(VGM::TwoVector(30. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(15. * fCm, -30. * fCm));
  polygon.push_back(VGM::TwoVector(15. * fCm, 15. * fCm));
  polygon.push_back(VGM::TwoVector(-15. * fCm, 15. * fCm));
  polygon.push_back(VGM::TwoVector(-15. * fCm, -30. * fCm));

  double array1[] = { -40. * cm, -20. * cm, 10. * cm, 1.5 };
  double array2[] = { 10. * cm, 0. * cm, 0. * cm, 0.5 };
  double array3[] = { 10. * cm, 0. * cm, 0. * cm, 0.7 };
  double array4[] = { 40. * cm, 20. * cm, 20. * cm, 0.9 };

  std::vector<std::vector<double> > zsections;
  zsections.push_back(std::vector<double>(array1, array1 + 4));
  zsections.push_back(std::vector<double>(array2, array2 + 4));
  zsections.push_back(std::vector<double>(array3, array3 + 4));
  zsections.push_back(std::vector<double>(array4, array4 + 4));

  return fFactory->CreateExtrudedSolid("xtru2S", polygon, zsections);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateHype()
{
  return fFactory->CreateHype(
    "hypeS", 20. * fCm, 30. * fCm, 30. * fDeg, 40. * fDeg, 50. * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreatePara()
{
  return fFactory->CreatePara("paraS", 40. * fCm, 60. * fCm, 50. * fCm,
    30. * fDeg, 30. * fDeg, 30. * fDeg);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateParaboloid()
{
  return fFactory->CreateParaboloid(
    "paraboloidS", 20. * fCm, 45. * fCm, 50. * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreatePolycone(double sphi, double dphi)
{
  // Define parameters

  int nofPlanes = 3;
  double z[3];
  double rin[3];
  double rout[3];

  z[0] = -50. * fCm;
  rin[0] = 10. * fCm;
  rout[0] = 50. * fCm;

  z[1] = 10. * fCm;
  rin[1] = 20. * fCm;
  rout[1] = 30. * fCm;

  z[2] = 40. * fCm;
  rin[2] = 30. * fCm;
  rout[2] = 60. * fCm;

  return fFactory->CreatePolycone(
    "pconeS", sphi, dphi, nofPlanes, z, rin, rout);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreatePolyhedra(double sphi, double dphi)
{
  // Define parameters

  int nofSides = 4;
  int nofPlanes = 3;
  double z[3];
  double rin[3];
  double rout[3];

  z[0] = -50. * fCm;
  rin[0] = 10. * fCm;
  rout[0] = 40. * fCm;

  z[1] = 10. * fCm;
  rin[1] = 20. * fCm;
  rout[1] = 30. * fCm;

  z[2] = 40. * fCm;
  rin[2] = 30. * fCm;
  rout[2] = 50. * fCm;

  return fFactory->CreatePolyhedra(
    "phedraS", sphi, dphi, nofSides, nofPlanes, z, rin, rout);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateSphere(double sphi, double dphi)
{
  return fFactory->CreateSphere(
    "sphereS", 20. * fCm, 60. * fCm, sphi, dphi, sphi / 2., dphi / 2.);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateTessellatedSolid()
{
  double targetSize = 100. * fCm;

  VGM::ThreeVector vertex;
  std::vector<VGM::ThreeVector> facet1;
  VGM::ThreeVector vertex1(3), vertex2(3), vertex3(3), vertex4(3);
  vertex1[0] = -targetSize;
  vertex1[1] = -targetSize;
  vertex1[2] = 0.0;
  vertex2[0] = +targetSize;
  vertex2[1] = -targetSize;
  vertex2[2] = 0.0;
  vertex3[0] = 0.0;
  vertex3[1] = 0.0;
  vertex3[2] = +targetSize;
  facet1.push_back(vertex1);
  facet1.push_back(vertex2);
  facet1.push_back(vertex3);

  std::vector<VGM::ThreeVector> facet2;
  vertex1[0] = +targetSize;
  vertex1[1] = -targetSize;
  vertex1[2] = 0.0;
  vertex2[0] = +targetSize;
  vertex2[1] = +targetSize;
  vertex2[2] = 0.0;
  vertex3[0] = 0.0;
  vertex3[1] = 0.0;
  vertex3[2] = +targetSize;
  facet2.push_back(vertex1);
  facet2.push_back(vertex2);
  facet2.push_back(vertex3);

  std::vector<VGM::ThreeVector> facet3;
  vertex1[0] = +targetSize;
  vertex1[1] = +targetSize;
  vertex1[2] = 0.0;
  vertex2[0] = -targetSize;
  vertex2[1] = +targetSize;
  vertex2[2] = 0.0;
  vertex3[0] = 0.0;
  vertex3[1] = 0.0;
  vertex3[2] = +targetSize;
  facet3.push_back(vertex1);
  facet3.push_back(vertex2);
  facet3.push_back(vertex3);

  std::vector<VGM::ThreeVector> facet4;
  vertex1[0] = -targetSize;
  vertex1[1] = +targetSize;
  vertex1[2] = 0.0;
  vertex2[0] = -targetSize;
  vertex2[1] = -targetSize;
  vertex2[2] = 0.0;
  vertex3[0] = 0.0;
  vertex3[1] = 0.0;
  vertex3[2] = +targetSize;
  facet4.push_back(vertex1);
  facet4.push_back(vertex2);
  facet4.push_back(vertex3);

  std::vector<VGM::ThreeVector> facet5;
  vertex1[0] = -targetSize;
  vertex1[1] = -targetSize;
  vertex1[2] = 0.0;
  vertex2[0] = -targetSize;
  vertex2[1] = +targetSize;
  vertex2[2] = 0.0;
  vertex3[0] = +targetSize;
  vertex3[1] = +targetSize;
  vertex3[2] = 0.0;
  vertex4[0] = +targetSize;
  vertex4[1] = -targetSize;
  vertex4[2] = 0.0;
  facet5.push_back(vertex1);
  facet5.push_back(vertex2);
  facet5.push_back(vertex3);
  facet5.push_back(vertex4);

  std::vector<std::vector<VGM::ThreeVector> > facets;
  facets.push_back(facet1);
  facets.push_back(facet2);
  facets.push_back(facet3);
  facets.push_back(facet4);
  facets.push_back(facet5);

  return fFactory->CreateTessellatedSolid("tessellatedS", facets);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateTorus(double sphi, double dphi)
{
  return fFactory->CreateTorus(
    "torusS", 20. * fCm, 30. * fCm, 40. * fCm, sphi, dphi);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateTrap()
{
  return fFactory->CreateTrap("trapS", 30. * fCm, 25. * fDeg, 35. * fDeg,
    20. * fCm, 10. * fCm, 15. * fCm, 0. * fDeg, 20. * fCm, 10. * fCm, 15. * fCm,
    0. * fDeg);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateTrd()
{
  return fFactory->CreateTrd(
    "trdS", 20. * fCm, 30 * fCm, 40. * fCm, 50. * fCm, 50. * fCm);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateTubs(double sphi, double dphi)
{
  return fFactory->CreateTubs(
    "tubsS", 20. * fCm, 40 * fCm, 50. * fCm, sphi, dphi);
}

//_____________________________________________________________________________
ISolid* TstGeometryViaVGM::CreateCtubs(double /*sphi*/, double /*dphi*/)
{
  return fFactory->CreateCtubs("ctubsS", 20. * fCm, 30 * fCm, 60.49 * fCm,
    330. * fDeg, 280. * fDeg, 0.00, 0.64, -0.77, 0.00, 0.09, 0.87);
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateVolume(ISolid* solid, bool scale)
{
  HepGeom::Scale3D scale3D(0.8, 0.5, 0.25);

  // Remove "S" from solid name
  std::string name = solid->Name();
  name.erase(name.find("S"), 1);

  ISolid* finalSolid = solid;
  if (scale) {
    finalSolid = fFactory->CreateScaledSolid(
      solid->Name(), solid, ClhepVGM::TransformScale(scale3D));
  }

  return fFactory->CreateVolume(name, finalSolid, "Basic");
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::PlaceSolids(
  IVolume* mother, bool fullPhi, bool reflect, bool scale, double zpos)
{
  double sphi = 0. * fDeg;
  double dphi = 360. * fDeg;
  if (!fullPhi) {
    sphi = 45. * fDeg;
    dphi = 90. * fDeg;
  }

  int counter = 0;
  double x0 = -500. * fCm;
  double dx = 150. * fCm;
  double dy = 150. * fCm;

  HepGeom::ReflectZ3D reflect3D;

  // Box
  //
  ISolid* box = CreateBox();
  IVolume* boxV = CreateVolume(box, scale);
  fFactory->CreatePlacement("box", 0, boxV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("box", 0, boxV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Cons
  //
  ISolid* cons = CreateCons(sphi, dphi);
  IVolume* consV = CreateVolume(cons, scale);
  fFactory->CreatePlacement("cons", 0, consV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("cons", 0, consV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Elliptical tube
  //
  ISolid* eltu = CreateEllipticalTube();
  IVolume* eltuV = CreateVolume(eltu, scale);
  fFactory->CreatePlacement("eltu", 0, eltuV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("eltu", 0, eltuV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Para
  //
  ISolid* para = CreatePara();
  IVolume* paraV = CreateVolume(para, scale);
  fFactory->CreatePlacement("para", 0, paraV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("para", 0, paraV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Polycone
  //
  ISolid* pcone = CreatePolycone(sphi, dphi);
  IVolume* pconeV = CreateVolume(pcone, scale);
  fFactory->CreatePlacement("pcone", 0, pconeV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("pcone", 0, pconeV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Polyhedra
  //
  ISolid* phedra = CreatePolyhedra(sphi, dphi);
  IVolume* phedraV = CreateVolume(phedra, scale);
  fFactory->CreatePlacement("phedra", 0, phedraV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("phedra", 0, phedraV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Sphere
  //
  ISolid* sphere = CreateSphere(sphi, dphi);
  IVolume* sphereV = CreateVolume(sphere, scale);
  fFactory->CreatePlacement("sphere", 0, sphereV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("sphere", 0, sphereV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Torus
  //
  ISolid* torus = CreateTorus(sphi, dphi);
  IVolume* torusV = CreateVolume(torus, scale);
  fFactory->CreatePlacement("torus", 0, torusV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("torus", 0, torusV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Trap
  //
  ISolid* trap = CreateTrap();
  IVolume* trapV = CreateVolume(trap, scale);
  fFactory->CreatePlacement("trap", 0, trapV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("trap", 0, trapV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Trd
  //
  ISolid* trd = CreateTrd();
  IVolume* trdV = CreateVolume(trd, scale);
  fFactory->CreatePlacement("trd", 0, trdV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("trd", 0, trdV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Tube
  //
  ISolid* tubs = CreateTubs(sphi, dphi);
  IVolume* tubsV = CreateVolume(tubs, scale);
  fFactory->CreatePlacement("tubs", 0, tubsV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("tubs", 0, tubsV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Ctubs
  //
  ISolid* ctubs = CreateCtubs(sphi, dphi);
  IVolume* ctubsV = CreateVolume(ctubs, scale);
  fFactory->CreatePlacement("ctubs", 0, ctubsV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("ctubs", 0, ctubsV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Xtru1
  //
  ISolid* xtru1 = CreateExtrudedSolid1();
  IVolume* xtru1V = CreateVolume(xtru1, scale);
  fFactory->CreatePlacement("xtru1", 0, xtru1V, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("xtru1", 0, xtru1V, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Xtru2
  //
  ISolid* xtru2 = CreateExtrudedSolid2();
  IVolume* xtru2V = CreateVolume(xtru2, scale);
  fFactory->CreatePlacement("xtru2", 0, xtru2V, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("xtru2", 0, xtru2V, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  // Hype
  //
  ISolid* hype = CreateHype();
  IVolume* hypeV = CreateVolume(hype, scale);
  fFactory->CreatePlacement("hype", 0, hypeV, mother,
    ClhepVGM::Transform(
      HepGeom::Translate3D(x0 + (++counter) * dx, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("hype", 0, hypeV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D));

  // Paraboloid
  //
  ISolid* paraboloid = CreateParaboloid();
  IVolume* paraboloidV = CreateVolume(paraboloid, scale);
  fFactory->CreatePlacement("paraboloid", 0, paraboloidV, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("paraboloid", 0, paraboloidV, mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D));

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void TstGeometryViaVGM::PlaceSolids(
  const std::vector<VGM::IVolume*>& volumes, VGM::IVolume* mother)
{
  // Place volumes defined in the vector

  double x0 = -500. * fCm;
  double dx = 150. * fCm;
  double zpos = 100. * fCm;

  HepGeom::ReflectZ3D reflect3D;

  for (unsigned int i = 0; i < volumes.size(); ++i) {
    fFactory->CreatePlacement("box", 0, volumes[i], mother,
      ClhepVGM::Transform(HepGeom::Translate3D(x0 + i * dx, 0, zpos)));
    fFactory->CreatePlacement("box", 0, volumes[i], mother,
      ClhepVGM::Transform(
        HepGeom::Translate3D(x0 + i * dx, 0, -zpos) * reflect3D));
  }
}

//_____________________________________________________________________________
void TstGeometryViaVGM::PlaceExtraSolid(
  VGM::SolidType solidType, IVolume* mother)
{
  IVolume* vol = 0;
  std::string volName;

  if (solidType == VGM::kArb8) {
    vol = CreateVolume(CreateArb8());
    volName = "arb8";
  }

  if (solidType == VGM::kEllipsoid) {
    vol = CreateVolume(CreateEllipsoid());
    volName = "ellipsoid";
  }

  if (solidType == VGM::kTessellated) {
    vol = CreateVolume(CreateTessellatedSolid());
    volName = "tessellated";
  }

  if (!vol) return;

  double zpos = 100. * fCm;
  HepGeom::ReflectZ3D reflect3D;

  fFactory->CreatePlacement(volName, 0, vol, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(0, 0, zpos)));

  fFactory->CreatePlacement(volName, 0, vol, mother,
    ClhepVGM::Transform(HepGeom::Translate3D(0, 0, -zpos) * reflect3D));
}

//
// public methods
//

//_____________________________________________________________________________
void TstGeometryViaVGM::DefineMaterials()
{
  // Get material factory
  IMaterialFactory* materialFactory = fFactory->MaterialFactory();

  // predefined elements
  IElement* elH = materialFactory->CreateElement(1);
  IElement* elC = materialFactory->CreateElement(6);

  // create elements
  double z, a, density, radlen, intlen, temperature, pressure;
  IElement* elVacuum = materialFactory->CreateElement(
    "Vacuum", "Vacuum_e", z = 1., a = 1.01 * fGmole);
  IElement* elN =
    materialFactory->CreateElement("Nitrogen", "N", z = 7., a = 14.01 * fGmole);
  IElement* elO =
    materialFactory->CreateElement("Oxygen", "O", z = 8., a = 16.00 * fGmole);
  IElement* elAl = materialFactory->CreateElement(
    "Aluminium", "Al", z = 13., a = 26.98 * fGmole);
  IElement* elW = materialFactory->CreateElement(
    "Tungsten", "W", z = 74., a = 183.84 * fGmole);

  // simple material (Al)
  //
  IMaterial* material1 = materialFactory->CreateMaterial(
    "Basic", density = 2.700 * fGcm3, elAl, radlen = 0., intlen = 0.);

  // compound/mixture material
  //
  ElementVector elements;
  elements.push_back(elN);
  elements.push_back(elO);

  MassFractionVector fractions;
  fractions.push_back(0.7);
  fractions.push_back(0.3);

  density = 1.290 * ClhepVGM::Units::MassDensity(mg / cm3);
  IMaterial* material2 =
    materialFactory->CreateMaterial("Air", density, elements, fractions);

  // material from predefined elements
  //

  ElementVector elements2;
  elements2.push_back(elC);
  elements2.push_back(elH);

  AtomCountVector atomCounts;
  atomCounts.push_back(9);
  atomCounts.push_back(10);

  density = 1.032 * ClhepVGM::Units::MassDensity(g / cm3);
  IMaterial* material3 = materialFactory->CreateMaterial(
    "Scintillator", density, elements2, atomCounts);

  // material using isotopes
  int iz, n;
  IIsotope* isoU5 = materialFactory->CreateIsotope(
    "U235", iz = 92, n = 235, a = 235.01 * fGmole);
  IIsotope* isoU8 = materialFactory->CreateIsotope(
    "U238", iz = 92, n = 238, a = 238.03 * fGmole);

  IsotopeVector isotopes;
  isotopes.push_back(isoU5);
  isotopes.push_back(isoU8);

  RelAbundanceVector relAbundances;
  relAbundances.push_back(0.90);
  relAbundances.push_back(0.10);

  IElement* elU = materialFactory->CreateElement(
    "enriched Uranium", "U", isotopes, relAbundances);

  density = 13.61 * ClhepVGM::Units::MassDensity(g / cm3);
  IMaterial* material4 = materialFactory->CreateMaterial(
    "Uranium", density, elU, radlen = 0., intlen = 0.);

  // vacuum
  //
  density = CLHEP::universe_mean_density / (g / cm3) * fGcm3;
  temperature = 2.73 * fKelvin;
  pressure = 3.e-18 * ClhepVGM::Units::Pressure(pascal);
  IMaterial* material5 = materialFactory->CreateMaterial("Vacuum", density,
    elVacuum, radlen = 0., intlen = 0., VGM::kGas, temperature, pressure);

  // simple material (Tungsten)  which caused problem in v3.03
  //
  IMaterial* material6 = materialFactory->CreateMaterial(
    "Tungsten", density = 19.25 * fGcm3, elW, radlen = 0., intlen = 0.);

  // define tracking media
  // with no parameters specified
  materialFactory->CreateMedium("Basic", 1, material1, 0, 0);
  materialFactory->CreateMedium("Air", 2, material2, 0, 0);
  materialFactory->CreateMedium("Scintillator", 3, material3, 0, 0);
  materialFactory->CreateMedium("Uranium", 4, material4, 0, 0);
  materialFactory->CreateMedium("Vacuum", 5, material5, 0, 0);
  materialFactory->CreateMedium("Tungsten", 6, material6, 0, 0);
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestSolids(bool fullPhi)
{
  IVolume* worldV = CreateWorld(620. * fCm, 300. * fCm, 200. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  PlaceSolids(worldV, fullPhi, false, false, 0.);

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestExtraSolid(VGM::SolidType solidType)
{
  IVolume* worldV = CreateWorld(620. * fCm, 300. * fCm, 200. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  PlaceExtraSolid(solidType, worldV);

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestNewSolid()
{
  IVolume* worldV = CreateWorld(200. * fCm, 200. * fCm, 200. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  IVolume* newSolidV = CreateVolume(CreateNewSolid());
  if (newSolidV) {
    fFactory->CreatePlacement(
      newSolidV->Name(), 0, newSolidV, worldV, ClhepVGM::Identity());
  }

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestNewSolid2()
{
  IVolume* worldV = CreateWorld(200. * fCm, 200. * fCm, 200. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  std::vector<IVolume*> volumes;
  CreateArb8Solids(volumes);
  PlaceSolids(volumes, worldV);

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestPlacements()
{
  // World
  //
  IVolume* worldV = CreateWorld(600. * fCm, 100. * fCm, 600. * fCm, "Vacuum");
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Big box A
  //
  ISolid* boxA = fFactory->CreateBox("boxA", 20. * fCm, 60. * fCm, 50. * fCm);
  IVolume* volA = fFactory->CreateVolume("layerA", boxA, "Air");

  // Thick layer B (in A)
  //
  ISolid* boxB = fFactory->CreateBox("boxB", 20. * fCm, 10. * fCm, 50. * fCm);
  IVolume* volB = fFactory->CreateVolume("layerB", boxB, "Uranium");

  // Thin layer C (in B)
  //
  ISolid* boxC = fFactory->CreateBox("boxC", 20. * fCm, 0.2 * fCm, 50. * fCm);
  IVolume* volC = fFactory->CreateVolume("layerC", boxC, "Scintillator");

  // Place layers B
  //
  // fFactory->CreateMultiplePlacement("layerB", volB, volA,
  //                                 VGM::kYAxis, 6, 20.*mm, 0.);
  // division in the whole mother

  fFactory->CreateMultiplePlacement(
    "layerB", volB, volA, VGM::kYAxis, 3, 20. * fCm, 60. * fCm, 0.);
  // division with offset

  // If layers C placed first, they are not passed
  // in a new TGeo Volume if running with Root.
  // To be improved later.

  // Place layers C
  //
  fFactory->CreatePlacement("layerC", 0, volC, volB,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 9.8 * fCm, 0.)));

  fFactory->CreatePlacement("layerC", 1, volC, volB,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., -9.8 * fCm, 0.)));

  // Placements of A in a circle
  //
  for (int i = 0; i < 24; i++) {

    double x0 = 5. * m;
    double y0 = 0. * m;
    double dphi = 15. * deg;
    // use directly CLHEP units when using CLHEP rotations

    double phi = dphi * (i + 1);
    double x = x0 * cos(phi);
    double z = x0 * sin(phi);

    CLHEP::HepRotation rot;
    rot.rotateY(-phi);
    // !!! Different meaning of rotation in VGM than in Geant4

    fFactory->CreatePlacement("layerA", i, volA, worldV,
      ClhepVGM::Transform(rot, CLHEP::Hep3Vector(x, y0, z)));
  }

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestPlacements2(bool /*bestMatch*/)
{
  // World
  //
  IVolume* worldV = CreateWorld(200. * fCm, 100. * fCm, 400. * fCm, "Air");
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Divison 1
  //
  // Box A (mother)
  ISolid* box1A = fFactory->CreateBox("box1A", 20. * fCm, 60. * fCm, 50. * fCm);
  IVolume* vol1A = fFactory->CreateVolume("vol1A", box1A, "Air");

  // Division B in A
  ISolid* box1B = fFactory->CreateBox("box1B", 20. * fCm, 10. * fCm, 50. * fCm);
  IVolume* vol1B = fFactory->CreateVolume("vol1B", box1B, "Scintillator");

  fFactory->CreateMultiplePlacement(
    "vol1B", vol1B, vol1A, VGM::kYAxis, 6, 20. * fCm, 0., 0.);

  // Divison 2 with gaps
  //
  // Box A (mother)
  ISolid* box2A = fFactory->CreateBox("box2A", 20. * fCm, 60. * fCm, 50. * fCm);
  IVolume* vol2A = fFactory->CreateVolume("vol2A", box2A, "Air");

  // Replicated Slice cell
  ISolid* box2B = fFactory->CreateBox("box2B", 20. * fCm, 6. * fCm, 50. * fCm);
  IVolume* vol2B = fFactory->CreateVolume("vol2B", box2B, "Scintillator");

  fFactory->CreateMultiplePlacement(
    "vol2B", vol2B, vol2A, VGM::kYAxis, 6, 20. * fCm, 0., 4. * cm);

  // Division 3
  //
  // Box A (mother)
  ISolid* box3A = fFactory->CreateBox("box3A", 20. * fCm, 60. * fCm, 50. * fCm);
  IVolume* vol3A = fFactory->CreateVolume("vol3A", box3A, "Air");

  // Division B in A
  ISolid* box3B = fFactory->CreateBox("box3B", 20. * fCm, 10. * fCm, 50. * fCm);
  IVolume* vol3B = fFactory->CreateVolume("vol3B", box3B, "Scintillator");

  fFactory->CreateMultiplePlacement(
    "vol3B", vol3B, vol3A, VGM::kYAxis, 6, 20. * fCm, 0., 0.);

  // Placements of A volumes along z axis
  //
  fFactory->CreatePlacement("vol1A", 0, vol1A, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, -200. * fCm)));
  fFactory->CreatePlacement("vol2A", 0, vol2A, worldV,
    ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, 0)));
  fFactory->CreatePlacement("vol3A", 0, vol3A, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, 200. * fCm)));

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestReflections(bool fullPhi)
{
  IVolume* worldV = CreateWorld(620. * fCm, 300. * fCm, 300. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  PlaceSolids(worldV, fullPhi, true, false, 100. * fCm);

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestScaledSolids(bool fullPhi)
{
  IVolume* worldV = CreateWorld(620. * fCm, 300. * fCm, 300. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  PlaceSolids(worldV, fullPhi, true, true, 100. * fCm);

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids1()
{
  // Only translation in solid displacement

  IVolume* worldV = CreateWorld(400. * fCm, 100. * fCm, 400. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Create solids
  ISolid* solid1 = fFactory->CreateBox("boxS", 50. * fCm, 50. * fCm, 50. * fCm);

  ISolid* solid2 = fFactory->CreateCons("consS", 10. * fCm, 30. * fCm,
    20. * fCm, 40. * fCm, 100. * fCm, 0., 360. * fDeg);

  // Simple solids placed for a control
  //
  IVolume* volume1 = fFactory->CreateVolume("solid1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-125. * fCm, 0., -200. * fCm)));

  IVolume* volume2 = fFactory->CreateVolume("solid2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(125. * fCm, 0., -200. * fCm)));

  // Intersection
  //
  ISolid* intersectionS = fFactory->CreateIntersectionSolid(
    "intersection_solid1_solid2_S", solid1, solid2,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(20. * fCm, 0., 0.)));

  IVolume* intersectionV = fFactory->CreateVolume(
    "intersection_solid1_solid2", intersectionS, "Basic");

  fFactory->CreatePlacement("intersection_solid1_solid2", 0, intersectionV,
    worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-250. * fCm, 0., 200. * fCm)));

  // Subtraction
  //
  ISolid* subtractionS = fFactory->CreateSubtractionSolid(
    "subtraction_solid1_solid2_S", solid1, solid2,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(20. * fCm, 0., 0.)));

  IVolume* subtractionV =
    fFactory->CreateVolume("subtraction_solid1_solid2", subtractionS, "Basic");

  fFactory->CreatePlacement("subtraction_solid1_solid2", 0, subtractionV,
    worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 200. * fCm)));

  // Union
  //
  ISolid* unionS =
    fFactory->CreateUnionSolid("union_solid1_solid2_S", solid1, solid2,
      ClhepVGM::Transform(
        CLHEP::HepRotation(), CLHEP::Hep3Vector(20. * fCm, 0., 0.)));
  IVolume* unionV =
    fFactory->CreateVolume("union_solid1_solid2", unionS, "Basic");

  fFactory->CreatePlacement("union_solid1_solid2", 0, unionV, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(250. * fCm, 0., 200. * fCm)));

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids2()
{
  // Translation + rotation in solid displacement

  IVolume* worldV = CreateWorld(400. * fCm, 100. * fCm, 400. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Create solids
  ISolid* solid1 = fFactory->CreateBox("boxS", 50. * fCm, 50. * fCm, 50. * fCm);

  ISolid* solid2 = fFactory->CreateCons("consS", 10. * fCm, 30. * fCm,
    20. * fCm, 40. * fCm, 100. * fCm, 0., 360. * fDeg);

  // Simple solids placed for a control
  //
  IVolume* volume1 = fFactory->CreateVolume("solid1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-125. * fCm, 0., -200. * fCm)));

  IVolume* volume2 = fFactory->CreateVolume("solid2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(125. * fCm, 0., -200. * fCm)));

  // Define displacement transformations
  //

  // Rotate solid1
  CLHEP::HepRotation rot1;
  rot1.rotateY(45. * deg);

  // Rotate + translate solid2
  //
  CLHEP::HepRotation rot2;
  rot2.rotateX(30. * deg);
  rot2.rotateY(-45. * deg);
  CLHEP::Hep3Vector tr2 = CLHEP::Hep3Vector(20. * fCm, 0., 0.);

  // Intersection
  //
  ISolid* intersectionS =
    fFactory->CreateIntersectionSolid("intersection_solid1_solid2_S", solid1,
      solid2, ClhepVGM::Transform(rot2, tr2));
  IVolume* intersectionV = fFactory->CreateVolume(
    "intersection_solid1_solid2", intersectionS, "Basic");

  fFactory->CreatePlacement("intersection_solid1_solid2", 0, intersectionV,
    worldV,
    ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(-250. * fCm, 0., 200. * fCm)));

  // Subtraction
  //
  ISolid* subtractionS =
    fFactory->CreateSubtractionSolid("subtraction_solid1_solid2_S", solid1,
      solid2, ClhepVGM::Transform(rot2, tr2));
  IVolume* subtractionV =
    fFactory->CreateVolume("subtraction_solid1_solid2", subtractionS, "Basic");

  fFactory->CreatePlacement("subtraction_solid1_solid2", 0, subtractionV,
    worldV, ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(0., 0., 200. * fCm)));

  // Union
  //
  ISolid* unionS = fFactory->CreateUnionSolid(
    "union_solid1_solid2_S", solid1, solid2, ClhepVGM::Transform(rot2, tr2));
  IVolume* unionV =
    fFactory->CreateVolume("union_solid1_solid2", unionS, "Basic");

  fFactory->CreatePlacement("union_solid1_solid2", 0, unionV, worldV,
    ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(250. * fCm, 0., 200. * fCm)));

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids3()
{
  // Translation + rotation + reflection in solid displacement

  IVolume* worldV = CreateWorld(400. * fCm, 100. * fCm, 400. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Create solids
  ISolid* solid1 = fFactory->CreateBox("boxS", 50. * fCm, 50. * fCm, 50. * fCm);

  ISolid* solid2 = fFactory->CreateCons("consS", 10. * fCm, 30. * fCm,
    20. * fCm, 40. * fCm, 100. * fCm, 0., 360. * fDeg);

  // Simple solids placed for a control
  //
  IVolume* volume1 = fFactory->CreateVolume("solid1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-125. * fCm, 0., -200. * fCm)));

  IVolume* volume2 = fFactory->CreateVolume("solid2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(125. * fCm, 0., -200. * fCm)));

  // Define displacement transformations
  //

  // Rotate solid1
  CLHEP::HepRotation rot1;
  rot1.rotateY(45. * deg);

  // Rotate + translate solid2
  //
  HepGeom::ReflectZ3D reflect2 = HepGeom::ReflectZ3D();
  HepGeom::Translate3D translate2 = HepGeom::Translate3D(20. * fCm, 0., 0.);
  HepGeom::Rotate3D rotInv1 = HepGeom::RotateY3D(-45. * deg);
  HepGeom::Transform3D transform2 = rotInv1 * translate2 * reflect2;

  // Intersection
  //
  ISolid* intersectionS =
    fFactory->CreateIntersectionSolid("intersection_solid1_solid2_S", solid1,
      solid2, ClhepVGM::Transform(transform2));
  IVolume* intersectionV = fFactory->CreateVolume(
    "intersection_solid1_solid2", intersectionS, "Basic");

  fFactory->CreatePlacement("intersection_solid1_solid2", 0, intersectionV,
    worldV,
    ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(-250. * fCm, 0., 200. * fCm)));

  // Subtraction
  //
  ISolid* subtractionS =
    fFactory->CreateSubtractionSolid("subtraction_solid1_solid2_S", solid1,
      solid2, ClhepVGM::Transform(transform2));
  IVolume* subtractionV =
    fFactory->CreateVolume("subtraction_solid1_solid2", subtractionS, "Basic");

  fFactory->CreatePlacement("subtraction_solid1_solid2", 0, subtractionV,
    worldV, ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(0., 0., 200. * fCm)));

  // Union
  //
  ISolid* unionS = fFactory->CreateUnionSolid(
    "union_solid1_solid2_S", solid1, solid2, ClhepVGM::Transform(transform2));

  IVolume* unionV =
    fFactory->CreateVolume("union_solid1_solid2", unionS, "Basic");

  fFactory->CreatePlacement("union_solid1_solid2", 0, unionV, worldV,
    ClhepVGM::Transform(rot1, CLHEP::Hep3Vector(250. * fCm, 0., 200. * fCm)));

  return (void*)fFactory->Top();
  return 0;
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestDisplacedSolids1()
{
  // Test solid displacement

  // World
  //
  IVolume* worldV = CreateWorld(60. * fCm, 60. * fCm, 160. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Create solids

  // Normal solid
  //
  ISolid* solid1 =
    fFactory->CreateBox("boxS1", 50. * fCm, 50. * fCm, 50. * fCm);

  IVolume* volume1 = fFactory->CreateVolume("volume1", solid1, "Basic");

  // Chained displaced solids
  //
  ISolid* solid2 =
    fFactory->CreateBox("boxS2", 50. * fCm, 50. * fCm, 50. * fCm);

  ISolid* solid2A = fFactory->CreateDisplacedSolid("boxS2A", solid2,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 50. * fCm)));

  ISolid* solid2B = fFactory->CreateDisplacedSolid("boxS2B", solid2A,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 50. * fCm)));
  ISolid* solid2C = fFactory->CreateDisplacedSolid("boxS2C", solid2B,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 50. * fCm)));
  IVolume* volume2C = fFactory->CreateVolume("volume2C", solid2C, "Basic");

  // Daughter to be placed in displaced solid
  //
  ISolid* solid3 =
    fFactory->CreateBox("boxS3", 20. * fCm, 20. * fCm, 20. * fCm);

  IVolume* volume3 = fFactory->CreateVolume("volume3", solid3, "Basic");

  // Daughter to be placed in normal solid
  //
  ISolid* solid4 =
    fFactory->CreateBox("boxS4", 20. * fCm, 20. * fCm, 10. * fCm);

  IVolume* volume4 = fFactory->CreateVolume("volume4", solid4, "Basic");

  // Daughter with displaced solid to be placed in displaced solid
  //
  ISolid* solid5 = fFactory->CreateBox("boxS5", 20. * fCm, 20. * fCm, 5. * fCm);

  ISolid* solid5A = fFactory->CreateDisplacedSolid("boxS5A", solid5,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 40. * fCm)));
  IVolume* volume5A = fFactory->CreateVolume("volume5A", solid5A, "Basic");

  // Make placements
  //

  fFactory->CreatePlacement("volume1", 1, volume1, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., -100. * fCm)));

  fFactory->CreatePlacement("volume2C", 2, volume2C, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., -100. * fCm)));

  fFactory->CreatePlacement("volume3", 1, volume3, volume2C,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 150. * fCm)));

  fFactory->CreatePlacement("volume4", 1, volume4, volume1,
    ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector()));

  fFactory->CreatePlacement("volume5A", 2, volume5A, volume2C,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 150. * fCm)));

  return (void*)fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestDisplacedSolids2()
{
  // Test BooleanSolids2 where displacement is defined via
  // Displaced solid

  IVolume* worldV = CreateWorld(400. * fCm, 100. * fCm, 400. * fCm);
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());

  // Create solids
  ISolid* solid1 = fFactory->CreateBox("boxS", 50. * fCm, 50. * fCm, 50. * fCm);

  ISolid* solid2 = fFactory->CreateCons("consS", 10. * fCm, 30. * fCm,
    20. * fCm, 40. * fCm, 100. * fCm, 0., 360. * fDeg);

  // Simple solids placed for a control
  //
  IVolume* volume1 = fFactory->CreateVolume("solid1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-125. * fCm, 0., -200. * fCm)));

  IVolume* volume2 = fFactory->CreateVolume("solid2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(125. * fCm, 0., -200. * fCm)));

  // Rotate solid1
  //
  CLHEP::HepRotation rot1;
  rot1.rotateY(45. * deg);
  CLHEP::Hep3Vector tr1 = CLHEP::Hep3Vector();

  // Rotate + translate solid2
  //
  CLHEP::HepRotation rot2;
  rot2.rotateX(30. * deg);
  // rot2.rotateY(-45.* deg);
  CLHEP::Hep3Vector tr2 = CLHEP::Hep3Vector(20. * fCm, 0., 0.);

  // Displaced solids
  //
  ISolid* dsolid1 = fFactory->CreateDisplacedSolid(
    "dboxS", solid1, ClhepVGM::Transform(rot1, tr1));

  ISolid* dsolid2 = fFactory->CreateDisplacedSolid(
    "dconsS", solid2, ClhepVGM::Transform(rot2, tr2));
  // Intersection
  //
  ISolid* intersectionS =
    fFactory->CreateIntersectionSolid("intersection_dsolid1_dsolid2_S", dsolid1,
      dsolid2, ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector()));
  IVolume* intersectionV = fFactory->CreateVolume(
    "intersection_solid1_solid2", intersectionS, "Basic");

  fFactory->CreatePlacement("intersection_solid1_solid2", 0, intersectionV,
    worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(-250. * fCm, 0., 200. * fCm)));

  // Subtraction
  //
  ISolid* subtractionS =
    fFactory->CreateSubtractionSolid("subtraction_dsolid1_dsolid2_S", dsolid1,
      dsolid2, ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector()));
  IVolume* subtractionV =
    fFactory->CreateVolume("subtraction_solid1_solid2", subtractionS, "Basic");

  fFactory->CreatePlacement("subtraction_solid1_solid2", 0, subtractionV,
    worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(0., 0., 200. * fCm)));

  // Union
  //
  ISolid* unionS =
    fFactory->CreateUnionSolid("union_dsolid1_dsolid2_S", dsolid1, dsolid2,
      ClhepVGM::Transform(CLHEP::HepRotation(), CLHEP::Hep3Vector()));
  IVolume* unionV =
    fFactory->CreateVolume("union_solid1_solid2", unionS, "Basic");

  fFactory->CreatePlacement("union_solid1_solid2", 0, unionV, worldV,
    ClhepVGM::Transform(
      CLHEP::HepRotation(), CLHEP::Hep3Vector(250. * fCm, 0., 200. * fCm)));

  return (void*)fFactory->Top();
}
