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
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IPlacement.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/VExporter.h"
#include "XmlVGM/IWriter.h"

const std::string XmlVGM::VExporter::fgkUndefinedFileName = "Undefined";

//_____________________________________________________________________________
XmlVGM::VExporter::VExporter(const VGM::IFactory* factory)
  : fFactory(factory),
    fWriter(0),  
    fVolumeNames(),
    fOutFile(),
    fFileName(fgkUndefinedFileName),
    fDebug(1), 
    fPositions(),
    fRotations(),
    fElements(),
    fMaterials()
{
//
}

//_____________________________________________________________________________
XmlVGM::VExporter::VExporter()
  : fFactory(0),
    fWriter(0),
    fVolumeNames(),
    fOutFile(),
    fFileName(fgkUndefinedFileName),
    fDebug(1), 
    fPositions(),
    fRotations(),
    fElements(),
    fMaterials()
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
    fVolumeNames(),
    fOutFile(),
    fFileName(fgkUndefinedFileName),
    fDebug(0),  
    fPositions(),
    fRotations(),
    fElements(),
    fMaterials()
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
void XmlVGM::VExporter::CutName(std::string& name) const
{
// Removes spaces after the name if present.
// ---

  int i = name.length();
  while (name[--i] == ' ') name = std::string(name, 0, i);
}  

//_____________________________________________________________________________
double XmlVGM::VExporter::Round(double number) const
{
// Rounds the position elements to the numeric precision of the
// convertor.

  double precision = fWriter->GetNumPrecision();
  return round(number*pow(10.,precision))/pow(10.,precision);
}


//_____________________________________________________________________________
XmlVGM::ThreeVector  
XmlVGM::VExporter::PurifyAngles(const ThreeVector& rotation) const
{
// Inverts angle sign if angle.is within the converter precision
// equal - M_PI.

  double roundedPI = Round(M_PI/fWriter->AngleUnit());

  ThreeVector roundedRotation(3);
  roundedRotation[0] = Round(rotation[0]/ fWriter->AngleUnit());
  roundedRotation[1] = Round(rotation[1]/ fWriter->AngleUnit());
  roundedRotation[2] = Round(rotation[2]/ fWriter->AngleUnit());
  
  ThreeVector rotation2(3);
  rotation2[0] = rotation[0];
  rotation2[1] = rotation[1];
  rotation2[2] = rotation[2];
  
  if (roundedRotation[0] == - roundedPI) rotation2[0] = - rotation2[0];
  if (roundedRotation[1] == - roundedPI) rotation2[1] = - rotation2[1];
  if (roundedRotation[2] == - roundedPI) rotation2[2] = - rotation2[2];

  return rotation2;
}

//_____________________________________________________________________________
bool  XmlVGM::VExporter::IsIdentity(const ThreeVector& rotation) const
{
// Returns true if roatation is identity within the converter precision.

  ThreeVector roundedRotation(3);
  roundedRotation[0] = Round(rotation[0]/ fWriter->AngleUnit());
  roundedRotation[1] = Round(rotation[1]/ fWriter->AngleUnit());
  roundedRotation[2] = Round(rotation[2]/ fWriter->AngleUnit());

  if ( roundedRotation[0] == 0. && 
       roundedRotation[1] == 0. &&
       roundedRotation[2] == 0. )
       
    return true;
  else
    return false;
}               

//_____________________________________________________________________________
std::string 
XmlVGM::VExporter::AddPositionToMap(const ThreeVector& position)
{
// Check if the specified position is not yet present (within the precision
// of the convertor) and add it to the map.
// Returns the XML name of the position element (if added)
// or empty string (if not added).
// ---

  ThreeVector roundedPosition(3);
  roundedPosition[0] = Round(position[0]/ fWriter->LengthUnit());
  roundedPosition[1] = Round(position[1]/ fWriter->LengthUnit());
  roundedPosition[2] = Round(position[2]/ fWriter->LengthUnit());
  
  if (fPositions.find(roundedPosition) != fPositions.end()) 
    return std::string();
  
  // Generate position name
  //
  std::string name("pos_");
  std::ostringstream tmpStream;
  tmpStream << fPositions.size();  
  name.append(tmpStream.str());

  // Add position to the map
  fPositions[roundedPosition] = name;
  
  return name;  
}    


