// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
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

#include "RootGM/common/axis.h"
#include "RootGM/common/transform.h"
#include "RootGM/materials/MaterialFactory.h"
#include "RootGM/solids/Arb8.h"
#include "RootGM/solids/BooleanSolid.h"
#include "RootGM/solids/Box.h"
#include "RootGM/solids/Cons.h"
#include "RootGM/solids/Ctubs.h"
#include "RootGM/solids/DisplacedSolid.h"
#include "RootGM/solids/Ellipsoid.h"
#include "RootGM/solids/EllipticalTube.h"
#include "RootGM/solids/ExtrudedSolid.h"
#include "RootGM/solids/Hype.h"
#include "RootGM/solids/Para.h"
#include "RootGM/solids/Paraboloid.h"
#include "RootGM/solids/Polycone.h"
#include "RootGM/solids/Polyhedra.h"
#include "RootGM/solids/ScaledSolid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/solids/Sphere.h"
#include "RootGM/solids/Torus.h"
#include "RootGM/solids/Trap.h"
#include "RootGM/solids/Trd.h"
#include "RootGM/solids/Tubs.h"
#include "RootGM/volumes/Factory.h"
#include "RootGM/volumes/Placement.h"
#include "RootGM/volumes/PlacementMap.h"
#include "RootGM/volumes/Volume.h"
#include "RootGM/volumes/VolumeMap.h"

#include "TGeoArb8.h"
#include "TGeoCompositeShape.h"
#include "TGeoCone.h"
#include "TGeoEltu.h"
#include "TGeoHalfSpace.h"
#include "TGeoHype.h"
#include "TGeoManager.h"
#include "TGeoPara.h"
#include "TGeoParaboloid.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoScaledShape.h"
#include "TGeoShape.h"
#include "TGeoShapeAssembly.h"
#include "TGeoSphere.h"
#include "TGeoTorus.h"
#include "TGeoTrd1.h"
#include "TGeoTrd2.h"
#include "TGeoVolume.h"
#include "TGeoXtru.h"
#include "TObjArray.h"

#include <algorithm>

//_____________________________________________________________________________
RootGM::Factory::Factory()
  : VGM::IFactory(),
    BaseVGM::VFactory("Root_GM_Factory", new RootGM::MaterialFactory()),
    fTop(0),
    fSolid(0)
{
  /// Standard default constructor

  if (!gGeoManager) new TGeoManager("VGM Root geometry", "VGM Root geometry");
}

