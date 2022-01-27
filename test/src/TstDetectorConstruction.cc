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
// Class TstDetectorConstruction
// -------------------------------
// The test detector construction
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "XmlVGM/AGDDExporter.h"
#include "XmlVGM/GDMLExporter.h"

#include "TstDetectorConstruction.hh"
#include "TstGeometryViaGeant4.hh"
#include "TstGeometryViaRoot.hh"
#include "TstGeometryViaVGM.hh"

#include "G4GDMLParser.hh"
#include "G4SolidStore.hh"

const G4String TstDetectorConstruction::fgkTestNameCandidates =
  "Solids NewSolid NewSolid2 ExtraSolid Placements Placements2 Reflections "
  "Assemblies1 Assemblies2 BooleanSolids1 BooleanSolids2 BooleanSolids3 "
  "BooleanSolids4 BooleanSolids5 BooleanSolids6 BooleanSolids7 ScaledSolids "
  "Special DisplacedSolids1 DisplacedSolids2 MultiUnion Special SingleMode";
const G4String TstDetectorConstruction::fgkVisModeCandidates =
  "Geant4 Root None";
const G4String TstDetectorConstruction::fgkInputCandidates = "VGM Geant4 Root";
const G4String TstDetectorConstruction::fgkFactoryCandidates =
  "Geant4 Root None";
const G4String TstDetectorConstruction::fgkOutputXMLCandidates =
  "AGDD GDML G4GDML noXML";

//_____________________________________________________________________________
TstDetectorConstruction::TstDetectorConstruction(const G4String& inputType,
  const G4String& inputFactory, const G4String& outputFactory,
  const G4String& outputXML)
  : G4VUserDetectorConstruction(),
    fSelectedTest("Solids"),
    fSelectedVisMode("Geant4"),
    fFullAngle(true),
    fBestMatchMode(false),
    fSingleMode(false),
    fInputFactory(0),
    fOutputFactory(0),
    fGeant4Factory(0),
    fRootFactory(0),
    fXMLExporter(0),
    fG4GDMLExporter(0),
    fXMLFileName(""),
    fGeometry(0),
    fColours()
{
  //
  SelectChannels(inputType, inputFactory, outputFactory, outputXML);
  DefineColours();
}

//_____________________________________________________________________________
TstDetectorConstruction::~TstDetectorConstruction()
{
  delete fInputFactory;
  delete fOutputFactory;
  delete fGeometry;
}

//
// public methods
//

