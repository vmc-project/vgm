// $Id$
//
// Class VExporter
// --------------------
// Class for generation of geometry data files in XML,
// the XML format is independent from the geometry object model. 
//
// Author: I. Hrivnacova, 19.1.2004

#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <sstream>

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/solids/ISolid.h"
#include "VGM/solids/IBooleanSolid.h"
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IPlacement.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/VExporter.h"
#include "XmlVGM/IWriter.h"

const std::string XmlVGM::VExporter::fgkUndefinedFileName = "Undefined";

//_____________________________________________________________________________
XmlVGM::VExporter::VExporter(const VGM::IFactory* factory,
                             IWriter* writer)
  : fFactory(factory),
    fWriter(writer),  
    fFileName(fgkUndefinedFileName),
    fVolumeNames(),
    fDebug(1),
    fMaps(writer->GetNumPrecision(),
          writer->AngleUnit(),
          writer->LengthUnit())
{
//
}

//_____________________________________________________________________________
XmlVGM::VExporter::VExporter()
  : fFactory(0),
    fWriter(0),
    fFileName(fgkUndefinedFileName),
    fVolumeNames(),
    fDebug(1), 
    fMaps(0, 1., 1.)
{
//
// 
  std::cerr << "    XmlVGM::VExporter::VExporter:" << std::endl;
  std::cerr << "    Not allowed constructor." << std::endl;
  std::cerr << "*** Error: Aborting execution  +++" << std::endl; 
  exit(1);
}

//_____________________________________________________________________________
XmlVGM::VExporter::VExporter(const VExporter& /*right*/) 
  : fWriter(0),
    fFileName(fgkUndefinedFileName),
    fVolumeNames(),
    fDebug(0), 
    fMaps(0, 1., 1.)
{
// 
  std::cerr << "   XmlVGM::VExporter::VExporter:" << std::endl;
  std::cerr << "   Copy constructor not implemented." << std::endl;
  std::cerr << "** Exception: Aborting execution **" << std::endl;   
  exit(1);
}

//_____________________________________________________________________________
XmlVGM::VExporter::~VExporter() {
//
  delete fWriter;
}

//
// operators
//

//_____________________________________________________________________________
XmlVGM::VExporter& 
XmlVGM::VExporter::operator=(const VExporter& right)
{
  // check assignement to self
  if (this == &right) return *this;

  std::cerr << "   XmlVGM::VExporter::operator=:" << std::endl;
  std::cerr << "   Assignement operator not implemented." << std::endl;
  std::cerr << "** Exception: Aborting execution **" << std::endl;   
  exit(1);
    
  return *this;  
}    
          

