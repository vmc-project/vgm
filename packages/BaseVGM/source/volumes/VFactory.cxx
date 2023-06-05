// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VFactory
// ---------------
// The interface to geometry factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/solids/IArb8.h"
#include "VGM/solids/IBooleanSolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/ICtubs.h"
#include "VGM/solids/IDisplacedSolid.h"
#include "VGM/solids/IEllipsoid.h"
#include "VGM/solids/IEllipticalTube.h"
#include "VGM/solids/IExtrudedSolid.h"
#include "VGM/solids/IHype.h"
#include "VGM/solids/IMultiUnion.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IParaboloid.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"
#include "VGM/solids/IScaledSolid.h"
#include "VGM/solids/ISolid.h"
#include "VGM/solids/ISphere.h"
#include "VGM/solids/ITessellatedSolid.h"
#include "VGM/solids/ITorus.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITubs.h"
#include "VGM/volumes/IPlacement.h"
#include "VGM/volumes/IVolume.h"

#include "BaseVGM/common/utilities.h"
#include "BaseVGM/common/version.h"
#include "BaseVGM/volumes/VFactory.h"

#include <cstdlib>

namespace {

//_____________________________________________________________________________
void PrintVersion()
{
  /// Prints the  version banner

  std::cout << std::endl
            << "============================================================="
            << std::endl
            << " Virtual Geometry Model " << std::endl
            << " Version " << VGM_RELEASE << " ( " << VGM_RELEASE_DATE << " )"
            << std::endl
            << " WWW : https://vmc-project.github.io/vgm-documentation/"
            << std::endl
            << "============================================================="
            << std::endl
            << std::endl;
}

} // namespace

//_____________________________________________________________________________
BaseVGM::VFactory::VFactory(
  const std::string& name, VGM::IMaterialFactory* materialFactory)
  : VGM::IFactory(),
    fDebug(0),
    fIgnore(false),
    fBestMatch(false),
    fSingleMode(false),
    fDummyBoxDimensions(VGM::kDefaultDummyBoxDimensions),
    fName(name),
    fSolids(),
    fVolumes(),
    fMaterialFactory(materialFactory)
{
  /// Standard constructor

  // Print version info
  static bool printVersion = true;
  if (printVersion) {
    PrintVersion();
    printVersion = false;
  }
}

