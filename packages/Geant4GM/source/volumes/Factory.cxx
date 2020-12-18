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
// Class Factory
// ---------------
// The interface to geometry factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"
#include "ClhepVGM/Units.h"
#include "ClhepVGM/transform.h"

#include "Geant4GM/materials/Material.h"
#include "Geant4GM/materials/MaterialFactory.h"
#include "Geant4GM/materials/Medium.h"
#include "Geant4GM/solids/Arb8.h"
#include "Geant4GM/solids/BooleanSolid.h"
#include "Geant4GM/solids/Box.h"
#include "Geant4GM/solids/Cons.h"
#include "Geant4GM/solids/Ctubs.h"
#include "Geant4GM/solids/DisplacedSolid.h"
#include "Geant4GM/solids/Ellipsoid.h"
#include "Geant4GM/solids/EllipticalTube.h"
#include "Geant4GM/solids/ExtrudedSolid.h"
#include "Geant4GM/solids/Hype.h"
#include "Geant4GM/solids/MultiUnion.h"
#include "Geant4GM/solids/Para.h"
#include "Geant4GM/solids/Paraboloid.h"
#include "Geant4GM/solids/Polycone.h"
#include "Geant4GM/solids/Polyhedra.h"
#include "Geant4GM/solids/ScaledSolid.h"
#include "Geant4GM/solids/SolidMap.h"
#include "Geant4GM/solids/Sphere.h"
#include "Geant4GM/solids/TessellatedSolid.h"
#include "Geant4GM/solids/Torus.h"
#include "Geant4GM/solids/Trap.h"
#include "Geant4GM/solids/Trd.h"
#include "Geant4GM/solids/Tubs.h"
#include "Geant4GM/volumes/Factory.h"
#include "Geant4GM/volumes/Placement.h"
#include "Geant4GM/volumes/PlacementMap.h"
#include "Geant4GM/volumes/Volume.h"
#include "Geant4GM/volumes/VolumeMap.h"

#include "G4BooleanSolid.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4CutTubs.hh"
#include "G4DisplacedSolid.hh"
#include "G4Ellipsoid.hh"
#include "G4EllipticalTube.hh"
#include "G4ExtrudedSolid.hh"
#include "G4Hype.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4MultiUnion.hh"
#include "G4PVDivisionFactory.hh"
#include "G4Para.hh"
#include "G4Paraboloid.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4ReflectedSolid.hh"
#include "G4ReplicatedSlice.hh"
#include "G4ScaledSolid.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4TessellatedSolid.hh"
#include "G4Torus.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"

bool Geant4GM::Factory::fgSurfCheck = false;

//
// static methods
//

//_____________________________________________________________________________
void Geant4GM::Factory::SetSurfCheck(bool surfCheck)
{
  /// Set the option to activate geometry checking:
  /// set pSurfChk=true for all G4PVPlacement objects

  fgSurfCheck = surfCheck;
}

//_____________________________________________________________________________
bool Geant4GM::Factory::GetSurfCheck()
{
  /// Return the option to activate geometry checking

  return fgSurfCheck;
}

//
// ctors, dtor
//

//_____________________________________________________________________________
Geant4GM::Factory::Factory()
  : VGM::IFactory(),
    BaseVGM::VFactory("Geant4_GM_Factory", new Geant4GM::MaterialFactory()),
    fTop(0),
    fSolid(0)
{
  /// Standard default constructor
}

