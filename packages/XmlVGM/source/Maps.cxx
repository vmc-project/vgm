// $Id$

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Maps
// --------------------
// Class for generation of geometry data files in XML,
// the XML format is independent from the geometry object model. 
//
// Author: I. Hrivnacova, 19.1.2004

#include "VGM/common/Math.h"
#include "VGM/materials/IElement.h"
#include "VGM/materials/IIsotope.h"
#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IMedium.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/Maps.h"
#include "XmlVGM/IWriter.h"

#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <sstream>

//_____________________________________________________________________________
XmlVGM::Maps::Maps(double numPrecision,
                   double angleUnit, 
		   double lengthUnit)
  : fNumPrecision(numPrecision),
    fAngleUnit(angleUnit),
    fLengthUnit(lengthUnit),
    fPositions(),
    fRotations(),
    fIsotopes(),
    fElements(),
    fMaterials(),
    fMedia(),
    fNofBoolPositions(0),
    fNofBoolRotations(0)
{
/// Standard constructor
/// \param numPrecision fixed format number precision
/// \param angleUnit the unit for angle values
/// \param lengthUnit the unit for length values
}

//_____________________________________________________________________________
XmlVGM::Maps::Maps() 
  : fPositions(),
    fRotations(),
    fIsotopes(),
    fElements(),
    fMaterials(),
    fMedia(),
    fNofBoolPositions(0),
    fNofBoolRotations(0)
{
/// Protected default constructor
 
  std::cerr << "   XmlVGM::Maps::Maps:" << std::endl;
  std::cerr << "   Dummy constructor protected." << std::endl;
  std::cerr << "** Exception: Aborting execution **" << std::endl;   
  exit(1);
}

//_____________________________________________________________________________
XmlVGM::Maps::Maps(const Maps& /*right*/) 
  : fPositions(),
    fRotations(),
    fIsotopes(),
    fElements(),
    fMaterials(),
    fNofBoolPositions(0),
    fNofBoolRotations(0)
{
/// Protected copy constructor

  std::cerr << "   XmlVGM::Maps::Maps:" << std::endl;
  std::cerr << "   Copy constructor not implemented." << std::endl;
  std::cerr << "** Exception: Aborting execution **" << std::endl;   
  exit(1);
}

//_____________________________________________________________________________
XmlVGM::Maps::~Maps() {
//
}

//
// operators
//

//_____________________________________________________________________________
XmlVGM::Maps& 
XmlVGM::Maps::operator=(const Maps& right)
{
/// Protected assignement operator

  // check assignement to self
  if (this == &right) return *this;

  std::cerr << "   XmlVGM::Maps::operator=:" << std::endl;
  std::cerr << "   Assignement operator not implemented." << std::endl;
  std::cerr << "** Exception: Aborting execution **" << std::endl;   
  exit(1);
    
  return *this;  
}    
          

//
// private methods
//

//_____________________________________________________________________________
void XmlVGM::Maps::CutName(std::string& name) const
{
/// Remove spaces after the name if present

  int i = name.length();
  while (name[--i] == ' ') name = std::string(name, 0, i);
}  

//_____________________________________________________________________________
double XmlVGM::Maps::Round2(double number) const
{
/// Round the number to the numeric precision of the map

  double precision = fNumPrecision;
  return ClhepVGM::Round(number*pow(10.,precision))/pow(10.,precision);
}


//_____________________________________________________________________________
VGM::ThreeVector  
XmlVGM::Maps::PurifyAngles(const VGM::ThreeVector& rotation) const
{
/// Invert angle sign if angle.is within the maps precision
/// equal - M_PI.

  double roundedPI = Round2(M_PI/fAngleUnit);

  VGM::ThreeVector roundedRotation(3);
  roundedRotation[0] = Round2(rotation[0]/ fAngleUnit);
  roundedRotation[1] = Round2(rotation[1]/ fAngleUnit);
  roundedRotation[2] = Round2(rotation[2]/ fAngleUnit);
  
  VGM::ThreeVector rotation2(3);
  rotation2[0] = rotation[0];
  rotation2[1] = rotation[1];
  rotation2[2] = rotation[2];
  
  if (roundedRotation[0] == - roundedPI) rotation2[0] = - rotation2[0];
  if (roundedRotation[1] == - roundedPI) rotation2[1] = - rotation2[1];
  if (roundedRotation[2] == - roundedPI) rotation2[2] = - rotation2[2];

  return rotation2;
}

//
// public methods
//