//_____________________________________________________________________________
BaseVGM::VFactory::VFactory() : VGM::IFactory()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
BaseVGM::VFactory::VFactory(const VFactory& rhs) : VGM::IFactory(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VFactory::~VFactory()
{
  // Deletes all objects created by factory
  // ---

  // Delete solids
  for (unsigned int i = 0; i < fSolids.size(); i++) {
    delete fSolids[i];
  }

  // Delete volumes
  for (unsigned int j = 0; j < fVolumes.size(); j++) {
    delete fVolumes[j];
  }

  // Placements are deleted together with volumes

  // Material factory
  delete fMaterialFactory;
}

//
// private functions
//

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VFactory::ExportDisplacedSolid(
  VGM::IDisplacedSolid* solid, VGM::IFactory* factory) const

{
  // Exports specified displaced solid to given factory
  // ---

  // Export constituent solids first
  VGM::ISolid* constituentSolid =
    ExportSolid(solid->ConstituentSolid(), factory);
  // Can lead to a duplication of solids in case
  // the solid has been already exported
  // Should not harm, but will be better to be avoided

  VGM::Transform transform = solid->Displacement();

  VGM::ISolid* newSolid =
    factory->CreateDisplacedSolid(solid->Name(), constituentSolid, transform);
  return newSolid;
}

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VFactory::ExportScaledSolid(
  VGM::IScaledSolid* solid, VGM::IFactory* factory) const

{
  // Exports specific scaled solid to given factory
  // ---

  // Export constituent solids first
  VGM::ISolid* constituentSolid =
    ExportSolid(solid->ConstituentSolid(), factory);
  // Can lead to a duplication of solids in case
  // the solid has been already exported
  // Should not harm, but will be better to be avoided

  VGM::Transform transform = solid->Scale();

  VGM::ISolid* newSolid =
    factory->CreateScaledSolid(solid->Name(), constituentSolid, transform);
  return newSolid;
}

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VFactory::ExportBooleanSolid(
  VGM::IBooleanSolid* solid, VGM::IFactory* factory) const

{
  // Exports specified Boolean solid to given factory
  // ---

  // Export constituent solids first
  VGM::ISolid* solidA = ExportSolid(solid->ConstituentSolidA(), factory);
  VGM::ISolid* solidB = ExportSolid(solid->ConstituentSolidB(), factory);
  // Can lead to a duplication of solids in case
  // the solid has been already exported
  // Should not harm, but will be better to be avoided

  VGM::BooleanType boolType = solid->BoolType();
  VGM::Transform transform = solid->Displacement();

  VGM::ISolid* newSolid = 0;
  if (boolType == VGM::kIntersection) {
    newSolid = factory->CreateIntersectionSolid(
      solid->Name(), solidA, solidB, transform);
  }
  else if (boolType == VGM::kSubtraction) {
    newSolid =
      factory->CreateSubtractionSolid(solid->Name(), solidA, solidB, transform);
  }
  else if (boolType == VGM::kUnion) {
    newSolid =
      factory->CreateUnionSolid(solid->Name(), solidA, solidB, transform);
  }

  if (!newSolid) {
    std::cerr << "    BaseVGM::VFactory::ExportBooleanSolid:" << std::endl;
    std::cerr << "    Unknown Boolean type (solid \"" << solid->Name() << "\")"
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  return newSolid;
}

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VFactory::ExportMultiUnion(
  VGM::IMultiUnion* solid, VGM::IFactory* factory) const
{
  // Exports specified Boolean solid to given factory
  // ---

  // Export constituent solids first
  std::vector<VGM::ISolid*> newConstituents;
  std::vector<VGM::Transform> newTransforms;
  for (int i = 0; i < solid->NofSolids(); ++i) {
    newConstituents.push_back(ExportSolid(solid->ConstituentSolid(i), factory));
    newTransforms.push_back(solid->Transformation(i));
  }
  VGM::ISolid* newSolid =
    factory->CreateMultiUnion(solid->Name(), newConstituents, newTransforms);

  return newSolid;
}

//_____________________________________________________________________________
VGM::ISolid* BaseVGM::VFactory::ExportSolid(
  VGM::ISolid* solid, VGM::IFactory* factory) const
{
  // Exports specified solid to given factory
  // ---

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "   Exporting solid: ";
    if (Debug() > 1) std::cout << solid;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << "   " << *solid << std::endl;
  }

  VGM::SolidType solidType = solid->Type();
  if (solidType == VGM::kArb8) {
    VGM::IArb8* arb8 = dynamic_cast<VGM::IArb8*>(solid);
    std::vector<VGM::TwoVector> vertices;
    for (int i = 0; i < arb8->NofVertices(); ++i)
      vertices.push_back(arb8->Vertex(i));
    return factory->CreateArb8(arb8->Name(), arb8->ZHalfLength(), vertices);
  }
  else if (solidType == VGM::kBox) {
    VGM::IBox* box = dynamic_cast<VGM::IBox*>(solid);
    return factory->CreateBox(
      box->Name(), box->XHalfLength(), box->YHalfLength(), box->ZHalfLength());
  }
  else if (solidType == VGM::kCons) {
    VGM::ICons* cons = dynamic_cast<VGM::ICons*>(solid);
    return factory->CreateCons(cons->Name(), cons->InnerRadiusMinusZ(),
      cons->OuterRadiusMinusZ(), cons->InnerRadiusPlusZ(),
      cons->OuterRadiusPlusZ(), cons->ZHalfLength(), cons->StartPhi(),
      cons->DeltaPhi());
  }
  else if (solidType == VGM::kCtubs) {
    VGM::ICtubs* ctubs = dynamic_cast<VGM::ICtubs*>(solid);
    return factory->CreateCtubs(ctubs->Name(), ctubs->InnerRadius(),
      ctubs->OuterRadius(), ctubs->ZHalfLength(), ctubs->StartPhi(),
      ctubs->DeltaPhi(), ctubs->NxLow(), ctubs->NyLow(), ctubs->NzLow(),
      ctubs->NxHigh(), ctubs->NyHigh(), ctubs->NzHigh());
  }
  else if (solidType == VGM::kEllipsoid) {
    VGM::IEllipsoid* ellipsoid = dynamic_cast<VGM::IEllipsoid*>(solid);
    return factory->CreateEllipsoid(ellipsoid->Name(), ellipsoid->XSemiAxis(),
      ellipsoid->YSemiAxis(), ellipsoid->ZSemiAxis(), ellipsoid->ZBottomCut(),
      ellipsoid->ZTopCut());
  }
  else if (solidType == VGM::kEltu) {
    VGM::IEllipticalTube* eltu = dynamic_cast<VGM::IEllipticalTube*>(solid);
    return factory->CreateEllipticalTube(
      eltu->Name(), eltu->Dx(), eltu->Dy(), eltu->ZHalfLength());
  }
  else if (solidType == VGM::kExtruded) {
    VGM::IExtrudedSolid* xtru = dynamic_cast<VGM::IExtrudedSolid*>(solid);
    std::vector<VGM::TwoVector> polygon;
    for (int i = 0; i < xtru->NofVertices(); ++i)
      polygon.push_back(xtru->Vertex(i));
    std::vector<std::vector<double>> zsections;
    for (int i = 0; i < xtru->NofZSections(); ++i) {
      std::vector<double> zsection;
      zsection.push_back(xtru->ZPosition(i));
      zsection.push_back(xtru->Offset(i).first);
      zsection.push_back(xtru->Offset(i).second);
      zsection.push_back(xtru->Scale(i));
      zsections.push_back(zsection);
    }
    return factory->CreateExtrudedSolid(xtru->Name(), polygon, zsections);
  }
  else if (solidType == VGM::kHype) {
    VGM::IHype* hype = dynamic_cast<VGM::IHype*>(solid);
    return factory->CreateHype(hype->Name(), hype->InnerRadius(),
      hype->OuterRadius(), hype->InnerStereoAngle(), hype->OuterStereoAngle(),
      hype->ZHalfLength());
  }
  else if (solidType == VGM::kPara) {
    VGM::IPara* para = dynamic_cast<VGM::IPara*>(solid);
    return factory->CreatePara(para->Name(), para->XHalfLength(),
      para->YHalfLength(), para->ZHalfLength(), para->Alpha(), para->Theta(),
      para->Phi());
  }
  else if (solidType == VGM::kParaboloid) {
    VGM::IParaboloid* paraboloid = dynamic_cast<VGM::IParaboloid*>(solid);
    return factory->CreateParaboloid(paraboloid->Name(),
      paraboloid->RadiusMinusZ(), paraboloid->RadiusPlusZ(),
      paraboloid->ZHalfLength());
  }
  else if (solidType == VGM::kPolycone) {
    VGM::IPolycone* polycone = dynamic_cast<VGM::IPolycone*>(solid);
    return factory->CreatePolycone(polycone->Name(), polycone->StartPhi(),
      polycone->DeltaPhi(), polycone->NofZPlanes(), polycone->ZValues(),
      polycone->InnerRadiusValues(), polycone->OuterRadiusValues());
  }
  else if (solidType == VGM::kPolyhedra) {
    VGM::IPolyhedra* polyhedra = dynamic_cast<VGM::IPolyhedra*>(solid);
    return factory->CreatePolyhedra(polyhedra->Name(), polyhedra->StartPhi(),
      polyhedra->DeltaPhi(), polyhedra->NofSides(), polyhedra->NofZPlanes(),
      polyhedra->ZValues(), polyhedra->InnerRadiusValues(),
      polyhedra->OuterRadiusValues());
  }
  else if (solidType == VGM::kSphere) {
    VGM::ISphere* sphere = dynamic_cast<VGM::ISphere*>(solid);
    return factory->CreateSphere(sphere->Name(), sphere->InnerRadius(),
      sphere->OuterRadius(), sphere->StartPhi(), sphere->DeltaPhi(),
      sphere->StartTheta(), sphere->DeltaTheta());
  }
  else if (solidType == VGM::kTessellated) {
    VGM::ITessellatedSolid* tessellated =
      dynamic_cast<VGM::ITessellatedSolid*>(solid);

    std::vector<std::vector<VGM::ThreeVector>> facets;
    for (int i = 0; i < tessellated->NofFacets(); ++i) {
      std::vector<VGM::ThreeVector> facet;
      for (int j = 0; j < tessellated->NofVertices(i); ++j) {
        facet.push_back(tessellated->Vertex(i, j));
      }
      facets.push_back(facet);
    }
    return factory->CreateTessellatedSolid(tessellated->Name(), facets);
  }
  else if (solidType == VGM::kTorus) {
    VGM::ITorus* torus = dynamic_cast<VGM::ITorus*>(solid);
    return factory->CreateTorus(torus->Name(), torus->InnerRadius(),
      torus->OuterRadius(), torus->AxialRadius(), torus->StartPhi(),
      torus->DeltaPhi());
  }
  else if (solidType == VGM::kTrap) {
    VGM::ITrap* trap = dynamic_cast<VGM::ITrap*>(solid);
    return factory->CreateTrap(trap->Name(), trap->ZHalfLength(), trap->Theta(),
      trap->Phi(), trap->YHalfLengthMinusZ(), trap->XHalfLengthMinusZMinusY(),
      trap->XHalfLengthMinusZPlusY(), trap->AlphaMinusZ(),
      trap->YHalfLengthPlusZ(), trap->XHalfLengthPlusZMinusY(),
      trap->XHalfLengthPlusZPlusY(), trap->AlphaPlusZ());
  }
  else if (solidType == VGM::kTrd) {
    VGM::ITrd* trd = dynamic_cast<VGM::ITrd*>(solid);
    return factory->CreateTrd(trd->Name(), trd->XHalfLengthMinusZ(),
      trd->XHalfLengthPlusZ(), trd->YHalfLengthMinusZ(),
      trd->YHalfLengthPlusZ(), trd->ZHalfLength());
  }
  else if (solidType == VGM::kTubs) {
    VGM::ITubs* tubs = dynamic_cast<VGM::ITubs*>(solid);
    return factory->CreateTubs(tubs->Name(), tubs->InnerRadius(),
      tubs->OuterRadius(), tubs->ZHalfLength(), tubs->StartPhi(),
      tubs->DeltaPhi());
  }
  else if (solidType == VGM::kDisplaced) {
    VGM::IDisplacedSolid* displaced =
      dynamic_cast<VGM::IDisplacedSolid*>(solid);
    return ExportDisplacedSolid(displaced, factory);
  }
  else if (solidType == VGM::kScaled) {
    VGM::IScaledSolid* scaled = dynamic_cast<VGM::IScaledSolid*>(solid);
    return ExportScaledSolid(scaled, factory);
  }
  else if (solidType == VGM::kBoolean) {
    VGM::IBooleanSolid* boolean = dynamic_cast<VGM::IBooleanSolid*>(solid);
    return ExportBooleanSolid(boolean, factory);
  }
  else if (solidType == VGM::kMultiUnion) {
    VGM::IMultiUnion* multiUnion = dynamic_cast<VGM::IMultiUnion*>(solid);
    return ExportMultiUnion(multiUnion, factory);
  }

  std::cerr << "    BaseVGM::VFactory::ExportSolid:" << std::endl;
  std::cerr << "    Unknown solid type (solid \"" << solid->Name() << "\")"
            << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl;
  exit(1);
  return 0;
}

//_____________________________________________________________________________
BaseVGM::VFactory::VolumeMap* BaseVGM::VFactory::ExportVolumeStore(
  VGM::IFactory* factory) const
{
  // Exports all volumes.
  // ---

  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting volume store: " << std::endl;
  }

  VolumeMap* volumeMap = new VolumeMap();

  for (unsigned int i = 0; i < Volumes().size(); i++) {

    VGM::IVolume* volume = Volumes()[i];

    // Export solid
    VGM::ISolid* solid = ExportSolid(volume->Solid(), factory);

    // Create factory's volume
    VGM::IVolume* newVolume =
      factory->CreateVolume(volume->Name(), solid, volume->MediumName());

    // Map new volume to old volume
    (*volumeMap)[volume] = newVolume;

    // Debug info
    //
    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << "Exporting volume:  " << i << "th  \"" << volume->Name();
      std::cout << "\"  "
                << "material: \"" << volume->MaterialName() << "\"";
      if (Debug() > 1)
        std::cout << "  "
                  << " oldVGM=" << volume << " newVGM=" << newVolume;
      std::cout << std::endl;
    }
  }

  return volumeMap;
}

