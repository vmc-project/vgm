// $Id$
//
// Author: I. Hrivnacova, 31.03.2004
//
// Class GDMLWriter 
// ----------------------
// See the class description in the header file.

#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>
#include <float.h>

#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IElement.h"

#include "XmlVGM/GDMLWriter.h"

const int         XmlVGM::GDMLWriter::fgkDefaultNumWidth = 10;
const int         XmlVGM::GDMLWriter::fgkDefaultNumPrecision = 4;
const std::string XmlVGM::GDMLWriter::fgkSolidNameExtension  = "_s";  
const std::string XmlVGM::GDMLWriter::fgkElementNameExtension = "_e"; 
const char        XmlVGM::GDMLWriter::fgkCharReplacement = '_'; 
const std::string XmlVGM::GDMLWriter::fgkNotAllowedChars = " +-*/&<>%^";
const std::string XmlVGM::GDMLWriter::fgkNotAllowedChars1 = "0123456789"; 

//_____________________________________________________________________________
XmlVGM::GDMLWriter::GDMLWriter(std::ofstream& outFile,
		               const std::string& unitName, 
                               const std::string& version)
  : IWriter(),
    fOutFile(outFile),
    fUnitName(unitName),
    fVersion(version),
    fkBasicIndention("   "),
    fIndention(fkBasicIndention),
    fNW(fgkDefaultNumWidth),
    fNP(fgkDefaultNumPrecision),
    fGDMLNames()
{
  fOutFile.width(fgkDefaultNumWidth);
  fOutFile.precision(fgkDefaultNumPrecision);
}

//_____________________________________________________________________________
XmlVGM::GDMLWriter::~GDMLWriter() {
//
}

//
// private methods
//

//_____________________________________________________________________________
std::string 
XmlVGM::GDMLWriter::UpdateName(const std::string& name,
                               const std::string& extension) const
{
// Removes spaces after the name if present,
// replaces not allowed characters with fgkCharReplacement inside names
// and appeds the specified extension.
// ---

  std::string newName(name);

  // Remove spaces after the name
  int i = newName.length();
  while (newName[--i] == ' ') newName = std::string(newName, 0, i);
  
  // Replace not allowed characters
  //
  for (i=0; i<int(newName.length()); i++) {
  
    if (( i==0 && 
          fgkNotAllowedChars1.find(newName[i]) < fgkNotAllowedChars1.size()) ||
          fgkNotAllowedChars.find(newName[i]) < fgkNotAllowedChars.size() )
	    
      newName[i] = fgkCharReplacement;
  }      
      
  // Append extension
  newName.append(extension);
  
  return newName;     
}  