//
// private methods
//

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessPositions(VGM::IVolume* volume) 
{
// Writes all position in the daughters tree of the given logical volume.
// ---

  std::string volumeName = volume->Name();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volumeName); 
  
  int nofDaughters = volume->NofDaughters();

  if (nofDaughters>0) {
    for (int i=0; i<nofDaughters; i++) {
      
      // Simple placement positions
      //
      VGM::IPlacement* dPlacement = volume->Daughter(i);
      if (dPlacement->Type() == VGM::kSimplePlacement) {
      
        VGM::Transform transform = dPlacement->Transformation();
        std::string name = fMaps.AddPosition(transform);

	if (name != "")
  	  fWriter->WritePosition(name, transform);
      }	

      // Displacemnt positions in Boolean solids
      //
      VGM::ISolid* dSolid = dPlacement->Volume()->Solid();
      if (dSolid->Type() == VGM::kBoolean) {
      
	ProcessPositionsInBoolean(dSolid);  
      }	

      std::string dVolumeName = dPlacement->Volume()->Name();
      if (fVolumeNames.find(dVolumeName) == fVolumeNames.end()) {
        // process volumed only if it was not yet processed
        ProcessPositions(dPlacement->Volume());
      }	
    }
  }  
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessPositionsInBoolean(VGM::ISolid* solid) 
{
// Writes all position in the boolean solid and its constituents
// (if Booleans too) 
// ---

   if (solid->Type() != VGM::kBoolean)  return;
      
   VGM::IBooleanSolid* boolSolid
     = dynamic_cast<VGM::IBooleanSolid*>(solid);
     
   VGM::Transform transform = boolSolid->Displacement();
   std::string name = fMaps.AddPosition(transform);
	
   if (name != "")
     fWriter->WritePosition(name, transform);

   // Process constituents
   VGM::ISolid* solidA = boolSolid->ConstituentSolidA();
   VGM::ISolid* solidB = boolSolid->ConstituentSolidB();
   
   if (solidA->Type() == VGM::kBoolean) ProcessPositionsInBoolean(solidA);
   if (solidB->Type() == VGM::kBoolean) ProcessPositionsInBoolean(solidB);
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessRotations(VGM::IVolume* volume) 
{
// Writes all rotation matrices in the volume tree of
// the given volume .
// ---

  std::string volumeName = volume->Name();

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volumeName); 
  
  int nofDaughters = volume->NofDaughters();

  if (nofDaughters>0) {
    for (int i=0; i<nofDaughters; i++) {
      
       // Simple placement rotations
      //
      VGM::IPlacement* dPlacement = volume->Daughter(i);
      if (dPlacement->Type() == VGM::kSimplePlacement) {
      
        VGM::Transform transform = dPlacement->Transformation();
        std::string name = fMaps.AddRotation(transform);

	if (name != "")
  	  fWriter->WriteRotation(name, transform);
      }	

      // Displacemnt rotations in Boolean solids
      //

      VGM::ISolid* dSolid = dPlacement->Volume()->Solid();
      if (dSolid->Type() == VGM::kBoolean) {
      
	ProcessRotationsInBoolean(dSolid);  
      }	

      std::string dVolumeName = dPlacement->Volume()->Name();
      if (fVolumeNames.find(dVolumeName) == fVolumeNames.end()) {
        // process volumed only if it was not yet processed
        ProcessRotations(dPlacement->Volume());
      }	
    }
  }  
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessRotationsInBoolean(VGM::ISolid* solid) 
{
// Writes all rotations in the boolean solid and its constituents
// (if Booleans too) 
// ---

   if (solid->Type() != VGM::kBoolean)  return;
      
   VGM::IBooleanSolid* boolSolid
     = dynamic_cast<VGM::IBooleanSolid*>(solid);
     
   VGM::Transform transform = boolSolid->Displacement();
   std::string name = fMaps.AddRotation(transform);
	
   if (name != "")
     fWriter->WriteRotation(name, transform);

   // Process constituents
   VGM::ISolid* solidA = boolSolid->ConstituentSolidA();
   VGM::ISolid* solidB = boolSolid->ConstituentSolidB();
   
   if (solidA->Type() == VGM::kBoolean) ProcessRotationsInBoolean(solidA);
   if (solidB->Type() == VGM::kBoolean) ProcessPositionsInBoolean(solidB);
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessMaterials(VGM::IVolume* volume) 
{
// Writes all position in the daughters tree of the given logical volume.
// ---

  std::string volumeName = volume->Name();

  const VGM::IMaterial* volumeMaterial 
    = fFactory->MaterialFactory()->Material(volume->MaterialName());
    
  if (!volumeMaterial) {
    std::cerr << "XmlVGM::VExporter::ProcessMaterials: " << std::endl;
    std::cerr << "   Material " << volume->MaterialName() << "not found." 
              << std::endl;
    exit(1);
  }  	      
    
  const VGM::IMaterial* material 
    = fMaps.AddMaterial(volumeMaterial);
	
  if (material) {
    // process material elements
    for (int j=0; j<int(material->NofElements()); j++){
      fMaps.AddElement(material->Element(j));
    }  
  }	

  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volumeName); 
  
  int nofDaughters = volume->NofDaughters();

  if (nofDaughters>0) {
    for (int i=0; i<nofDaughters; i++) {
      
      VGM::IPlacement* dPlacement = volume->Daughter(i);

      std::string dVolumeName = dPlacement->Volume()->Name();
      if (fVolumeNames.find(dVolumeName) == fVolumeNames.end()) {
        // process volumed only if it was not yet processed
        ProcessMaterials(dPlacement->Volume());
      }	
    }
  }  
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::ProcessSolids(VGM::IVolume* volume) 
{
// Writes all solids of given volume.
// ---

  VGM::ISolid* solid = volume->Solid();
  std::string volumeName = volume->Name();
  std::string materialName = volume->MaterialName();
  fWriter->WriteSolid(volumeName, solid, materialName);
  
  // store the name of logical volume in the set
  fVolumeNames.insert(fVolumeNames.begin(), volumeName); 

  // process daughters
  int nofDaughters = volume->NofDaughters();
  if (nofDaughters>0) 
    for (int i=0; i<nofDaughters; i++) {

      if (fDebug > 1) {
        std::cout << "processing " << i << "th daughter of " 
                  << volume->Name() << std::endl;
      }
              
      VGM::IVolume* dVolume = volume->Daughter(i)->Volume();
      std::string dVolumeName = dVolume->Name();

      if (fVolumeNames.find(dVolumeName) == fVolumeNames.end()) {
        // process dVolume only if it was not yet processed
        ProcessSolids(dVolume);
      }	
    }
}  

//
// protected methods
//

//_____________________________________________________________________________
void XmlVGM::VExporter::GeneratePositions(VGM::IVolume* volume)
{
// Generates the XML elements containing
// all positions present in given logical volume daughters tree.
// ---

  // Open section
  fWriter->OpenPositions();  
  
  // Store first the center position
  std::string name = fMaps.AddPosition(ClhepVGM::Identity());
  fWriter->WritePosition(name, ClhepVGM::Identity());

  // Process and write positions
  ProcessPositions(volume);
  ClearVolumeNames();

  // Close section
  fWriter->ClosePositions();
  fWriter->WriteEmptyLine();
}   

//_____________________________________________________________________________
void XmlVGM::VExporter::GenerateRotations(VGM::IVolume* volume)
{
// Generates the XML elements containing
// all positions present in given logical volume daughters tree.
// ---

  // Open section
  fWriter->OpenRotations();  
  
  // Store first the identity matrix
  std::string name = fMaps.AddRotation(ClhepVGM::Identity());
  fWriter->WriteRotation(name, ClhepVGM::Identity());

  // Process and write rotations
  ProcessRotations(volume);
  ClearVolumeNames();

  // Close section
  fWriter->CloseRotations();
  fWriter->WriteEmptyLine();
}   

//_____________________________________________________________________________
void XmlVGM::VExporter::GenerateMaterials(VGM::IVolume* volume)
{
// Generates the XML material element containing
// all materials present in given logical volume.
// ---

  // Create section
  fWriter->OpenMaterials();  
  
  // Fill maps of elements and materials
  ProcessMaterials(volume);
  
  // Write elements from the map
  fMaps.WriteAllElements(fWriter);

  // Empty line
  fWriter->WriteEmptyLine();
  
  // Write materials from the map
  fMaps.WriteAllMaterials(fWriter);
  
  fWriter->WriteEmptyLine();
  ClearVolumeNames();

  // Close section
  fWriter->CloseMaterials();
  fWriter->WriteEmptyLine();
}   

//_____________________________________________________________________________
void XmlVGM::VExporter::GenerateSolids(VGM::IVolume* volume)
{
// Generates the XML solids element containing
// all solids present in given logical volume.
// ---

  fWriter->OpenSolids();  
  ProcessSolids(volume);
  fWriter->CloseSolids();  
  fWriter->WriteEmptyLine();
  ClearVolumeNames();
}   

//_____________________________________________________________________________
void XmlVGM::VExporter::ClearVolumeNames() 
{
// Clears the set of volume names.
// ---

  fVolumeNames.erase(fVolumeNames.begin(), fVolumeNames.end());
}  


//
// public methods
//

//_____________________________________________________________________________
void XmlVGM::VExporter::GenerateXMLGeometry()
{
// Generates XML geometry file from the top (world) volume.
// ---

  GenerateGeometry(fFactory->Top()->Volume());
}  

//_____________________________________________________________________________
void XmlVGM::VExporter::GenerateXMLGeometry(const std::string& volumeName) 
{
// Generates XML geometry file from the logical volume specified by name.
// ---

  // Find volume
  const VGM::VolumeStore& volumeStore = fFactory->Volumes();

  for (unsigned int i=0; i<volumeStore.size(); i++) {
    VGM::IVolume* volume = volumeStore[i];
    if (volume->Name() == volumeName) {

      // Generate XML
      GenerateGeometry(volume);
      
      // Clear temprary maps
      fMaps.ClearAllMaps();
      
      return;
    }  
  }
  
  std::cerr << "++ Warning: ++ " << std::endl;
  std::cerr << "   XmlVGM::VExporter::GenerateXMLGeometry:" << std::endl; 
  std::cerr << "   Logical volume " << volumeName << " does not exist." << std::endl;
}  