//_____________________________________________________________________________
VGM::IPlacement* BaseVGM::VFactory::ExportSimplePlacement(
  VGM::IPlacement* placement, VGM::IFactory* factory,
  VolumeMap* volumeMap) const
{
  // Export simple placement.
  // ---

#ifndef NEW_DEBUG
  if (Debug() > 0) {
    std::cout << "  simple placement: " << placement->Name() << std::endl;
  }
#endif

  VGM::IVolume* newVolume = (*volumeMap)[placement->Volume()];
  VGM::IVolume* newMother = (*volumeMap)[placement->Mother()];

  // If boolean or scaled solid that have to be reflected
  /// set reflection to the transformation
  VGM::Transform transform = placement->Transformation();
  VGM::IBooleanSolid* booleanSolid =
    dynamic_cast<VGM::IBooleanSolid*>(placement->Volume()->Solid());
  VGM::IScaledSolid* scaledSolid =
    dynamic_cast<VGM::IScaledSolid*>(placement->Volume()->Solid());
  if ((booleanSolid && booleanSolid->ToBeReflected()) ||
      (scaledSolid && scaledSolid->ToBeReflected())) {
    transform[VGM::kReflZ] = 1;
  }

  VGM::IPlacement* newPlacement = factory->CreatePlacement(
    placement->Name(), placement->CopyNo(), newVolume, newMother, transform);

  return newPlacement;
}