//_____________________________________________________________________________
std::string 
XmlVGM::VExporter::AddRotationToMap(const ThreeVector& rotation)
{
// Check if the specified rotation matrix is not yet present and 
// add it to the map.
// Returns the XML name of the rotation element (if added)
// or empty string (if not added).
// ---

  ThreeVector roundedRotation(3);
  roundedRotation[0] = Round(rotation[0]/ fWriter->AngleUnit());
  roundedRotation[1] = Round(rotation[1]/ fWriter->AngleUnit());
  roundedRotation[2] = Round(rotation[2]/ fWriter->AngleUnit());
  
  if (fRotations.find(roundedRotation) != fRotations.end()) 
    return std::string();
  
  // Generate position name
  //
  std::string name("rot_");
  std::ostringstream tmpStream;
  tmpStream << fRotations.size();  
  name.append(tmpStream.str());

  // Add position to the map
  fRotations[roundedRotation] = name;
  
  return name;  
}    

//_____________________________________________________________________________
const VGM::IElement* 
XmlVGM::VExporter::AddElementToMap(const VGM::IElement* element)
{
// Check if the specified element is not yet present (within the precision
// of the convertor) and add it to the map.
// Returns the element (if added) or 0.
// ---

  ThreeVector roundedValues(3);
  roundedValues[0] = Round(element->Z());
  roundedValues[1] = Round(element->N());
  roundedValues[2] = Round(element->A());
  
  //if (fElements.find(roundedValues) != fElements.end()) return 0;
  ElementMap::iterator it;
  for (it=fElements.begin(); it != fElements.end(); it++) {
    if ( (*it).first  == roundedValues &&
         (*it).second->Name() == element->Name() ) return 0; 
  }      
  
  // Add element to the map
  //fElements[roundedValues] = element;
  fElements.insert(std::make_pair(roundedValues, element));
 
  return element;  
}    