//_____________________________________________________________________________
double XmlVGM::GDMLWriter::UpdateAngle(double angle) const
{
// Checks if the value of the angle is within (-2*PI, 2*PI),
// and converts the value to fit within (0, 2*PI).
// ---
 
  if (angle < -2.0*M_PI || angle > 2.0*M_PI) {
    std::cerr << "+++ Warning +++: " << std::endl;
    std::cerr << "    XmlVGM::GDMLWriter::UpdateAngle:" << std::endl;
    std::cerr << "    Angle " << angle/AngleUnit() 
              << " is outside <-360., 360.>" << std::endl;
    std::cerr << "    It was converted to 0." << std::endl;
    return 0.;	      
  }
  
  if (angle < 0.) return angle + 2.0*M_PI;
  
  return angle;  
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::Append(std::string& name,      
                                int size, 
				std::string string) const
{
// Completes the specified string with spaces to get the desired size
// and appends it to the name.
// ---

  for (int i=0; i < size - int(string.size()); i++) {
    //std::cout << string << "appending " << i << std::endl;
    name.append(" ");
  }  
  name.append(string);
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::RegisterName(const std::string& name, 
                                      bool warning)
 {
  
  // Check if the name is unique
  if (fGDMLNames.find(name) == fGDMLNames.end())
    fGDMLNames.insert(name);
  else 
    if (warning) {
      std::cerr << "+++ Warning +++: " << std::endl;
      std::cerr << "    Duplicated name has occured: \"" << name << "\"" 
                << " in geometry." << std::endl;
      std::cerr << "    Duplicated names are not allowed in GDML." << std::endl;
    }
}  

//_____________________________________________________________________________
std::ostream& 
XmlVGM::GDMLWriter::SmartPut(std::ostream& out, 
                             int size, int precision,
		             const std::string& separator1,
                             double number, 
			     const std::string& separator2) const
{
// Help function to supress - sign in case the number == 0
// within the given precision

  if ( round(number*pow(10.,precision))/pow(10.,precision) == 0.0) {
    number = 0.;
  }  
  
  out << separator1;
  out << std::setw(size) << std::setprecision(precision) << number;
  out << separator2;
  
  return out;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteBox(
                              std::string name,
                              double hx, double hy, double hz,  
                              std::string /*materialName*/)
{			      
// Writes box solid.
// ---

  // get parameters
  double x = hx/LengthUnit()*2.;
  double y = hy/LengthUnit()*2.;
  double z = hz/LengthUnit()*2.;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<box  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "x=\"";
  std::string element4 = "y=\"";
  std::string element5 = "z=\"";
  std::string element6 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl  
           << indention  << element2 << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << x << quota << "  "
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << y << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << z 
	   << element6 << std::endl << std::endl;
}
 
//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteBox(
                              std::string name, 
			      const VGM::IBox* box, 
                              std::string materialName)
{
// Writes box solid.
// ---

  WriteBox(name, 
           box->XHalfLength(), box->YHalfLength(), box->ZHalfLength(),
	   materialName);
}
 
//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTubs(
                              std::string name, 
			      const VGM::ITubs* tubs, 
                              std::string /*materialName*/)
{
// Writes tubs solid.
// ---

  // get parameters
  double rmin = tubs->InnerRadius()/LengthUnit();
  double rmax = tubs->OuterRadius()/LengthUnit();
  double hz   = tubs->ZHalfLength()/LengthUnit()*2.;
  double sphi = UpdateAngle(tubs->StartPhi())/AngleUnit();
  double dphi = UpdateAngle(tubs->DeltaPhi())/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<tube  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "z=\"";
  std::string element4 = "rmin=\"";
  std::string element5 = "rmax=\"";
  std::string element6 = "startphi=\"";
  std::string element7 = "deltaphi=\"";
  std::string element8 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl
	   << indention  << element2 << std::endl
	   << indention        
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << rmin << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << rmax << quota << "  " 
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << hz << quota
	   << std::endl
	   << indention        
	   << element6 << std::setw(fNW)   << std::setprecision(fNP) << sphi << quota << "  "
	   << element7 << std::setw(fNW)   << std::setprecision(fNP) << dphi
	   << element8 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteCons(
                              std::string name, 
			      const VGM::ICons* cons, 
                              std::string /*materialName*/)
{
// Writes cons solid.
// ---

  // get parameters
  double rmin1 = cons->InnerRadiusMinusZ()/LengthUnit();
  double rmax1 = cons->OuterRadiusMinusZ()/LengthUnit();
  double rmin2 = cons->InnerRadiusPlusZ()/LengthUnit();
  double rmax2 = cons->OuterRadiusPlusZ()/LengthUnit();
  double hz   = cons->ZHalfLength()/LengthUnit()*2.;
  double sphi = UpdateAngle(cons->StartPhi())/AngleUnit();
  double dphi = UpdateAngle(cons->DeltaPhi())/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<cone  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "z=\"";
  std::string element4 = "rmin1=\"";
  std::string element5 = "rmin2=\"";
  std::string element6 = "rmax1=\"";
  std::string element7 = "rmax2=\"";
  std::string element8 = "startphi=\"";
  std::string element9 = "deltaphi=\"";
  std::string element10 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl
	   << indention  << element2 << std::endl
	   << indention        
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << rmin1 << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << rmin2 << quota << "  "
	   << element6 << std::setw(fNW) << std::setprecision(fNP) << rmax1 << quota << "  "
	   << element7 << std::setw(fNW) << std::setprecision(fNP) << rmax2 << quota << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << hz << quota << std::endl
	   << indention        
	   << element8 << std::setw(fNW)   << std::setprecision(fNP) << sphi << quota << "  "
	   << element9 << std::setw(fNW)   << std::setprecision(fNP) << dphi
	   << element10 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTrd(
                              std::string name, 
			      const VGM::ITrd* trd, 
                              std::string /*materialName*/)
{
// Writes VGM::ITrd solid.
// ---

  // get parameters
  double x1 = trd->XHalfLengthMinusZ()/LengthUnit()*2.;
  double x2 = trd->XHalfLengthPlusZ()/LengthUnit()*2.;
  double y1 = trd->YHalfLengthMinusZ()/LengthUnit()*2.;
  double y2 = trd->YHalfLengthPlusZ()/LengthUnit()*2.;
  double hz = trd->ZHalfLength()/LengthUnit()*2.;

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<trd  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "x1=\"";
  std::string element4 = "x2=\"";
  std::string element5 = "y1=\"";
  std::string element6 = "y2=\"";
  std::string element7 = "z=\"";
  std::string element8 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << x1 << quota << "  "
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << x2 << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << y1 << quota << "  "
	   << element6 << std::setw(fNW) << std::setprecision(fNP) << y2 << quota << std::endl
	   << indention
	   << element7 << std::setw(fNW) << std::setprecision(fNP) << hz
	   << element8 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTrap(
                              std::string name, 
			      const VGM::ITrap* trap, 
                              std::string /*materialName*/)
{
// Writes VGM::ITrap solid.
// ---

  // get parameters
  double dz = trap->ZHalfLength()/LengthUnit()*2.;
  double theta = UpdateAngle(trap->Theta())/AngleUnit();
  double phi   = UpdateAngle(trap->Phi())/AngleUnit();
  double y1 = trap->YHalfLengthMinusZ()/LengthUnit()*2.;
  double x1 = trap->XHalfLengthMinusZMinusY()/LengthUnit()*2.;
  double x2 = trap->XHalfLengthMinusZPlusY()/LengthUnit()*2.;
  double alpha1 = trap->AlphaMinusZ()/AngleUnit();
  double y2 = trap->YHalfLengthPlusZ()/LengthUnit()*2.;
  double x3 = trap->XHalfLengthPlusZMinusY()/LengthUnit()*2.;
  double x4 = trap->XHalfLengthPlusZPlusY()/LengthUnit()*2.;
  double alpha2 = trap->AlphaPlusZ()/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1  = "<trap  lunit=\"cm\" aunit=\"degree\"";
  std::string element2  = "name=\"" + name + quota;
  std::string element3  = "z=\"";
  std::string element4  = "theta=\"";
  std::string element5  = "phi=\"";
  std::string element6  = "y1=\"";
  std::string element7  = "x1=\"";
  std::string element8  = "x2=\"";
  std::string element9  = "alpha1=\"";
  std::string element10 = "y2=\"";
  std::string element11 = "x3=\"";
  std::string element12 = "x4=\"";
  std::string element13 = "alpha2=\"";
  std::string element14 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
	   << indention        << element2 << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << dz << quota << std::endl
	   << indention        
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << theta << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << phi << quota << std::endl
	   << indention        
	   << element6 << std::setw(fNW) << std::setprecision(fNP) << y1 << quota << "  "
	   << element7 << std::setw(fNW) << std::setprecision(fNP) << x1 << quota << "  "
	   << element8 << std::setw(fNW) << std::setprecision(fNP) << x2 << quota << "  "
	   << element9 << std::setw(fNW) << std::setprecision(fNP) << alpha1 << quota << std::endl
	   << indention        
	   << element10 << std::setw(fNW) << std::setprecision(fNP) << y2 << quota << "  "
	   << element11 << std::setw(fNW) << std::setprecision(fNP) << x3 << quota << "  "
	   << element12 << std::setw(fNW) << std::setprecision(fNP) << x4 << quota << "  "
	   << element13 << std::setw(fNW) << std::setprecision(fNP) << alpha2
	   << element14 << std::endl << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePara(
                              std::string name, 
			      const VGM::IPara* para, 
                              std::string /*materialName*/)
{
// Writes VGM::IPara solid.
// ---

  // get parameters
  double dx = para->XHalfLength()/LengthUnit()*2.;
  double dy = para->YHalfLength()/LengthUnit()*2.;
  double dz = para->ZHalfLength()/LengthUnit()*2.;
  double alpha = para->Alpha()/AngleUnit();
  double theta = UpdateAngle(para->Theta())/AngleUnit();
  double phi   = UpdateAngle(para->Phi())/AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<para  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "x=\"";
  std::string element4 = "y=\"";
  std::string element5 = "z=\"";
  std::string element6 = "alpha=\"";
  std::string element7 = "theta=\"";
  std::string element8 = "phi=\"";
  std::string element9 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl  
           << indention        << element2 << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << dx << quota << "  "
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << dy << quota << "  "
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << dz << quota << std::endl
	   << indention        
	   << element6 << std::setw(fNW) << std::setprecision(fNP) << alpha << quota << "  "
	   << element7 << std::setw(fNW) << std::setprecision(fNP) << theta << quota << "  "
	   << element8 << std::setw(fNW) << std::setprecision(fNP) << phi 
	   << element9 << std::endl << std::endl;
}
 
/*
//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePolycone(
                             std::string name, 
			     const VGM::IPolycone* polycone, 
                             std::string materialName)
{
// Writes VGM::IPolycone solid.
// Not yet supported by GDML.
// ---

  // get profile parameters
  double sphi = polycone->StartPhi()/AngleUnit();
  double dphi = polycone->DeltaPhi()/AngleUnit();
  
  // get polycone Z planes parameters
  int nofZPlanes = polycone->NofZPlanes();
  double* rminArray = new double[nofZPlanes];
  double* rmaxArray = new double[nofZPlanes];
  double* zArray = new double[nofZPlanes];
  for (int i=0; i<nofZPlanes; i++) {
    rminArray[i] = polycone->InnerRadiusValues()[i];
    rmaxArray[i] = polycone->OuterRadiusValues()[i];
    zArray[i] = polycone->ZValues()[i];
  }  
    
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

  delete [] rminArray;			      
  delete [] rmaxArray;	
  delete [] zArray;			      
}  
*/

/*
//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePolyhedra(    
                              std::string name, 
			      const VGM::IPolyhedra* polyhedra, 
                              std::string materialName)
{
// Writes VGM::IPolycone solid.
// Not yet supported by GDML.
// ---

  // get parameters
  int nofSides = polyhedra->NofSides();
  double sphi = polyhedra->StartPhi()/AngleUnit();
  double dphi = polyhedra->DeltaPhi()/AngleUnit();

  // get polyhedra Z planes parameters
  int nofZPlanes = polyhedra->NofZPlanes();
  double* rminArray = new double[nofZPlanes];
  double* rmaxArray = new double[nofZPlanes];
  double* zArray = new double[nofZPlanes];
  for (int i=0; i<nofZPlanes; i++) {
    rminArray[i] = polyhedra->InnerRadiusValues()[i];
    rmaxArray[i] = polyhedra->OuterRadiusValues()[i];
    zArray[i] = polyhedra->ZValues()[i];
  }  

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

  delete [] rminArray;			      
  delete [] rmaxArray;	
  delete [] zArray;			      
}  
*/

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteSphere(
                              std::string name, 
			      const VGM::ISphere* sphere, 
                              std::string /*materialName*/)
{
// Writes VGM::ISphere solid.
// ---

  // get parameters
  double rmin = sphere->InnerRadius()/LengthUnit();
  double rmax = sphere->OuterRadius()/LengthUnit();
  double sphi = UpdateAngle(sphere->StartPhi())/AngleUnit();
  double dphi = UpdateAngle(sphere->DeltaPhi())/AngleUnit();
  double stheta = UpdateAngle(sphere->StartTheta())/AngleUnit();
  double dtheta = UpdateAngle(sphere->DeltaTheta())/AngleUnit();


  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<sphere  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "rmin=\"";
  std::string element4 = "rmax=\"";
  std::string element5 = "startphi=\"";
  std::string element6 = "deltaphi=\"";
  std::string element7 = "starttheta=\"";
  std::string element8 = "deltatheta=\"";
  std::string element9 = "\" />";
  std::string indention = fIndention + fkBasicIndention;
  
  // write element
  fOutFile << fIndention << element1 << std::endl  
           << indention  << element2 << std::endl
	   << indention        
	   << element3 << std::setw(fNW) << std::setprecision(fNP) << rmin << quota << "  "
	   << element4 << std::setw(fNW) << std::setprecision(fNP) << rmax << quota << std::endl
	   << indention        
	   << element5 << std::setw(fNW) << std::setprecision(fNP) << sphi << quota << "  "
	   << element6 << std::setw(fNW) << std::setprecision(fNP) << dphi << quota << "  "
	   << element7 << std::setw(fNW) << std::setprecision(fNP) << stheta << quota << "  "
	   << element8 << std::setw(fNW) << std::setprecision(fNP) << dtheta
	   << element9 << std::endl << std::endl;
}
 
//
// public methods
//

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenDocument()
{
// Writes document opening.
// Could be made customizable in future.
// ---
			 
  fOutFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"\?>" 
           << std::endl
           << "<gdml xmlns:gdml=\"http://cern.ch/2001/Schemas/GDML\"" 
	   << std::endl
	   << "      xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" 
	   << std::endl
	   << "      xsi:noNamespaceSchemaLocation=\"gdml_1.0.xsd\">" 
	   << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenSection(const std::string& /*topVolume*/)
{
// Writes section opening.
// ---

  // nothing to be done in GDML			 
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenPositions()
{
// Opens element for general definitions 
// (positions and rotations for generated XML files.)
// ---

  std::string element1 = "<define>"; 

  // write element
  fOutFile << fIndention << element1 << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenRotations()
{
// Rotations are written in the same element as positions.
// The element is already open.
// ---

}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenMaterials()
{
// Writes materials opening.
// ---
			 
  std::string element = "<materials>";
  
  // write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenSolids()
{
// Writes solids opening. 
// ---

  std::string element = "<solids>"; 

  // write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenStructure()
{
// Writes composition opening.
// ---
			 
  std::string element = "<structure>";
  
  // Write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenComposition(
                                const std::string& name,
                                const std::string& materialName)
{
// Writes composition opening.
// ---

  // Update names
  std::string volName = UpdateName(name);
  std::string matName = UpdateName(materialName);
  std::string sldName = UpdateName(name, fgkSolidNameExtension);
  
  // Register volume name
  RegisterName(volName);
			 
  std::string element1 = "<volume name=\"";
  element1.append(volName);
  element1.append("\">");
  
  std::string element2 = "<materialref ref=\"";
  element2.append(matName);
  element2.append("\"/>");
  
  std::string element3 = "<solidref ref=\"";
  element3.append(sldName);
  element3.append("\"/>");
  
  std::string indention =  fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention  << element2 << std::endl
           << indention  << element3 << std::endl;

  // increase indention
  IncreaseIndention();	   
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseDocument()
{
// Writes document closing.
// ---

   fOutFile << "</gdml>" << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseSection(const std::string& topVolume)
{
// Writes section closing.
// ---

  // Define element
  //
  std::string quota = "\"";
  std::string element2 = "<setup name=\"";
  element2.append(fUnitName);
  element2.append(quota);
  
  std::string element3 = "version=\"";
  element3.append(fVersion);
  element3.append(quota);
  		
  std::string element4 = "<world ref=\"";
  element4.append(topVolume);
  element4.append(quota);
    
  std::string element5 = "</setup>";
  std::string indention = fIndention + fkBasicIndention;
 
  // Write element
  //
  fOutFile << fIndention       << element2
	   << fkBasicIndention << element3 << ">"  << std::endl
	   << indention        << element4 << "/>" << std::endl
	   << fIndention       << element5 << std::endl
	   << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::ClosePositions()
{
// Do not close the element.
// Rotations will be written in the same element as positions.
// ---

}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseRotations()
{
// Close element for general definitions 
// (positions and rotations for generated XML files.)
// ---

  // decrease indention
  DecreaseIndention();	   

  std::string element1 = "</define>"; 

  // write element
  fOutFile << fIndention << element1 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseMaterials()
{
// Writes materials closing.
// ---

  // decrease indention
  DecreaseIndention();	   

  // define element
  std::string element = "</materials>";

  // write element
  fOutFile << fIndention << element << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseSolids()
{
// Close element for solids. 
// ---

  // decrease indention
  DecreaseIndention();	   

  std::string element1 = "</solids>"; 

  // write element
  fOutFile << fIndention << element1 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseStructure()
{
// Close element for solids. 
// ---

  // decrease indention
  DecreaseIndention();	   

  std::string element = "</structure>";

  // write element
  fOutFile << fIndention << element << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseComposition()
{
// Writes composition closing.
// ---

  // decrease indention
  DecreaseIndention();

  // define element
  std::string element = "</volume>";

  // write element
  fOutFile << fIndention << element << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteElement(const VGM::IElement* element) 
{
// Writes VGM::IElement. 
// ---

  std::string name = UpdateName(element->Name(), fgkElementNameExtension);
  RegisterName(name);  
    
  // Get parameters
  double theZ = element->Z();
  int    theN = (int) round(element->N());
  double theA = element->A()/ AtomicWeightUnit();
  
  // GDML does not allow N=0
  // Let's put =1 in this case
  if (theN == 0) theN = 1;

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<element  name=";
  Append(element1, 15, quota1 + name + quota2);
  
  std::string element2 = "Z=\"";
  std::string element3 = "N=\"";
  std::string element4 = "<atom type=\"A\" unit=\"g/mol\" value=\"";
  std::string element5 = "\" />";
  std::string element6 = "</element>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention << element1;
  SmartPut(fOutFile, fNW-2, fNP, element2, theZ, quota2);
  //SmartPut(fOutFile, fNW-2, fNP, element3, theN, "\" >");
  //fOutFile << std::endl; 
  fOutFile << element3 << std::setw(3) << theN << "\" >" << std::endl;
  
  fOutFile << indention;
  SmartPut(fOutFile, fNW-2, fNP, element4, theA, element5);
  fOutFile << std::endl; 

  fOutFile << fIndention << element6 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteMaterial(const VGM::IMaterial* material) 
{
// Writes VGM::IMaterial. 
// ---

  std::string materialName = UpdateName(material->Name());
  RegisterName(materialName);

  // Get parameters
  double density = material->Density()/ MassDensityUnit();
 
  // Compose material string template
  std::string quota = "\"  ";
  std::string element1 = "<material  name=\"";
  element1.append(materialName);
  element1.append(quota);
  element1.append(">");
  
  std::string element2 = "<D type=\"density\" unit=\"g/cm3\" value=\"";
  std::string element3 = "<fraction n=\"";
  std::string element4 = "ref=\"";
  std::string element5 = "\"/>";
  std::string element6 = "</material>";
  
  std::string indention = fIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention << element1 << std::endl;

  fOutFile << indention;
  SmartPut(fOutFile, fNW+1, fNP, element2, density, element5);
  fOutFile << std::endl; 
  
  for (int i=0; i<int(material->NofElements()); i++) {
    double fraction
      = material->MassFraction(i);
    std::string elementName
      = UpdateName(material->Element(i)->Name(), fgkElementNameExtension);  

    fOutFile << indention;
    SmartPut(fOutFile, fNW, fNP, element3, fraction, quota);
    fOutFile << element4 << elementName << element5 << std::endl;
  }  

  fOutFile << fIndention << element6 << std::endl;
 }  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteNotSupportedSolid(
                              std::string name, 
                              std::string materialName)
{				   
// Write a comment line with awarning
// and then write a box element instead 
// ---

  // Compose comment
  std::string element1 = "<!-- !!! unsupported shape  !!!  name= \""; 
  std::string element2 = "\" -->";
  std::string element3 = "<!-- dummy box is written instead  -->"; 
  
  // Write element with warning
  fOutFile << fIndention << element1 << name << element2 << std::endl
	   << fIndention << element3 << std::endl;
	   
  // Write dummy box element
  WriteBox(name, 1.*mm, 1.*mm, 1.*mm, materialName); 
}  	   

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteSolid(
                              std::string volumeName, 
			      const VGM::ISolid* solid, 
                              std::string materialName) 
{
// Finds solid concrete type and calls writing function. 
// For not yet implemented solids, only XML comment element is written.
// ---

  std::string solidName = UpdateName(volumeName, fgkSolidNameExtension);
  RegisterName(solidName);
  
  VGM::SolidType solidType = solid->Type();
  if (solidType == VGM::kBox) { 
    const VGM::IBox* box = dynamic_cast<const VGM::IBox*>(solid); 
    WriteBox(solidName, box, materialName); 
    return;   
  }
  else if (solidType == VGM::kCons) { 
    const VGM::ICons* cons = dynamic_cast<const VGM::ICons*>(solid); 
    WriteCons(solidName, cons, materialName); 
    return;   
  }
  else if (solidType == VGM::kPara) { 
    const VGM::IPara* para = dynamic_cast<const VGM::IPara*>(solid); 
    WritePara(solidName, para, materialName); 
    return;   
  }
/*
  else if (solidType == VGM::kPolycone) { 
    const VGM::IPolycone* polycone = dynamic_cast<const VGM::IPolycone*>(solid); 
    WritePolycone(solidName, polycone, materialName); 
    return;   
  }
  else if (solidType == VGM::kPolyhedra) { 
    const VGM::IPolyhedra* polyhedra = dynamic_cast<const VGM::IPolyhedra*>(solid); 
    WritePolyhedra(solidName, polyhedra, materialName); 
    return;   
  }
*/
  else if (solidType == VGM::kSphere) { 
    const VGM::ISphere* sphere = dynamic_cast<const VGM::ISphere*>(solid); 
    WriteSphere(solidName, sphere, materialName); 
    return;   
  }
/*
  else if (solidType == VGM::kTorus) { 
    const VGM::ITorus* torus = dynamic_cast<const VGM::ITorus*>(solid); 
    WriteTorus(solidName, torus, materialName); 
    return;   
  }
*/
  else if (solidType == VGM::kTrap) { 
    const VGM::ITrap* trap = dynamic_cast<const VGM::ITrap*>(solid); 
    WriteTrap(solidName, trap, materialName); 
    return;   
  }
  else if (solidType == VGM::kTrd) { 
    const VGM::ITrd* trd = dynamic_cast<const VGM::ITrd*>(solid); 
    WriteTrd(solidName, trd, materialName); 
    return;   
  }
  else if (solidType == VGM::kTubs) { 
    const VGM::ITubs* tubs = dynamic_cast<const VGM::ITubs*>(solid); 
    WriteTubs(solidName, tubs, materialName); 
    return;   
  }
/*
  else if (solidType == VGM::kBoolean) { 
    VGM::IBooleanSolid* boolean = dynamic_cast<VGM::IBooleanSolid*>(solid);
    WriteBoolean(solidName, boolean, materialName); 
    return;   
  }
*/

  // Not supported solid
  WriteNotSupportedSolid(solidName, materialName);
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePosition(
                              const std::string& name, 
                              const VGM::ThreeVector& position) 
{
// Writes position element with a given name. 
// ---

  // get parameters
  double x = position[0]/LengthUnit();
  double y = position[1]/LengthUnit();
  double z = position[2]/LengthUnit();

  // compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<position  name=";
  Append(element1, 12, quota1 + name + quota2);

  std::string element2 = "x=\"";
  std::string element3 = "y=\"";
  std::string element4 = "z=\"";
  std::string element5 = "\"  unit=\"cm\" />";
  
  // write element
  fOutFile << fIndention << element1;

  SmartPut(fOutFile, fNW+1, fNP, element2, x, quota2);
  SmartPut(fOutFile, fNW+1, fNP, element3, y, quota2);
  SmartPut(fOutFile, fNW+1, fNP, element4, z, "");

  fOutFile << element5 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteRotation(
                              const std::string& name, 
                              const VGM::Rotation& rotation)
{
// Writes rotation element with a given name. 
// ---

  // Get parameters
  double angleX = rotation[0] / AngleUnit();
  double angleY = rotation[1] / AngleUnit();
  double angleZ = rotation[2] / AngleUnit();

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<rotation  name=";
  Append(element1, 12, quota1 + name + quota2);

  std::string element2 = "x=\"";
  std::string element3 = "y=\"";
  std::string element4 = "z=\"";
  std::string element5 = "\"  unit=\"degree\" />";
  
  // Write element
  fOutFile << fIndention << element1;

  SmartPut(fOutFile, fNW+1, fNP, element2, angleX, quota2);
  SmartPut(fOutFile, fNW+1, fNP, element3, angleY, quota2);
  SmartPut(fOutFile, fNW+1, fNP, element4, angleZ, "");

  fOutFile << element5 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePlacementWithRotation(
                              const std::string& volumeName, 
			      const std::string& positionRef,
			      const std::string& rotationRef)
{
// Writes position with rotation with a given volume name.
// ---

  // Update name
  std::string name = UpdateName(volumeName);

  // Compose element strings
  //
  std::string element0 = "\"/>";
  std::string element1 = "<child>";
 
  std::string element2 = "<volumeref ref=\"";
  element2.append(name);
  element2.append(element0);

  std::string element3 = "<positionref ref=\"";
  element3.append(positionRef);
  element3.append(element0);
  
  std::string element4 = "<rotationref ref=\"";
  element4.append(rotationRef);
  element4.append(element0);

  std::string element5 = "</child>";
  
  std::string indention1 = fIndention + fkBasicIndention;
  std::string indention2 = fIndention + fkBasicIndention + fkBasicIndention;
  
  // Write element
  fOutFile << fIndention << element1 << std::endl
           << indention1 << element2 << std::endl
           << indention2 << element3 << std::endl
           << indention2 << element4 << std::endl
	   << fIndention << element5 << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteMultiplePlacement(
                              const std::string& /*volumeName*/,
                              VGM::Axis /*axis*/, 
			      int /*nofReplicas*/,
			      double /*width*/, 
			      double /*offset*/)			       
{
// Not yet available in GDML
// ---
/*
  // get parameters
  VGM::Axis axis;
  int nReplicas;
  double width;
  double offset;
  bool consuming;
  pvr->GetReplicationData(axis, nReplicas, width, offset, consuming);
  
  std::string tag;
  switch (axis) {
    case kXAxis: tag = "X"; break;
    case kYAxis: tag = "Y"; break;
    case kZAxis: tag = "Z"; break;
    case kRho:   tag = "R"; break;
    case kPhi:   tag = "Phi"; break;
    case kRadial3D:  tag = "R3D"; break; // CHECK
    case kUndefined: tag = "Undefined"; break;
  }  

  // set units
  double value0 = - width*(nReplicas-1)*0.5 + offset;
  double dValue = width;
  if (axis != kPhi) {
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
  std::string element1 = "<" + a0 + "      volume=\"#####################   ncopy=\"";
  std::string element2 = "\"   " + a1 + "=\"";
  std::string element3 = "\"   " + a2 + "=\"";
  std::string element4 = "\" />";
  
  // put solid name
  PutName(element1, volumeName, "#");
  
  // write element
  fOutFile << fIndention
           << element1
           << std::setw(fNW+1) << std::setprecision(fNP) << nReplicas
	   << element2
           << std::setw(fNW+1) << std::setprecision(fNP) << value0
	   << element3	   
           << std::setw(fNW+1) << std::setprecision(fNP) << dValue
	   << element4
	   << std::endl;
*/
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteEmptyLine()
{
// Writes empty line.
// ---

  fOutFile << std::endl;
}  

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::IncreaseIndention()
{
// Increase indention
// ---

  fIndention.append(fkBasicIndention);	   
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::DecreaseIndention()
{
// Decrease indention
// ---

  fIndention.replace(fIndention.find(fkBasicIndention), 3 , "");
}