//_____________________________________________________________________________
std::string
XmlVGM::Maps::AddPosition(const VGM::Transform& transform)
{
/// Check if the specified position is not yet present (within the maps 
/// precision), add it to the map and return its generated name

  VGM::ThreeVector position(3);
  position[0] = transform[VGM::kDx]; 
  position[1] = transform[VGM::kDy]; 
  position[2] = transform[VGM::kDz]; 

  VGM::ThreeVector roundedPosition(3);
  roundedPosition[0] = Round2(position[0]/ fLengthUnit);
  roundedPosition[1] = Round2(position[1]/ fLengthUnit);
  roundedPosition[2] = Round2(position[2]/ fLengthUnit);
  
  if (fPositions.find(roundedPosition) != fPositions.end()) return "";
  
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
XmlVGM::Maps::AddRotation(const VGM::Transform& transform)
{
/// Check if the specified rotation matrix is not yet present, 
/// add it to the map and return its generated name

  // Get rotation
  VGM::ThreeVector rotation(3);
  rotation[0] = transform[VGM::kAngleX]; 
  rotation[1] = transform[VGM::kAngleY]; 
  rotation[2] = transform[VGM::kAngleZ]; 
  VGM::ThreeVector rotation2 = PurifyAngles(rotation);
      
  VGM::ThreeVector roundedRotation(3);
  roundedRotation[0] = Round2(rotation2[0]/ fAngleUnit);
  roundedRotation[1] = Round2(rotation2[1]/ fAngleUnit);
  roundedRotation[2] = Round2(rotation2[2]/ fAngleUnit);
  
  if (fRotations.find(roundedRotation) != fRotations.end()) return "";
  
  // Generate rotation name
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
std::string
XmlVGM::Maps::AddBooleanPosition()
{
/// Increase Boolean position counter and generate position name

  std::string name("posB_");
  std::ostringstream tmpStream;
  tmpStream << fNofBoolPositions++;  
  name.append(tmpStream.str());

  return name;
}    

//_____________________________________________________________________________
std::string
XmlVGM::Maps::AddBooleanRotation()
{
/// Increase Boolean position counter and generate position name

  std::string name("rotB_");
  std::ostringstream tmpStream;
  tmpStream << fNofBoolRotations++;  
  name.append(tmpStream.str());

  return name;
}    


//_____________________________________________________________________________
const VGM::IIsotope* 
XmlVGM::Maps::AddIsotope(const VGM::IIsotope* isotope)
{
/// Check if the specified isotope is not yet present (within the maps 
/// precision) and add it to the map.
/// Return the isotope (if added) or 0.

  VGM::ThreeVector roundedValues(3);
  roundedValues[0] = Round2(isotope->Z());
  roundedValues[1] = Round2(isotope->N());
  roundedValues[2] = Round2(isotope->A());
  
  //if (fIsotopes.find(roundedValues) != fIsotopes.end()) return 0;
  IsotopeMap::iterator it;
  for (it=fIsotopes.begin(); it != fIsotopes.end(); it++) {
    if ( (*it).first  == roundedValues &&
         (*it).second->Name() == isotope->Name() ) return 0; 
  }      
  
  // Add isotope to the map
  //fIsotopes[roundedValues] = isotope;
  fIsotopes.insert(std::make_pair(roundedValues, isotope));
 
  return isotope;  
}    

//_____________________________________________________________________________
const VGM::IElement* 
XmlVGM::Maps::AddElement(const VGM::IElement* element)
{
/// Check if the specified element is not yet present (within the maps 
/// precision) and add it to the map.
/// Return the element (if added) or 0.

  VGM::ThreeVector roundedValues(3);
  roundedValues[0] = Round2(element->Z());
  roundedValues[1] = Round2(element->N());
  roundedValues[2] = Round2(element->A());
  
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
XmlVGM::Maps::AddMaterial(const VGM::IMaterial* material)
{
/// Check if the specified material is not yet present and add it to the map.
/// Return the material (if added) or 0.

  std::string name = material->Name();
  CutName(name);

  if (fMaterials.find(name) != fMaterials.end()) return 0;
  
  // Add material to the map
  fMaterials[name] = material;
  
  return material;  
}    


//_____________________________________________________________________________
const VGM::IMedium* 
XmlVGM::Maps::AddMedium(const VGM::IMedium* medium)
{
/// Check if the specified material is not yet present and add it to the map.
/// Return the material (if added) or 0.

  std::string name = medium->Name();
  CutName(name);

  if (fMedia.find(name) != fMedia.end()) return 0;
  
  // Add material to the map
  fMedia[name] = medium;
  
  return medium;  
}    



//_____________________________________________________________________________
std::string 
XmlVGM::Maps::FindPositionName(const VGM::Transform& transform) const
{
/// Find the position from the given transformation in the map (within the maps
/// precision) and return its xml name.
/// Return an empty string if not found.

  VGM::ThreeVector position(3);
  position[0] = transform[VGM::kDx];
  position[1] = transform[VGM::kDy];
  position[2] = transform[VGM::kDz];
      
  VGM::ThreeVector roundedPosition(3);
  roundedPosition[0] = Round2(position[0]/ fLengthUnit);
  roundedPosition[1] = Round2(position[1]/ fLengthUnit);
  roundedPosition[2] = Round2(position[2]/ fLengthUnit);
  
  ThreeVectorMap::const_iterator it = fPositions.find(roundedPosition);    
  if (it != fPositions.end())
    return (*it).second;
  else
    return std::string();
}      

//_____________________________________________________________________________
std::string  
XmlVGM::Maps::FindRotationName(const VGM::Transform& transform) const
{
/// Find the rotation from the given transformation in the map (within the maps
/// precision) and return its xml name.
/// Return an empty string if not found.

  // rotation
  VGM::ThreeVector rotation(3);
  rotation[0] = transform[VGM::kAngleX];
  rotation[1] = transform[VGM::kAngleY];
  rotation[2] = transform[VGM::kAngleZ];

  VGM::ThreeVector rotation2 = PurifyAngles(rotation);

  VGM::ThreeVector roundedRotation(3);
  roundedRotation[0] = Round2(rotation2[0]/ fAngleUnit);
  roundedRotation[1] = Round2(rotation2[1]/ fAngleUnit);
  roundedRotation[2] = Round2(rotation2[2]/ fAngleUnit);
  
  ThreeVectorMap::const_iterator it = fRotations.find(roundedRotation);
  if (it != fRotations.end())
    return (*it).second;
  else
    return std::string();
}      

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllPositions(IWriter* writer)
{
/// Write all positions in the map with the given writer

  ThreeVectorMap::const_iterator it1;
  for (it1 = fPositions.begin(); it1 != fPositions.end(); it1++)
    writer->WritePosition((*it1).second, (*it1).first);
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllRotations(IWriter* writer)
{
/// Write all rotations in the map with the given writer

  ThreeVectorMap::const_iterator it1;
  for (it1 = fRotations.begin(); it1 != fRotations.end(); it1++)
    writer->WriteRotation((*it1).second, (*it1).first);
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllIsotopes(IWriter* writer)
{
/// Write all isotopes from the map with the given writer

  IsotopeMap::const_iterator it1;
  for (it1 = fIsotopes.begin(); it1 != fIsotopes.end(); it1++)
    writer->WriteIsotope((*it1).second);
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllElements(IWriter* writer)
{
/// Write all elements from the map with the given writer

  ElementMap::const_iterator it1;
  for (it1 = fElements.begin(); it1 != fElements.end(); it1++)
    writer->WriteElement((*it1).second);
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllMaterials(IWriter* writer)
{
/// Write all materials from the map with the given writer

  MaterialMap::const_iterator it2;
  for (it2 = fMaterials.begin(); it2 != fMaterials.end(); it2++)
    writer->WriteMaterial((*it2).second);
  
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllMedia(IWriter* writer)
{
/// Write all materials from the map with the given writer

  MediumMap::const_iterator it;
  for ( it = fMedia.begin(); it != fMedia.end(); it++)
    writer->WriteMedium((*it).second);
  
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::WriteAllMediaFromMaterials(IWriter* writer)
{
/// Write all materials from the map with the given writer

  MaterialMap::const_iterator it;
  for ( it = fMaterials.begin(); it != fMaterials.end(); it++)
    writer->WriteMedium((*it).second);
  
}    

//_____________________________________________________________________________
void 
XmlVGM::Maps::ClearAllMaps()
{
/// Clear all maps

  fPositions.erase(fPositions.begin(), fPositions.end());
  fRotations.erase(fRotations.begin(), fRotations.end());
  fIsotopes.erase(fIsotopes.begin(), fIsotopes.end());
  fElements.erase(fElements.begin(), fElements.end());
  fMaterials.erase(fMaterials.begin(), fMaterials.end());
  fMedia.erase(fMedia.begin(), fMedia.end());
}  



