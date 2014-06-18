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

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ReflectionFactory.hh"
#include "G4AssemblyVolume.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Ellipsoid.hh"
#include "G4EllipticalTube.hh"
#include "G4ExtrudedSolid.hh"
#include "G4Hype.hh"
#include "G4Para.hh"
#include "G4Paraboloid.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4Sphere.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4QuadrangularFacet.hh"
#include "G4Torus.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4PVDivision.hh"
#include "G4RotationMatrix.hh"
#include "G4TwoVector.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "TstGeometryViaGeant4.hh"

#include <math.h>

using CLHEP::Hep3Vector;
using CLHEP::HepRotation;

//_____________________________________________________________________________
TstGeometryViaGeant4::TstGeometryViaGeant4()
  : TstVGeometry(),
    fBasicMaterial(0)
{
//
}  

//_____________________________________________________________________________
TstGeometryViaGeant4::~TstGeometryViaGeant4()
{
}

//
// private methods
// 

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateWorld(G4double x, G4double y, G4double z)
{
// Create world volume
// ---
  
  // Get material from G4
  if (!fBasicMaterial)
    fBasicMaterial = G4Material::GetMaterial("Basic");

  G4VSolid* worldS = new G4Box("worldS", x, y, z);

  return new G4LogicalVolume(worldS, fBasicMaterial, "world");
}    

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateNewSolid()
{
// Create a new solid
// ---

  return CreateEllipsoid();
}    

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateBox()
{
  G4VSolid* boxS
    = new G4Box("boxS", 20.*cm, 60.*cm, 50.*cm);
  
  return new G4LogicalVolume(boxS, fBasicMaterial, "box");
}  


//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateCons(G4double sphi, G4double dphi)
{
  G4VSolid* consS
    = new G4Cons("consS", 10.*cm, 40.*cm, 20.*cm, 60.*cm, 50*cm,
                 sphi, dphi);
  
  return new G4LogicalVolume(consS, fBasicMaterial, "cons");
}