//_____________________________________________________________________________
VGM::IPlacement* BaseVGM::VFactory::ExportMultiplePlacement(
  VGM::IPlacement* placement, VGM::IFactory* factory,
  VolumeMap* volumeMap) const
{
  // Exports multiple placement.
  // ---

  VGM::IVolume* newVolume = (*volumeMap)[placement->Volume()];
  VGM::IVolume* newMother = (*volumeMap)[placement->Mother()];

  VGM::Axis axis = VGM::kUnknownAxis;
  int nofItems = 0;
  double width = 0.;
  double offset = 0.;
  double halfGap = 0.;
  placement->MultiplePlacementData(axis, nofItems, width, offset, halfGap);

#ifndef NEW_DEBUG
  if (Debug() > 0) {
    std::cout << "  multiple placement - data: " << axis << ",  " << nofItems
              << ",  " << width << ",  " << offset << ",  " << halfGap
              << std::endl;
  }
#endif

  VGM::IPlacement* newPlacement =
    factory->CreateMultiplePlacement(placement->Name(), newVolume, newMother,
      axis, nofItems, width, offset, halfGap);

  return newPlacement;
}

//_____________________________________________________________________________
VGM::IPlacement* BaseVGM::VFactory::ExportParameterisedPlacement(
  VGM::IPlacement* placement, VGM::IFactory* factory,
  VolumeMap* volumeMap) const
{
  // Exports parameterised placement.
  // ---

  // Daughters might be anywhere inside the mothers with any rotations. We
  // extract the transformations first
  std::vector<VGM::Transform> Transforms;
  placement->ParameterisedPlacementData(Transforms);

#ifndef NEW_DEBUG
  if (Debug() > 0) {
    std::cout << "  parameterised placement - transforms: " << std::endl;
    for (VGM::Transform& tr : Transforms) {
      std::cout << tr << std::endl;
    }
  }
#endif

  VGM::IVolume* newVolume = (*volumeMap)[placement->Volume()];
  VGM::IVolume* newMother = (*volumeMap)[placement->Mother()];

  // Daughters may also change solids or materials. We account for that where we
  // search for all volumes in the store now that have names associated to the
  // original volume
  std::map<int, VGM::IVolume*> newVolumes;

  // Of course we need to store the first daugther
  newVolumes.insert(std::make_pair(0, newVolume));

  std::string NameVol = newVolume->Name();
  for (auto vol : *volumeMap) {
    std::string NameHere = vol.first->Name();
    // Test if we find volume names that match the original daughter + "_x",
    // where x is indicating the first element during parameterisation that
    // should use this new volume.
    if (NameHere.find(NameVol) != std::string::npos && NameHere != NameVol) {
      // Get rid of the "_" and the original name to extract the first element
      // position that the new volume should represent
      std::string Ending = NameHere.substr(NameVol.size() + 1);
      newVolumes.insert(
        std::make_pair(std::stoi(Ending), (*volumeMap)[vol.first]));
    }
  }

#ifndef NEW_DEBUG
  if (Debug() > 0) {
    std::cout << "  parameterised placement - number of different volumes "
                 "during parameterisation: "
              << std::endl;
    for (auto& p : newVolumes) {
      std::cout << "Volume from element " << p.first << ": " << p.second->Name()
                << std::endl;
    }
  }
#endif

  return factory->CreateParameterisedPlacement(
    placement->Name(), newVolumes, newMother, Transforms);
}