#include <TGeoManager.h>
//_____________________________________________________________________________
G4VPhysicalVolume* TstDetectorConstruction::Construct()
{
  //  Load Root geometry from a file, import it in VGM and
  //  exports it in Geant4 and in XML.
  // ---

  Geant4GM::Factory::SetSurfCheck(false);

  // Define materials first
  fGeometry->DefineMaterials();

  // Construct geometry via builder
  // using selected test
  //
  void* world = 0;
  if (fSelectedTest == "Solids") {
    world = fGeometry->TestSolids(fFullAngle);
    std::cout << "TestSolids finished" << std::endl;
  }
  else if (fSelectedTest == "NewSolid") {
    world = fGeometry->TestNewSolid();
    std::cout << "TestNewSolid finished" << std::endl;
  }
  else if (fSelectedTest == "NewSolid2") {
    world = fGeometry->TestNewSolid2();
    std::cout << "TestNewSolid2 finished" << std::endl;
  }
  else if (fSelectedTest == "ExtraSolid") {
    // world = fGeometry->TestExtraSolid(VGM::kArb8);
    world = fGeometry->TestExtraSolid(VGM::kEllipsoid);
    // world = fGeometry->TestExtraSolid(VGM::kTessellated);
    std::cout << "TestExtraSolid finished" << std::endl;
  }
  else if (fSelectedTest == "Placements") {
    world = fGeometry->TestPlacements();
    std::cout << "TestPlacements finished" << std::endl;
  }
  else if (fSelectedTest == "Placements2") {
    world = fGeometry->TestPlacements2(fBestMatchMode);
    std::cout << "TestPlacements finished" << std::endl;
  }
  else if (fSelectedTest == "Reflections") {
    world = fGeometry->TestReflections(fFullAngle);
    std::cout << "TestReflections finished" << std::endl;
  }
  else if (fSelectedTest == "Assemblies1") {
    world = fGeometry->TestAssemblies();
    std::cout << "TestAssemblies finished" << std::endl;
  }
  else if (fSelectedTest == "Assemblies2") {
    world = fGeometry->TestAssemblies2();
    std::cout << "TestAssemblies2 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids1") {
    world = fGeometry->TestBooleanSolids1();
    std::cout << "TestBooleanSolids1 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids2") {
    world = fGeometry->TestBooleanSolids2();
    std::cout << "TestBooleanSolids2 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids3") {
    world = fGeometry->TestBooleanSolids3();
    std::cout << "TestBooleanSolids3 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids4") {
    world = fGeometry->TestBooleanSolids4();
    std::cout << "TestBooleanSolids4 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids5") {
    world = fGeometry->TestBooleanSolids5();
    std::cout << "TestBooleanSolids5 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids6") {
    world = fGeometry->TestBooleanSolids6();
    std::cout << "TestBooleanSolids6 finished" << std::endl;
  }
  else if (fSelectedTest == "BooleanSolids7") {
    world = fGeometry->TestBooleanSolids7();
    std::cout << "TestBooleanSolids7 finished" << std::endl;
  }
  else if (fSelectedTest == "ScaledSolids") {
    world = fGeometry->TestScaledSolids();
    std::cout << "TestScaledSolids finished" << std::endl;
  }
  else if (fSelectedTest == "DisplacedSolids1") {
    world = fGeometry->TestDisplacedSolids1();
    std::cout << "TestDisplacedSolids1 finished" << std::endl;
  }
  else if (fSelectedTest == "DisplacedSolids2") {
    world = fGeometry->TestDisplacedSolids2();
    std::cout << "TestDisplacedSolids2 finished" << std::endl;
  }
  else if (fSelectedTest == "MultiUnion") {
    world = fGeometry->TestMultiUnion();
    std::cout << "TestMultiUnion finished" << std::endl;
  }
  else if (fSelectedTest == "Special") {
    world = fGeometry->TestSpecial();
    std::cout << "TestSpecial finished" << std::endl;
  }

  // Single mode test (does not build valid geometry)
  if (fSingleMode) {
    std::cout << "Go to Import/Export solids one by one" << std::endl;

    // Detect input/output types
    Geant4GM::Factory* g4InputFactory =
      dynamic_cast<Geant4GM::Factory*>(fInputFactory);

    RootGM::Factory* rtInputFactory =
      dynamic_cast<RootGM::Factory*>(fInputFactory);

    Geant4GM::Factory* g4OutputFactory =
      dynamic_cast<Geant4GM::Factory*>(fOutputFactory);

    RootGM::Factory* rtOutputFactory =
      dynamic_cast<RootGM::Factory*>(fOutputFactory);

    // Root -> Geant4
    if (rtInputFactory && g4OutputFactory) {
      TObjArray* solids = gGeoManager->GetListOfShapes();
      TIter next(solids);
      std::vector<TGeoShape*> solidsVector;
      while (TObject* obj = next()) {
        TGeoShape* rtSolid = (TGeoShape*)obj;
        solidsVector.push_back(rtSolid);
      }
      for (int i = 0; i < int(solidsVector.size()); i++) {
        TGeoShape* rtSolid = solidsVector[i];
        std::cout << "Processing solid " << rtSolid->GetName() << std::endl;
        rtSolid->Dump();
        rtInputFactory->Import(rtSolid);
        std::cout << "Import  of solid finished" << std::endl;
        rtInputFactory->Export(g4OutputFactory);
        G4VSolid* g4Solid = g4OutputFactory->Solid();
        std::cout << g4Solid << std::endl;
        std::cout << *g4Solid << std::endl;
        // Circular check
        // g4OutputFactory->Solid();
        // std::cout << "Export of solid finished: " << std::endl;
        // // Export back in Root
        // // this allows to check in the debug output if the new VGM solid
        // // has identical parameters as the original one
        // g4OutputFactory->Export(rtInputFactory);
        // std::cout << "Export-back of solid finished: " << std::endl;
      }
    }
    else if (g4InputFactory && rtOutputFactory) {
      G4SolidStore* solidStore = G4SolidStore::GetInstance();
      std::vector<G4VSolid*> solidsVector;
      for (int i = 0; i < int(solidStore->size()); i++) {
        G4VSolid* g4Solid = (*solidStore)[i];
        solidsVector.push_back(g4Solid);
      }
      for (int i = 0; i < int(solidsVector.size()); i++) {
        G4VSolid* g4Solid = solidsVector[i];
        std::cout << "Processing solid " << g4Solid->GetName() << std::endl;
        std::cout << *g4Solid << std::endl;
        g4InputFactory->Import(g4Solid);
        g4InputFactory->Export(rtOutputFactory);
        TGeoShape* rtSolid = rtOutputFactory->Solid();
        std::cout << rtSolid << std::endl;
        rtSolid->Dump();
        // Circular check
        // rtOutputFactory->Solid();
        // std::cout << "Export of solid finished: ";
        // // Export back in Geant4
        // // this allows to check in the debug output if the new VGM solid
        // // has identical parameters as the original one
        // rtOutputFactory->Export(g4InputFactory);
        // std::cout << "Export-back of solid finished: " << std::endl;
      }
    }
    else {
      std::cout << "Not supported input/output." << std::endl;
      exit(0);
      return 0;
    }
    std::cout << " Import/Export solids one by one finished." << std::endl;
    exit(0);
    return 0;
  }

  // Check if geometry was built
  if (!world) {
    std::cout << "No geometry is built." << std::endl;
    exit(0);
    return 0;
  }

  // If native geometry, import it into VGM
  // and export it into other factory
  //

  if (!fInputFactory->Top()) {
    std::cout << "Go to Import" << std::endl;
    // fInputFactory->Import(world);
    // Now VGM::IFactory::Import(void*) is not public
    // We have to use the concrete factory Import function

    Geant4GM::Factory* g4InputFactory =
      dynamic_cast<Geant4GM::Factory*>(fInputFactory);
    if (g4InputFactory) {
      // return static_cast<G4VPhysicalVolume*>(world);
      g4InputFactory->Import(static_cast<G4VPhysicalVolume*>(world));
    }

    RootGM::Factory* rtInputFactory =
      dynamic_cast<RootGM::Factory*>(fInputFactory);
    if (rtInputFactory) {
      G4String fileName = fSelectedTest;
      fileName += ".root";
      gGeoManager->Export(fileName);
      rtInputFactory->Import(static_cast<TGeoNode*>(world));
    }

    std::cout << "Import finished" << std::endl;
  }

  // Export geometry into other factory
  //
  if (fOutputFactory) {
    std::cout << "Go to export" << std::endl;
    fInputFactory->Export(fOutputFactory);
    std::cout << "Export finished" << std::endl;
  }

  if (fSelectedVisMode == "Geant4") SetG4VisAttributes();
  if (fSelectedVisMode == "Root") DrawRootGeometry();

  // Save Root geometry
  if (fRootFactory) {
    std::cout << "Go to save Root geometry" << std::endl;
    gGeoManager->CloseGeometry();
    SaveRootGeometry();
  }

  // Print materials
  //
  /*
    std::cout << "*** G4 materials" << std::endl;
    PrintGeant4Materials();
    std::cout << "*** Root materials" << std::endl;
    PrintRootMaterials();
    std::cout << "*** VGM materials" << std::endl;
    fInputFactory->MaterialFactory()->PrintMaterials();
  */

  // Generate XML output
  GenerateXML();

  // Return top volume
  //
  if (IsGeant4Geometry()) {
    return fGeant4Factory->World();
  }
  else {
    std::cout << "No Geant4 geometry is built." << std::endl;
    exit(0);
    return 0;
  }
}

