// $Id$
//
// Author: I. Hrivnacova, 27.07.2000 
// (redesigned  31.03.2004) 
//
// Class AGDDExporter
// -------------------
// See the class description in the header file.

#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"
#include "VGM/volumes/IPlacement.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/AGDDExporter.h"
#include "XmlVGM/AGDDWriter.h"

//_____________________________________________________________________________
XmlVGM::AGDDExporter::AGDDExporter(const VGM::IFactory* factory)
  : VExporter(factory, new AGDDWriter())
{
//
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
// private methods
//

//_____________________________________________________________________________
XmlVGM::ThreeVector  
XmlVGM::AGDDExporter::Identity() const
{
// Returns zero vector
// ---
  
  ThreeVector rotation(3);
  rotation[0] = 0.;
  rotation[1] = 0.;
  rotation[2] = 0.;

  return rotation;
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
    fileName = fileName + ".agdd";
  }  
  else 
    fileName = fFileName;
  
  // Open XML file and document  
  fWriter->OpenFile(fileName);
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
  fWriter->CloseFile();
  
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
    
  // process geometry tree
  ProcessVolume(volume);
  fWriter->WriteEmptyLine();
  ClearVolumeNames();
  
  // close section
  fWriter->CloseSection(volume->Name());
}   

//_____________________________________________________________________________
void XmlVGM::AGDDExporter::ProcessVolume(VGM::IVolume* volume) 
{
// Writes the logical volume tree.
// ---
  
  int nofDaughters = volume->NofDaughters();
  if (nofDaughters == 0) return;
  
  // open composition
  fWriter->OpenComposition(volume->Name(), volume->MaterialName());
  
  // write positions  
  int i;
  for (i=0; i<nofDaughters; i++) {

    if (fDebug > 1) {
      std::cout << "processing " << i << "th daughter of " 
                << volume->Name() << std::endl;
    }	     
   
    fWriter->WritePlacement(*volume->Daughter(i));
  }  

  // close composition
  fWriter->CloseComposition();	
  fWriter->WriteEmptyLine();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volume->Name()); 

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
