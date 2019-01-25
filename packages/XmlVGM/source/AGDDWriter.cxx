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
// Class AGDDWriter
// ---------------------
// The implementation of the interface for the XML convertor that
// converts VGM geometry objects to XML defined by AGDD.dtd
// (ATLAS Generic Detector Description)
//
// Author: I. Hrivnacova, 16.01.2004 

#include <VGM/materials/IElement.h>
#include <VGM/materials/IMaterial.h>
#include <VGM/materials/IMedium.h>
#include <VGM/volumes/IPlacement.h>
#include <VGM/volumes/IVolume.h>
#include <VGM/solids/ISolid.h>
#include <VGM/solids/IBooleanSolid.h>
#include <VGM/solids/IBox.h>
#include <VGM/solids/ICons.h>
#include <VGM/solids/IPara.h>
#include <VGM/solids/IPolycone.h>
#include <VGM/solids/IPolyhedra.h>
#include <VGM/solids/ISphere.h>
#include <VGM/solids/ITrap.h>
#include <VGM/solids/ITrd.h>
#include <VGM/solids/ITubs.h>

#include <ClhepVGM/transform.h>

#include "XmlVGM/AGDDWriter.h"
#include "XmlVGM/utilities.h"

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Units/SystemOfUnits.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <time.h>
#include <cstdlib>

using CLHEP::deg;

const int         XmlVGM::AGDDWriter::fgkDefaultNumWidth       = 7;
const int         XmlVGM::AGDDWriter::fgkDefaultNumPrecision   = 4;
const std::string XmlVGM::AGDDWriter::fgkCompNameExtension     = "_comp";
const std::string XmlVGM::AGDDWriter::fgkElementNameExtension  = "_e";
const std::string XmlVGM::AGDDWriter::fgkMaterialNameExtension = "_mat";
const double      XmlVGM::AGDDWriter::fgkCarTolerance = 1e-10; 
const double      XmlVGM::AGDDWriter::fgkAngTolerance = 1e-8;

//_____________________________________________________________________________
XmlVGM::AGDDWriter::AGDDWriter(const std::string& version,
                               const std::string& author,
			       const std::string dtdVersion) 
  : IWriter(),
    fOutFile(),
    fVersion(version),
    fAuthor(author),
    fDtdVersion(dtdVersion),
    fkBasicIndention("   "),
    fIndention(fkBasicIndention),
    fNW(fgkDefaultNumWidth),
    fNP(fgkDefaultNumPrecision)
{
/// Standard constructor
/// \param version AGDD file version
/// \param author  AGDD file author
/// \param dtdVersion AGDD DTD version
 
  fOutFile.width(fgkDefaultNumWidth);
  fOutFile.precision(fgkDefaultNumPrecision);
}

//_____________________________________________________________________________
XmlVGM::AGDDWriter::AGDDWriter(const AGDDWriter& /*rhs*/)
  : IWriter()
{
/// Protected copy constructor
}

//_____________________________________________________________________________
XmlVGM::AGDDWriter::~AGDDWriter() {
//
}

//
// private methods
//

//_____________________________________________________________________________
std::string 
XmlVGM::AGDDWriter::ElementSymbol(const VGM::IElement* element) const
{
/// Return element symbol if defined, element name with element extension
/// otherwise

  std::string symbol = element->Symbol();
  if ( symbol == " " ) {
    symbol = element->Name();
    symbol.append(fgkElementNameExtension);
  }  
  
  return symbol;
}  
                       
//_____________________________________________________________________________
void XmlVGM::AGDDWriter::RegisterName(const std::string& name, 
                                      bool warning)
{
/// Register the given name
/// and give a warning if a duplicated name occurs
  
  // Check if the name is unique
  if (fAGDDNames.find(name) == fAGDDNames.end())
    fAGDDNames.insert(name);
  else 
    if (warning) {
      std::cerr << "+++ Warning +++: " << std::endl;
      std::cerr << "    Duplicated name has occured: \"" << name << "\"" 
                << " in geometry." << std::endl;
      std::cerr << "    Duplicated names are not allowed in AGDD." << std::endl;
    }
}  

//_____________________________________________________________________________
double XmlVGM::AGDDWriter::Round2(double number) const
{
/// Round the position elements to the numeric precision of the
/// convertor

  double precision = fNP;
  return ClhepVGM::Round(number*pow(10.,precision))/pow(10.,precision);
}