//_____________________________________________________________________________
void TstDetectorConstruction::SelectTest(
  const G4String& testName, G4bool fullAngle)
{
  if (fgkTestNameCandidates.find(testName) == std::string::npos) {
    G4Exception("TstDetectorConstruction::SelectTest", "IllegalConstruct",
      FatalException, "Wrong testName specified.");
  }

  fSelectedTest = testName;
  fFullAngle = fullAngle;
}

//_____________________________________________________________________________
void TstDetectorConstruction::SelectVisualization(const G4String& visMode)
{
  if (fgkVisModeCandidates.find(visMode) == std::string::npos) {
    G4Exception("TstDetectorConstruction::SelectVisualization",
      "IllegalConstruct", FatalException, "Wrong visMode specified.");
  }

  fSelectedVisMode = visMode;
}

//_____________________________________________________________________________
void TstDetectorConstruction::SetDebug(G4bool debugMode)
{
  // Set debug mode to instantiated factories

  if (fInputFactory) fInputFactory->SetDebug(debugMode);
  if (fOutputFactory) fOutputFactory->SetDebug(debugMode);
}

//_____________________________________________________________________________
void TstDetectorConstruction::SetIgnore(G4bool ignoreMode)
{
  // Set debug mode to instantiated factories

  if (fInputFactory) fInputFactory->SetIgnore(ignoreMode);
  if (fOutputFactory) fOutputFactory->SetIgnore(ignoreMode);
}