//_____________________________________________________________________________
void BaseVGM::VFactory::ExportPlacements(
  VGM::IFactory* factory, VolumeMap* volumeMap) const
{
  // Exports all placements.
  // ---

#ifdef NEW_DEBUG
  if (Debug() > 0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting placements:" << std::endl;
  }
#endif

  for (unsigned int i = 0; i < Volumes().size(); i++) {

    VGM::IVolume* volume = Volumes()[i];

#ifndef NEW_DEBUG
    if (Debug() > 0) {
      BaseVGM::DebugInfo();
      std::cout << "ExportPlacements for " << i << "th volume ";
      if (Debug() > 1) std::cout << volume << "  ";
      std::cout << volume->Name() << std::endl;
    }
#endif

    for (int id = 0; id < volume->NofDaughters(); id++) {

      VGM::IPlacement* daughter = volume->Daughter(id);

#ifndef NEW_DEBUG
      if (Debug() > 0) {
        BaseVGM::DebugInfo();
        std::cout << "   " << id << "th daughter vol = ";
        if (Debug() > 1) std::cout << daughter->Volume() << "  ";
        std::cout << daughter->Volume()->Name();
      }
#endif

#ifdef NEW_DEBUG
      if (Debug() > 0) {
        BaseVGM::DebugInfo();
        std::cout << "Exporting placement: ";
        if (Debug() > 1) std::cout << daughter;
        std::cout << std::endl;
        BaseVGM::DebugInfo();
        std::cout << "   " << *daughter << std::endl;
      }
#endif

      if (daughter->Type() == VGM::kSimplePlacement) {
        ExportSimplePlacement(daughter, factory, volumeMap);
      }
      else if (daughter->Type() == VGM::kMultiplePlacement) {
        ExportMultiplePlacement(daughter, factory, volumeMap);
      }
      else if (daughter->Type() == VGM::kParameterised) {
        ExportParameterisedPlacement(daughter, factory, volumeMap);
      }
      else {
        std::cout << std::endl;
        std::cerr << "    BaseVGM::VFactory::ExportPlacements:" << std::endl;
        std::cerr << "    Unknown placement type (placement \""
                  << daughter->Name() << "\")" << std::endl;
        std::cerr << "*** Error: Aborting execution  ***" << std::endl;
        exit(1);
      }
    }
  }

  // Position the top volume
  // (top volume has no mother volume that's why it must be placed
  //  explicitely)

  VGM::IVolume* topVolume = (*volumeMap)[Top()->Volume()];

  factory->CreatePlacement(
    Top()->Name(), Top()->CopyNo(), topVolume, 0, Identity());

  delete volumeMap;
}