//_____________________________________________________________________________
RootGM::Factory::Factory(const Factory& rhs)
  : VGM::IFactory(rhs), BaseVGM::VFactory(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Factory::~Factory()
{
  //

  // delete map singletons
  delete RootGM::SolidMap::Instance();
  delete RootGM::VolumeMap::Instance();
  delete RootGM::PlacementMap::Instance();
  // There is inconsistence in using the singleton maps
  // via a factory which is not a singleton
  // TO DO: to be improved later
}

//
// private functions
//

//_____________________________________________________________________________
void RootGM::Factory::ImportConstituentSolid(
  int index, TGeoCompositeShape* solid)
{
  /// Import constituents of Root Boolean solid into VGM

  TGeoShape* consSolid =
    RootGM::BooleanSolid::GetConstituentSolid(index, solid);

  if (!RootGM::SolidMap::Instance()->GetSolid(consSolid)) {
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
VGM::ISolid* RootGM::Factory::ImportSolid(TGeoShape* shape)
{
  /// Convert TGeo shape into VGM solid

  // Do not import the same solid twice
  //
  VGM::ISolid* importedSolid = RootGM::SolidMap::Instance()->GetSolid(shape);
  if (importedSolid) return importedSolid;

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing shape: ";
    if (Debug() > 1) std::cout << shape << "  ";
    std::cout << shape->GetName() << std::endl;
  }

  TGeoBBox* box = dynamic_cast<TGeoBBox*>(shape);
  if (box && std::string(shape->ClassName()) == std::string("TGeoBBox")) {

    // Import box if it has not offset defined
    const Double_t* origin = box->GetOrigin();
    if (!origin || (origin[0] == 0.0 && origin[1] == 0.0 && origin[2] == 0.0)) {

      // Import box itself
      return Register(new RootGM::Box(box));
    }

    // Import box with offset via displaced solid
    return Register(new RootGM::DisplacedSolid(box));
  }

  TGeoConeSeg* cons = dynamic_cast<TGeoConeSeg*>(shape);
  if (cons) {
    return Register(new RootGM::Cons(cons));
  }

  TGeoEltu* eltu = dynamic_cast<TGeoEltu*>(shape);
  if (eltu) {
    return Register(new RootGM::EllipticalTube(eltu));
  }

  TGeoCone* cone = dynamic_cast<TGeoCone*>(shape);
  if (cone) {
    return Register(new RootGM::Cons(cone));
  }

  TGeoHalfSpace* halfSpace = dynamic_cast<TGeoHalfSpace*>(shape);
  if (halfSpace) {
    return Register(new RootGM::DisplacedSolid(halfSpace));
  }

  TGeoHype* hype = dynamic_cast<TGeoHype*>(shape);
  if (hype) {
    return Register(new RootGM::Hype(hype));
  }

  TGeoPara* para = dynamic_cast<TGeoPara*>(shape);
  if (para) {
    return Register(new RootGM::Para(para));
  }

  TGeoParaboloid* paraboloid = dynamic_cast<TGeoParaboloid*>(shape);
  if (paraboloid) {
    return Register(new RootGM::Paraboloid(paraboloid));
  }

  TGeoPgon* polyhedra = dynamic_cast<TGeoPgon*>(shape);
  if (polyhedra) {
    return Register(new RootGM::Polyhedra(polyhedra));
  }

  TGeoPcon* polycone = dynamic_cast<TGeoPcon*>(shape);
  if (polycone) {
    return Register(new RootGM::Polycone(polycone));
  }

  TGeoSphere* sphere = dynamic_cast<TGeoSphere*>(shape);
  if (sphere) {
    return Register(new RootGM::Sphere(sphere));
  }

  TGeoTorus* torus = dynamic_cast<TGeoTorus*>(shape);
  if (torus) {
    return Register(new RootGM::Torus(torus));
  }

  TGeoTrap* trap = dynamic_cast<TGeoTrap*>(shape);
  if (trap) {
    return Register(new RootGM::Trap(trap));
  }

  TGeoTrd1* trd1 = dynamic_cast<TGeoTrd1*>(shape);
  if (trd1) {
    return Register(new RootGM::Trd(trd1));
  }

  TGeoTrd2* trd2 = dynamic_cast<TGeoTrd2*>(shape);
  if (trd2) {
    return Register(new RootGM::Trd(trd2));
  }

  TGeoArb8* arb8 = dynamic_cast<TGeoArb8*>(shape);
  if (arb8) {
    return Register(new RootGM::Arb8(arb8));
  }

  TGeoCtub* ctubs = dynamic_cast<TGeoCtub*>(shape);
  if (ctubs) {
    return Register(new RootGM::Ctubs(ctubs));
  }

  TGeoTubeSeg* tubs = dynamic_cast<TGeoTubeSeg*>(shape);
  if (tubs) {
    return Register(new RootGM::Tubs(tubs));
  }

  TGeoTube* tube = dynamic_cast<TGeoTube*>(shape);
  if (tube) {
    return Register(new RootGM::Tubs(tube));
  }

  TGeoXtru* xtru = dynamic_cast<TGeoXtru*>(shape);
  if (xtru) {
    return Register(new RootGM::ExtrudedSolid(xtru));
  }

  TGeoShapeAssembly* assembly = dynamic_cast<TGeoShapeAssembly*>(shape);
  if (assembly) {
    return 0;
  }

  TGeoScaledShape* scaled = dynamic_cast<TGeoScaledShape*>(shape);
  if (scaled) {
    ImportSolid(scaled->GetShape());
    return Register(new RootGM::ScaledSolid(scaled));
  }

  TGeoCompositeShape* composite = dynamic_cast<TGeoCompositeShape*>(shape);
  if (composite) {
    ImportConstituentSolid(0, composite);
    ImportConstituentSolid(1, composite);
    VGM::IBooleanSolid* vgmBoolean = new RootGM::BooleanSolid(composite);
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

  std::cerr << "    RootGM::Factory::ImportSolid: " << std::endl;
  std::cerr << "    Unsupported solid type (solid \"" << shape->GetName()
            << "\""
            << "   type \"" << shape->ClassName() << "\")" << std::endl;

  if (Ignore()) {
    std::cerr << "*** Warning: Using a box instead  ***" << std::endl;
    return Register(new RootGM::Box(shape->GetName(), 1., 1., 1.));
  }
  else {
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
VGM::IVolume* RootGM::Factory::ImportVolume(TGeoVolume* rootVolume)
{
  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "Importing volume: " << rootVolume->GetName() << std::endl;
  }

  // Import solid
  VGM::ISolid* solid = ImportSolid(rootVolume->GetShape());

  if (Debug()) {
    BaseVGM::DebugInfo();
    if (solid)
      std::cout << "   Imported solid: " << *solid << std::endl;
    else
      std::cout << "   Imported solid: "
                << "0x0" << std::endl;
  }

  // Do not import assembly volumes
  if (dynamic_cast<TGeoVolumeAssembly*>(rootVolume)) return 0;

  // Create vgm volume
  VGM::IVolume* volume = new RootGM::Volume(solid, rootVolume);
  VolumeStore().push_back(volume);
  return volume;
}

//_____________________________________________________________________________
void RootGM::Factory::ImportDaughters(TGeoVolume* rootVolume)
{
  /// Imports recursively all daughters volumes

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "ImportDaughters for " << rootVolume->GetName() << std::endl;
  }

  for (int i = 0; i < rootVolume->GetNdaughters(); i++) {

    TGeoVolume* rootDVolume = rootVolume->GetNode(i)->GetVolume();

    VGM::IVolume* dVolume =
      RootGM::VolumeMap::Instance()->GetVolume(rootDVolume);

    if (!dVolume) {
      // Import logical volume
      dVolume = ImportVolume(rootDVolume);

      // Process its daughters
      ImportDaughters(rootDVolume);
    }
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportAssembly(const TGeoVolume* rootVolume,
  VGM::IVolume* volume, const TGeoNode* rootAssemblyNode,
  std::vector<const TGeoNode*>& assemblyNodes)
{
  /// Import an assembly daughter of the rootVolume. \n Called recursively if
  /// the daughter of assembly is again assembly.

  TGeoVolume* rootAssemblyVolume = rootAssemblyNode->GetVolume();

  if (!rootAssemblyVolume->IsAssembly()) return;

  assemblyNodes.push_back(rootAssemblyNode);

  for (int i = 0; i < rootAssemblyVolume->GetNdaughters(); i++) {

    TGeoNode* dNode = rootAssemblyVolume->GetNode(i);
    TGeoVolume* dRootVolume = dNode->GetVolume();

    if (!dRootVolume->IsAssembly()) {
      VGM::IVolume* dVolume =
        RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);

      if (Debug() > 0) {
        BaseVGM::DebugInfo();
        std::cout << "   " << i << "th assembly daughter  rtVol = ";
        if (Debug() > 1) std::cout << dRootVolume << "  ";
        std::cout << dRootVolume->GetName() << " vgmVol = ";
        if (Debug() > 1) std::cout << dVolume << "  ";
        std::cout << dVolume->Name() << std::endl;
      }
      // Create placement
      new RootGM::Placement(dVolume, volume, dNode, assemblyNodes);
    }
    else {
      std::vector<const TGeoNode*> assemblyNodes2(assemblyNodes.size());
      copy(assemblyNodes.begin(), assemblyNodes.end(), assemblyNodes2.begin());

      ImportAssembly(rootVolume, volume, dNode, assemblyNodes2);
    }
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportPlacements(
  const TGeoVolume* rootVolume, VGM::IVolume* volume)
{
  /// Build Root geometry for the daughters of the specified volume

  for (int i = 0; i < rootVolume->GetNdaughters(); i++) {

    TGeoNode* dNode = rootVolume->GetNode(i);
    TGeoVolume* dRootVolume = dNode->GetVolume();

    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << "   " << i << "th daughter  rtNode = ";
      if (Debug() > 1) std::cout << dNode << "  ";
      std::cout << dNode->GetName() << "  rtVol = ";
      if (Debug() > 1) std::cout << dRootVolume << "  ";
      std::cout << dRootVolume->GetName();
    }

    if (!dRootVolume->IsAssembly()) {

      VGM::IVolume* dVolume =
        RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);

      // Create placement
      VGM::IPlacement* dPlacement =
        new RootGM::Placement(dVolume, volume, dNode);

      if (Debug() > 0) {
        std::cout << " vgmPl = ";
        if (Debug() > 1) std::cout << dPlacement << "  ";
        std::cout << dPlacement->Name() << " vgmVol = ";
        if (Debug() > 1) std::cout << dVolume << "  ";
        std::cout << dVolume->Name() << std::endl;
      }
    }
    else {
      std::vector<const TGeoNode*> assemblyNodes;
      ImportAssembly(rootVolume, volume, dNode, assemblyNodes);
    }
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportDivision(
  const TGeoVolume* rootVolume, VGM::IVolume* volume)
{
  /// Import division

  // Get  pattern finder
  TGeoPatternFinder* finderNonConst = rootVolume->GetFinder();

  // Get the first division volume
  TGeoNode* dNode = finderNonConst->GetNodeOffset(0);
  TGeoVolume* dRootVolume = dNode->GetVolume();
  VGM::IVolume* dVolume = RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "   "
              << "0th daughter (division) rtNode = ";
    if (Debug() > 1) std::cout << dNode << "  ";
    std::cout << dNode->GetName() << "  rtVol = ";
    if (Debug() > 1) std::cout << dRootVolume << "  ";
    std::cout << dRootVolume->GetName();
  }

  // Create placement
  VGM::IPlacement* placement = new RootGM::Placement(dVolume, volume, dNode);

  if (Debug() > 0) {
    std::cout << " vgmPl = ";
    if (Debug() > 1) std::cout << placement << "  ";
    std::cout << placement->Name() << " vgmVol = ";
    if (Debug() > 1) std::cout << volume << "  ";
    std::cout << volume->Name() << std::endl;
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportPositions()
{
  /// Imports placements for all volumes imported

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Import positions: " << std::endl;
  }

  TObjArray* rootVolumes = gGeoManager->GetListOfVolumes();

  for (int i = 0; i < rootVolumes->GetEntriesFast(); i++) {

    TGeoVolume* rootVolume = (TGeoVolume*)rootVolumes->At(i);
    if (rootVolume->IsAssembly()) continue;

    VGM::IVolume* volume = RootGM::VolumeMap::Instance()->GetVolume(rootVolume);

    if (!volume) continue;
    // There may be defined volumes which are placed
    // or not placed withing this top volume
    // Hence they were not imported and we skip them

    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << i << "th volume: " << rootVolume->GetName() << "  ";
      if (Debug() > 1)
        std::cout << "   rt : " << rootVolume << "  "
                  << "  vgm: " << volume;
      std::cout << std::endl;
    }

    if (IsDivided(rootVolume))
      ImportDivision(rootVolume, volume);
    else
      ImportPlacements(rootVolume, volume);
  }
}

//_____________________________________________________________________________
bool RootGM::Factory::Import(void* topNode)
{
  //
  TGeoNode* rootNode = static_cast<TGeoNode*>(topNode);

  return Import(rootNode);
}

//_____________________________________________________________________________
bool RootGM::Factory::ImportSolid(void* solid)
{
  //
  TGeoShape* rootSolid = static_cast<TGeoShape*>(solid);

  return Import(rootSolid);
}

//_____________________________________________________________________________
bool RootGM::Factory::IsDivided(const TGeoVolume* volume) const
{
  /// Returns true if the volume is divided
  /// and division is known to VGM.

  // Check if division is present
  const TGeoPatternFinder* finder = volume->GetFinder();
  if (!finder) return false;

  // Get division axis
  VGM::Axis axis = Axis(finder);
  if (axis == VGM::kUnknownAxis) return false;

  // Volume can be processed as VGM division
  return true;
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::Register(VGM::ISolid* vgmSolid)
{
  /// Register solid in  SolidStore()

  SolidStore().push_back(vgmSolid);
  return vgmSolid;
}

//_____________________________________________________________________________
void RootGM::Factory::EmulateReplicatedSlice(const std::string& name,
  VGM::IVolume* volume, VGM::IVolume* motherVolume, VGM::Axis axis,
  int nofItems, double width, double offset, double halfGap)
{
  // Only box shape is supported
  if (motherVolume->Solid()->Type() != VGM::kBox) {
    std::cerr << "    RootGM::Factory:::EmulateReplicatedSlice " << std::endl;
    std::cerr << "    Unsupported solid type \""
              << VGM::SolidTypeName(motherVolume->Solid()->Type()) << "\", "
              << "mother volume: \"" << motherVolume->Name() << "\""
              << std::endl;
    return;
  }

  // Compute slice dimensions
  VGM::IBox* motherBox = dynamic_cast<VGM::IBox*>(motherVolume->Solid());
  double hx = motherBox->XHalfLength();
  double hy = motherBox->YHalfLength();
  double hz = motherBox->ZHalfLength();

  if (axis == VGM::kXAxis) {
    hx = (width - 2. * halfGap) / 2.;
  }
  else if (axis == VGM::kYAxis) {
    hy = (width - 2. * halfGap) / 2.;
  }
  else if (axis == VGM::kZAxis) {
    hz = (width - 2. * halfGap) / 2.;
  }

  // Create the cell solid
  // (Should not be needed if the slice solid is correct- check)
  VGM::IBox* sliceBox = dynamic_cast<VGM::IBox*>(volume->Solid());
  VGM::IVolume* sliceVolume = volume;

  // Check dimensions
  if (sliceBox->XHalfLength() != hx || sliceBox->YHalfLength() != hy ||
      sliceBox->ZHalfLength() != hz) {
    std::cerr << "    RootGM::Factory:::EmulateReplicatedSlice " << std::endl;
    std::cerr << "    Slice solid dimensions do not respect multiple placement "
                 "parameters."
              << std::endl;
    std::cerr << "    Solid dimensions: " << sliceBox->XHalfLength() << ","
              << sliceBox->YHalfLength() << "," << sliceBox->ZHalfLength()
              << "," << std::endl;
    std::cerr << "    Expected: " << hx << "," << hy << "," << hz << ","
              << std::endl;
    std::cerr << "    New solid and volume will be created." << std::endl;

    VGM::ISolid* newSolid = CreateBox(volume->Solid()->Name(), hx, hy, hz);
    sliceVolume = CreateVolume(volume->Name(), newSolid, volume->MediumName());
  }

  if (BestMatch()) {
    // Compute start position and its delta for a=each copy
    std::vector<double> start = { 0., 0., 0. };
    std::vector<double> delta = { 0., 0., 0. };

    if (axis == VGM::kXAxis) {
      delta[0] = width;
      start[0] = -motherBox->XHalfLength() + offset + width / 2.;
    }
    else if (axis == VGM::kYAxis) {
      delta[1] = width;
      start[1] = -motherBox->YHalfLength() + offset + width / 2.;
    }
    else if (axis == VGM::kZAxis) {
      delta[2] = width;
      start[2] = -motherBox->ZHalfLength() + offset + width / 2.;
    }

    // Place the slice multiple times
    for (int i = 0; i < nofItems; ++i) {
      // Define trasformation
      std::cout << i << "th position: " << start[0] + i * delta[0] << ",";
      std::cout << start[1] + i * delta[1] << ",";
      std::cout << start[2] + i * delta[2] << std::endl;

      VGM::Transform transform = { start[0] + i * delta[0],
        start[1] + i * delta[1], start[2] + i * delta[2], 0., 0., 0., 0. };

      CreatePlacement(name, i, sliceVolume, motherVolume, transform);
    }
  }
  else {
    // Create an interim volume (envelope) by division and place the slice
    // inside it
    std::string nameBis = name + "bis";
    VGM::IVolume* volumeBis =
      CreateVolume(nameBis, volume->Solid(), motherVolume->MediumName());

    // Create TGeo division without gaps
    BaseVGM::VPlacement* placement = new RootGM::Placement(
      nameBis, volumeBis, motherVolume, axis, nofItems, width, offset);

    // Import divison volume
    // (The VGM::IVolume* volume is ignored)
    TGeoNode* node = RootGM::PlacementMap::Instance()->GetPlacement(placement);
    TGeoVolume* rootVolume = node->GetVolume();
    rootVolume->SetName(volumeBis->Name().data());
    (dynamic_cast<RootGM::Volume*>(volumeBis))->ResetVolume(rootVolume);

    // Place the slice volume in the created division
    VGM::Transform transform = { 0, 0, 0, 0, 0, 0, 0 };
    CreatePlacement(name, 0, sliceVolume, volumeBis, transform);
  }
}

//
// protected functions
//

//_____________________________________________________________________________
void RootGM::Factory::SetSolid(VGM::ISolid* solid)
{
  /// Set solid (in single mode)

  fSolid = solid;
}

//
// public functions
//

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateArb8(
  const std::string& name, double hz, std::vector<VGM::TwoVector> vertices)
{
  //
  return Register(new RootGM::Arb8(name, hz, vertices));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateBox(
  const std::string& name, double hx, double hy, double hz)
{
  //
  return Register(new RootGM::Box(name, hx, hy, hz));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateCons(const std::string& name, double rin1,
  double rout1, double rin2, double rout2, double hz, double sphi, double dphi)
{
  //
  return Register(
    new RootGM::Cons(name, rin1, rout1, rin2, rout2, hz, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateCtubs(const std::string& name, double rin,
  double rout, double hz, double sphi, double dphi, double nxlow, double nylow,
  double nzlow, double nxhigh, double nyhigh, double nzhigh)
{
  //
  return Register(new RootGM::Ctubs(name, rin, rout, hz, sphi, dphi, nxlow,
    nylow, nzlow, nxhigh, nyhigh, nzhigh));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateEllipsoid(const std::string& name,
  double dx, double dy, double dz, double zBottomCut, double zTopCut)
{
  //
  return Register(new RootGM::Ellipsoid(name, dx, dy, dz, zBottomCut, zTopCut));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateEllipticalTube(
  const std::string& name, double dx, double dy, double hz)
{
  //
  return Register(new RootGM::EllipticalTube(name, dx, dy, hz));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateHype(const std::string& name, double r1,
  double r2, double stereo1, double stereo2, double hz)
{
  //
  return Register(new RootGM::Hype(name, r1, r2, stereo1, stereo2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreatePara(const std::string& name, double dx,
  double dy, double dz, double alpha, double theta, double phi)
{
  //
  return Register(new RootGM::Para(name, dx, dy, dz, alpha, theta, phi));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateParaboloid(
  const std::string& name, double r1, double r2, double hz)
{
  //
  return Register(new RootGM::Paraboloid(name, r1, r2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreatePolycone(const std::string& name,
  double sphi, double dphi, int nofZplanes, double* z, double* rin,
  double* rout)
{
  //
  return Register(
    new RootGM::Polycone(name, sphi, dphi, nofZplanes, z, rin, rout));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreatePolyhedra(const std::string& name,
  double sphi, double dphi, int nofSides, int nofZplanes, double* z,
  double* rin, double* rout)
{
  //
  return Register(new RootGM::Polyhedra(
    name, sphi, dphi, nofSides, nofZplanes, z, rin, rout));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateSphere(const std::string& name, double rin,
  double rout, double sphi, double dphi, double stheta, double dtheta)
{
  //
  return Register(
    new RootGM::Sphere(name, rin, rout, sphi, dphi, stheta, dtheta));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateTessellatedSolid(const std::string& name,
  std::vector<std::vector<VGM::ThreeVector> > /*facets*/)
{
  // Not supported solid in Root

  std::cerr << "*** Error: Cannot create Tessellated solid in Root ***"
            << std::endl;
  if (Ignore()) {
    std::cerr << "*** Warning: Using a box instead  ***" << std::endl;
    std::cerr << std::endl;
    return Register(new RootGM::Box(name, 1., 1., 1.));
  }
  else {
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateTorus(const std::string& name, double rin,
  double rout, double rax, double sphi, double dphi)
{
  //
  return Register(new RootGM::Torus(name, rin, rout, rax, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateTrap(const std::string& name, double hz,
  double theta, double phi, double dy1, double dx1, double dx2, double alpha1,
  double dy2, double dx3, double dx4, double alpha2)
{
  //
  return Register(new RootGM::Trap(
    name, hz, theta, phi, dy1, dx1, dx2, alpha1, dy2, dx3, dx4, alpha2));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateTrd(const std::string& name, double hx1,
  double hx2, double hy1, double hy2, double hz)
{
  //
  return Register(new RootGM::Trd(name, hx1, hx2, hy1, hy2, hz));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateTubs(const std::string& name, double rin,
  double rout, double hz, double sphi, double dphi)
{
  //
  return Register(new RootGM::Tubs(name, rin, rout, hz, sphi, dphi));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateExtrudedSolid(const std::string& name,
  std::vector<VGM::TwoVector> polygon,
  std::vector<std::vector<double> > zsections)
{
  //
  return Register(new RootGM::ExtrudedSolid(name, polygon, zsections));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateIntersectionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //
  return Register(new RootGM::BooleanSolid(
    name, VGM::kIntersection, solidA, solidB, CreateTransform(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateSubtractionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //
  return Register(new RootGM::BooleanSolid(
    name, VGM::kSubtraction, solidA, solidB, CreateTransform(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateUnionSolid(const std::string& name,
  VGM::ISolid* solidA, VGM::ISolid* solidB, const VGM::Transform& transform)
{
  //
  return Register(new RootGM::BooleanSolid(
    name, VGM::kUnion, solidA, solidB, CreateTransform(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateDisplacedSolid(
  const std::string& name, VGM::ISolid* solid, const VGM::Transform& transform)
{
  //
  return Register(
    new RootGM::DisplacedSolid(name, solid, CreateTransform(transform)));
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::CreateScaledSolid(
  const std::string& name, VGM::ISolid* solid, const VGM::Transform& transform)
{
  //
  return Register(new RootGM::ScaledSolid(name, solid, CreateScale(transform)));
}

//_____________________________________________________________________________
VGM::IVolume* RootGM::Factory::CreateVolume(
  const std::string& name, VGM::ISolid* solid, const std::string& mediumName)
{
  //
  VGM::IVolume* volume = new RootGM::Volume(name, solid, mediumName);

  VolumeStore().push_back(volume);
  return volume;
}

//_____________________________________________________________________________
VGM::IPlacement* RootGM::Factory::CreatePlacement(const std::string& name,
  int copyNo, VGM::IVolume* volume, VGM::IVolume* motherVolume,
  const VGM::Transform& transform)
{
  //
  VGM::IPlacement* placement = new RootGM::Placement(
    name, copyNo, volume, motherVolume, CreateTransform(transform));

  // Top volume
  if (!motherVolume) {
    if (!fTop)
      fTop = placement;
    else {
      std::cerr << "    RootGM::Factory::CreatePlacement:" << std::endl;
      std::cerr << "    Top volume defided twice!" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl;
      exit(1);
    }
  }

  return placement;
}

//_____________________________________________________________________________
VGM::IPlacement* RootGM::Factory::CreateMultiplePlacement(
  const std::string& name, VGM::IVolume* volume, VGM::IVolume* motherVolume,
  VGM::Axis axis, int nofItems, double width, double offset, double halfGap)
{
  //
  // Cannot be top volume
  if (!motherVolume) {
    std::cerr << "    RootGM::Factory::CreateMultiplePlacement:" << std::endl;
    std::cerr << "    Mother volume not defined!" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  if (halfGap != 0) {
    EmulateReplicatedSlice(
      name, volume, motherVolume, axis, nofItems, width, offset, halfGap);
    return 0;
  }
  else {

    // Create TGeo division
    BaseVGM::VPlacement* placement = new RootGM::Placement(
      name, volume, motherVolume, axis, nofItems, width, offset);

    // Import divison volume
    // (The VGM::IVolume* volume is ignored)
    TGeoNode* node = RootGM::PlacementMap::Instance()->GetPlacement(placement);
    TGeoVolume* rootVolume = node->GetVolume();
    rootVolume->SetName(volume->Name().data());
    // Now we should copy old root volume daughters to this new one
    // but there is no way to do it
    // For the time being only check if it happens

    TGeoVolume* oldVolume = RootGM::VolumeMap::Instance()->GetVolume(volume);
    oldVolume->SetName("volumeNotPlacedInGeometry");
    if (oldVolume->GetNdaughters() > 0) {
      std::cerr << "*** Limitation  ***" << std::endl;
      std::cerr << "    RootGM::Factory::CreateMultiplePlacement: "
                << std::endl;
      std::cerr << "    Daughters of divided volume can be set " << std::endl
                << "    only after multiple placement definition." << std::endl
                << "    Geometry would be incomplete." << std::endl;
      exit(1);
    }

    (dynamic_cast<RootGM::Volume*>(volume))->ResetVolume(rootVolume);

    return placement;
  }
}

//_____________________________________________________________________________
VGM::IPlacement* RootGM::Factory::Top() const
{
  /// Returns the top volume (VGM placement)

  return fTop;
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::Factory::SingleSolid() const
{
  /// Returns the solid (if in one solid conversion mode)

  return fSolid;
}

//_____________________________________________________________________________
TGeoNode* RootGM::Factory::World() const
{
  /// Returns the world volume (Root node)

  return RootGM::PlacementMap::Instance()->GetPlacement(fTop);
}

//_____________________________________________________________________________
TGeoShape* RootGM::Factory::Solid() const
{
  /// Returns the solid (if in one solid conversion mode)

  return RootGM::SolidMap::Instance()->GetSolid(fSolid);
}

//_____________________________________________________________________________
bool RootGM::Factory::Import(TGeoNode* topNode)
{
  /// Import Root native geometry

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import started ...";
    if (Debug() > 1) std::cout << topNode;
    std::cout << std::endl;
  }

  // Inactivate single mode (if it was switch previously)
  //
  SetSingleMode(false);

  // Import materials
  //
  MaterialFactory()->Import();

  // Get top volume
  TGeoVolume* topVolume = topNode->GetVolume();

  // Import the top volume
  VGM::IVolume* worldVolume = ImportVolume(topVolume);

  // Import recursively all daughters
  ImportDaughters(topVolume);

  // Import positions
  ImportPositions();

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << std::endl;
    PrintSolids();
    PrintVolumes();
    if (Debug() > 1) RootGM::VolumeMap::Instance()->Print();
  }

  // Position the top volume
  fTop = new RootGM::Placement(worldVolume, 0, topNode);

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import finished." << std::endl;
  }

  return true;
}

//_____________________________________________________________________________
bool RootGM::Factory::Import(TGeoShape* shape)
{
  /// Import one Root shape.
  /// This call automatically activates a special single mode

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import of one solid started ...";
    if (Debug() > 1) std::cout << shape;
    std::cout << std::endl;
  }

  // Clear solid store
  // (Do not delete objects as they are also referenced in a singleton mao)
  SolidStore().clear();

  // Activate single mode
  //
  SetSingleMode(true);

  // Import shape
  fSolid = ImportSolid(shape);

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import of one solid finished." << std::endl;
  }

  return (fSolid != 0);
}