//_____________________________________________________________________________
void TstDetectorConstruction::SetBestMatch(G4bool bestMatchMode)
{
  // Set debug mode to instantiated factories

  fBestMatchMode = bestMatchMode;
  if (fInputFactory) fInputFactory->SetBestMatch(bestMatchMode);
  if (fOutputFactory) {
    fOutputFactory->SetBestMatch(bestMatchMode);
  }
}

//_____________________________________________________________________________
void TstDetectorConstruction::SetSingleMode(G4bool singleMode)
{
  // Set single mode option

  fSingleMode = singleMode;
}

//
// private methods
//

//_____________________________________________________________________________
bool TstDetectorConstruction::IsGeant4Geometry() const
{
  return fGeant4Factory != 0;
}

//_____________________________________________________________________________
bool TstDetectorConstruction::IsRootGeometry() const
{
  return fRootFactory != 0;
}

#include "G4LogicalVolumeStore.hh"
#include "G4VisAttributes.hh"
#include "Randomize.hh"
//_____________________________________________________________________________
void TstDetectorConstruction::SetG4VisAttributes() const
{
  if (!IsGeant4Geometry()) return;

  std::cout << "TstDetectorConstruction::SetG4VisAttributes()" << std::endl;

  // Set volumes colours
  G4LogicalVolumeStore* lvStore = G4LogicalVolumeStore::GetInstance();
  for (G4int i = 0; i < G4int(lvStore->size()); i++) {
    G4LogicalVolume* lv = (*lvStore)[i];
    G4Colour colour = fColours[(i + 1) % fColours.size()];
    G4VisAttributes* visAtt = new G4VisAttributes(colour);
    visAtt->SetVisibility(true);
    lv->SetVisAttributes(visAtt);
  }

  // Make world invisible
  G4VPhysicalVolume* world = fGeant4Factory->World();
  G4LogicalVolume* worldLog = world->GetLogicalVolume();
  worldLog->SetVisAttributes(G4VisAttributes::GetInvisible());

  std::cout << "TstDetectorConstruction::SetG4VisAttributes() finished"
            << std::endl;
}

#include "TApplication.h"
#include "TBrowser.h"
#include "TGeoManager.h"
#include "TPad.h"
//_____________________________________________________________________________
void TstDetectorConstruction::DrawRootGeometry() const
{
  if (!IsRootGeometry()) return;

  // Set visualization attributes
  //
  TObjArray* volumes = gGeoManager->GetListOfVolumes();
  for (Int_t i = 0; i < volumes->GetEntriesFast(); i++) {
    TGeoVolume* daughter = (TGeoVolume*)volumes->At(i);
    daughter->SetLineColor((i + 1) % fColours.size());
    // How to set a RBG colour ??
  }

  // Save Root geometry
  gGeoManager->CloseGeometry();
  // SaveRootGeometry();

  // Draw Root geometry
  //
  gGeoManager->SetVisLevel(4);
  gGeoManager->SetVisOption(0);
  gGeoManager->GetTopVolume()->SetVisContainers(kTRUE);
  new TBrowser();

  gGeoManager->GetTopVolume()->Draw("ogl");
  // gGeoManager->GetTopVolume()->Raytrace();
  gApplication->Run();

  std::cout << "TstDetectorConstruction::DrawRootGeometry() finished"
            << std::endl;
}
//_____________________________________________________________________________
void TstDetectorConstruction::SaveRootGeometry() const
{
  if (!IsRootGeometry()) return;

  G4String fileName = fSelectedTest + ".root";
  gGeoManager->Export(fileName.data());
}

#include "G4Material.hh"
//_____________________________________________________________________________
void TstDetectorConstruction::PrintGeant4Materials() const
{
  // Prints all materials.
  // ---
  if (!IsGeant4Geometry()) return;

  const G4MaterialTable* matTable = G4Material::GetMaterialTable();
  G4cout << *matTable;
}

