// $Id$
//
// Class AGDDWriter
// ---------------------
// The implementation of the interface for the XML convertor that
// converts VGM geometry objects to XML defined by AGDD.dtd
// (ATLAS Generic Detector Description)
//
// Author: I. Hrivnacova, 16.01.2004 

#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Units/SystemOfUnits.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>

#include <VGM/materials/IMaterial.h>
#include <VGM/volumes/IPlacement.h>
#include <VGM/volumes/IVolume.h>
#include <VGM/solids/ISolid.h>
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

const int         XmlVGM::AGDDWriter::fgkMaxVolumeNameLength   = 20;
const int         XmlVGM::AGDDWriter::fgkMaxMaterialNameLength = 20;
const int         XmlVGM::AGDDWriter::fgkDefaultNumWidth       = 7;
const int         XmlVGM::AGDDWriter::fgkDefaultNumPrecision   = 4;
const std::string XmlVGM::AGDDWriter::fgkCompNameExtension     = "_comp";

//_____________________________________________________________________________
XmlVGM::AGDDWriter::AGDDWriter(const std::string& version,
		               const std::string& date,
                               const std::string& author,
			       const std::string dtdVersion) 
  : IWriter(),
    fOutFile(),
    fVersion(version),
    fDate(date),
    fAuthor(author),
    fDtdVersion(dtdVersion),
    fkBasicIndention("   "),
    fIndention(fkBasicIndention),
    fNW(fgkDefaultNumWidth),
    fNP(fgkDefaultNumPrecision)
{
/// Standard constructor
/// \param version AGDD file version
/// \param date    AGDD file generation date
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
void XmlVGM::AGDDWriter::Append(std::string& s, int a) const
{
/// Append number to string

  std::ostringstream tmpStream;
  tmpStream << a;  
  s.append(tmpStream.str());
}

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CutName(std::string& name) const
{
/// Removes spaces after the name if present

  int i = name.length();
  while (name[--i] == ' ') name = std::string(name,0,i);
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::CutName(std::string& name, int size) const
{
// Cut name to given size

  if (int(name.length()) > size) name = std::string(name, 0, size);
}  

//_____________________________________________________________________________
std::ostream& 
XmlVGM::AGDDWriter::SmartPut(std::ostream& out, 
                             int size, int precision,
                             double number, 
		             const std::string& separator) const
{
/// Help function to supress - sign in case the number == 0
/// within the given precision

  if ( round(number*pow(10.,precision))/pow(10.,precision) == 0.0) {
    number = 0.;
  }  
  
  out << std::setw(size) << std::setprecision(precision) 
      << number << separator;
  
  return out;
}

//_____________________________________________________________________________
double XmlVGM::AGDDWriter::Round(double number) const
{
/// Round the position elements to the numeric precision of the
/// convertor

  double precision = fNP;
  return round(number*pow(10.,precision))/pow(10.,precision);
}

//_____________________________________________________________________________
bool  XmlVGM::AGDDWriter::IsIdentity(const ThreeVector& rotation) const
{
/// Return true if roatation is identity within the converter precision.

  ThreeVector roundedRotation(3);
  roundedRotation[0] = Round(rotation[0]/ AngleUnit());
  roundedRotation[1] = Round(rotation[1]/ AngleUnit());
  roundedRotation[2] = Round(rotation[2]/ AngleUnit());

  if ( roundedRotation[0] == 0. && 
       roundedRotation[1] == 0. &&
       roundedRotation[2] == 0. )
       
    return true;
  else
    return false;
}               


//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteBox(
                              std::string volumeName, 
                              double hx, double hy, double hz,  
                              std::string materialName)
{
/// Write box solid defined by parameters

  // get parameters
  double x = hx/LengthUnit()*2.;
  double y = hy/LengthUnit()*2.;
  double z = hz/LengthUnit()*2.;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<box    name=\"" + volumeName + quota;
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
{
/// Write box solid

  WriteBox(volumeName, 
           box->XHalfLength(), box->YHalfLength(), box->ZHalfLength(),
	   materialName); 
}
 
//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteTubs(
                              std::string volumeName, 
			      const VGM::ITubs* tubs, 
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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

  Hep3Vector symAxis(thetaCphi*cosTheta, thetaSphi*cosTheta, cosTheta);
  double inc1 = atan(symAxis.x()/symAxis.z())/deg;
  double inc2 = atan(symAxis.y()/symAxis.z())/deg;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<trap   name=\"" + volumeName + quota; 
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  std::string element2 = "material=\"" + materialName + quota;
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
                              std::string materialName)
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
  WriteBox(name, 1.0, 1.0, 1.0, materialName); 
}  	   

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacementWithRotation(
                              std::string volumeName, 
			      const ThreeVector& position, 
			      const ThreeVector& rotation)
{
/// Write position with a rotation with a given volume name 

  // get parameters  
  double x = position[0]/LengthUnit();
  double y = position[1]/LengthUnit();
  double z = position[2]/LengthUnit();
  
  // convert object rotation to frame rotation
  HepRotation hepRotation;
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

  SmartPut(fOutFile, fNW+1, fNP, x, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, y, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, z, quota);	   

  fOutFile << fIndention << element2; 
	   
  SmartPut(fOutFile, 8, 5, xx, "; ");	   
  SmartPut(fOutFile, 8, 5, xy, "; ");	   
  SmartPut(fOutFile, 8, 5, xz, "; ");	   

  fOutFile << std::endl
           << fIndention << element3;

  SmartPut(fOutFile, 8, 5, yx, "; ");	   
  SmartPut(fOutFile, 8, 5, yy, "; ");	   
  SmartPut(fOutFile, 8, 5, yz, "; ");	   

  fOutFile << std::endl
	   << fIndention << element3;

  SmartPut(fOutFile, 8, 5, zx, "; ");	   
  SmartPut(fOutFile, 8, 5, zy, "; ");	   
  SmartPut(fOutFile, 8, 5, zz, "");	   

  fOutFile << element4 << volumeName << element5 << std::endl
           << fIndention << element6 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacementWithRotationAndReflection(
                              std::string volumeName, 
			      const ThreeVector& position, 
			      const ThreeVector& rotation)
{
// Write position with rotation and reflection with a given volume name 

  // get parameters
  //
  HepTranslate3D translate3D(position[0], position[1], position[2]);

  // rotation
  HepRotation hepRotation;
  hepRotation.rotateX(rotation[0]*deg);
  hepRotation.rotateY(rotation[1]*deg);
  hepRotation.rotateZ(rotation[2]*deg);
  HepRotate3D rotate3D(hepRotation);

  HepScaleZ3D scale3D(-1.0);

  HepTransform3D transform3D = translate3D * rotate3D * scale3D;

  Hep3Vector translation = transform3D.getTranslation();
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

  SmartPut(fOutFile, fNW+1, fNP, x, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, y, "; ");	   
  SmartPut(fOutFile, fNW+1, fNP, z, quota);	   

  fOutFile << fIndention << element2; 
	   
  SmartPut(fOutFile, 8, 5, xx, "; ");	   
  SmartPut(fOutFile, 8, 5, xy, "; ");	   
  SmartPut(fOutFile, 8, 5, xz, "; ");	   

  fOutFile << std::endl
           << fIndention << element3;

  SmartPut(fOutFile, 8, 5, yx, "; ");	   
  SmartPut(fOutFile, 8, 5, yy, "; ");	   
  SmartPut(fOutFile, 8, 5, yz, "; ");	   

  fOutFile << std::endl
	   << fIndention << element3;

  SmartPut(fOutFile, 8, 5, zx, "; ");	   
  SmartPut(fOutFile, 8, 5, zy, "; ");	   
  SmartPut(fOutFile, 8, 5, zz, "");	   

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
	   << "<AGDD DTD_version = \"v6\">" << std::endl
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
  if (version == "Undefined") version = "$Id$";

  std::string name = topVolume;
  name.append(fgkCompNameExtension);

  // write element
  fOutFile << element1 << fDtdVersion << quota << std::endl
           << element2 << topVolume   << quota << std::endl
           << element3 << version     << quota << std::endl
           << element4 << fDate       << quota << std::endl
           << element5 << fAuthor     << quota << std::endl
           << element6 << name        << quota
           << element7 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::OpenMaterials()
{
// Write materials opening.
			 

 fOutFile << "<!-- materials are not yet generated --> "
	  << std::endl 
	  << std::endl;

/*
  std::string element1 = "<materials  version = \"";
  std::string element2 = "            date    = \"";
  std::string element3 = "            author  = \"";
  std::string element4 = "            DTD_version=\"";
  std::string element5 = "  >";
  std::string quota = "\"";   
  
  // write element
  fOutFile << element1 << fVersion << quota << std::endl
           << element2 << fDate    << quota << std::endl
           << element3 << fAuthor  << quota << std::endl
           << element4 << fDtdVersion << quota
           << element5 << std::endl;
*/
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

/*
  // define element
  std::string element = "</materials>";

  // write element
  fOutFile << element
	   << std::endl;
*/
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
void XmlVGM::AGDDWriter::WriteMaterial(const VGM::IMaterial* material) 
{
// Write Material. 
// Not yet implemented, only XML comment element is written

  std::string name = material->Name();
  CutName(name);

  // only comment line
  std::string element1 = "<!-- material = \""; 
  std::string element2 = "\" -->";
  
  // write element
  fOutFile << fkBasicIndention
           << element1 << name
	   << element2
           << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WriteSolid(
                              std::string volumeName, 
			      const VGM::ISolid* solid, 
                              std::string materialName) 
{
// Get VGM::ISolid concrete type and calls writing function

  VGM::SolidType solidType = solid->Type();

  if (solidType == VGM::kBox) { 
    const VGM::IBox* box = dynamic_cast<const VGM::IBox*>(solid); 
    WriteBox(volumeName, box, materialName); 
    return;   
  }
  else if (solidType == VGM::kCons) { 
    const VGM::ICons* cons = dynamic_cast<const VGM::ICons*>(solid); 
    WriteCons(volumeName, cons, materialName); 
    return;   
  }
  else if (solidType == VGM::kPara) { 
    const VGM::IPara* para = dynamic_cast<const VGM::IPara*>(solid); 
    WritePara(volumeName, para, materialName); 
    return;   
  }
  else if (solidType == VGM::kPolycone) { 
    const VGM::IPolycone* polycone = dynamic_cast<const VGM::IPolycone*>(solid); 
    WritePolycone(volumeName, polycone, materialName); 
    return;   
  }
  else if (solidType == VGM::kPolyhedra) { 
    const VGM::IPolyhedra* polyhedra = dynamic_cast<const VGM::IPolyhedra*>(solid); 
    WritePolyhedra(volumeName, polyhedra, materialName); 
    return;   
  }
/*
  else if (solidType == VGM::kSphere) { 
    const VGM::ISphere* sphere = dynamic_cast<const VGM::ISphere*>(solid); 
    WriteSphere(volumeName, sphere, materialName); 
    return;   
  }
  else if (solidType == VGM::kTorus) { 
    const VGM::ITorus* torus = dynamic_cast<const VGM::ITorus*>(solid); 
    WriteTorus(volumeName, torus, materialName); 
    return;   
  }
*/
  else if (solidType == VGM::kTrap) { 
    const VGM::ITrap* trap = dynamic_cast<const VGM::ITrap*>(solid); 
    WriteTrap(volumeName, trap, materialName); 
    return;   
  }
  else if (solidType == VGM::kTrd) { 
    const VGM::ITrd* trd = dynamic_cast<const VGM::ITrd*>(solid); 
    WriteTrd(volumeName, trd, materialName); 
    return;   
  }
  else if (solidType == VGM::kTubs) { 
    const VGM::ITubs* tubs = dynamic_cast<const VGM::ITubs*>(solid); 
    WriteTubs(volumeName, tubs, materialName); 
    return;   
  }
/*
  else if (solidType == VGM::kBoolean) { 
    VGM::IBooleanSolid* boolean = dynamic_cast<VGM::IBooleanSolid*>(solid);
    WriteBoolean(volumeName, boolean, materialName); 
    return;   
  }
*/

  // Not supported solid
  WriteNotSupportedSolid(volumeName, materialName);
}  

//_____________________________________________________________________________
void XmlVGM::AGDDWriter::WritePlacement(
                              const std::string& volumeName, 
                              const ThreeVector& position) 
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

  SmartPut(fOutFile, fNW+1, fNP, x, "; ");
  SmartPut(fOutFile, fNW+1, fNP, y, "; ");
  SmartPut(fOutFile, fNW+1, fNP, z, "");

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

    // position
    ThreeVector position(3);
    position[0] = transform[VGM::kDx];
    position[1] = transform[VGM::kDy];
    position[2] = transform[VGM::kDz];
      
    // rotation
    ThreeVector rotation(3);
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
    placement.MultiplePlacementData(axis, nReplicas, width, offset);
	    
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
