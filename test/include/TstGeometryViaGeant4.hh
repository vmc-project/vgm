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

#ifndef TST_GEOMETRY_VIA_GEANT4_H
#define TST_GEOMETRY_VIA_GEANT4_H

#include "TstVGeometry.hh"

class G4LogicalVolume;
class G4Material;

class TstGeometryViaGeant4 : public TstVGeometry
{
 public:
  TstGeometryViaGeant4();
  virtual ~TstGeometryViaGeant4();

  virtual void DefineMaterials();

  virtual void* TestSolids(G4bool fullPhi);
  virtual void* TestExtraSolid(VGM::SolidType solidType);
  virtual void* TestNewSolid();
  virtual void* TestNewSolid2();
  virtual void* TestPlacements();
  virtual void* TestPlacements2(G4bool bestMatch);
  virtual void* TestReflections(G4bool fullPhi);
  virtual void* TestScaledSolids(G4bool fullPhi);
  virtual void* TestAssemblies();
  virtual void* TestAssemblies2();
  virtual void* TestBooleanSolids1();
  virtual void* TestBooleanSolids2();
  virtual void* TestBooleanSolids3();
  virtual void* TestDisplacedSolids1();
  virtual void* TestDisplacedSolids2();
  virtual void* TestSpecial();

 private:
  G4LogicalVolume* CreateWorld(G4double x, G4double y, G4double z);
  G4VSolid* CreateNewSolid();
  G4VSolid* CreateBox();
  G4VSolid* CreateCons(G4double sphi, G4double dphi);
  G4VSolid* CreateEllipsoid();
  G4VSolid* CreateEllipticalTube();
  G4VSolid* CreateExtrudedSolid1();
  G4VSolid* CreateExtrudedSolid2();
  G4VSolid* CreateHype();
  G4VSolid* CreatePara();
  G4VSolid* CreateParaboloid();
  G4VSolid* CreatePolycone(G4double sphi, G4double dphi);
  G4VSolid* CreatePolyhedra(G4double sphi, G4double dphi);
  G4VSolid* CreateSphere(G4double sphi, G4double dphi);
  G4VSolid* CreateTessellatedSolid();
  G4VSolid* CreateTorus(G4double sphi, G4double dphi);
  G4VSolid* CreateTrap();
  G4VSolid* CreateTrd();
  G4VSolid* CreateTubs(G4double sphi, G4double dphi);
  G4VSolid* CreateCtubs(G4double sphi, G4double dphi);
  G4LogicalVolume* CreateVolume(G4VSolid* solid, G4bool scale = false);
  G4LogicalVolume* PlaceSolids(G4LogicalVolume* mother, G4bool fullPhi,
    G4bool reflect, G4bool scale, G4double zpos);
  void PlaceExtraSolid(VGM::SolidType solidType, G4LogicalVolume* mother);

  // data members
  G4Material* fBasicMaterial;
};

#endif // TST_GEOMETRY_VIA_GEANT4_H
