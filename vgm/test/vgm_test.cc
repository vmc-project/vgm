// $Id$
//
// VGM test main program
// --------------------
// Usage:
// vgm_test inputType inputFactory outputFactory selectedTest 
//         [debug] [openAngle] [noVis]
//
//         inputType     = VGM, Geant4, Root
//         inputFactory  = Geant4, Root
//         outputFactory = Geant4, Root, None
//         outputXML = AGDD, GDML, None
//         selectedTest  = Solids, Placements, Reflections, Assemblies, 
//                         BooleanSolidsN
//                             where N = 1, 2, 3
//         debug         = if specified the factories operate in debug mode
//         openAngle     = if specified, solids like tubs, cons etc. are built
//                         with open azimuthal angle
//         noVis         = no visualisation
//
// Author: Ivana Hrivnacova; IPN Orsay


#include "TApplication.h"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "TstVisManager.hh"
#endif

#include "TstDetectorConstruction.hh"
#include "TstPhysicsList.hh"
#include "TstPrimaryGeneratorAction.hh"


int main(int argc, char** argv) 
{
  // Root
  TApplication theApp("otherwise it does not work", &argc, argv);

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager();

  if (argc < 6 || argc > 8) {
    std::cerr << " Usage: " << std::endl;
    std::cerr << " vgm_test inputType inputFactory outputFactory outputXML selectedTest " 
              << std::endl;
    std::cerr << "          [debug] [openAngle] [noVis]" << std::endl;
    std::cerr << "          inputType     = VGM, Geant4, Root" << std::endl;
    std::cerr << "          inputFactory  = Geant4, Root" << std::endl;
    std::cerr << "          outputFactory = Geant4, Root, None" << std::endl;
    std::cerr << "          outputXML     = AGDD, GDML, noXML" << std::endl;
    std::cerr << "          selectedTest  = Solids, Placements, Reflections, Assemblies," << std::endl;
    std::cerr << "                          BooleanSolids" << std::endl;
    std::cerr << "                               where N = 1, 2, 3" << std::endl;
    std::cerr << "          debug         = if specified the factories operate in debug mode"  << std::endl;
    std::cerr << "          openAngle     = if specified, solids like tubs, cons etc. are built" << std::endl;
    std::cerr << "                          with open azimuthal angle" << std::endl;
    std::cerr << "          noVis         = no visualisation" << std::endl;
    
    exit(1);
  }  

  // Manadatory parameters
  //
  G4String inputType  = argv[1];
  G4String inputFactory  = argv[2];
  G4String outputFactory = argv[3];
  G4String outputXML = argv[4];
  G4String selectedTest = argv[5];

  // Optional parameters
  //
  G4bool   debugMode = false;
  G4bool   fullAngle = true;
  G4String visMode = outputFactory;
  if (outputFactory == "None") visMode = inputFactory;
  
  if (argc > 6)
  for (G4int i=6; i<argc; i++) {
    if (G4String(argv[i]) == "debug")       
      debugMode = true;
    else if (G4String(argv[i]) == "openAngle")       
      fullAngle = false;
    else if (G4String(argv[i]) == "noVis")  
      visMode = "None";
    else  
      std::cerr << " Argument " << argv[i] << " not recognized." << std::endl;
  }    

  TstDetectorConstruction* detector
    = new TstDetectorConstruction(inputType, inputFactory, outputFactory, 
                                  outputXML);
  detector->SetDebug(debugMode);
  detector->SelectTest(selectedTest, fullAngle);  
  detector->SelectVisualization(visMode);  

  // Set mandatory initialization classes
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new TstPhysicsList());

  G4UIsession* session = 0; 
  if (visMode != "None") {
#ifdef G4UI_USE_TCSH
    session = new G4UIterminal(new G4UItcsh);      
#else
    session = new G4UIterminal();
#endif
  }
  
#ifdef G4VIS_USE
  G4VisManager* visManager = 0;
  if (visMode == "Geant4") {
    // Visualization manager
    visManager = new TstVisManager();
    visManager->Initialize();
  }  
#endif
    
  // Set user action classes
  runManager->SetUserAction(new TstPrimaryGeneratorAction());
  
  // Initialize G4 kernel
  runManager->Initialize();
    
  // Get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  if (session) {
      UI->ApplyCommand("/control/execute vis.mac");    
      session->SessionStart();
      delete session;
  }  

  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}
