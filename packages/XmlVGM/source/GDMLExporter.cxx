// $Id$
//
// Author: I. Hrivnacova, 31.03.2004 
//
// Class GDMLExporter
// ------------------------------
// See the class description in the header file.

#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"
#include "VGM/volumes/IPlacement.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/GDMLExporter.h"
#include "XmlVGM/GDMLWriter.h"

//_____________________________________________________________________________
XmlVGM::GDMLExporter::GDMLExporter(const VGM::IFactory* factory)
  : VExporter(factory)
{
//
  fWriter = new GDMLWriter(fOutFile);  
}

//_____________________________________________________________________________
XmlVGM::GDMLExporter::GDMLExporter(const GDMLExporter& right) 
  : VExporter(right)
{
// 
}

//_____________________________________________________________________________
XmlVGM::GDMLExporter::~GDMLExporter() {
//
}

// operators

//_____________________________________________________________________________
XmlVGM::GDMLExporter& 
XmlVGM::GDMLExporter::operator=(const GDMLExporter& right)
{
  // check assignement to self
  if (this == &right) return *this;
  
  // call assignement of the base class
  VExporter::operator=(right);

  return *this;  
}    
          
//
// protected methods
//

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::GenerateGeometry(VGM::IVolume* volume)  
{
// Generates XML geometry file starting from the specified logical volume.
// ---

  // Compose filename
  std::string fileName;
  if (fFileName == fgkUndefinedFileName) {
    fileName = volume->Name();
    fileName = fileName + ".gdml";
  }  
  else
    fileName = fFileName;
  
  // Open XML file and document  
  OpenFile(fileName);
  fWriter->OpenDocument();

  // Generate volumes tree
  GenerateSection(volume);

  // Close XML file and document  
  fWriter->CloseDocument();
  CloseFile();
  
  if (fDebug > 0) 
    std::cout << "File " << fileName << " has been generated." << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::GenerateSection(VGM::IVolume* volume)
{
// Generates the XML section element containing
// all geometry objects defined in given logical volume:
// rotation matrices, solids and volumes hierarchy.
// ---

  // Create section
  fWriter->OpenSection(volume->Name());  
  fWriter->WriteEmptyLine();
  
  // Process basic elements needed by geometry tree
  GeneratePositions(volume);
  GenerateRotations(volume);
  GenerateMaterials(volume);
  GenerateSolids(volume);
    
  // Process geometry tree
  fWriter->OpenStructure();  
  ProcessVolume(volume);
  fWriter->CloseStructure();  
  fWriter->WriteEmptyLine();
  ClearVolumeNames();
  
  // Close section
  fWriter->CloseSection(volume->Name());
}   

//_____________________________________________________________________________
void XmlVGM::GDMLExporter::ProcessVolume(VGM::IVolume* volume) 
{
// Writes logical volume tree.
// ---
  
  int nofDaughters = volume->NofDaughters();

  if (nofDaughters == 0) {
    // Open composition
    fWriter->OpenComposition(volume->Name(), 
                                volume->MaterialName());
  }
  else {
   
    // Recursively process daughters
    //
    for (int i=0; i<nofDaughters; i++) {
      
      VGM::IVolume* dVolume = volume->Daughter(i)->Volume();
      
      if (fVolumeNames.find(dVolume->Name()) == fVolumeNames.end())
        ProcessVolume(dVolume);
    }
    
    // Write the volume with its childs now
    //
    // Open composition
    fWriter->OpenComposition(volume->Name(), 
                                volume->MaterialName());
    
    // Write positions  
    for (int j=0; j<nofDaughters; j++) {

      if (fDebug > 1) {
        std::cout << "processing " << j << "th daughter of " 
                  << volume->Name() << std::endl;
      }	     
   
      VGM::IPlacement* dPlacement = volume->Daughter(j);
      VGM::IVolume* dVolume = dPlacement->Volume();
      
      VGM::PlacementType dPlacementType = dPlacement->Type();

      if (dPlacementType == VGM::kSimplePlacement) {
        // simple placement
	 
	VGM::Transform transform = dPlacement->Transformation();
        VGM::Transform inverse = ClhepVGM::Inverse(transform);
	 
        // position
        ThreeVector position(3);
        position[0] = transform[VGM::kDx];
        position[1] = transform[VGM::kDy];
        position[2] = transform[VGM::kDz];
      
        // rotation
        ThreeVector rotation(3);
        rotation[0] = inverse[VGM::kAngleX];
        rotation[1] = inverse[VGM::kAngleY];
        rotation[2] = inverse[VGM::kAngleZ];

        // Get position
	std::string positionRef = FindPositionName(position);
      
        // Get rotation
	std::string rotationRef = FindRotationName(rotation);
	
        // Reflection is not supported by GDML
        if  (ClhepVGM::HasReflection(transform)) {
          std::cerr << "+++ Warning  +++" << std::endl; 
          std::cerr << "    XmlVGM::GDMLExporter::ProcessVolume: " << std::endl;
          std::cerr << "    Placement with reflection is not yet supported in GDML." 
	            << std::endl;
          std::cerr << "    Volume \"" << dPlacement->Name() 
	            << "\" was not converted."  << std::endl; 
        }		    
	else   
          fWriter->WritePlacementWithRotation(
	                   dVolume->Name(), positionRef, rotationRef);
      }
      else if (dPlacementType == VGM::kMultiplePlacement) {
        // not yet supported in GDML
        std::cerr << "+++ Warning  +++" << std::endl; 
        std::cerr << "    XmlVGM::GDMLExporter::ProcessVolume: " << std::endl;
        std::cerr << "    Multiple placement is not yet supported in GDML." 
	          << std::endl;
        std::cerr << "    Volume \"" << dPlacement->Name() 
	          << "\" was not converted." << std::endl; 
     
      }
      else {
        std::cerr << "+++ Warning  +++" << std::endl; 
        std::cerr << "    XmlVGM::GDMLExporter::ProcessVolume: " << std::endl;
        std::cerr << "    Unknown placement type. " << std::endl;
        std::cerr << "    Volume \"" << dPlacement->Name() 
	          << "\" was not converted." << std::endl;  
      }
    }  
  }
  
  // Close composition
  fWriter->CloseComposition();	
  fWriter->WriteEmptyLine();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volume->Name()); 
}  