#include "TGeoMaterial.h"
#include "TList.h"
//_____________________________________________________________________________
void TstDetectorConstruction::PrintRootMaterials() const
{
  if (!IsRootGeometry()) return;

  TList* materials = gGeoManager->GetListOfMaterials();
  TIter next(materials);
  while (TObject* obj = next()) obj->Print();
}

//_____________________________________________________________________________
void TstDetectorConstruction::GenerateXML() const
{

  if (!fXMLExporter && !fG4GDMLExporter) return;

  if (fXMLExporter) {
    // File name
    std::string xmlFileName = fSelectedTest;
    xmlFileName += fXMLFileName;

    fXMLExporter->SetFileName(xmlFileName);
    fXMLExporter->GenerateXMLGeometry();
  }
  else if (fG4GDMLExporter) {
    if (!IsGeant4Geometry()) return;

    // File name
    std::string xmlFileName = "g4";
    xmlFileName += fSelectedTest;
    xmlFileName += fXMLFileName;

    G4VPhysicalVolume* world = fGeant4Factory->World();
    fG4GDMLExporter->Write(xmlFileName, world);
  }
}

//_____________________________________________________________________________
void TstDetectorConstruction::SelectChannels(const G4String& inputType,
  const G4String& inputFactory, const G4String& outputFactory,
  const G4String& outputXML)
{
  // Check
  if (fgkInputCandidates.find(inputType) == std::string::npos ||
      fgkFactoryCandidates.find(inputFactory) == std::string::npos ||
      fgkFactoryCandidates.find(outputFactory) == std::string::npos ||
      fgkOutputXMLCandidates.find(outputXML) == std::string::npos ||
      inputFactory == "None" || outputFactory == inputFactory ||
      (inputType != inputFactory && inputType != "VGM")) {

    G4Exception("TstDetectorConstruction::SelectChannels", "IllegalConstruct",
      FatalException, "Wrong channels specified.");
  }

  // Create factories
  //
  if (inputFactory == "Geant4" || outputFactory == "Geant4") {
    fGeant4Factory = new Geant4GM::Factory();
  }

  if (inputFactory == "Root" || outputFactory == "Root") {
    fRootFactory = new RootGM::Factory();
  }

  // Select factories
  //
  if (inputFactory == "Geant4") {
    fInputFactory = fGeant4Factory;
    fXMLFileName = "G4";
  }
  else if (inputFactory == "Root") {
    fInputFactory = fRootFactory;
    fXMLFileName = "Root";
  }

  if (outputFactory == "Geant4") {
    fOutputFactory = fGeant4Factory;
  }
  else if (outputFactory == "Root") {
    fOutputFactory = fRootFactory;
  }
  else if (outputFactory == "None") {
    fOutputFactory = 0;
  }

  // Select input
  //
  if (inputType == "VGM") {
    fGeometry = new TstGeometryViaVGM(fInputFactory);
    fXMLFileName += "ViaVGM";
  }
  else if (inputType == "Geant4") {
    fGeometry = new TstGeometryViaGeant4();
    fXMLFileName += "ViaG4";
  }
  else if (inputType == "Root") {
    fGeometry = new TstGeometryViaRoot();
    fXMLFileName += "ViaRoot";
  }

  // Select XML output
  if (outputXML == "AGDD") {
    fXMLExporter = new XmlVGM::AGDDExporter(fInputFactory);
    fXMLFileName += ".agdd";
  }
  else if (outputXML == "GDML") {
    fXMLExporter = new XmlVGM::GDMLExporter(fInputFactory);
    fXMLFileName += ".gdml";
  }
  else if (outputXML == "G4GDML") {
    fG4GDMLExporter = new G4GDMLParser();
    fXMLFileName += ".gdml";
  }

  // Print info
  //
  G4cout << inputFactory << " geometry will be defined via " << inputType;
  if (fOutputFactory) G4cout << " and exported to " << outputFactory;
  G4cout << G4endl;
}

//_____________________________________________________________________________
void TstDetectorConstruction::DefineColours()
{
  /// Store prefeined colours

  fColours.push_back(G4Colour::White());
  fColours.push_back(G4Colour::Gray());
  fColours.push_back(G4Colour::Red());
  fColours.push_back(G4Colour::Green());
  fColours.push_back(G4Colour::Blue());
  fColours.push_back(G4Colour::Yellow());
  fColours.push_back(G4Colour::Magenta());
  fColours.push_back(G4Colour::Cyan());
  fColours.push_back(G4Colour(0.3, .8, 0.4)); // blue-green
}