//_____________________________________________________________________________
Geant4GM::Factory::Factory(const Factory& rhs)
  : VGM::IFactory(rhs), BaseVGM::VFactory(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Factory::~Factory()
{
  //
  // delete map singletons
  delete Geant4GM::SolidMap::Instance();
  delete Geant4GM::VolumeMap::Instance();
  delete Geant4GM::PlacementMap::Instance();
  // There is inconsistence in using the singleton maps
  // via a factory which is not a singleton
  // TO DO: to be improved later
}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::Factory::ImportConstituentSolid(int index, G4BooleanSolid* solid)
{
  /// Import constituents of G4 Boolean solid into VGM

  G4VSolid* consSolid =
    Geant4GM::BooleanSolid::GetConstituentSolid(index, solid);

  if (!Geant4GM::SolidMap::Instance()->GetSolid(consSolid)) {
    VGM::ISolid* vgmSolid = ImportSolid(consSolid);
    if (Debug()) {
      BaseVGM::DebugInfo();
      if (vgmSolid)
        std::cout << "   Imported solid: " << *vgmSolid << std::endl;
      else
        std::cout << "   Imported solid: "
                  << "0x0" << std::endl;
    }
  }
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportConstituentSolid(int index, G4MultiUnion* solid)
{
  /// Import constituents of G4 Boolean solid into VGM

  G4VSolid* consSolid = solid->GetSolid(index);

  if (!Geant4GM::SolidMap::Instance()->GetSolid(consSolid)) {
    VGM::ISolid* vgmSolid = ImportSolid(consSolid);
    if (Debug()) {
      BaseVGM::DebugInfo();
      if (vgmSolid)
        std::cout << "   Imported solid: " << *vgmSolid << std::endl;
      else
        std::cout << "   Imported solid: "
                  << "0x0" << std::endl;
    }
  }
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::ImportSolid(G4VSolid* solid)
{
  /// Import G4 solid into VGM

  // Do not import the same solid twice
  //
  VGM::ISolid* importedSolid = Geant4GM::SolidMap::Instance()->GetSolid(solid);
  if (importedSolid) return importedSolid;

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing solid: ";
    if (Debug() > 1) std::cout << solid << "  ";
    std::cout << solid->GetName() << std::endl;
  }

  G4VSolid* consSolid = solid;

  // Get constituent solid if the solid is a reflected solid
  //
  G4ReflectedSolid* reflSolid = dynamic_cast<G4ReflectedSolid*>(solid);
  if (reflSolid) consSolid = reflSolid->GetConstituentMovedSolid();

  G4Box* box = dynamic_cast<G4Box*>(consSolid);
  if (box) {
    return Register(new Geant4GM::Box(box, reflSolid));
  }

  G4Cons* cons = dynamic_cast<G4Cons*>(consSolid);
  if (cons) {
    return Register(new Geant4GM::Cons(cons, reflSolid));
  }

  G4CutTubs* ctubs = dynamic_cast<G4CutTubs*>(consSolid);
  if (ctubs) {
    return Register(new Geant4GM::Ctubs(ctubs, reflSolid));
  }

  G4Ellipsoid* ellipsoid = dynamic_cast<G4Ellipsoid*>(consSolid);
  if (ellipsoid) {
    return Register(new Geant4GM::Ellipsoid(ellipsoid, reflSolid));
  }

  G4EllipticalTube* eltu = dynamic_cast<G4EllipticalTube*>(consSolid);
  if (eltu) {
    return Register(new Geant4GM::EllipticalTube(eltu, reflSolid));
  }

  G4ExtrudedSolid* xtru = dynamic_cast<G4ExtrudedSolid*>(consSolid);
  if (xtru) {
    return Register(new Geant4GM::ExtrudedSolid(xtru, reflSolid));
  }

  G4Hype* hype = dynamic_cast<G4Hype*>(consSolid);
  if (hype) {
    return Register(new Geant4GM::Hype(hype, reflSolid));
  }

  G4Para* para = dynamic_cast<G4Para*>(consSolid);
  if (para) {
    return Register(new Geant4GM::Para(para, reflSolid));
  }

  G4Paraboloid* paraboloid = dynamic_cast<G4Paraboloid*>(consSolid);
  if (paraboloid) {
    return Register(new Geant4GM::Paraboloid(paraboloid, reflSolid));
  }

  G4Polycone* polycone = dynamic_cast<G4Polycone*>(consSolid);
  if (polycone) {
    return Register(new Geant4GM::Polycone(polycone, reflSolid));
  }

  G4Polyhedra* polyhedra = dynamic_cast<G4Polyhedra*>(consSolid);
  if (polyhedra) {
    return Register(new Geant4GM::Polyhedra(polyhedra, reflSolid));
  }

  G4Sphere* sphere = dynamic_cast<G4Sphere*>(consSolid);
  if (sphere) {
    return Register(new Geant4GM::Sphere(sphere, reflSolid));
  }

  G4TessellatedSolid* tessel = dynamic_cast<G4TessellatedSolid*>(consSolid);
  if (tessel) {
    return Register(new Geant4GM::TessellatedSolid(tessel, reflSolid));
  }

  G4Torus* torus = dynamic_cast<G4Torus*>(consSolid);
  if (torus) {
    return Register(new Geant4GM::Torus(torus, reflSolid));
  }

  G4Trap* trap = dynamic_cast<G4Trap*>(consSolid);
  if (trap) {
    return Register(new Geant4GM::Trap(trap, reflSolid));
  }

  G4Trd* trd = dynamic_cast<G4Trd*>(consSolid);
  if (trd) {
    return Register(new Geant4GM::Trd(trd, reflSolid));
  }

  G4Tubs* tubs = dynamic_cast<G4Tubs*>(consSolid);
  if (tubs) {
    return Register(new Geant4GM::Tubs(tubs, reflSolid));
  }

  G4DisplacedSolid* displaced = dynamic_cast<G4DisplacedSolid*>(consSolid);
  if (displaced) {
    ImportSolid(displaced->GetConstituentMovedSolid());
    return Register(new Geant4GM::DisplacedSolid(displaced, reflSolid));
  }

  G4ScaledSolid* scaled = dynamic_cast<G4ScaledSolid*>(consSolid);
  if (scaled) {
    ImportSolid(scaled->GetUnscaledSolid());
    return Register(new Geant4GM::ScaledSolid(scaled, reflSolid));
  }

  G4BooleanSolid* boolean = dynamic_cast<G4BooleanSolid*>(consSolid);
  if (boolean) {
    ImportConstituentSolid(0, boolean);
    ImportConstituentSolid(1, boolean);
    VGM::IBooleanSolid* vgmBoolean =
      new Geant4GM::BooleanSolid(boolean, reflSolid);
    Register(vgmBoolean);

    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << "Imported Boolean solid: ";
      if (Debug() > 1) std::cout << vgmBoolean;
      std::cout << std::endl;
      BaseVGM::DebugInfo();
      std::cout << *vgmBoolean << std::endl;
    }

    return vgmBoolean;
  }

  G4MultiUnion* multiUnion = dynamic_cast<G4MultiUnion*>(consSolid);
  if (multiUnion) {
    for (G4int i = 0; i < multiUnion->GetNumberOfSolids(); ++i) {
      ImportConstituentSolid(i, multiUnion);
    }
    VGM::IMultiUnion* vgmMultiUnion =
      new Geant4GM::MultiUnion(multiUnion, reflSolid);
    Register(vgmMultiUnion);

    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << "Imported MultiUnion solid: ";
      if (Debug() > 1) std::cout << vgmMultiUnion;
      std::cout << std::endl;
      BaseVGM::DebugInfo();
      std::cout << *vgmMultiUnion << std::endl;
    }

    return vgmMultiUnion;
  }

  std::cerr << "Geant4GM::Factory::ImportSolid: " << std::endl;
  std::cerr << "Unsupported solid type (solid \"" << solid->GetName() << "\""
            << "   type \"" << solid->GetEntityType() << "\")" << std::endl;

  if (Ignore()) {
    std::cerr << "*** Warning: Using a box instead  ***" << std::endl;
    return Register(new Geant4GM::Box(solid->GetName(),
      DummyBoxDimensions() / ClhepVGM::Units::Length(),
      DummyBoxDimensions() / ClhepVGM::Units::Length(),
      DummyBoxDimensions() / ClhepVGM::Units::Length()));
  }
  else {
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
VGM::IVolume* Geant4GM::Factory::ImportLV(G4LogicalVolume* lv)
{
  /// Import logical volume in VGM

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "Importing LV: " << lv->GetName() << std::endl;
  }

  // Import solid
  VGM::ISolid* solid = ImportSolid(lv->GetSolid());

  if (Debug()) {
    BaseVGM::DebugInfo();
    if (solid)
      std::cout << "   Imported solid: " << *solid << std::endl;
    else
      std::cout << "   Imported solid: "
                << "0x0" << std::endl;
  }

  // Create vgm volume
  VGM::IVolume* volume =
    new Geant4GM::Volume(solid, lv, lv->GetMaterial()->GetName());
  VolumeStore().push_back(volume);
  return volume;
}

//_____________________________________________________________________________
VGM::IVolume* Geant4GM::Factory::ImportLV(
  G4LogicalVolume* lv, const std::string& mediumName)
{
  /// Import logical volume in VGM

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "Importing LV: " << lv->GetName() << std::endl;
  }

  // Import solid
  VGM::ISolid* solid = ImportSolid(lv->GetSolid());

  // Create vgm volume
  VGM::IVolume* volume = new Geant4GM::Volume(solid, lv, mediumName);
  VolumeStore().push_back(volume);
  return volume;
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportDaughters(G4LogicalVolume* lv)
{
  // Import recursively all daughters logical volumes.

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "ImportDaughters for " << lv->GetName() << std::endl;
  }

  for (size_t i = 0; i < lv->GetNoDaughters(); i++) {

    G4LogicalVolume* dLV = lv->GetDaughter(i)->GetLogicalVolume();

    VGM::IVolume* dVolume = Geant4GM::VolumeMap::Instance()->GetVolume(dLV);

    if (!dVolume) {
      // Import logical volume
      dVolume = ImportLV(dLV);

      // Process its daughters
      ImportDaughters(dLV);
    }
  }
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportPositions()
{
  // Import placements for all volumes imported

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Import positions: " << std::endl;
  }

  for (unsigned int i = 0; i < Volumes().size(); i++) {

    VGM::IVolume* volume = Volumes()[i];
    G4LogicalVolume* lv = Geant4GM::VolumeMap::Instance()->GetVolume(volume);

    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << i << "th volume: " << lv->GetName() << "  ";
      if (Debug() > 1)
        std::cout << "   lv: " << lv << "  "
                  << "  vgm: " << volume;
      std::cout << std::endl;
    }

    for (size_t id = 0; id < lv->GetNoDaughters(); id++) {

      G4VPhysicalVolume* dPV = lv->GetDaughter(id);
      G4LogicalVolume* dLV = dPV->GetLogicalVolume();

      if (Debug() > 0) {
        BaseVGM::DebugInfo();
        std::cout << "   " << id << "th daughter  pv = ";
        if (Debug() > 1) std::cout << dPV << "  ";
        std::cout << dPV->GetName() << "  lv = ";
        if (Debug() > 1) std::cout << dLV << "  ";
        std::cout << dLV->GetName();
      }

      VGM::IVolume* dVolume = Geant4GM::VolumeMap::Instance()->GetVolume(dLV);

      // Create placement
      VGM::IPlacement* dPlacement =
        new Geant4GM::Placement(dVolume, volume, dPV);

      if (Debug() > 0) {
        std::cout << " vgmPl = ";
        if (Debug() > 1) std::cout << dPlacement << "  ";
        std::cout << dPlacement->Name() << " vgmVol = ";
        if (Debug() > 1) std::cout << dVolume << "  ";
        std::cout << dVolume->Name() << std::endl;
      }
    }
  }
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportPositions(G4LogicalVolume* lv)
{
  // Import placements for daughters tree of specified lv.
  // Check if the placement has been already imported.

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "ImportPositions for lv " << lv->GetName()
              << " nofDaughters: " << lv->GetNoDaughters() << std::endl;
  }

  VGM::IVolume* volume = Geant4GM::VolumeMap::Instance()->GetVolume(lv);

  for (size_t id = 0; id < lv->GetNoDaughters(); id++) {

    G4VPhysicalVolume* dPV = lv->GetDaughter(id);

    if (Debug()) {
      BaseVGM::DebugInfo();
      std::cout << id << "th daugher: " << dPV->GetName() << std::endl;
    }

    if (!Geant4GM::PlacementMap::Instance()->GetPlacement(dPV)) {
      /*
            if (Debug()>0) {
              BaseVGM::DebugInfo();
              std::cout <<
         "Geant4GM::PlacementMap::Instance()->GetPlacement(dPV) *not* found"
                        << std::endl;
              BaseVGM::DebugInfo();
              std::cout << "  go to import position" << std::endl;
            }
      */
      G4LogicalVolume* dLV = dPV->GetLogicalVolume();
      VGM::IVolume* dVolume = Geant4GM::VolumeMap::Instance()->GetVolume(dLV);

      // Create placement
      new Geant4GM::Placement(dVolume, volume, dPV);

      // Recursively import positions of daughters
      ImportPositions(dLV);
    }
    /*
        else
          if (Debug()>0) {
            BaseVGM::DebugInfo();
            std::cout << "Geant4GM::PlacementMap::Instance()->GetPlacement(dPV)
       found"
                      << std::endl;
            BaseVGM::DebugInfo();
            std::cout << "  do not import position" << std::endl;
          }
    */
  }
}