//_____________________________________________________________________________
bool  XmlVGM::AGDDWriter::IsIdentity(const VGM::ThreeVector& rotation) const
{
/// Return true if roatation is identity within the converter precision.

  VGM::ThreeVector roundedRotation(3);
  roundedRotation[0] = Round2(rotation[0]/ AngleUnit());
  roundedRotation[1] = Round2(rotation[1]/ AngleUnit());
  roundedRotation[2] = Round2(rotation[2]/ AngleUnit());

  if ( roundedRotation[0] == 0. && 
       roundedRotation[1] == 0. &&
       roundedRotation[2] == 0. )
       
    return true;
  else
    return false;
}               

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteBooleanSolid(
                              std::string volumeName, 
                              const VGM::IBooleanSolid* booleanSolid,
                              std::string mediumName)
{
/// Write Boolean solid
			      
  // Get constituent solids
  VGM::ISolid* solidA = booleanSolid->ConstituentSolidA();
  VGM::ISolid* solidB = booleanSolid->ConstituentSolidB();
  
  // Write constituent solids
  std::string nameA = volumeName + "_constA";
  std::string nameB = volumeName + "_constB";
  WriteSolid(nameA, solidA, mediumName); 
  WriteSolid(nameB, solidB, mediumName); 
  
  // Zero position
  VGM::ThreeVector position0(3);
  position0[0] = 0.0;
  position0[1] = 0.0;
  position0[2] = 0.0;

  // Get displacement
  VGM::Transform transform = booleanSolid->Displacement();
	
  // position
  VGM::ThreeVector position(3);
  position[0] = transform[VGM::kDx];
  position[1] = transform[VGM::kDy];
  position[2] = transform[VGM::kDz];
    
  // rotation
  VGM::ThreeVector rotation(3);
  rotation[0] = transform[VGM::kAngleX];
  rotation[1] = transform[VGM::kAngleY];
  rotation[2] = transform[VGM::kAngleZ];

  // Get boolean type
  VGM::BooleanType boolType = booleanSolid->BoolType();
  
  // compose element string template
  //
  std::string element1;
  std::string element3;
  switch (boolType) {
    case VGM::kIntersection:
      element1 = "<intersection name=\"";
      element3 = "</intersection>";
      break;
    case VGM::kSubtraction:
      element1 = "<subtraction name=\"";
      element3 = "</subtraction>";
      break;
    case VGM::kUnion:
      element1 = "<union name=\"";
      element3 = "</union>";
      break;
    case VGM::kUnknownBoolean:
      break;
  }    
  std::string element2 = "\" >";
  std::string indention = fIndention;
  
  // write element
  fOutFile << fIndention << element1 << volumeName  
           << element2   << std::endl;

  // write first constituent
  fIndention = fIndention + fkBasicIndention;
  WritePlacement(nameA, position0);

  // write second constituent
  if ( ClhepVGM::HasReflection(transform) ) 
    WritePlacementWithRotationAndReflection(nameB, position, rotation);
  else
    if (IsIdentity(rotation))
      WritePlacement(nameB, position);
    else 
      WritePlacementWithRotation(nameB, position, rotation);

  fIndention = indention;

  fOutFile << fIndention << element3 << std::endl << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteBox(
                              std::string volumeName, 
                              double hx, double hy, double hz,  
                              std::string mediumName)
{
/// Write box solid defined by parameters

  // get parameters
  double x = hx/LengthUnit()*2.;
  double y = hy/LengthUnit()*2.;
  double z = hz/LengthUnit()*2.;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<box    name=\"" + volumeName + quota;
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "X_Y_Z=\"";
  std::string element4 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl  
           << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << x << "; "
           << std::setw(fNW) << std::setprecision(fNP) << y << "; "
           << std::setw(fNW) << std::setprecision(fNP) << z 
	   << element4 << std::endl << std::endl;
}
 
//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteBox(
                              std::string volumeName, 
			      const VGM::IBox* box, 
                              std::string mediumName)
{
/// Write box solid

  WriteBox(volumeName, 
           box->XHalfLength(), box->YHalfLength(), box->ZHalfLength(),
	   mediumName); 
}
 