//_____________________________________________________________________________
VGM::Transform BaseVGM::VFactory::Identity() const
{
  //
  VGM::Transform transform(VGM::kSize);
  for (int i = 0; i < 7; i++) transform[i] = 0;

  return transform;
}

//
// public functions
//

//_____________________________________________________________________________
bool BaseVGM::VFactory::Export(VGM::IFactory* factory) const
{
  /// Export the whole geometry to the given factory.

  // set the mode to destination factory
  factory->SetSingleMode(SingleMode());

  if (!SingleMode()) {
    // Export materials
    //
    fMaterialFactory->Export(factory->MaterialFactory());

    // Export volumes
    //
    VolumeMap* volumeMap = ExportVolumeStore(factory);
    ExportPlacements(factory, volumeMap);

    return true;
  }
  else {
    // one solid mode

    // Check if a solid was created/imported
    if (!SingleSolid()) {
      std::cerr << "++ Warning: ++ " << std::endl;
      std::cerr << "   BaseVGM::Export:" << std::endl;
      std::cerr << "   A solid must be created/imported first." << std::endl;

      return false;
    }

    // Export solid
    VGM::ISolid* solid = ExportSolid(SingleSolid(), factory);
    factory->SetSolid(solid);

    return (solid != 0);
  }
}

//_____________________________________________________________________________
void BaseVGM::VFactory::PrintSolids() const
{
  // Print all solids.
  // ---

  std::cout << Name() << " factory solids store: " << std::endl;

  const VGM::SolidStore& solids = Solids();

  for (unsigned i = 0; i < solids.size(); i++) {
    std::cout << "   " << i << "th solid: " << *solids[i] << std::endl;
  }
}

//_____________________________________________________________________________
void BaseVGM::VFactory::PrintVolumes() const
{
  // Print all volumes.
  // ---

  std::cout << Name() << " factory volumes store: " << std::endl;

  const VGM::VolumeStore& volumes = Volumes();

  for (unsigned i = 0; i < volumes.size(); i++) {
    std::cout << "   " << i << "th: " << *volumes[i] << std::endl;
  }
}

//_____________________________________________________________________________
void BaseVGM::VFactory::SetDebug(int debug)
{
  // Sets debug level; the same level is set to material factory.
  // ---

  fDebug = debug;
  MaterialFactory()->SetDebug(debug);
}

//_____________________________________________________________________________
void BaseVGM::VFactory::SetIgnore(bool ignore, double dummyBoxDimensions)
{
  fIgnore = ignore;
  fDummyBoxDimensions = dummyBoxDimensions;
}