//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateEllipsoid()
{
  G4VSolid* ellipsoidS
    = new G4Ellipsoid("ellipsiodS", 10.* cm, 20.* cm, 50* cm, -10.*cm, 40.*cm);
  
  return new G4LogicalVolume(ellipsoidS, fBasicMaterial, "ellipsoid");
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateEllipticalTube()
{
  G4VSolid* eltuS
    = new G4EllipticalTube("eltuS", 20.* cm, 30.* cm, 50* cm);
  
  return new G4LogicalVolume(eltuS, fBasicMaterial, "eltu");
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateExtrudedSolid1()
{   
  std::vector<G4TwoVector> polygon;
  polygon.push_back(G4TwoVector(-30.*cm, -30.*cm));
  polygon.push_back(G4TwoVector(-30.*cm,  30.*cm));
  polygon.push_back(G4TwoVector( 30.*cm,  30.*cm));
  polygon.push_back(G4TwoVector( 30.*cm, -30.*cm));
  polygon.push_back(G4TwoVector( 15.*cm, -30.*cm));
  polygon.push_back(G4TwoVector( 15.*cm,  15.*cm));
  polygon.push_back(G4TwoVector(-15.*cm,  15.*cm));
  polygon.push_back(G4TwoVector(-15.*cm, -30.*cm));
  
  std::vector<G4ExtrudedSolid::ZSection> zsections;
  zsections.push_back(G4ExtrudedSolid::ZSection(-40.*cm, G4TwoVector(-20.*cm, 10.*cm), 1.5));
  zsections.push_back(G4ExtrudedSolid::ZSection( 10.*cm, G4TwoVector(  0.*cm,  0.*cm), 0.5));
  zsections.push_back(G4ExtrudedSolid::ZSection( 15.*cm, G4TwoVector(  0.*cm,  0.*cm), 0.7));
  zsections.push_back(G4ExtrudedSolid::ZSection( 40.*cm, G4TwoVector( 20.*cm, 20.*cm), 0.9));

  G4ExtrudedSolid* xtruS 
    = new G4ExtrudedSolid("XtruS", polygon, zsections);

  G4LogicalVolume* xtruV 
    = new G4LogicalVolume(xtruS, fBasicMaterial, "xtru1");

  return xtruV;  
}  
 
//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateExtrudedSolid2()
{   
  std::vector<G4TwoVector> polygon;
  polygon.push_back(G4TwoVector(-30.*cm, -30.*cm));
  polygon.push_back(G4TwoVector(-30.*cm,  30.*cm));
  polygon.push_back(G4TwoVector( 30.*cm,  30.*cm));
  polygon.push_back(G4TwoVector( 30.*cm, -30.*cm));
  polygon.push_back(G4TwoVector( 15.*cm, -30.*cm));
  polygon.push_back(G4TwoVector( 15.*cm,  15.*cm));
  polygon.push_back(G4TwoVector(-15.*cm,  15.*cm));
  polygon.push_back(G4TwoVector(-15.*cm, -30.*cm));
  
  std::vector<G4ExtrudedSolid::ZSection> zsections1;
  zsections1.push_back(G4ExtrudedSolid::ZSection(-40.*cm, G4TwoVector(-20.*cm, 10.*cm), 1.5));
  zsections1.push_back(G4ExtrudedSolid::ZSection( 10.*cm, G4TwoVector(  0.*cm,  0.*cm), 0.5));

  G4ExtrudedSolid* xtruS1 
    = new G4ExtrudedSolid("XtruS1", polygon, zsections1);

  std::vector<G4ExtrudedSolid::ZSection> zsections2;
  zsections2.push_back(G4ExtrudedSolid::ZSection( 10.*cm, G4TwoVector(  0.*cm,  0.*cm), 0.7));
  zsections2.push_back(G4ExtrudedSolid::ZSection( 40.*cm, G4TwoVector( 20.*cm, 20.*cm), 0.9));

  G4ExtrudedSolid* xtruS2 
    = new G4ExtrudedSolid("XtruS1", polygon, zsections2);

  G4UnionSolid* unionS
    = new G4UnionSolid("xtruU", xtruS1, xtruS2, 0, G4ThreeVector());

  G4LogicalVolume* xtruV 
    = new G4LogicalVolume(unionS, fBasicMaterial, "xtru2");

  return xtruV;  
}  
 
//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateHype()
{
  G4VSolid* hypeS
    = new G4Hype("hypeS", 20.*cm, 30.*cm, 30.0*deg, 40.0*deg, 50.*cm);

  return new G4LogicalVolume(hypeS, fBasicMaterial, "hype");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreatePara()
{
  G4VSolid* paraS
    = new G4Para("paraS", 40.*cm, 60.*cm, 50.*cm, 
                  30.*deg, 30.*deg, 30.*deg);

  return new G4LogicalVolume(paraS, fBasicMaterial, "para");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateParaboloid()
{
  G4VSolid* paraboloidS
    = new G4Paraboloid("paraboloidS", 50.*cm, 20.*cm, 45.*cm);

  return new G4LogicalVolume(paraboloidS, fBasicMaterial, "paraboloid");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreatePolycone(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 50.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 30.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 60.*cm;
  
  G4VSolid* pconeS
    = new G4Polycone("pconeS", sphi, dphi, nofPlanes, z, rin, rout);
  
  return new G4LogicalVolume(pconeS, fBasicMaterial, "pcone");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreatePolyhedra(G4double sphi, G4double dphi)
{
  // Define parameters

  G4int nofSides = 4;
  G4int nofPlanes = 3;
  G4double z[3];
  G4double rin[3];
  G4double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 40.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 20.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 50.*cm;
  
  G4VSolid* phedraS
    = new G4Polyhedra("phedraS", sphi, dphi, 
                       nofSides, nofPlanes, z, rin, rout);

  return new G4LogicalVolume(phedraS, fBasicMaterial, "phedra");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreateSphere(G4double sphi, G4double dphi)
{
  G4VSolid* sphereS1
    = new G4Sphere("sphereS", 20.*cm, 60.*cm,
                    sphi, dphi, sphi/2., dphi/2.); 
			    
  return new G4LogicalVolume(sphereS1, fBasicMaterial, "sphere");
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreateTessellatedSolid()
{
  // First declare a tessellated solid
  //
  G4TessellatedSolid* tessellatedS 
    = new G4TessellatedSolid("tessellatedS");

  G4double targetSize = 100*cm ;
  G4TriangularFacet *facet1 
    = new G4TriangularFacet(
            G4ThreeVector(-targetSize,-targetSize,        0.0),
            G4ThreeVector(+targetSize,-targetSize,        0.0),
            G4ThreeVector(        0.0,        0.0,+targetSize),
            ABSOLUTE);

  G4TriangularFacet *facet2 
    = new G4TriangularFacet (
            G4ThreeVector(+targetSize,-targetSize,        0.0),
            G4ThreeVector(+targetSize,+targetSize,        0.0),
            G4ThreeVector(        0.0,        0.0,+targetSize),
            ABSOLUTE);

  G4TriangularFacet *facet3 
    = new G4TriangularFacet (
            G4ThreeVector(+targetSize,+targetSize,        0.0),
            G4ThreeVector(-targetSize,+targetSize,        0.0),
            G4ThreeVector(        0.0,        0.0,+targetSize),
            ABSOLUTE);

  G4TriangularFacet *facet4 
    = new G4TriangularFacet (
            G4ThreeVector(-targetSize,+targetSize,        0.0),
            G4ThreeVector(-targetSize,-targetSize,        0.0),
            G4ThreeVector(        0.0,        0.0,+targetSize),
            ABSOLUTE);

  G4QuadrangularFacet *facet5 
    = new G4QuadrangularFacet (
            G4ThreeVector(-targetSize,-targetSize,        0.0),
            G4ThreeVector(-targetSize,+targetSize,        0.0),
            G4ThreeVector(+targetSize,+targetSize,        0.0),
            G4ThreeVector(+targetSize,-targetSize,        0.0),
            ABSOLUTE);

  tessellatedS->AddFacet((G4VFacet*) facet1);
  tessellatedS->AddFacet((G4VFacet*) facet2);
  tessellatedS->AddFacet((G4VFacet*) facet3);
  tessellatedS->AddFacet((G4VFacet*) facet4);
  tessellatedS->AddFacet((G4VFacet*) facet5);
  tessellatedS->SetSolidClosed(true);
			    
  return new G4LogicalVolume(tessellatedS, fBasicMaterial, "tessellated");  
}  

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::CreateTorus(G4double sphi, G4double dphi)
{
  G4VSolid* torusS
    = new G4Torus("torusS", 20.*cm, 30.*cm, 40.*cm,
                   sphi, dphi);
			    
  return new G4LogicalVolume(torusS, fBasicMaterial, "torus");  
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTrap()
{
  G4VSolid* trapS
    = new G4Trap("trapS", 30.*cm, 25.*deg, 35.*deg,
		  20.*cm, 10.*cm, 15.*cm, 0.*deg,
		  20.*cm, 10.*cm, 15.*cm, 0.*deg);

  return new G4LogicalVolume(trapS, fBasicMaterial, "trap");
}

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTrd()
{
  G4VSolid* trdS
    = new G4Trd("trdS", 20.*cm, 30*cm, 40.*cm, 50.*cm, 50.*cm);

  return new G4LogicalVolume(trdS, fBasicMaterial, "trd");
}  

//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateTubs(G4double sphi, G4double dphi)
{
  G4VSolid* tubsS
    = new G4Tubs("tubsS", 20.*cm, 40*cm, 50.*cm, sphi, dphi);

  return new G4LogicalVolume(tubsS, fBasicMaterial, "tubs");
}  
 
//_____________________________________________________________________________
G4LogicalVolume* TstGeometryViaGeant4::CreateCtubs(G4double /*sphi*/, G4double /*dphi*/)
{
  // Input parameters
  G4double rin  = 20.*cm;
  G4double rout = 30.*cm;
  G4double hz = 60.49*cm;
  G4double sphi = 330.*deg;
  G4double dphi = 280.*deg;
  Hep3Vector nLow( 0.00, 0.64, -0.77);
  Hep3Vector nHigh( 0.00, 0.09, 0.87);

  // Get angles 
  double thetaLow = nLow.theta();
  double thetaHigh = nHigh.theta();

  // Calculate new hz
  double dzLow  = fabs(rout * tan(thetaLow));
  double dzHigh = fabs(rout * tan(thetaHigh));
  double dzMax = dzLow >= dzHigh ? dzLow : dzHigh;
  double hzNew = hz + dzMax*1.2;

  /// Create tube 
  G4VSolid* tubs = new G4Tubs("tubs", rin, rout, hzNew, sphi, dphi);
		     
  // Define  dimensions of boxes
  //
  double hzLow = 1.2 * fabs(rout / cos(thetaLow));		     
  double hzHigh = 1.2 * fabs(rout / cos(thetaHigh));

  double dHz = hzNew-hz;
  double thetaLow2 = thetaLow;
  double thetaHigh2 = thetaHigh;
  if ( thetaLow2 > CLHEP::pi/2. ) thetaLow2 = thetaLow - CLHEP::pi/2.;
  if ( thetaHigh2 > CLHEP::pi/2. ) thetaHigh2 = thetaHigh - CLHEP::pi/2.;
  double rCorner = sqrt(rout*rout + dHz*dHz);
  double thetaPlusLow = atan(dHz/rout) - thetaLow2;
  double thetaPlusHigh = atan(dHz/rout) - thetaHigh2;
  double hxLow = 2.*rCorner*cos(thetaPlusLow);
  double hxHigh = 2.*rCorner*cos(thetaPlusHigh);

  G4VSolid* boxLow = new G4Box("boxLow", hxLow, hxLow, hzLow);  
  G4VSolid* boxHigh = new G4Box("boxHigh", hxHigh, hxHigh, hzHigh);  

  
  // Define rotations of boxes
  //
  // Rotation axis - cross product of normals
  Hep3Vector axisLow = Hep3Vector(0,0,1).cross(nLow);
  double angleLow = Hep3Vector(0,0,1).angle(nLow);
  HepRotation rotLow;
  rotLow.set(axisLow, angleLow);
  
  Hep3Vector axisHigh = Hep3Vector(0,0,1).cross(nHigh);
  double angleHigh = Hep3Vector(0,0,1).angle(nHigh);
  HepRotation rotHigh;
  rotHigh.set(axisHigh, angleHigh);
 
  // Define displacement of boxes
  //
  double zposLow  = fabs(hzLow  / cos(thetaLow));
  double zposHigh = fabs(hzHigh / cos(thetaHigh));
  //std::cout << "zposLow="  << zposLow  << std::endl;
  //std::cout << "zposHigh=" << zposHigh << std::endl;


  // Subtract boxes from tube
  G4VSolid* booleanSolid1
     = new G4SubtractionSolid("ctubs1", tubs, boxLow,
                               new HepRotation(rotLow.inverse()),
                               Hep3Vector(0, 0, - (hz + zposLow)));			

  G4VSolid* booleanSolid2
     = new G4SubtractionSolid("ctubs2", booleanSolid1, boxHigh,
                               new HepRotation(rotHigh.inverse()),
                               Hep3Vector(0, 0, hz + zposHigh));			

  return new G4LogicalVolume(booleanSolid2, fBasicMaterial, "ctubs");
}  
 

//_____________________________________________________________________________
G4LogicalVolume* 
TstGeometryViaGeant4::PlaceSolids(G4LogicalVolume* mother,
                                  G4bool fullPhi, G4bool reflect, G4double zpos)
{

  G4double sphi =   0.*deg;
  G4double dphi = 360.*deg;
  if (!fullPhi) {
    sphi = 45.*deg;
    dphi = 90.*deg;
  }  
 
  G4int counter = 0;
  G4double x0 = -5.0*m;
  G4double dx =  1.5*m;
  G4double dy =  1.5*m;
  
  HepGeom::ReflectZ3D reflect3D;
 
  // Box
  //
  G4LogicalVolume* boxV = CreateBox();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (counter)*dx,  -dy, zpos),
	       boxV, "box", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx,  -dy, -zpos) * reflect3D,
	      "box", boxV, mother, false, 0);
  }	      

  // Cons 
  //
  G4LogicalVolume* consV = CreateCons(sphi, dphi);
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos),
	       consV, "cons", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
	      "cons", consV, mother, false, 0);
  }	      

  // Elliptical tube 
  //
  G4LogicalVolume* eltuV = CreateEllipticalTube();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       eltuV, "eltu", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "eltu", eltuV, mother, false, 0);
  }	      

  // Para
  //
  G4LogicalVolume* paraV = CreatePara();
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (counter)*dx,  dy, zpos),
	       paraV, "para", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx,  dy, -zpos) * reflect3D,
	      "para", paraV, mother, false, 0);
  }	      
  
  // Polycone
  //
  G4LogicalVolume* pconeV = CreatePolycone(sphi, dphi);
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       pconeV, "pcone", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "pcone", pconeV, mother, false, 0);
  }	      

  // Polyhedra
  //
  G4LogicalVolume* phedraV = CreatePolyhedra(sphi, dphi);
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (counter)*dx,  dy, zpos),
	       phedraV, "phedra", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx,  dy, -zpos) * reflect3D,
	      "phedra", phedraV, mother, false, 0);
  }	      

  // Sphere 
  //
  G4LogicalVolume* sphereV = CreateSphere(sphi, dphi);
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       sphereV, "sphere", mother, false, 0);
	       
  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "sphere", sphereV, mother, false, 0);
  }	      

  // Torus
  //
  G4LogicalVolume* torusV = CreateTorus(sphi, dphi);
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (counter)*dx,  dy, zpos),
	       torusV, "torus", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx,  dy, -zpos) * reflect3D,
	      "torus", torusV, mother, false, 0);
  }	      

  // Trap 
  //
  G4LogicalVolume* trapV = CreateTrap();
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       trapV, "trap", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "trap", trapV, mother, false, 0);
  }	      

  // Trd
  //
  G4LogicalVolume* trdV = CreateTrd();
  new G4PVPlacement( 
               HepGeom::Translate3D(x0 + (counter)*dx,  dy, zpos),
	       trdV, "trd", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx,  dy, -zpos) * reflect3D,
	      "trd", trdV, mother, false, 0);
  }	      
 
  // Tubs
  //
  G4LogicalVolume* tubsV = CreateTubs(sphi, dphi);
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       tubsV, "tubs", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "tubs", tubsV, mother, false, 0);
  }	      

  // CTubs
  //
  G4LogicalVolume* ctubsV = CreateCtubs(sphi, dphi);
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos),
	       ctubsV, "ctubs", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
	      "ctubs", ctubsV, mother, false, 0);
  }	      

 
  // Xtru1
  //
  G4LogicalVolume* xtru1V = CreateExtrudedSolid1();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       xtru1V, "xtru1", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "xtru1", xtru1V, mother, false, 0);
  }	      

  // Xtru2
  //
  G4LogicalVolume* xtru2V = CreateExtrudedSolid2();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos),
	       xtru2V, "xtru2", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
	      "xtru2", xtru2V, mother, false, 0);
  }	      

  // Hype
  //
  G4LogicalVolume* hypeV = CreateHype();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (++counter)*dx, -dy, zpos),
	       hypeV, "hype", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, -dy, -zpos) * reflect3D,
	      "hype", hypeV, mother, false, 0);
  }	      

  // Paraboloid
  //
  G4LogicalVolume* paraboloidV = CreateParaboloid();
  new G4PVPlacement(
               HepGeom::Translate3D(x0 + (counter)*dx, dy, zpos),
	       paraboloidV, "paraboloid", mother, false, 0);

  if (reflect) {
    G4ReflectionFactory::Instance()
      ->Place(HepGeom::Translate3D(x0 + (counter)*dx, dy, -zpos) * reflect3D,
	      "paraboloid", paraboloidV, mother, false, 0);
  }	      

 
  return mother;
  
 }