//_____________________________________________________________________________
VGM::IPlacement* Geant4GM::Factory::ImportPVPair(VGM::IVolume* volume,
  VGM::IVolume* motherVolume, G4PhysicalVolumesPair pvPair)
{
  G4ReflectionFactory* g4ReflectionFactory = G4ReflectionFactory::Instance();

  // Get info about created PV
  G4VPhysicalVolume* pv1 = pvPair.first;
  G4LogicalVolume* lv1 = pv1->GetLogicalVolume();
  VGM::IVolume* iv1 = Geant4GM::VolumeMap::Instance()->GetVolume(lv1);
  if (!iv1) {
    // a new logical volume has been created by G4 reflection factory
    // has to be imported into VGM
    iv1 = ImportLV(lv1, volume->MediumName());
    ImportDaughters(lv1);
    ImportPositions(lv1);
  }
  VGM::IPlacement* placement1 = new Geant4GM::Placement(iv1, motherVolume, pv1);
  // Register physical volume in the map
  Geant4GM::PlacementMap::Instance()->AddPlacement(placement1, pv1);

  G4VPhysicalVolume* pv2 = pvPair.second;
  if (pv2) {
    G4LogicalVolume* g4MotherLV =
      Geant4GM::VolumeMap::Instance()->GetVolume(motherVolume);

    // mother volume is the other volume in the pair
    // constituen/reflected mother lv
    G4LogicalVolume* mlv2 = 0;
    if (g4ReflectionFactory->IsReflected(g4MotherLV))
      mlv2 = g4ReflectionFactory->GetConstituentLV(g4MotherLV);
    if (g4ReflectionFactory->IsConstituent(g4MotherLV))
      mlv2 = g4ReflectionFactory->GetReflectedLV(g4MotherLV);
    if (!mlv2) {
      // should not happen
      std::cerr << "    Geant4GM::Factory::CreatePlacement: " << std::endl;
      std::cerr << "    Misundersood G4ReflectionFactory behavior "
                << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
    else {
      VGM::IVolume* miv2 = Geant4GM::VolumeMap::Instance()->GetVolume(mlv2);
      if (!miv2) {
        // should not happen
        std::cerr << "    Geant4GM::Factory::CreatePlacement: " << std::endl;
        std::cerr << "    Missing mapping of existing LV to VGM" << std::endl;
        std::cerr << "*** Error: Aborting execution  ***" << std::endl;
        exit(1);
      }

      G4LogicalVolume* lv2 = pv2->GetLogicalVolume();
      VGM::IVolume* iv2 = Geant4GM::VolumeMap::Instance()->GetVolume(lv2);
      if (!iv2) {
        // a new logical volume has been created by G4 reflection factory
        // has to be imported into VGM
        iv2 = ImportLV(lv2, volume->MediumName());
        ImportDaughters(lv2);
        ImportPositions(lv2);
      }
      VGM::IPlacement* placement2 = new Geant4GM::Placement(iv2, miv2, pv2);
      // Register physical volume in the map
      Geant4GM::PlacementMap::Instance()->AddPlacement(placement2, pv2);
    }
  }

  // Register physical volume in the map
  Geant4GM::PlacementMap::Instance()->AddPlacement(placement1, pv1);

  return placement1;
  // should allow to return a list of placements
}

//_____________________________________________________________________________
bool Geant4GM::Factory::SwitchSolid(
  VGM::IVolume* volume, G4LogicalVolume* g4LV, G4LogicalVolume* g4MotherLV)
{
  /// Replace g4LV solid with an equivalent solid of the
  /// same type as g4Mother solid as it is required for G4PVDivision.
  /// Implemented cases:
  /// - G4Cons -> G4Polycone
  /// - G4Tubs -> G4Polycone

  if (g4LV->GetSolid()->GetEntityType() == "G4Cons" &&
      g4MotherLV->GetSolid()->GetEntityType() == "G4Polycone") {

    G4Cons* cons = static_cast<G4Cons*>(g4LV->GetSolid());
    VGM::ISolid* vgmSolid = new Geant4GM::Polycone(cons);
    dynamic_cast<Geant4GM::Volume*>(volume)->ResetSolid(vgmSolid);

    return true;
  }

  if (g4LV->GetSolid()->GetEntityType() == "G4Tubs" &&
      g4MotherLV->GetSolid()->GetEntityType() == "G4Polycone") {

    G4Tubs* tubs = static_cast<G4Tubs*>(g4LV->GetSolid());
    VGM::ISolid* vgmSolid = new Geant4GM::Polycone(tubs);
    dynamic_cast<Geant4GM::Volume*>(volume)->ResetSolid(vgmSolid);

    return true;
  }

  return false;
}

//_____________________________________________________________________________
bool Geant4GM::Factory::Import(void* topVolume)
{
  /// Import native geometry

  G4VPhysicalVolume* worldPV = static_cast<G4VPhysicalVolume*>(topVolume);

  return Import(worldPV);
}

//_____________________________________________________________________________
bool Geant4GM::Factory::ImportSolid(void* solid)
{
  /// Import native geometry

  G4VSolid* g4Solid = static_cast<G4VSolid*>(solid);

  return Import(g4Solid);
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::Register(VGM::ISolid* vgmSolid)
{
  /// Register solid in SolidStore()

  SolidStore().push_back(vgmSolid);
  return vgmSolid;
}

//
// protected functions
//

//_____________________________________________________________________________
void Geant4GM::Factory::SetSolid(VGM::ISolid* solid)
{
  /// Set solid (in single mode)

  fSolid = solid;
}

//
// public functions
//

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateArb8(
  const std::string& name, double hz, std::vector<VGM::TwoVector> vertices)
{
  //
  if (Geant4GM::Arb8::IsTwisted(vertices)) {
    std::cerr << "*** Error: Cannot create Twisted Arb8 solid in Geant4 ***"
              << std::endl;
    if (Ignore()) {
      std::cerr << "*** Warning: Using a box instead  ***" << std::endl;
      return Register(new Geant4GM::Box(name, 1., 1., 1.));
    }
    else {
      std::cerr << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
  }

  return Register(new Geant4GM::Arb8(name, hz, vertices));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateBox(
  const std::string& name, double hx, double hy, double hz)
{
  //
  return Register(new Geant4GM::Box(name, hx, hy, hz));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateCons(const std::string& name, double rin1,
  double rout1, double rin2, double rout2, double hz, double sphi, double dphi)
{
  //
  return Register(
    new Geant4GM::Cons(name, rin1, rout1, rin2, rout2, hz, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateCtubs(const std::string& name, double rin,
  double rout, double hz, double sphi, double dphi, double nxlow, double nylow,
  double nzlow, double nxhigh, double nyhigh, double nzhigh)
{
  //
  return Register(new Geant4GM::Ctubs(name, rin, rout, hz, sphi, dphi, nxlow,
    nylow, nzlow, nxhigh, nyhigh, nzhigh));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateEllipsoid(const std::string& name,
  double dx, double dy, double dz, double zBottomCut, double zTopCut)
{
  //
  return Register(
    new Geant4GM::Ellipsoid(name, dx, dy, dz, zBottomCut, zTopCut));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateEllipticalTube(
  const std::string& name, double dx, double dy, double hz)
{
  //
  return Register(new Geant4GM::EllipticalTube(name, dx, dy, hz));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateHype(const std::string& name, double r1,
  double r2, double stereo1, double stereo2, double hz)
{
  //
  return Register(new Geant4GM::Hype(name, r1, r2, stereo1, stereo2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreatePara(const std::string& name, double dx,
  double dy, double dz, double alpha, double theta, double phi)
{
  //
  return Register(new Geant4GM::Para(name, dx, dy, dz, alpha, theta, phi));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateParaboloid(
  const std::string& name, double r1, double r2, double hz)
{
  //
  return Register(new Geant4GM::Paraboloid(name, r1, r2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreatePolycone(const std::string& name,
  double sphi, double dphi, int nofZplanes, double* z, double* rin,
  double* rout)
{
  //
  return Register(
    new Geant4GM::Polycone(name, sphi, dphi, nofZplanes, z, rin, rout));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreatePolyhedra(const std::string& name,
  double sphi, double dphi, int nofSides, int nofZplanes, double* z,
  double* rin, double* rout)
{
  //
  return Register(new Geant4GM::Polyhedra(
    name, sphi, dphi, nofSides, nofZplanes, z, rin, rout));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateSphere(const std::string& name,
  double rin, double rout, double sphi, double dphi, double stheta,
  double dtheta)
{
  //
  return Register(
    new Geant4GM::Sphere(name, rin, rout, sphi, dphi, stheta, dtheta));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateTessellatedSolid(
  const std::string& name, std::vector<std::vector<VGM::ThreeVector> > facets)
{
  //
  return Register(new Geant4GM::TessellatedSolid(name, facets));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateTorus(const std::string& name, double rin,
  double rout, double rax, double sphi, double dphi)
{
  //
  return Register(new Geant4GM::Torus(name, rin, rout, rax, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateTrap(const std::string& name, double hz,
  double theta, double phi, double dy1, double dx1, double dx2, double alpha1,
  double dy2, double dx3, double dx4, double alpha2)
{
  //
  return Register(new Geant4GM::Trap(
    name, hz, theta, phi, dy1, dx1, dx2, alpha1, dy2, dx3, dx4, alpha2));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateTrd(const std::string& name, double hx1,
  double hx2, double hy1, double hy2, double hz)
{
  //
  return Register(new Geant4GM::Trd(name, hx1, hx2, hy1, hy2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateTubs(const std::string& name, double rin,
  double rout, double hz, double sphi, double dphi)
{
  //
  return Register(new Geant4GM::Tubs(name, rin, rout, hz, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateExtrudedSolid(const std::string& name,
  std::vector<VGM::TwoVector> polygon,
  std::vector<std::vector<double> > zsections)
{
  //
  return Register(new Geant4GM::ExtrudedSolid(name, polygon, zsections));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateIntersectionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //
  if (ClhepVGM::HasReflection(transform)) {
    std::cerr << "    Geant4GM::Factory::CreateIntersectionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return Register(new Geant4GM::BooleanSolid(name, VGM::kIntersection, solidA,
    solidB, new CLHEP::HepRotation(ClhepVGM::Rotation(transform).inverse()),
    ClhepVGM::Translation(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateSubtractionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //

  if (ClhepVGM::HasReflection(transform)) {
    std::cerr << "    Geant4GM::Factory::CreateSubtractionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return Register(new Geant4GM::BooleanSolid(name, VGM::kSubtraction, solidA,
    solidB, new CLHEP::HepRotation(ClhepVGM::Rotation(transform).inverse()),
    ClhepVGM::Translation(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateUnionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //
  if (ClhepVGM::HasReflection(transform)) {
    std::cerr << "    Geant4GM::Factory::CreateUnionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return Register(new Geant4GM::BooleanSolid(name, VGM::kUnion, solidA, solidB,
    new CLHEP::HepRotation(ClhepVGM::Rotation(transform).inverse()),
    ClhepVGM::Translation(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateDisplacedSolid(
  const std::string& name, VGM::ISolid* solid, const VGM::Transform& transform)
{
  //
  if (ClhepVGM::HasReflection(transform)) {
    std::cerr << "    Geant4GM::Factory::CreateDisplacedSolid:" << std::endl;
    std::cerr << "    Reflection in Displaced solid not supported in Geant4."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return Register(new Geant4GM::DisplacedSolid(name, solid,
    new CLHEP::HepRotation(ClhepVGM::Rotation(transform).inverse()),
    ClhepVGM::Translation(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateScaledSolid(
  const std::string& name, VGM::ISolid* solid, const VGM::Transform& transform)
{
  //
  if (ClhepVGM::HasReflection(transform)) {
    std::cerr << "    Geant4GM::Factory::CreateDisplacedSolid:" << std::endl;
    std::cerr << "    Reflection in ScaledSolid solid not supported in Geant4."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return Register(
    new Geant4GM::ScaledSolid(name, solid, ClhepVGM::Scale(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::CreateMultiUnion(const std::string& name,
  std::vector<VGM::ISolid*> constituents,
  std::vector<VGM::Transform> transforms)
{
  //
  std::vector<G4Transform3D> g4Transforms;
  for (auto transform : transforms) {
    if (ClhepVGM::HasReflection(transform)) {
      std::cerr << "    Geant4GM::Factory::CreateMultiUnion:" << std::endl;
      std::cerr
        << "    Reflection in MultiUnion solid is not supported in Geant4."
        << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
    g4Transforms.push_back(ClhepVGM::Transform(transform));
  }

  return Register(new Geant4GM::MultiUnion(name, constituents, g4Transforms));
}

//_____________________________________________________________________________
VGM::IVolume* Geant4GM::Factory::CreateVolume(
  const std::string& name, VGM::ISolid* solid, const std::string& mediumName)
{
  //
  // Get material name from medium
  const VGM::IMedium* medium = MaterialFactory()->Medium(mediumName);
  if (!medium) {
    std::cerr << "Geant4GM::Factory::CreateVolume: " << std::endl;
    std::cerr << "   Medium " << mediumName << " not found." << std::endl;
    exit(1);
  }
  const VGM::IMaterial* material = medium->Material();
  if (!material) {
    std::cerr << "Geant4GM::Factory::CreateVolume: " << std::endl;
    std::cerr << "   No material is defined for medium " << mediumName
              << std::endl;
    exit(1);
  }
  std::string materialName = material->Name();

  VGM::IVolume* volume =
    new Geant4GM::Volume(name, solid, materialName, mediumName);

  VolumeStore().push_back(volume);
  return volume;
}

//_____________________________________________________________________________
VGM::IPlacement* Geant4GM::Factory::CreatePlacement(const std::string& name,
  int copyNo, VGM::IVolume* volume, VGM::IVolume* motherVolume,
  const VGM::Transform& transform)
{
  //
  /*
    if (!ClhepVGM::HasReflection(transform)) {
      return CreateSimplePlacement(name, copyNo, volume, motherVolume,
    transform);
    }
  */
  // Get logical volumes from the volumes map
  G4LogicalVolume* g4LV = Geant4GM::VolumeMap::Instance()->GetVolume(volume);

  G4LogicalVolume* g4MotherLV =
    Geant4GM::VolumeMap::Instance()->GetVolume(motherVolume);

  // Create PV placement
  // for a general transformation we have to use G4 reflection factory
  G4ReflectionFactory* g4ReflectionFactory = G4ReflectionFactory::Instance();

  G4PhysicalVolumesPair pvPair =
    g4ReflectionFactory->Place(ClhepVGM::Transform(transform), name, g4LV,
      g4MotherLV, false, copyNo, fgSurfCheck);

  // Import volumes created via G4 reflection factory
  VGM::IPlacement* placement1 = ImportPVPair(volume, motherVolume, pvPair);

  // Top volume
  if (!motherVolume) {
    if (!fTop)
      fTop = placement1;
    else {
      std::cerr << "    Geant4GM::Factory::CreatePlacement:" << std::endl;
      std::cerr << "    Top volume defined twice!" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
  }

  return placement1;
  // should allow to return a list of placements
}

//_____________________________________________________________________________
VGM::IPlacement* Geant4GM::Factory::CreateMultiplePlacement(
  const std::string& name, VGM::IVolume* volume, VGM::IVolume* motherVolume,
  VGM::Axis axis, int nofItems, double width, double offset, double halfGap)
{
  //

  // Top volume
  if (!motherVolume) {
    std::cerr << "Geant4GM::Factory::CreateMultiplePlacement: "
              << "    Mother volume not defined!" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Get logical volumes from the volumes map
  G4LogicalVolume* g4LV = Geant4GM::VolumeMap::Instance()->GetVolume(volume);

  G4LogicalVolume* g4MotherLV =
    Geant4GM::VolumeMap::Instance()->GetVolume(motherVolume);

  // Geant4 requires the same type of solid in both
  // volume and mother volume
  VGM::SolidType solidType = volume->Solid()->Type();
  VGM::SolidType motherSolidType = motherVolume->Solid()->Type();
  if (solidType != motherSolidType) {
    bool result = SwitchSolid(volume, g4LV, g4MotherLV);
    if (!result) {
      std::cerr << "    Geant4GM::Factory::CreateMultiplePlacement: "
                << std::endl
                << "    Different solid types in volume and mother!"
                << std::endl
                << "    volume: " << volume->Name() << "  "
                << VGM::SolidTypeName(solidType)
                << " mother: " << motherVolume->Name() << "  "
                << VGM::SolidTypeName(motherSolidType) << std::endl
                << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
  }

  // Apply units
  width /= ClhepVGM::Units::AxisUnit(axis);
  offset /= ClhepVGM::Units::AxisUnit(axis);

  // Update offset if it goes beyond mother dhi
  if (axis == VGM::kPhi && offset + nofItems * width > 2 * CLHEP::pi)
    offset = offset - 2 * CLHEP::pi;

  // The instance of G4PVDivisionFactory must exist
  G4PVDivisionFactory::GetInstance();

  // The halfGap is not yet supported by G4ReflectionFactory
  G4PhysicalVolumesPair pvPair;
  if (halfGap != 0.) {
    G4VPhysicalVolume* replicatedSlice =
      new G4ReplicatedSlice(name, g4LV, g4MotherLV,
        Geant4GM::Placement::GetAxis(axis), nofItems, width, halfGap, offset);
    pvPair.first = replicatedSlice;
    pvPair.second = 0;
  }
  else {
    // Create PV division
    // for a general transformation we have to use G4 reflection factory
    G4ReflectionFactory* g4ReflectionFactory = G4ReflectionFactory::Instance();

    // G4PhysicalVolumesPair pvPair
    pvPair = g4ReflectionFactory->Divide(name, g4LV, g4MotherLV,
      Geant4GM::Placement::GetAxis(axis), nofItems, width, offset);
  }

  // Import volumes created via G4 reflection factory
  VGM::IPlacement* placement1 = ImportPVPair(volume, motherVolume, pvPair);

  return placement1;
  // should allow to return a list of placements
}

//_____________________________________________________________________________
VGM::IPlacement* Geant4GM::Factory::Top() const
{
  /// Return the top volume (VGM placement)

  return fTop;
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::Factory::SingleSolid() const
{
  /// Returns the solid (if in one solid conversion mode)

  return fSolid;
}

//_____________________________________________________________________________
G4VPhysicalVolume* Geant4GM::Factory::World() const
{
  /// Return the world volume (G4 physical volume)

  return Geant4GM::PlacementMap::Instance()->GetPlacement(fTop);
}

//_____________________________________________________________________________
G4VSolid* Geant4GM::Factory::Solid() const
{
  /// Returns the solid (if in one solid conversion mode)

  return Geant4GM::SolidMap::Instance()->GetSolid(fSolid);
}

//_____________________________________________________________________________
bool Geant4GM::Factory::Import(G4VPhysicalVolume* worldPV)
{
  /// Import Geant4 native geometry

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import started ...";
    if (Debug() > 1) std::cout << worldPV;
    std::cout << std::endl;
  }

  // Inactivate single mode (if it was switch previously)
  //
  SetSingleMode(false);

  // Import materials
  //
  MaterialFactory()->Import();

  // Get logical volume
  G4LogicalVolume* worldLV = worldPV->GetLogicalVolume();

  // Import the top volume
  VGM::IVolume* worldVolume = ImportLV(worldLV);

  // Import recursively all daughters
  ImportDaughters(worldLV);

  // Import positions
  ImportPositions();

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << std::endl;
    PrintSolids();
    PrintVolumes();
    if (Debug() > 1) Geant4GM::VolumeMap::Instance()->Print();
  }

  // Position the top volume
  fTop = new Geant4GM::Placement(worldVolume, 0, worldPV);

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import finished." << std::endl;
  }

  return true;
}

//_____________________________________________________________________________
bool Geant4GM::Factory::Import(G4VSolid* solid)
{
  /// Import one Geant4 solid.
  /// This call automatically activates a special single mode

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import of one solid started ...";
    if (Debug() > 1) std::cout << solid;
    std::cout << std::endl;
  }

  // Clear solid store
  // (Do not delete objects as they are also referenced in a singleton mao)
  SolidStore().clear();

  // Activate single mode
  //
  SetSingleMode(true);

  // Import solid
  fSolid = ImportSolid(solid);

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import of one solid finished."
              << std::endl;
  }

  return (fSolid != 0);
}