//_____________________________________________________________________________
const VGM::IMaterial* 
XmlVGM::VExporter::AddMaterialToMap(const VGM::IMaterial* material)
{
// Check if the specified material is not yet present and add it to the map.
// Returns the material (if added) or 0.
// ---

  std::string name = material->Name();
  CutName(name);

  if (fMaterials.find(name) != fMaterials.end()) return 0;
  
  // Add material to the map
  fMaterials[name] = material;
  
  return material;  
}    


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
      
      VGM::IPlacement* dPlacement = volume->Daughter(i);
      
      if (dPlacement->Type() == VGM::kSimplePlacement) {
        // Write only simple placement positions
      
        // Get position
        VGM::Transform  transform = dPlacement->Transformation();
        ThreeVector position(3);
        position[0] = transform[VGM::kDx]; 
        position[1] = transform[VGM::kDy]; 
        position[2] = transform[VGM::kDz]; 
      
        std::string posName = AddPositionToMap(position);
      
        if (posName != std::string())
          fWriter->WritePosition(posName, position);
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
      
      VGM::IPlacement* dPlacement = volume->Daughter(i);
      VGM::Transform transform = dPlacement->Transformation();
      VGM::Transform inverse = ClhepVGM::Inverse(transform);

      // Get rotation
      ThreeVector rotation(3);
      rotation[0] = inverse[VGM::kAngleX]; 
      rotation[1] = inverse[VGM::kAngleY]; 
      rotation[2] = inverse[VGM::kAngleZ]; 
      ThreeVector rotation2 = PurifyAngles(rotation);
      
      if (!IsIdentity(rotation2)) {
        std::string rotName = AddRotationToMap(rotation2);

        if (rotName != std::string())
          fWriter->WriteRotation(rotName, rotation2);
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
    = AddMaterialToMap(volumeMaterial);
	
  if (material) {
    // process material elements
    for (int j=0; j<int(material->NofElements()); j++){
      AddElementToMap(material->Element(j));
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
std::string 
XmlVGM::VExporter::FindPositionName(const ThreeVector& position) const
{
// Finds the specified position in the map (within the precision of the 
// convertor) and returns its xml name.
// Returns empty string if not found.
// ---

  ThreeVector roundedPosition(3);
  roundedPosition[0] = Round(position[0]/ fWriter->LengthUnit());
  roundedPosition[1] = Round(position[1]/ fWriter->LengthUnit());
  roundedPosition[2] = Round(position[2]/ fWriter->LengthUnit());
  
  ThreeVectorMap::const_iterator it = fPositions.find(roundedPosition);    
  if (it != fPositions.end())
    return (*it).second;
  else
    return std::string();
}      

//_____________________________________________________________________________
std::string  
XmlVGM::VExporter::FindRotationName(const ThreeVector& rotation) const
{
// Finds the rotation in the map and returns its xml name.
// Returns empty string if not found.
// ---

  ThreeVector rotation2 = PurifyAngles(rotation);

  ThreeVector roundedRotation(3);
  roundedRotation[0] = Round(rotation2[0]/ fWriter->AngleUnit());
  roundedRotation[1] = Round(rotation2[1]/ fWriter->AngleUnit());
  roundedRotation[2] = Round(rotation2[2]/ fWriter->AngleUnit());
  
  ThreeVectorMap::const_iterator it = fRotations.find(roundedRotation);
  if (it != fRotations.end())
    return (*it).second;
  else
    return std::string();
}      

//_____________________________________________________________________________
void XmlVGM::VExporter::GeneratePositions(VGM::IVolume* volume)
{
// Generates the XML elements containing
// all positions present in given logical volume daughters tree.
// ---

  // Open section
  fWriter->OpenPositions();  
  
  // Store first the center position
  std::string posName = AddPositionToMap(Identity());
  fWriter->WritePosition(posName, Identity());

  // Process positions
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
  
  // Identity
  ThreeVector identity(3);
  identity[0] = 0.;
  identity[1] = 0.;
  identity[2] = 0.;

  // Store first the identity matrix
  std::string rotName = AddRotationToMap(identity);
  fWriter->WriteRotation(rotName, identity);

  // Process rotations
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
  ElementMap::const_iterator it1;
  for (it1 = fElements.begin(); it1 != fElements.end(); it1++)
    fWriter->WriteElement((*it1).second);

  // Empty line
  fWriter->WriteEmptyLine();
  
  // Write materials from the map
  MaterialMap::const_iterator it2;
  for (it2 = fMaterials.begin(); it2 != fMaterials.end(); it2++)
    fWriter->WriteMaterial((*it2).second);
  
  fWriter->WriteEmptyLine();
  fElements.erase(fElements.begin(), fElements.end());
  fMaterials.erase(fMaterials.begin(), fMaterials.end());
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
void XmlVGM::VExporter::OpenFile(std::string filePath)
{ 
// Opens output file.
// ---

  fOutFile.open(filePath.data(), std::ios::out); 
  
  if (!fOutFile) {
    std::cerr << "   Cannot open " << filePath << std::endl;  
    std::cerr << "** Exception: Aborting execution **" << std::endl;   
    exit(1);
  }
  
  // use FORTRAN compatibility output
  fOutFile.setf(std::ios::fixed, std::ios::floatfield);
}


//_____________________________________________________________________________
void XmlVGM::VExporter::CloseFile()
{ 
// Closes output file.
// ---

  fOutFile.close(); 
}

//_____________________________________________________________________________
void XmlVGM::VExporter::ClearVolumeNames() 
{
// Clears the set of volume names.
// ---

  fVolumeNames.erase(fVolumeNames.begin(), fVolumeNames.end());
}  

//_____________________________________________________________________________
XmlVGM::ThreeVector  
XmlVGM::VExporter::Identity() const
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
      fPositions.erase(fPositions.begin(), fPositions.end());
      fRotations.erase(fRotations.begin(), fRotations.end());
      
      return;
    }  
  }
  
  std::cerr << "++ Warning: ++ " << std::endl;
  std::cerr << "   XmlVGM::VExporter::GenerateXMLGeometry:" << std::endl; 
  std::cerr << "   Logical volume " << volumeName << " does not exist." << std::endl;
}  

