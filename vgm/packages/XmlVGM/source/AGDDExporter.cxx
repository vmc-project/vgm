// $Id$
//
// Author: I. Hrivnacova, 27.07.2000 
// (redesigned  31.03.2004) 
//
// Class AGDDExporter
// -------------------
// See the class description in the header file.

#include "CLHEP/Vector/Rotation.h"

#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"
#include "VGM/volumes/IPlacement.h"

#include "XmlVGM/AGDDExporter.h"
#include "XmlVGM/AGDDWriter.h"

//_____________________________________________________________________________
XmlVGM::AGDDExporter::AGDDExporter(const VGM::IFactory* factory)
  : VExporter(factory)
{
//
  fWriter = new AGDDWriter(fOutFile);  
}

//_____________________________________________________________________________
XmlVGM::AGDDExporter::AGDDExporter(const AGDDExporter& right) 
  : VExporter(right)
{
// 
}

//_____________________________________________________________________________
XmlVGM::AGDDExporter::~AGDDExporter() {
//
}

// operators

//_____________________________________________________________________________
XmlVGM::AGDDExporter& 
XmlVGM::AGDDExporter::operator=(const AGDDExporter& right)
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
void XmlVGM::AGDDExporter::GenerateGeometry(VGM::IVolume* volume)  
{
// Generates XML geometry file for the geometry tree 
// starting from the specified logical volume.
// ---

  // filename
  std::string fileName;
  if (fFileName == fgkUndefinedFileName) {
    fileName = volume->Name();
    fileName = fileName + ".xml";
  }  
  else 
    fileName = fFileName;
  
  // set top volume name
  std::string topName = volume->Name() + "_comp";
  
  // Open XML file and document  
  OpenFile(fileName);
  fWriter->OpenDocument();

  // generate materials 
  fWriter->OpenMaterials();
  // not implemented
  // GenerateMaterials(volume);
  fWriter->CloseMaterials();  

  // generate volumes tree
  GenerateSection(volume);

  // Close XML file and document  
  fWriter->CloseDocument();
  CloseFile();
  
  if (fDebug > 0) 
    std::cout << "File " << fileName << " has been generated." << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDExporter::GenerateSection(VGM::IVolume* volume)
{
// Generates the XML section element containing
// all geometry objects defined in given logical volume:
// solids and volumes tree.
// ---

  // create section
  fWriter->OpenSection(volume->Name());  
  fWriter->WriteEmptyLine();
  
  // process solids
  GenerateSolids(volume);
    
  // write top volume
  ProcessTopVolume(volume);

  // process geometry tree
  ProcessVolume(volume);
  fWriter->WriteEmptyLine();
  ClearVolumeNames();
  
  // close section
  fWriter->CloseSection(volume->Name());
}   

//_____________________________________________________________________________
void XmlVGM::AGDDExporter::ProcessTopVolume(VGM::IVolume* volume) 
{
// Writes the top volume position.
// ---
  
  // open composition
  std::string volumeName = volume->Name();
  std::string name = volumeName;
  name.append("_comp");

  fWriter->OpenComposition(volumeName, volume->MaterialName());
  fWriter->WritePlacement(name, Origin());
  fWriter->CloseComposition();	
  fWriter->WriteEmptyLine();
}  

//_____________________________________________________________________________
void XmlVGM::AGDDExporter::ProcessVolume(VGM::IVolume* volume) 
{
// Writes the logical volume tree.
// ---
  
  int nofDaughters = volume->NofDaughters();
  if (nofDaughters == 0) return;
  
  // open composition
  std::string volumeName = volume->Name();
  std::string name = volumeName;
  name.append("_comp");
  fWriter->OpenComposition(name, volume->MaterialName());
  
  // write positions  
  int i;
  for (i=0; i<nofDaughters; i++) {

    if (fDebug > 1) {
      std::cout << "processing " << i << "th daughter of " 
                << volume->Name() << std::endl;
    }	     
   
    VGM::IPlacement* dPlacement = volume->Daughter(i);
    VGM::IVolume* dVolume = dPlacement->Volume();
      
    // get parameters
    std::string volumeName = dVolume->Name();
    std::string compName = dVolume->Name();
    compName.append("_comp");      
    int nd = dVolume->NofDaughters(); 
    
    VGM::PlacementType dPlacementType = dPlacement->Type();

    if (dPlacementType == VGM::kSimplePlacement) {
    
      // simple placement
      VGM::ThreeVector position = dPlacement->ObjectTranslation();
      VGM::Rotation rotation = dPlacement->ObjectRotation();
      bool isReflection = dPlacement->ReflectionZ();

      if (isReflection) {
        fWriter
	  ->WritePlacementWithRotationAndReflection(
	         volumeName, position, rotation);
        if (nd>0) 
      	   fWriter->WritePlacementWithRotationAndReflection(
	                    compName, position, rotation);
      }	  
      else {
        HepRotation hepRotation;
	hepRotation.rotateX(rotation[0]);
	hepRotation.rotateY(rotation[1]);
	hepRotation.rotateZ(rotation[2]);
      
        if (hepRotation.isIdentity()) {
     	  fWriter->WritePlacement(volumeName, position);
          // if volume is not leaf node place its logical volume
          if (nd>0) 
    	    fWriter->WritePlacement(compName, position);
        }
        else {  
  	  fWriter->WritePlacementWithRotation(
	                   volumeName, position, rotation);
          if (nd>0) 
      	     fWriter->WritePlacementWithRotation(
	                      compName, position, rotation);
        }
      }	
    }
    else if (dPlacementType == VGM::kMultiplePlacement) {
      
      // get parameters
      VGM::Axis axis;
      int nReplicas;
      double width;
      double offset;
      dPlacement->MultiplePlacementData(axis, nReplicas, width, offset);
	    
      // write multiple position
      fWriter
        ->WriteMultiplePlacement(volumeName, axis, nReplicas, width, offset);

      // if volume is not leaf node place its logical volume
      if (nd>0) 
      	fWriter
	  ->WriteMultiplePlacement(compName, axis, nReplicas, width, offset);
    }
    else {
      std::cerr << "+++ Warning  +++" << std::endl; 
      std::cerr << "    XmlVGM::AGDDExporter::ProcessVolume: " << std::endl;
      std::cerr << "    Unknown placement type. " << std::endl;
      std::cerr << "    Volume \"" << dPlacement->Name() 
                << "\" was not converted." << std::endl;  
    }
  }  

  // close composition
  fWriter->CloseComposition();	
  fWriter->WriteEmptyLine();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volumeName); 

  // process daughters
  for (i=0; i<nofDaughters; i++) {
    VGM::IVolume* dVolume = volume->Daughter(i)->Volume();
    std::string dVolumeName = dVolume->Name();

    if (fVolumeNames.find(dVolumeName) == fVolumeNames.end()) {
      // process dVolume only if it was not yet processed
      ProcessVolume(dVolume);
    }
  }      
}  
