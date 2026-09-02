// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Test vgm_boolean_frame_test
// ---------------------------
// A Root composite solid is defined in the frame in which its constituent
// matrices are written, while its Geant4 counterpart is defined in the frame
// of the first constituent.  The two frames differ whenever the first
// constituent carries a transformation, and the volumes placed inside such a
// solid have to be converted into the second frame.
//
// The test builds one volume whose solid is "(A:trA)+(B:trB)" and one whose
// solid is the same shape written as "A2+(B2:trB2)", places a small box at the
// origin of each, converts the geometry to Geant4 and checks that both boxes
// are still where Root put them.
//
// Needs no run manager and returns a non-zero code on failure.

#include "Geant4GM/volumes/Factory.h"
#include "RootGM/volumes/Factory.h"

#include "TGeoBBox.h"
#include "TGeoCompositeShape.h"
#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoMedium.h"
#include "TGeoVolume.h"

#include "G4LogicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"

#include <cmath>
#include <iostream>
#include <string>

namespace {

const double kTolerance = 1.e-6; // cm

/// Build the Root geometry described above.
void CreateGeometry()
{
  new TGeoManager("booleanFrame", "boolean solid with a transformed first constituent");
  TGeoMedium* medium = new TGeoMedium("medium", 1, new TGeoMaterial("material", 26.98, 13., 2.7));
  TGeoVolume* world = gGeoManager->MakeBox("world", medium, 300., 300., 300.);
  gGeoManager->SetTopVolume(world);

  // the first constituent is displaced, so the solid frame and the frame of
  // the expression are 7 cm apart
  new TGeoBBox("A", 20., 20., 10.);
  new TGeoBBox("B", 15., 15., 5.);
  (new TGeoTranslation("trA", 0., 0., -7.))->RegisterYourself();
  (new TGeoTranslation("trB", 0., 0., 8.))->RegisterYourself();
  TGeoVolume* shifted =
    new TGeoVolume("shifted", new TGeoCompositeShape("shiftedS", "(A:trA)+(B:trB)"), medium);
  shifted->AddNode(gGeoManager->MakeBox("inShifted", medium, 1., 1., 1.), 1, gGeoIdentity);
  world->AddNode(shifted, 1, new TGeoTranslation(0., 0., 100.));

  // the same solid with the first constituent at rest: the two frames coincide
  new TGeoBBox("A2", 20., 20., 10.);
  new TGeoBBox("B2", 15., 15., 5.);
  (new TGeoTranslation("trB2", 0., 0., 15.))->RegisterYourself();
  TGeoVolume* atRest =
    new TGeoVolume("atRest", new TGeoCompositeShape("atRestS", "A2+(B2:trB2)"), medium);
  atRest->AddNode(gGeoManager->MakeBox("inAtRest", medium, 1., 1., 1.), 1, gGeoIdentity);
  world->AddNode(atRest, 1, new TGeoTranslation(0., 0., -100.));

  gGeoManager->CloseGeometry();
}

/// Return the global position of the Geant4 placement of the volume \em name.
bool GlobalPosition(G4VPhysicalVolume* pv, const G4RotationMatrix& rotation,
  const G4ThreeVector& translation, const std::string& name, G4ThreeVector& position)
{
  const G4ThreeVector t = translation + rotation * pv->GetObjectTranslation();
  G4RotationMatrix r = rotation;
  if (pv->GetObjectRotation()) r = rotation * (*pv->GetObjectRotation());

  if (pv->GetLogicalVolume()->GetName() == name) {
    position = t;
    return true;
  }
  for (std::size_t i = 0; i < pv->GetLogicalVolume()->GetNoDaughters(); ++i) {
    if (GlobalPosition(pv->GetLogicalVolume()->GetDaughter(i), r, t, name, position))
      return true;
  }
  return false;
}

/// Compare the Geant4 position of \em name with the position Root gave it.
bool Check(G4VPhysicalVolume* world, const std::string& name, double expectedZ)
{
  G4ThreeVector position;
  if (!GlobalPosition(world, G4RotationMatrix(), G4ThreeVector(), name, position)) {
    std::cerr << "FAILED  " << name << " not found in the Geant4 geometry" << std::endl;
    return false;
  }
  const double z = position.z() / cm;
  const bool ok = std::abs(z - expectedZ) < kTolerance;
  std::cout << (ok ? "OK      " : "FAILED  ") << name << " at z = " << z
            << " cm, expected " << expectedZ << " cm" << std::endl;
  return ok;
}

} // namespace

int main()
{
  CreateGeometry();

  RootGM::Factory rootFactory;
  rootFactory.Import(gGeoManager->GetTopNode());
  Geant4GM::Factory g4Factory;
  rootFactory.Export(&g4Factory);

  G4VPhysicalVolume* world = nullptr;
  for (auto* pv : *G4PhysicalVolumeStore::GetInstance()) {
    if (pv->GetMotherLogical() == nullptr) world = pv;
  }
  if (!world) {
    std::cerr << "FAILED  no world volume after the conversion" << std::endl;
    return 1;
  }

  bool ok = true;
  ok &= Check(world, "inShifted", 100.);
  ok &= Check(world, "inAtRest", -100.);
  return ok ? 0 : 1;
}
