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
#include "TstGeometryViaVGM.hh"
#include "TstGeometryViaAgdd.hh"
#include "TstGeometryViaGeant4.hh"
#include "TstGeometryViaRoot.hh"

#include "G4GDMLParser.hh"

const G4String TstDetectorConstruction::fgkTestNameCandidates 
  = "Solids NewSolid NewSolid2 ExtraSolid Placements Reflections Assemblies1 Assemblies2 BooleanSolids1 BooleanSolids2 BooleanSolids3 BooleanSolids4 BooleanSolids5 Special";
const G4String TstDetectorConstruction::fgkVisModeCandidates 
  = "Geant4 Root None";
const G4String TstDetectorConstruction::fgkInputCandidates 
  = "VGM AGDD Geant4 Root";
const G4String TstDetectorConstruction::fgkFactoryCandidates 
  = "AGDD Geant4 Root None";
const G4String TstDetectorConstruction::fgkOutputXMLCandidates 
  = "AGDD GDML G4GDML noXML";

//_____________________________________________________________________________
TstDetectorConstruction::TstDetectorConstruction(const G4String& inputType, 
                                              const G4String& inputFactory,
                                              const G4String& outputFactory,
					      const G4String& outputXML) 
  : G4VUserDetectorConstruction(),
    fSelectedTest("Solids"),
    fSelectedVisMode("Geant4"),
    fFullAngle(true),
    fInputFactory(0),
    fOutputFactory(0),
    fAgddFactory(0),
    fGeant4Factory(0),
    fRootFactory(0),
    fXMLExporter(0),
    fG4GDMLExporter(0),
    fXMLFileName(""),
    fGeometry(0)
{
//
  SelectChannels(inputType, inputFactory, outputFactory, outputXML);
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
    world = fGeometry->TestExtraSolid(VGM::kArb8);
    //world = fGeometry->TestExtraSolid(VGM::kTessellated);
    std::cout << "TestExtraSolid finished" << std::endl;
  }
  else if (fSelectedTest == "Placements") {
    world = fGeometry->TestPlacements();
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
  else if (fSelectedTest == "Special") {
    world = fGeometry->TestSpecial();
    std::cout << "TestSpecial finished" << std::endl;
  }
  
  // Check if geometry was built
  if ( !world) {  
    std::cout << "No geometry is built." << std::endl;
    exit (0);
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

     AgddGM::Factory* agddInputFactory
       = dynamic_cast<AgddGM::Factory*>(fInputFactory);
     if (agddInputFactory) {
       // return static_cast<G4VPhysicalVolume*>(world);
       agddInputFactory->Import(static_cast<agdd::AGDD*>(world));
     }  

     Geant4GM::Factory* g4InputFactory
       = dynamic_cast<Geant4GM::Factory*>(fInputFactory);
     if (g4InputFactory) {
       // return static_cast<G4VPhysicalVolume*>(world);
       g4InputFactory->Import(static_cast<G4VPhysicalVolume*>(world));
     }  

     RootGM::Factory* rtInputFactory
       = dynamic_cast<RootGM::Factory*>(fInputFactory);
     if ( rtInputFactory ) {
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

  if (fSelectedVisMode == "Geant4")
    SetG4VisAttributes();
  if (fSelectedVisMode == "Root") 
    DrawRootGeometry(fSelectedTest.find("Boolean") != std::string::npos);

  // Save Root geometry
  if ( fRootFactory ) {
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
    exit (0);
    return 0;
  }  
}

//_____________________________________________________________________________
void TstDetectorConstruction::SelectTest(const G4String& testName, 
                                         G4bool fullAngle)
{
  if (fgkTestNameCandidates.find(testName) == std::string::npos) {      
      G4Exception("TstDetectorConstruction::SelectTest",
                  "IllegalConstruct", FatalException,
                  "Wrong testName specified.");
  }		  
  
  fSelectedTest = testName;
  fFullAngle = fullAngle;
}  

//_____________________________________________________________________________
void TstDetectorConstruction::SelectVisualization(const G4String& visMode) 
{
  if (fgkVisModeCandidates.find(visMode) == std::string::npos) {      
      G4Exception("TstDetectorConstruction::SelectVisualization",
                  "IllegalConstruct", FatalException,
                  "Wrong visMode specified.");
  }		  
  
  fSelectedVisMode = visMode;
}  

//_____________________________________________________________________________
void TstDetectorConstruction::SetDebug(G4bool debugMode) 
{
// Set debug mode to instantiated factories

 if (fInputFactory)  fInputFactory->SetDebug(debugMode);
 if (fOutputFactory) fOutputFactory->SetDebug(debugMode);
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
  for (G4int i=0; i<G4int(lvStore->size()); i++) {
    G4LogicalVolume* lv = (*lvStore)[i];
    G4VisAttributes* visAtt
      = new G4VisAttributes(G4Colour(0.2 + G4UniformRand()/2., 
                                     0.2 + G4UniformRand()/2., 
				     0.2 + G4UniformRand()/2.));
    visAtt->SetVisibility(true);
    lv->SetVisAttributes(visAtt);
  }  

  // Make world invisible
  G4VPhysicalVolume* world = fGeant4Factory->World();
  G4LogicalVolume* worldLog = world->GetLogicalVolume();
  worldLog->SetVisAttributes (G4VisAttributes::Invisible);

  std::cout << "TstDetectorConstruction::SetG4VisAttributes() finished" << std::endl;
}  
  
#include "TApplication.h"
#include "TBrowser.h"
#include "TPad.h"
#include "TGeoManager.h"
//_____________________________________________________________________________
void TstDetectorConstruction::DrawRootGeometry(bool withRayTrace) const
{ 
  if (!IsRootGeometry()) return;

  TGeoVolume* topVolume = gGeoManager->GetTopVolume();

  // Set visualization attributes
  //
  for (Int_t i=0; i<topVolume->GetNdaughters(); i++) {
    TGeoNode* dNode = topVolume->GetNode(i);
    TGeoVolume* daughter = dNode->GetVolume();
    Int_t colourNo = i+1;
    if (colourNo > 9) colourNo -= 9;
    daughter->SetLineColor(colourNo);    
       // How to set a RBG colour ??
  }  

  // Save Root geometry
  gGeoManager->CloseGeometry();
  // SaveRootGeometry();
  
  // Draw Root geometry
  //
  gGeoManager->SetVisLevel(4);
  gGeoManager->SetVisOption(0);
  new TBrowser();

  if (withRayTrace)
    gGeoManager->GetTopVolume()->Raytrace();
  else {
    gGeoManager->GetTopVolume()->Draw();
  } 
  gApplication->Run();

  std::cout << "TstDetectorConstruction::DrawRootGeometry() finished" << std::endl;
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
  while (TObject *obj = next()) obj->Print();
}

//_____________________________________________________________________________
void TstDetectorConstruction::GenerateXML() const
{

  if ( ! fXMLExporter && ! fG4GDMLExporter ) return;

  if ( fXMLExporter ) {
    // File name
    std::string xmlFileName = fSelectedTest; 
    xmlFileName += fXMLFileName;
  
    fXMLExporter->SetFileName(xmlFileName);
    fXMLExporter->GenerateXMLGeometry();
  }
  else if ( fG4GDMLExporter ) {
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
                                          const G4String& inputFactory, 
                                          const G4String& outputFactory,
					  const G4String& outputXML)
{
  // Check 
  if (fgkInputCandidates.find(inputType) == std::string::npos ||
      fgkFactoryCandidates.find(inputFactory) == std::string::npos ||
      fgkFactoryCandidates.find(outputFactory) == std::string::npos ||
      fgkOutputXMLCandidates.find(outputXML) == std::string::npos ||     
      inputFactory == "None" ||
      outputFactory == inputFactory ||
      inputType != inputFactory && inputType != "VGM") {
      
      G4Exception("TstDetectorConstruction::SelectChannels",
                  "IllegalConstruct", FatalException,
                  "Wrong channels specified.");
  }		  
  
  // Create factories
  //
  if (inputFactory == "Geant4" || outputFactory == "Geant4") {
    fGeant4Factory  = new Geant4GM::Factory();
  }  

  if (inputFactory == "Root" || outputFactory == "Root") {
    fRootFactory  = new RootGM::Factory();
  }  

  if (inputFactory == "AGDD" || outputFactory == "AGDD") {
    fAgddFactory  = new AgddGM::Factory();
  }  

  // Select factories
  //
  if  (inputFactory == "AGDD") {    
    fInputFactory = fAgddFactory;
    fXMLFileName = "Agdd";
  }  
  else if  (inputFactory == "Geant4") {    
    fInputFactory = fGeant4Factory;
    fXMLFileName = "G4";
  }  
  else if (inputFactory == "Root") {  
    fInputFactory = fRootFactory;
    fXMLFileName = "Root";
  }  
     
  if  (outputFactory == "AGDD") { 
    fOutputFactory  = fAgddFactory; 
  }  
  else if  (outputFactory == "Geant4") { 
    fOutputFactory  = fGeant4Factory; 
  }  
  else if (outputFactory == "Root") {
    fOutputFactory  = fRootFactory; 
  }  
  else if (outputFactory == "None") {  
    fOutputFactory  = 0;
  }  

  // Select input
  //
  if (inputType == "VGM" ) { 
    fGeometry = new TstGeometryViaVGM(fInputFactory);
    fXMLFileName += "ViaVGM";
  }  				      
  else if (inputType == "AGDD" ) {
    fGeometry = new TstGeometryViaAgdd();
    fXMLFileName += "ViaAgdd";
  }  
  else if (inputType == "Geant4" ) {
    fGeometry = new TstGeometryViaGeant4();
    fXMLFileName += "ViaG4";
  }  
  else if (inputType == "Root" ) {
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
  
  // Set ignore
  if (fGeant4Factory) fGeant4Factory->SetIgnore(true);
  if (fRootFactory) fRootFactory->SetIgnore(true);

  // Print info
  //
  G4cout << inputFactory  
         << " geometry will be defined via " 
	 << inputType;
  if (fOutputFactory)
    G4cout << " and exported to " << outputFactory;
  G4cout << G4endl;  
}  		  