//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteTubs(
                              std::string volumeName, 
			      const VGM::ITubs* tubs, 
                              std::string mediumName)
{
/// Write tubs solid

  // get parameters
  double rmin = tubs->InnerRadius()/LengthUnit();
  double rmax = tubs->OuterRadius()/LengthUnit();
  double hz   = tubs->ZHalfLength()/LengthUnit()*2.;
  double sphi = tubs->StartPhi()/AngleUnit();
  double dphi = tubs->DeltaPhi()/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<tubs   name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "profile=\"";
  std::string element4 = "Rio_Z  =\"";
  std::string element5 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW)   << std::setprecision(fNP) << sphi << "; "
           << std::setw(fNW)   << std::setprecision(fNP) << dphi
	   << quota << std::endl 	   	   
	   << indention        << element4
           << std::setw(fNW) << std::setprecision(fNP) << rmin << "; "
           << std::setw(fNW) << std::setprecision(fNP) << rmax << "; "
           << std::setw(fNW) << std::setprecision(fNP) << hz 
	   << element5 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteCons(
                              std::string volumeName, 
			      const VGM::ICons* cons, 
                              std::string mediumName)
{
/// Write cons solid

  // get parameters
  double rmin1 = cons->InnerRadiusMinusZ()/LengthUnit();
  double rmax1 = cons->OuterRadiusMinusZ()/LengthUnit();
  double rmin2 = cons->InnerRadiusPlusZ()/LengthUnit();
  double rmax2 = cons->OuterRadiusPlusZ()/LengthUnit();
  double hz   = cons->ZHalfLength()/LengthUnit()*2.;
  double sphi = cons->StartPhi()/AngleUnit();
  double dphi = cons->DeltaPhi()/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<cons   name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "profile=\"";
  std::string element4 = "Rio1_Rio2_Z  =\"";
  std::string element5 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW)   << std::setprecision(fNP) << sphi << "; "
           << std::setw(fNW)   << std::setprecision(fNP) << dphi
	   << quota << std::endl 	   	   
	   << indention        << element4
           << std::setw(fNW) << std::setprecision(fNP) << rmin1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << rmin2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << rmax1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << rmax2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << hz 
	   << element5 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteTrd(
                              std::string volumeName, 
			      const VGM::ITrd* trd, 
                              std::string mediumName)
{
/// Write VGM::ITrd solid

  // get parameters
  double x1 = trd->XHalfLengthMinusZ()/LengthUnit()*2;
  double x2 = trd->XHalfLengthPlusZ() /LengthUnit()*2;
  double y1 = trd->YHalfLengthMinusZ()/LengthUnit()*2;
  double y2 = trd->YHalfLengthPlusZ()  /LengthUnit()*2;
  double hz = trd->ZHalfLength()/LengthUnit()*2;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<trd    name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "Xmp_Ymp_Z=\"";
  std::string element4 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << x1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << x2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << y1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << y2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << hz
	   << element4 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteTrap(
                              std::string volumeName, 
			      const VGM::ITrap* trap, 
                              std::string mediumName)
{
/// Write VGM::ITrap solid

  // get parameters
  double dz = trap->ZHalfLength()/LengthUnit()*2.;
  double theta = trap->Theta()/AngleUnit();
  double phi   = trap->Phi()/AngleUnit();
  double y1 = trap->YHalfLengthMinusZ()/LengthUnit()*2.;
  double x1 = trap->XHalfLengthMinusZMinusY()/LengthUnit()*2.;
  double x2 = trap->XHalfLengthMinusZPlusY()/LengthUnit()*2.;
  double alpha1 = trap->AlphaMinusZ()/AngleUnit();
  double y2 = trap->YHalfLengthPlusZ()/LengthUnit()*2.;
  double x3 = trap->XHalfLengthPlusZMinusY()/LengthUnit()*2.;
  double x4 = trap->XHalfLengthPlusZPlusY()/LengthUnit()*2.;
  double alpha2 = trap->AlphaPlusZ()/AngleUnit();

  // ordering of parameters in XML element
  // Xmumdpupd_Ymp_Z: 2x2 2x1 2x4 2x3 2y2 2y1 2dz
  // inclination: atan(symAxis.x/symAxis.z), atan(symAxis.y/symAxis.z)
  // declination: alpha1, alpha2

  // get inclination angles
  double thetaCphi = tan(theta*deg)*cos(phi*deg);
  double thetaSphi = tan(theta*deg)*sin(phi*deg);
  double cosTheta = 1.0/sqrt(1+thetaCphi*thetaCphi + thetaSphi*thetaSphi) ;

  CLHEP::Hep3Vector symAxis(thetaCphi*cosTheta, thetaSphi*cosTheta, cosTheta);
  double inc1 = atan(symAxis.x()/symAxis.z())/deg;
  double inc2 = atan(symAxis.y()/symAxis.z())/deg;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<trap   name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "Xmumdpupd_Ymp_Z=\"";
  std::string element4 = "inclination=\""; 
  std::string element5 = "declination=\""; 
  std::string element6 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;

  // write element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << x2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << x1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << x4 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << x3 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << y2 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << y1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << dz 
	   << quota << std::endl
           << indention       << element4
           << std::setw(fNW) << std::setprecision(fNP) << inc1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << inc2 
	   << quota << std::endl
	   << indention       << element5
           << std::setw(fNW) << std::setprecision(fNP) << alpha1 << "; "
           << std::setw(fNW) << std::setprecision(fNP) << alpha2 
	   << element6 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePara(     
                              std::string volumeName, 
			      const VGM::IPara* para, 
                              std::string mediumName)
{
/// Write VGM::IPara solid

  // get parameters
  double dx = para->XHalfLength()/LengthUnit()*2.;
  double dy = para->YHalfLength()/LengthUnit()*2.;
  double dz = para->ZHalfLength()/LengthUnit()*2.;
  double alpha = para->Alpha()/AngleUnit();
  double theta = para->Theta()/AngleUnit();
  double phi   = para->Phi()/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<para   name=\"" + volumeName + quota;
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "X_Y_Z=\"";
  std::string element4 = "alpha=\"";
  std::string element5 = "theta=\"";
  std::string element6 = "phi=  \"";
  std::string element7 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl  
           << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << dx << "; "
           << std::setw(fNW) << std::setprecision(fNP) << dy << "; "
           << std::setw(fNW) << std::setprecision(fNP) << dz 
	   << quota << std::endl
	   << indention        << element4
           << std::setw(fNW) << std::setprecision(fNP) << alpha 
	   << quota << std::endl
	   << indention        << element5
           << std::setw(fNW) << std::setprecision(fNP) << theta
	   << quota << std::endl
	   << indention        << element6
           << std::setw(fNW) << std::setprecision(fNP) << phi 	   
	   << element7 << std::endl << std::endl;
}
 
//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePolycone(
                              std::string volumeName, 
                              const VGM::IPolycone* polycone, 
                              std::string mediumName)
{
/// Write VGM::IPolycone solid

  // get profile parameters
  double sphi = polycone->StartPhi()/AngleUnit();
  double dphi = polycone->DeltaPhi()/AngleUnit();
  
  // get polycone Z planes parameters
  int nofZPlanes = polycone->NofZPlanes();
  double* rminArray = polycone->InnerRadiusValues();
  double* rmaxArray = polycone->OuterRadiusValues();
  double* zArray = polycone->ZValues();
    
  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<pcon   name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "profile=\"";
  std::string element4 = "\" >";
  std::string element5 = "<polyplane Rio_Z=\"";
  std::string element6 = "\" />";
  std::string element7 = "</pcon>";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write pcon element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << sphi << "; "
           << std::setw(fNW) << std::setprecision(fNP) << dphi
	   << element4 << std::endl;

  // write polyplane elements
  for (int i=0; i<nofZPlanes; i++) {
  
    // set units
    double rmin = rminArray[i]/LengthUnit();
    double rmax = rmaxArray[i]/LengthUnit();
    double z    = zArray[i]/LengthUnit();

    fOutFile << indention << element5
             << std::setw(fNW) << std::setprecision(fNP) << rmin << "; "
             << std::setw(fNW) << std::setprecision(fNP) << rmax << "; " 
             << std::setw(fNW) << std::setprecision(fNP) << z 
	     << element6
	     << std::endl;
  }
  
  // close pcon element
  fOutFile << fkBasicIndention
           << element7 << std::endl << std::endl;  	     
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePolyhedra(
                              std::string volumeName, 
                              const VGM::IPolyhedra* polyhedra, 
                              std::string mediumName)
{
/// Write VGM::IPolyhedra solid

  // get parameters
  int nofSides = polyhedra->NofSides();
  double sphi = polyhedra->StartPhi()/AngleUnit();
  double dphi = polyhedra->DeltaPhi()/AngleUnit();

  // get polyhedra Z planes parameters
  int nofZPlanes = polyhedra->NofZPlanes();
  double* rminArray = polyhedra->InnerRadiusValues();
  double* rmaxArray = polyhedra->OuterRadiusValues();
  double* zArray = polyhedra->ZValues();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<phedra name=\"" + volumeName + quota; 
  std::string element2 = "medium=\"" + mediumName + quota;
  std::string element3 = "profile=\"";
  std::string element4 = "sides =\"";
  std::string element5 = "Ris=\"";
  std::string element6 = "Ros=\"";
  std::string element7 = "Zs =\"";
  std::string element8 = "\" />";
  std::string indention = fkBasicIndention + fkBasicIndention;
  
  // write element
  fOutFile << fkBasicIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        << element3
           << std::setw(fNW) << std::setprecision(fNP) << sphi << "; "
           << std::setw(fNW) << std::setprecision(fNP) << dphi
	   << quota << std::endl
	   << indention       << element4 
	   << nofSides
	   << quota << std::endl;

  fOutFile << indention << element5;
  int i;
  for (i=0; i<nofZPlanes; i++) {  
    // set units    
    double rmin = rminArray[i]/LengthUnit();
    if (i>0) fOutFile << "; ";
    fOutFile << std::setw(fNW) << std::setprecision(fNP) << rmin;
  };
  fOutFile << quota << std::endl;

  fOutFile << indention << element6;
  for (i=0; i<nofZPlanes; i++) {  
    // set units
    double rmax = rmaxArray[i]/LengthUnit();
    if (i>0) fOutFile << "; ";
    fOutFile << std::setw(fNW) << std::setprecision(fNP) << rmax;
  };
  fOutFile << quota << std::endl;

  fOutFile << indention << element7;
  for (i=0; i<nofZPlanes; i++) {  
    // set units
    double z = zArray[i]/LengthUnit();
    if (i>0) fOutFile << "; ";
    fOutFile << std::setw(fNW) << std::setprecision(fNP) << z;
  };
  fOutFile << element8 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteNotSupportedSolid(
                              std::string name, 
                              std::string mediumName)
{				   
/// Write a comment line with a warning
/// and then write a box element instead 

  // Compose comment
  std::string element1 = "<!-- !!! unsupported shape  !!!  name= \""; 
  std::string element2 = "\" -->";
  std::string element3 = "<!-- dummy box is written instead  -->"; 
  
  // Write element with warning
  fOutFile << fIndention << element1 << name << element2 << std::endl
	   << fIndention << element3 << std::endl;
	   
  // Write dummy box element
  WriteBox(name, 1.0, 1.0, 1.0, mediumName); 
}  	   

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacementWithRotation(
                              std::string volumeName, 
			      const VGM::ThreeVector& position, 
			      const VGM::ThreeVector& rotation)
{
/// Write position with a rotation with a given volume name 

  // get parameters  
  double x = position[0]/LengthUnit();
  double y = position[1]/LengthUnit();
  double z = position[2]/LengthUnit();
  
  // convert object rotation to frame rotation
  CLHEP::HepRotation hepRotation;
  hepRotation.rotateX(rotation[0]*deg);
  hepRotation.rotateY(rotation[1]*deg);
  hepRotation.rotateZ(rotation[2]*deg);
 
  double xx = hepRotation.xx();
  double xy = hepRotation.xy();
  double xz = hepRotation.xz();
  double yx = hepRotation.yx();
  double yy = hepRotation.yy();
  double yz = hepRotation.yz();
  double zx = hepRotation.zx();
  double zy = hepRotation.zy();
  double zz = hepRotation.zz();
  
  // compose element string template
  std::string quota = "\"\n";
  std::string element1 = "<transform    pos=\"";
  std::string element2 = "           matrix=\"";
  std::string element3 = "                   ";
  std::string element4 = "\"> <volume name=\"";
  std::string element5 = "\"/>";
  std::string element6 = "</transform>";
  
  // write element
  fOutFile << fIndention
           << element1;

  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, x, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, y, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, z, quota);	   

  fOutFile << fIndention << element2; 
	   
  SmartPut(fOutFile, 8, 5, 0, xx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, xy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, xz, "; ");	   

  fOutFile << std::endl
           << fIndention << element3;

  SmartPut(fOutFile, 8, 5, 0, yx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, yy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, yz, "; ");	   

  fOutFile << std::endl
	   << fIndention << element3;

  SmartPut(fOutFile, 8, 5, 0, zx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, zy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, zz, "");	   

  fOutFile << element4 << volumeName << element5 << std::endl
           << fIndention << element6 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacementWithRotationAndReflection(
                              std::string volumeName, 
			      const VGM::ThreeVector& position, 
			      const VGM::ThreeVector& rotation)
{
// Write position with rotation and reflection with a given volume name 

  // get parameters
  //
  HepGeom::Translate3D translate3D(position[0], position[1], position[2]);

  // rotation
  CLHEP::HepRotation hepRotation;
  hepRotation.rotateX(rotation[0]*deg);
  hepRotation.rotateY(rotation[1]*deg);
  hepRotation.rotateZ(rotation[2]*deg);
  HepGeom::Rotate3D rotate3D(hepRotation);

  HepGeom::ScaleZ3D scale3D(-1.0);

  HepGeom::Transform3D transform3D = translate3D * rotate3D * scale3D;

  CLHEP::Hep3Vector translation = transform3D.getTranslation();
  double x = translation.x()/LengthUnit();
  double y = translation.y()/LengthUnit();
  double z = translation.z()/LengthUnit();

  double xx = transform3D(0,0);
  double xy = transform3D(0,1);
  double xz = transform3D(0,2);
  double yx = transform3D(1,0);
  double yy = transform3D(1,1);
  double yz = transform3D(1,2);
  double zx = transform3D(2,0);
  double zy = transform3D(2,1);
  double zz = transform3D(2,2);
  
  // compose element string template
  std::string quota = "\"\n";
  std::string element1 = "<transform    pos=\"";
  std::string element2 = "           matrix=\"";
  std::string element3 = "                   ";
  std::string element4 = "\"> <volume name=\"";
  std::string element5 = "\"/>";
  std::string element6 = "</transform>";
  
  // write element
  fOutFile << fIndention
           << element1;

  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, x, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, y, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, z, quota);	   

  fOutFile << fIndention << element2; 
	   
  SmartPut(fOutFile, 8, 5, 0, xx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, xy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, xz, "; ");	   

  fOutFile << std::endl
           << fIndention << element3;

  SmartPut(fOutFile, 8, 5, 0, yx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, yy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, yz, "; ");	   

  fOutFile << std::endl
	   << fIndention << element3;

  SmartPut(fOutFile, 8, 5, 0, zx, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, zy, "; ");	   
  SmartPut(fOutFile, 8, 5, 0, zz, "");	   

  fOutFile << element4 << volumeName << element5 << std::endl
           << fIndention << element6 << std::endl;

}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteMultiplePlacement(
                              const std::string& volumeName,
                              VGM::Axis axis, 
			      int nofReplicas,
			      double width, 
			      double offset)			       
			     
{
// Write multiple position

  std::string tag;
  switch (axis) {
    case VGM::kXAxis: tag = "X"; break;
    case VGM::kYAxis: tag = "Y"; break;
    case VGM::kZAxis: tag = "Z"; break;
    case VGM::kRho:   tag = "R"; break;
    case VGM::kPhi:   tag = "Phi"; break;
    case VGM::kRadial3D:    tag = "R3D";       break; // CHECK
    case VGM::kSphTheta:    tag = "Undefined"; break; // CHECK
    case VGM::kUnknownAxis: tag = "Undefined"; break;
  }  

  // set units
  double value0 = - width*(nofReplicas-1)*0.5 + offset;
  double dValue = width;
  if (axis != VGM::kPhi) {
    value0 = value0/LengthUnit();
    dValue = dValue/LengthUnit();
  }  
  else  {
    value0 = value0/AngleUnit();
    dValue = dValue/AngleUnit();
  }  
  
  // set tag and attributes names
  std::string a0 = "mpos"; a0 = a0 + tag;
  std::string a1 = tag;  a1 = a1 + "0";
  std::string a2 = "d";  a2 = a2 + tag; 

  // compose element string template
  std::string element1 = "<" + a0 + " ncopy=\"";
  std::string element2 = "\"  " + a1 + "=\"";
  std::string element3 = "\"  " + a2 + "=\"";
  std::string element4 = "\"> <volume name=\"";
  std::string element5 = "\"/>";
  std::string element6 = "</" + a0 + ">";
  
  // write element
  fOutFile << fIndention
           << element1
           << std::setw(fNW+1-fNP) << nofReplicas
	   << element2
           << std::setw(fNW+1) << std::setprecision(fNP) << value0
	   << element3	   
           << std::setw(fNW+1) << std::setprecision(fNP) << dValue
	   << element4 << volumeName << element5 << std::endl
           << fIndention << element6 << std::endl;
}  


//
// public methods
//

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenFile(std::string filePath)
{ 
// Open output file

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
void XmlVGM::AGDDWriter::OpenDocument()
{
// Write document opening.
// Could be made customizable in future.

  // Opening xml document
  fOutFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
	   << std::endl
	   << "<AGDD DTD_version = \"v7\"" << std::endl
           << "      xmlns:xi=\"http://www.w3.org/2001/XInclude\">" << std::endl
	   << std::endl
           << "<xi:include href=\"StandardColors.agdd\"/>" << std::endl
           << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenSection(const std::string& topVolume)
{
// Write section opening.
// Could be made customizable in future.

  // Define section element
  
  std::string element1 = "<section DTD_version = \"";
  std::string element2 = "         name        = \"";
  std::string element3 = "         version     = \"";
  std::string element4 = "         date        = \"";
  std::string element5 = "         author      = \"";
  std::string element6 = "         top_volume  = \"";
  std::string element7 = "  >";
  std::string quota = "\"";   
  
  std::string version = fVersion;
  if (version == "Undefined") {
    version = "$Id$";
    // strip $ from the string
    version = version.substr(1,version.size()-2);
  }  

  std::string name = topVolume;
  name.append(fgkCompNameExtension);
  
  std::string date = Date();

  // write element
  fOutFile << element1 << fDtdVersion << quota << std::endl
           << element2 << topVolume   << quota << std::endl
           << element3 << version     << quota << std::endl
           << element4 << date       << quota << std::endl
           << element5 << fAuthor     << quota << std::endl
           << element6 << name        << quota
           << element7 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenMaterials()
{
// Write materials opening.
			 
  std::string element1 = "<materials  version = \"";
  std::string element2 = "            date    = \"";
  std::string element3 = "            author  = \"";
  std::string element4 = "            DTD_version=\"";
  std::string element5 = "  >";
  std::string quota = "\"";   
  
  std::string version = fVersion;
  if (version == "Undefined") {
    version = "$Id$";
    // strip $ from the string
    version = version.substr(1,version.size()-2);
  }  

  std::string date = Date();

  // write element
  fOutFile << element1 << version << quota << std::endl
           << element2 << date    << quota << std::endl
           << element3 << fAuthor  << quota << std::endl
           << element4 << fDtdVersion << quota
           << element5 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenMedia()
{
// Write materials opening.
			 
  std::string element1 = "<media  version = \"";
  std::string element2 = "        date    = \"";
  std::string element3 = "        author  = \"";
  std::string element4 = "        DTD_version=\"";
  std::string element5 = "  >";
  std::string quota = "\"";   
  
  std::string version = fVersion;
  if (version == "Undefined") {
    version = "$Id$";
    // strip $ from the string
    version = version.substr(1,version.size()-2);
  }  

  std::string date = Date();

  // write element
  fOutFile << element1 << version << quota << std::endl
           << element2 << date    << quota << std::endl
           << element3 << fAuthor  << quota << std::endl
           << element4 << fDtdVersion << quota
           << element5 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenComposition(
                                  const std::string& name,
                                  const std::string& /*materialName*/)
{
// Write composition opening.

  std::string compName = name;
  compName.append(fgkCompNameExtension);
			 
  std::string element = "<composition name=\"";
  element.append(compName);
  element.append("\">");

  // write element
  fOutFile << fIndention
           << element
	   << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseFile()
{ 
// Close output file.

  fOutFile.close(); 
}

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseDocument()
{
// Write document closing

  // define element
  std::string element = "</AGDD>";

  // write element
  fOutFile << element << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseSection(const std::string& /*topVolume*/)
{
// Write section closing

  // define element
  std::string element = "</section>";

  // write element
  fOutFile << element 
           << std::endl 
	   << std::endl;           
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseMaterials()
{
// Write materials closing


  // define element
  std::string element = "</materials>";

  // write element
  fOutFile << element
	   << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseMedia()
{
// Write materials closing


  // define element
  std::string element = "</media>";

  // write element
  fOutFile << element
	   << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CloseComposition()
{
// Write composition closing

  // decrease indention
  DecreaseIndention();

  // define element
  std::string element = "</composition>";

  // write element
  fOutFile << fIndention
           << element
	   << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteIsotope(const VGM::IIsotope* isotope) 
{
// Write VGM::IElement 

  // Get parameters
  int    theZ = isotope->Z();
  int    theN = isotope->N();
  int    theA = isotope->N();
  //double theA = isotope->A()/ AtomicWeightUnit();
      /// !! Should not be int here
  
  // Compose name as name_N
  std::string name = IsotopeName(isotope);
  RegisterName(name);  

  // AGDD does not allow N=0
  // Let's put =1 in this case
  if (theN == 0) theN = 1;

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<isotope  name=\"";  
  std::string element2 = "z=\"";
  std::string element3 = "n=\"";
  std::string element4 = "a=\"";
  std::string element5 = "\"/>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention << element1 << name << quota1;
  for ( int i=0; i< 8 - int(name.size()); i++ ) fOutFile << " ";
  
  fOutFile << element2 << std::setw(3) << theZ << quota2;
  //SmartPut(fOutFile, fNW, fNP, theZ, quota2);

  fOutFile << element3 << std::setw(3) << theN << quota2;
  //SmartPut(fOutFile, fNW, fNP, theN, quota2);

  fOutFile << element4 << std::setw(3) << theA << element5;
  // SmartPut(fOutFile, fNW, fNP, theA, element5);
  fOutFile << std::endl; 
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteElement(const VGM::IElement* element) 
{
// Write VGM::IElement 

  std::string symbol = ElementSymbol(element);
  RegisterName(symbol);  
    
  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<element  symbol=\"";
  std::string element2 = "\">";
  std::string element6 = "</element>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element name
  fOutFile << fIndention << element1 << symbol << element2 << std::endl;

  // Get parameters
  if ( element->NofIsotopes() > 0 ) {
    for ( int i=0; i<element->NofIsotopes(); i++ ) {
      VGM::IIsotope* isotope = element->Isotope(i);
      std::string name = IsotopeName(isotope);
      double natoms = element->RelAbundance(i);
      int natomsInt = (int)(Round2(natoms * 100));
  
      std::string element3 = "<addisotope name=\"";
      std::string element4 = "natoms=\"";
      std::string element5 = "\" />";
  
      fOutFile << indention << element3 << name << quota2;
      fOutFile << element4;
      //SmartPut(fOutFile, fNW-2, fNP, natoms, element5);
      fOutFile << std::setw(3) << natomsInt << element5;
      fOutFile << std::endl; 
    }  
  }
  else { 
    double theZ = element->Z();
    int    theN = (int) ClhepVGM::Round(element->N());
    double theA = element->A()/ AtomicWeightUnit();
  
    // AGDD does not allow N=0
    // Let's put =1 in this case
    if (theN == 0) theN = 1;

    std::string element3 = "<atom zeff=\"";
    std::string element4 = "aweight=\"";
    std::string element5 = "\" />";
  
    fOutFile << indention << element3;
    SmartPut(fOutFile, fNW-2, fNP, 0, theZ, quota2);

    fOutFile << element4;
    SmartPut(fOutFile, fNW-2, fNP, 0, theA, element5);
    fOutFile << std::endl; 
  }  

  fOutFile << fIndention << element6 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteMaterial(const VGM::IMaterial* material) 
{
// Write material. 

  std::string materialName 
    = UpdateName(material->Name(), fgkMaterialNameExtension);
  RegisterName(materialName);

  // Get parameters
  double density = material->Density()/ MassDensityUnit();
 
  // Compose material string template
  std::string quota = "\"  ";
  std::string element1 = "<material  name=\"";
  std::string element2 = "density=\"";
  std::string element3 = "\">"; 
  std::string element4 = "<addelement name=\""; 
  std::string element5 = "natoms=\""; 
  std::string element6 = "\"/>"; 
  std::string element7 = "</material>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention;
  fOutFile  << element1 << materialName << quota;
  
  fOutFile  << element2;
  SmartPut(fOutFile, fNW+1, fNP, 0, density, element3);
  fOutFile << std::endl; 
  
  for (int i=0; i<int(material->NofElements()); i++) {
    double atomCount = material->AtomCount(i);
    std::string elementSymbol= ElementSymbol(material->Element(i));  

    fOutFile << indention << element4 << elementSymbol << quota;
    fOutFile << element5;
    SmartPut(fOutFile, fNW, fNP, 0, atomCount, element6);
    fOutFile << std::endl;
  }  

  fOutFile << fIndention << element7 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteMedium(const VGM::IMedium* medium) 
{
// Write medium. 

  std::string mediumName = UpdateName(medium->Name());
  RegisterName(mediumName);

  // Get parameters
  std::string materialName 
    = UpdateName(medium->Material()->Name(), fgkMaterialNameExtension);
 
  // Compose material string template
  std::string quota = "\"  ";
  std::string element1 = "<medium  name=\"";
  std::string element2 = "material=\"";
  std::string element3 = "color=\"random\"";
  std::string element4 = "sensitive=\"true\"";
  std::string element5 = "parameters=\"";
  std::string element6 = ";  "; 
  std::string element7 = "\"/>"; 
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention;
  fOutFile  << element1 << mediumName << quota << std::endl;
  
  fOutFile << indention << element2 << materialName << quota << std::endl;
  fOutFile << indention << element3 << std::endl;
  fOutFile << indention << element4 << std::endl;
  fOutFile << indention << element5;
  
  for (int i=0; i<medium->NofParameters(); i++) {
    double parameter = medium->Parameter(i);
    std::string separator = element6;
    if ( i == medium->NofParameters()-1 ) separator = element7;
    SmartPut(fOutFile, fNW, fNP, 0, parameter, separator);
  }  
  fOutFile  << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteMedium(const VGM::IMaterial* material) 
{
// Write medium element from material. 

  std::string mediumName = UpdateName(material->Name());
  RegisterName(mediumName);

  // Get parameters
  std::string materialName 
    = UpdateName(material->Name(), fgkMaterialNameExtension);
 
  // Compose material string template
  std::string quota = "\"  ";
  std::string element1 = "<medium  name=\"";
  std::string element2 = "material=\"";
  std::string element3 = "color=\"random\"";
  std::string element4 = "sensitive=\"true\"";
  std::string element5 = "parameters=\"\"/>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention;
  fOutFile  << element1 << mediumName << quota << std::endl;
  
  fOutFile << indention << element2 << materialName << quota << std::endl;
  fOutFile << indention << element3 << std::endl;
  fOutFile << indention << element4 << std::endl;
  fOutFile << indention << element5 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteSolid(
                              std::string volumeName, 
			      const VGM::ISolid* solid, 
                              std::string mediumName) 
{
// Get VGM::ISolid concrete type and calls writing function

  VGM::SolidType solidType = solid->Type();

  if (solidType == VGM::kBox) { 
    const VGM::IBox* box = dynamic_cast<const VGM::IBox*>(solid); 
    WriteBox(volumeName, box, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kCons) { 
    const VGM::ICons* cons = dynamic_cast<const VGM::ICons*>(solid); 
    WriteCons(volumeName, cons, UpdateName(mediumName)); 
    return;   
  }
/*
  else if (solidType == VGM::kEltu) { 
    const VGM::IEllipticalTube* eltu 
      = dynamic_cast<const VGM::IEllipticalTube*>(solid); 
    WriteEllipticalTube(solidName, eltu); 
    return;   
  }
*/
  else if (solidType == VGM::kPara) { 
    const VGM::IPara* para = dynamic_cast<const VGM::IPara*>(solid); 
    WritePara(volumeName, para, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kPolycone) { 
    const VGM::IPolycone* polycone = dynamic_cast<const VGM::IPolycone*>(solid); 
    WritePolycone(volumeName, polycone, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kPolyhedra) { 
    const VGM::IPolyhedra* polyhedra = dynamic_cast<const VGM::IPolyhedra*>(solid); 
    WritePolyhedra(volumeName, polyhedra, UpdateName(mediumName)); 
    return;   
  }
/*
  else if (solidType == VGM::kSphere) { 
    const VGM::ISphere* sphere = dynamic_cast<const VGM::ISphere*>(solid); 
    WriteSphere(volumeName, sphere, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kTorus) { 
    const VGM::ITorus* torus = dynamic_cast<const VGM::ITorus*>(solid); 
    WriteTorus(volumeName, torus, UpdateName(mediumName)); 
    return;   
  }
*/
  else if (solidType == VGM::kTrap) { 
    const VGM::ITrap* trap = dynamic_cast<const VGM::ITrap*>(solid); 
    WriteTrap(volumeName, trap, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kTrd) { 
    const VGM::ITrd* trd = dynamic_cast<const VGM::ITrd*>(solid); 
    WriteTrd(volumeName, trd, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kTubs) { 
    const VGM::ITubs* tubs = dynamic_cast<const VGM::ITubs*>(solid); 
    WriteTubs(volumeName, tubs, UpdateName(mediumName)); 
    return;   
  }
  else if (solidType == VGM::kBoolean) { 
    const VGM::IBooleanSolid* boolean = dynamic_cast<const VGM::IBooleanSolid*>(solid);
    WriteBooleanSolid(volumeName, boolean, UpdateName(mediumName)); 
    return;   
  }

  // Not supported solid
  WriteNotSupportedSolid(volumeName, UpdateName(mediumName));
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacement(
                              const std::string& volumeName, 
                              const VGM::ThreeVector& position) 
{
/// Write position without rotation with a given volume name 

  // get parameters
  double x = position[0]/LengthUnit();
  double y = position[1]/LengthUnit();
  double z = position[2]/LengthUnit();

  // compose element string template
  std::string element1 = "<posXYZ   X_Y_Z=\"";
  std::string element2 = "\"> <volume name=\"";
  std::string element3 = "\"/>"; 
  std::string element4 = "</posXYZ>";
  
  // write element
  fOutFile << fIndention << element1;

  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, x, "; ");
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, y, "; ");
  SmartPut(fOutFile, fNW+1, fNP, fgkCarTolerance, z, "");

  fOutFile << element2  << volumeName << element3 << std::endl 
           << fIndention << element4 << std::endl;
	   
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacement(
                              const VGM::IPlacement& placement)
{			      
  // get parameters
  std::string volumeName = placement.Volume()->Name();
  std::string compName = volumeName;
  compName.append(fgkCompNameExtension);    
  int nd = placement.Volume()->NofDaughters();

  VGM::PlacementType placementType = placement.Type();

  if (placementType == VGM::kSimplePlacement) {
    
    VGM::Transform transform = placement.Transformation();
    
    // If boolean solid that have to be reflected
    // set reflection to the transformation
    VGM::IBooleanSolid* booleanSolid 
      = dynamic_cast<VGM::IBooleanSolid*>(placement.Volume()->Solid());
    if ( booleanSolid && booleanSolid->ToBeReflected() )
       transform[VGM::kReflZ] = 1;

    // position
    VGM::ThreeVector position(3);
    position[0] = transform[VGM::kDx];
    position[1] = transform[VGM::kDy];
    position[2] = transform[VGM::kDz];
      
    // rotation
    VGM::ThreeVector rotation(3);
    rotation[0] = transform[VGM::kAngleX];
    rotation[1] = transform[VGM::kAngleY];
    rotation[2] = transform[VGM::kAngleZ];

    if (ClhepVGM::HasReflection(transform)) {
      WritePlacementWithRotationAndReflection(
	         volumeName, position, rotation);
		 
      if (nd>0) 
    	 WritePlacementWithRotationAndReflection(
	                    compName, position, rotation);
    }	  
    else {
      if (IsIdentity(rotation)) {
     	WritePlacement(volumeName, position);
        // if volume is not leaf node place its logical volume
        if (nd>0) 
    	  WritePlacement(compName, position);
      }
      else {  
  	WritePlacementWithRotation(
	                   volumeName, position, rotation);
        if (nd>0) 
          WritePlacementWithRotation(
	                      compName, position, rotation);
      }
    }	
  }
  else if (placementType == VGM::kMultiplePlacement) {
      
    // get parameters
    VGM::Axis axis;
    int nReplicas;
    double width;
    double offset;
    double halfGap; // not supported
    placement.MultiplePlacementData(axis, nReplicas, width, offset, halfGap);

    if ( halfGap != 0. ) {
      std::cerr << "+++ Warning  +++" << std::endl;
      std::cerr << "  XmlVGM::Writer::WritePlacement: " << std::endl;
      std::cerr << "  Multiple placement with a half gap is not supported. " << std::endl;
      std::cerr << "  The half gap parameter will be ignored. " << std::endl;
    }

    // write multiple position
    WriteMultiplePlacement(volumeName, axis, nReplicas, width, offset);

    // if volume is not leaf node place its logical volume
    if (nd>0) 
     WriteMultiplePlacement(compName, axis, nReplicas, width, offset);
  }
  else {
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "  XmlVGM::Writer::WritePlacement: " << std::endl;
    std::cerr << "  Unknown placement type. " << std::endl;
    std::cerr << "  Volume \"" << placement.Name() 
              << "\" was not converted." << std::endl;  
  }
}

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteEmptyLine()
{
// Write empty line

  fOutFile << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::IncreaseIndention()
{
// Increase indention

  fIndention.append(fkBasicIndention);	   
}

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::DecreaseIndention()
{
// Decrease indention
  
  fIndention.replace(fIndention.find(fkBasicIndention), 3 , "");
}