//_____________________________________________________________________________
void  TstGeometryViaGeant4::PlaceExtraSolid(VGM::SolidType solidType, 
                                            G4LogicalVolume* mother)
{

  // Arb8 
  //
  G4LogicalVolume* lv = 0;
  G4String lvName;
 
  if ( solidType == VGM::kEllipsoid ) {
    lv = CreateEllipsoid();
    lvName = "ellipsoid";
  }    
    
  if ( solidType == VGM::kTessellated ) {
    lv = CreateTessellatedSolid();
    lvName = "tessellated";
  }    
    
  if ( ! lv )  return;

  G4double zpos =  1.0*m;
  HepGeom::ReflectZ3D reflect3D;
 
  new G4PVPlacement(
          HepGeom::Translate3D(0, 0, zpos), 
          lv, lvName, mother, false, 0);

  G4ReflectionFactory::Instance()
    ->Place(HepGeom::Translate3D(0, 0, -zpos) * reflect3D,
          lvName, lv, mother, false, 0);

}

//
// public methods
// 


//_____________________________________________________________________________
void  TstGeometryViaGeant4::DefineMaterials()
{
  // simple material (Al)
  //
  G4double z, a, density, fractionmass; 
  new G4Material("Basic", z=13., a=26.98*g/mole, density=2.700*g/cm3);

  // compound/mixture material
  //
  G4Element* N 
    = new G4Element("Nitrogen", "N" , z= 7., a=14.01*g/mole);
  G4Element* O  
    = new G4Element("Oxygen"  , "O" , z= 8., a=16.00*g/mole);

  density = 1.290*mg/cm3;
  G4Material* material2 = new G4Material("Air", density, 2);
  material2->AddElement(N, fractionmass=0.7);
  material2->AddElement(O, fractionmass=0.3);
  
  // material from predefined elements
  //
  G4NistManager* nistManager = G4NistManager::Instance();
  G4Element* H = nistManager->FindOrBuildElement(1);
  G4Element* C = nistManager->FindOrBuildElement(6);

  G4int natoms; 
  density = 1.032*g/cm3;
  G4Material* material3 = new G4Material("Scintillator", density, 2);  
  material3->AddElement(C, natoms= 9);
  material3->AddElement(H, natoms=10);

  // material using isotopes
  G4int iz, n, ncomponents;
  G4double abundance;
  G4Isotope* U5 = new G4Isotope("U235", iz=92, n=235, a=235.01*g/mole);
  G4Isotope* U8 = new G4Isotope("U238", iz=92, n=238, a=238.03*g/mole);
  G4Element* U  
    = new G4Element("enriched Uranium", "U", ncomponents=2);
  U->AddIsotope(U5, abundance= 90.*perCent);
  U->AddIsotope(U8, abundance= 10.*perCent);

  G4Material* material4
    = new G4Material("Uranium", density=13.61*g/cm3, ncomponents=1);
  material4->AddElement(U, 1);

  // vacuum
  //
  new G4Material("Vacuum", 
                 z=1., a=1.01*g/mole,density= universe_mean_density,
                 kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // simple material (Tungsten)  which caused problem in v3.03
  //
  new G4Material("Tungsten", z=74., a=183.84*g/mole, density= 19.25*g/cm3);


}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestSolids(G4bool fullPhi)
{

  G4LogicalVolume* worldV = CreateWorld(6.2*m, 3.*m, 2.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  PlaceSolids(worldV, fullPhi, false, 0.);

  return (void*) world;
 }

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestExtraSolid(VGM::SolidType solidType)
{

  G4LogicalVolume* worldV = CreateWorld(6.2*m, 3.*m, 2.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  PlaceExtraSolid(solidType, worldV);

  return (void*) world;
 }

#include "G4VisAttributes.hh"
//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestNewSolid()
{

  G4LogicalVolume* worldV = CreateWorld(2.*m, 2.*m, 2.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), 
                        worldV, worldV->GetName(), 0, false, 0); 
  worldV->SetVisAttributes (G4VisAttributes::Invisible);
      
  G4LogicalVolume* solidV = CreateNewSolid();
  
  if (solidV) {
      new G4PVPlacement(0, CLHEP::Hep3Vector(), 
                        solidV, solidV->GetName(), worldV, false, 0);
  }               

  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestNewSolid2()
{
  G4LogicalVolume* worldV = CreateWorld(2.*m, 2.*m, 2.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), 
                        worldV, worldV->GetName(), 0, false, 0); 
  worldV->SetVisAttributes (G4VisAttributes::Invisible);
      
  std::cerr << "TstGeometryViaGeant4::TestNewSolid2: not yet implemented." 
            << std::endl;
  exit(1);          

  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestPlacements()
{
  // World
  //
  G4LogicalVolume* worldV = CreateWorld(6.*m, 1.*m, 6.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
    
  // Get materials via names
  G4Material* air = G4Material::GetMaterial("Air");
  G4Material* scintillator = G4Material::GetMaterial("Scintillator");
  G4Material* uranium = G4Material::GetMaterial("Uranium");
  G4Material* vacuum = G4Material::GetMaterial("Vacuum");
  
  // Reset world material to vacuum
  worldV->SetMaterial(vacuum);

  // Big box A
  //
  G4VSolid * boxA
    = new G4Box("boxA", 20.*cm, 60.*cm, 50.*cm);
  G4LogicalVolume* volA
    = new G4LogicalVolume(boxA, air, "layerA");
  
  // Thick layer B (in A)
  //
  G4VSolid * boxB
    = new G4Box("boxB", 20.*cm, 10.*cm, 50.*cm);
  G4LogicalVolume * volB
    = new G4LogicalVolume(boxB, uranium, "layerB");

  // Thin layer C (in B)
  //
  G4VSolid * boxC
    = new G4Box("boxC", 20.*cm, 0.2*cm, 50.*cm);
  G4LogicalVolume * volC
    = new G4LogicalVolume(boxC, scintillator, "layerC");

  // Place layers C
  //
  new G4PVPlacement(0, CLHEP::Hep3Vector(0.,  9.8*cm, 0.),
                    volC, "layerC", volB, false, 0);
  new G4PVPlacement( 0, CLHEP::Hep3Vector(0., -9.8*cm, 0.),
                    volC, "layerC", volB, false, 1);

  // Place layers B   
  //
  //new G4PVDivision("layerB", volB, volA, kYAxis, 6, 20.*cm, 0.);
             // division in the whole mother
  
  new G4PVDivision("layerB", volB, volA, kYAxis, 3, 20.*cm, 60.*cm);
             // division with offeset

  // Placements of A in a circle
  //
  for (G4int i=0; i<24; i++) {
   
     G4double x0 = 5. *m;
     G4double y0 = 0. *m;
     G4double dphi = 15.*deg;

     G4double phi = dphi*(i+1);
     G4double x = x0*cos(phi);
     G4double z = x0*sin(phi);

     CLHEP::HepRotation* rot = new CLHEP::HepRotation();
     rot->rotateY(phi);
        // !!! Different meaning of rotation in Geant4 than in Root, VGM
     
     new G4PVPlacement(rot, CLHEP::Hep3Vector(x, y0, z),
                       volA, "layerA", worldV, false, i);
   }
   
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestReflections(G4bool fullPhi)
{

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(6.2*m, 3.*m, 3.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  PlaceSolids(worldV, fullPhi, true, 1.*m);

  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestAssemblies()
{
// Example for assemblies from Root tutorial

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(10.*m, 10.*m, 1.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, G4ThreeVector(), worldV, "world", 0, false, 0); 
   
  // Make the elementary assembly of the whole structure
  //
  G4int ntooth = 5;
  G4double xplate = 25.*cm;
  G4double yplate = 50.*cm;
  G4double xtooth = 10.*cm;
  G4double ytooth = 0.5*yplate/ntooth;
  G4double dshift = 2.*xplate + xtooth;
  G4double xt,yt;

  G4AssemblyVolume* tplate = new G4AssemblyVolume();

  // plate volume
  G4Box* plateS
    = new G4Box("plateS", xplate, yplate, 1.*cm);
  G4LogicalVolume* plateV
    = new G4LogicalVolume(plateS, fBasicMaterial, "PLATE");
   
  // tooth volume
  G4Box* toothS
    = new G4Box("toothS", xtooth, ytooth, 1.*cm);
  G4LogicalVolume* toothV
    = new G4LogicalVolume(toothS, fBasicMaterial, "TOOTH");
   
  // compose assembly 
  G4ThreeVector pos0(0.,0., 0.);
  tplate->AddPlacedVolume(plateV, pos0, 0);
  for (G4int i=0; i<ntooth; i++) {
    xt = xplate+xtooth;
    yt = -yplate + (4*i+1)*ytooth;
    G4ThreeVector pos1(xt, yt, 0);
    tplate->AddPlacedVolume(toothV, pos1, 0);

    xt = -xplate-xtooth;
    yt = -yplate + (4*i+3)*ytooth;
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
  rot1->rotateX(90.*deg);
  G4RotationMatrix *rot;
  G4AssemblyVolume* cell = new G4AssemblyVolume();
  // Make a hexagone cell out of 6 toothplates. These can zip togeather
  // without generating overlaps (they are self-contained)
  for (G4int i2=0; i2<6; i2++) {
    G4double phi =  60.*i2 * deg;
    G4double xp = dshift*sin(phi);
    G4double yp = -dshift*cos(phi);
    rot = new G4RotationMatrix(*rot1);
    rot->rotateZ(phi); 
    G4ThreeVector pos(xp, yp,0.);
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
  // structure. This again works without any need to define rows as "overlapping"
  G4AssemblyVolume* row = new G4AssemblyVolume();
  G4int ncells = 5;
  for (G4int i3=0; i3<ncells; i3++) {
    G4double ycell = (2*i3+1)*(dshift+10.*cm);
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
  G4double dxrow = 3.*(dshift+10.*cm)*tan(30.*deg);
  G4double dyrow = dshift+10.*cm;
  G4int nrows = 5;
  for (G4int i4=0; i4<nrows; i4++) {
    G4double xrow = 0.5*(2*i4+1)*dxrow;
    G4double yrow = 0.5*dyrow;
    if ((i4%2)==0) yrow = -yrow;
    G4ThreeVector pos1(xrow, yrow, 0.);
    row->MakeImprint(worldV, pos1, 0);
    G4ThreeVector pos2(-xrow, -yrow, 0.);
    row->MakeImprint(worldV, pos2, 0);
  }        
  
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestAssemblies2()
{
// Example for assemblies with reflections

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(2.*m, 2.*m, 1.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, G4ThreeVector(), worldV, "world", 0, false, 0); 
   
  // Assembly 
  //
  G4AssemblyVolume* assembly = new G4AssemblyVolume();

  // Cons volume
  G4VSolid* consS
    = new G4Cons("consS", 10.*cm, 40.*cm, 20.*cm, 60.*cm, 50*cm, 0., 360.*deg);

  G4LogicalVolume* consV
    = new G4LogicalVolume(consS, fBasicMaterial, "CONS");

  // Transformations
  //
  HepGeom::Transform3D transform1
   = HepGeom::Translate3D( 110.*cm,0., 0.)
   * HepGeom::RotateY3D( 90.*deg);
 
  HepGeom::Transform3D transform2
   = HepGeom::ReflectX3D()
   * HepGeom::Translate3D( 110.*cm,0., 0.)
   * HepGeom::RotateY3D( 90.*deg);
  
  HepGeom::Transform3D transform3
   = HepGeom::Translate3D( 0., 110.*cm, 0.)
   * HepGeom::RotateX3D(-90.*deg);
 
  HepGeom::Transform3D transform4
   = HepGeom::ReflectY3D()
   * HepGeom::Translate3D( 0., 110.*cm, 0.)
   * HepGeom::RotateX3D(-90.*deg);
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
 
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids1()
{
// Only translation in solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4.*m, 1.*m, 4.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  G4VSolid* solid1 
    = new G4Box("boxS", 50.*cm, 50.*cm, 50.*cm);

  G4VSolid* solid2 
    = new G4Cons("consS", 10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
 
  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25*m, 0., -2.*m),
		    volume1, "solid1", worldV, false, 0);

  G4LogicalVolume* volume2
    = new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, CLHEP::Hep3Vector( 1.25*m, 0., -2.*m),
                    volume2, "solid2", worldV, false, 0);


  // Intersection
  //
  G4VSolid* intersectionS
    = new G4IntersectionSolid(
                  "intersection_solid1_solid2_S", solid1, solid2, 0, 
		  CLHEP::Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* intersectionV
    = new G4LogicalVolume(intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(-2.5*m, 0., 2.*m),
                    intersectionV, "intersection_solid1_solid2", worldV, false, 0); 
  
  // Subtraction
  //
  G4VSolid* subtractionS
    = new G4SubtractionSolid(
                  "subtraction_solid1_solid2_S", solid1, solid2, 0, 
		  CLHEP::Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* subtractionV
    = new G4LogicalVolume(subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., 2.*m), 
                   subtractionV, "subtraction_solid1_solid2", worldV, false, 0);
  
  // Union
  //
  G4VSolid* unionS
    = new G4UnionSolid(
                  "union_solid1_solid2_S", solid1, solid2, 0, 
		  CLHEP::Hep3Vector(20.*cm, 0., 0.)); 
  G4LogicalVolume* unionV
    = new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector( 2.5*m, 0., 2.*m),
                    unionV, "union_solid1_solid2", worldV, false, 0);
  
  return (void*) world;
}


//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids2()
{
// Translation + rotation in solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4.*m, 1.*m, 4.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  G4VSolid* solid1 
    = new G4Box("boxS", 50.*cm, 50.*cm, 50.*cm);

  G4VSolid* solid2 
    = new G4Cons("consS", 10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
 
  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "solid1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25*m, 0., -2.*m),
		    volume1, "solid1", worldV, false, 0);

  G4LogicalVolume* volume2
    = new G4LogicalVolume(solid2, fBasicMaterial, "solid2");
  new G4PVPlacement(0, CLHEP::Hep3Vector( 1.25*m, 0., -2.*m),
                    volume2, "solid2", worldV, false, 0);


  // Define displacement transformations
  //
 
   // Rotate solid1  
  CLHEP::HepRotation* rot1 = new CLHEP::HepRotation();
  rot1->rotateY(-45.*deg);

  // Rotate + translate solid2
  //
  CLHEP::HepRotation* rot2 = new CLHEP::HepRotation();
  rot2->rotateY( 45.*deg); 
  rot2->rotateX(-30.*deg);
  CLHEP::Hep3Vector  tr2 = CLHEP::Hep3Vector(20.*cm, 0., 0.);
  
  // Intersection
  //
  G4VSolid* intersectionS
    = new G4IntersectionSolid(
                  "intersection_solid1_solid2_S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* intersectionV
    = new G4LogicalVolume(intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector(-2.5*m, 0., 2.*m),
                    intersectionV, "intersection_solid1_solid2", worldV, false, 0); 
  
  // Subtraction
  //
  G4VSolid* subtractionS
    = new G4SubtractionSolid(
                  "subtraction_solid1_solid2_S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* subtractionV
    = new G4LogicalVolume(subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector(0., 0., 2.*m), 
                   subtractionV, "subtraction_solid1_solid2", worldV, false, 0);
  
  // Union
  //
  G4VSolid* unionS
    = new G4UnionSolid(
                  "union_solid1_solid2_S", solid1, solid2, rot2, tr2); 
  G4LogicalVolume* unionV
    = new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(rot1, CLHEP::Hep3Vector( 2.5*m, 0., 2.*m),
                    unionV, "union_solid1_solid2", worldV, false, 0);
  
  return (void*) world;
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestBooleanSolids3()
{
// Translation + reflection in solid displacement

  G4cout << "Reflections are not allowed in Boolean solids in Geant4." << G4endl;
  exit(1);
}

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestDisplacedSolids1()
{
// Test solid displacement

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(60.*cm, 60.*cm, 160.*cm);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  
  // Normal solid
  //
  G4VSolid* solid1 
    = new G4Box("boxS1", 50.*cm, 50.*cm, 50.*cm);

  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "volume1");

  // Chained displaced solids
  //
  G4VSolid* solid2 
    = new G4Box("boxS2", 50.*cm, 50.*cm, 50.*cm);

  G4DisplacedSolid* solid2A 
    = new G4DisplacedSolid("boxS2A", solid2, 0, G4ThreeVector(0., 0., 50.*cm));
 
  G4DisplacedSolid* solid2B 
    = new G4DisplacedSolid("boxS2B", solid2A, 0, G4ThreeVector(0., 0., 50.*cm));
 
  G4DisplacedSolid* solid2C 
    = new G4DisplacedSolid("boxS2C", solid2B, 0, G4ThreeVector(0., 0., 50.*cm));
 
  G4LogicalVolume* volume2C
    = new G4LogicalVolume(solid2C, fBasicMaterial, "volume2C");

  // Daughter to be placed in displaced solid
  //
  G4VSolid* solid3 
    = new G4Box("boxS3", 20.*cm, 20.*cm, 20.*cm);

  G4LogicalVolume* volume3
    = new G4LogicalVolume(solid3, fBasicMaterial, "volume3");

  
  // Daughter to be placed in normal solid
  //
  G4VSolid* solid4 
    = new G4Box("boxS4", 20.*cm, 20.*cm, 10.*cm);

  G4LogicalVolume* volume4
    = new G4LogicalVolume(solid4, fBasicMaterial, "volume4");

  // Daughter with displaced solid to be placed in displaced solid
  //
  G4VSolid* solid5 
    = new G4Box("boxS5", 20.*cm, 20.*cm, 5.*cm);

  G4VSolid* solid5A 
    = new G4DisplacedSolid("boxS5A", solid5, G4ThreeVector(0., 0., 40.*cm));

  G4LogicalVolume* volume5A
    = new G4LogicalVolume(solid5A, fBasicMaterial, "volume3");

  
  // Make placements
  //
  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., -100.*cm),
                    volume1, "volume1", worldV, false, 1);

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., -100.*cm),
		    volume2C, "volume2C", worldV, false, 2);

  new G4PVPlacement(0, CLHEP::Hep3Vector( 0., 0., 150.*cm),
                    volume3, "volume3", volume2C, false, 1);
  
  new G4PVPlacement(0, CLHEP::Hep3Vector( 0.*cm, 0.*cm, 0.),
                    volume4, "volume4", volume1, false, 1);

  new G4PVPlacement(0, CLHEP::Hep3Vector( 0.*cm, 0.*cm, 150.*cm),
                    volume5A, "volume5A", volume2C, false, 2);

  return (void*) world;
}  

//_____________________________________________________________________________
void* TstGeometryViaGeant4::TestDisplacedSolids2()
{
// Test BooleanSolids2 where displacement is defined via
// Displaced solid

  // World
  //
  G4LogicalVolume* worldV = CreateWorld(4.*m, 1.*m, 4.*m);
  G4VPhysicalVolume* world
    = new G4PVPlacement(0, CLHEP::Hep3Vector(), worldV, "world", 0, false, 0); 
  
  // Create solids
  G4VSolid* solid1 
    = new G4Box("boxS", 50.*cm, 50.*cm, 50.*cm);

  G4VSolid* solid2 
    = new G4Cons("consS", 10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
 
  // Simple solids placed for a control
  //
  G4LogicalVolume* volume1
    = new G4LogicalVolume(solid1, fBasicMaterial, "volume1");
  new G4PVPlacement(0, CLHEP::Hep3Vector(-1.25*m, 0., -2.*m),
		    volume1, "solid1", worldV, false, 0);

  G4LogicalVolume* volume2
    = new G4LogicalVolume(solid2, fBasicMaterial, "volume2");
  new G4PVPlacement(0, CLHEP::Hep3Vector( 1.25*m, 0., -2.*m),
                    volume2, "solid2", worldV, false, 0);


   // Rotate solid1 
   // 
  CLHEP::HepRotation* rot1 = new CLHEP::HepRotation();
  rot1->rotateY(-45.*deg);
  CLHEP::Hep3Vector  tr1 = CLHEP::Hep3Vector();

  // Rotate + translate solid2
  //
  CLHEP::HepRotation* rot2 = new CLHEP::HepRotation();
  //rot2->rotateY( 45.*deg); 
  rot2->rotateX(-30.*deg);
  CLHEP::Hep3Vector  tr2 = CLHEP::Hep3Vector(20.*cm, 0., 0.);
  
  // Displaced solids
  //
  G4DisplacedSolid* dsolid1
    = new G4DisplacedSolid("dboxS", solid1, rot1, tr1);

  G4DisplacedSolid* dsolid2
    = new G4DisplacedSolid("dconsS", solid2, rot2, tr2);

  // Intersection
  //
  G4VSolid* intersectionS
    = new G4IntersectionSolid(
                  "intersection_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, 
		  CLHEP::Hep3Vector()); 
  G4LogicalVolume* intersectionV
    = new G4LogicalVolume(intersectionS, fBasicMaterial, "intersection_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(-2.5*m, 0., 2.*m),
                    intersectionV, "intersection_solid1_solid2", worldV, false, 0); 
  
  // Subtraction
  //
  G4VSolid* subtractionS
    = new G4SubtractionSolid(
                  "subtraction_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, 
		  CLHEP::Hep3Vector()); 
  G4LogicalVolume* subtractionV
    = new G4LogicalVolume(subtractionS, fBasicMaterial, "subtraction_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector(0., 0., 2.*m), 
                   subtractionV, "subtraction_solid1_solid2", worldV, false, 0);
  
  // Union
  //
  G4VSolid* unionS
    = new G4UnionSolid(
                  "union_dsolid1_dsolid2_S", dsolid1, dsolid2, 0, 
		  CLHEP::Hep3Vector()); 
  G4LogicalVolume* unionV
    = new G4LogicalVolume(unionS, fBasicMaterial, "union_solid1_solid2");

  new G4PVPlacement(0, CLHEP::Hep3Vector( 2.5*m, 0., 2.*m),
                    unionV, "union_solid1_solid2", worldV, false, 0);
  
  return (void*) world;
 }  

//#include "MyDetectorConstruction.hh"

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
 
