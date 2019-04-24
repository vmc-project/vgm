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
// Author: I. Hrivnacova, 31.03.2004
//
// Class GDMLWriter
// ----------------------
// See the class description in the header file.

#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"
#include "VGM/solids/IArb8.h"
#include "VGM/solids/IBooleanSolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/ICtubs.h"
#include "VGM/solids/IEllipsoid.h"
#include "VGM/solids/IEllipticalTube.h"
#include "VGM/solids/IExtrudedSolid.h"
#include "VGM/solids/IHype.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IParaboloid.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"
#include "VGM/solids/ISolid.h"
#include "VGM/solids/ISphere.h"
#include "VGM/solids/ITessellatedSolid.h"
#include "VGM/solids/ITorus.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITubs.h"
#include "VGM/volumes/IPlacement.h"
#include "VGM/volumes/IVolume.h"

#include "ClhepVGM/transform.h"

#include "XmlVGM/GDMLWriter.h"
#include "XmlVGM/Maps.h"
#include "XmlVGM/utilities.h"

#include <cstdlib>
#include <float.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <sstream>

const int XmlVGM::GDMLWriter::fgkDefaultNumWidth = 10;
const int XmlVGM::GDMLWriter::fgkDefaultNumPrecision = 4;
const std::string XmlVGM::GDMLWriter::fgkSolidNameExtension = "_s";
const std::string XmlVGM::GDMLWriter::fgkIsotopeNameExtension = "_i";
const std::string XmlVGM::GDMLWriter::fgkElementNameExtension = "_e";
const char XmlVGM::GDMLWriter::fgkCharReplacement = '_';
const std::string XmlVGM::GDMLWriter::fgkNotAllowedChars = " +-*/&<>%^";
const std::string XmlVGM::GDMLWriter::fgkNotAllowedChars1 = "0123456789";
const double XmlVGM::GDMLWriter::fgkSTPTemperature = 273.15; // in kelvin
const double XmlVGM::GDMLWriter::fgkSTPPressure = 101325;    // in pascal
const double XmlVGM::GDMLWriter::fgkCarTolerance = 1e-10;
const double XmlVGM::GDMLWriter::fgkAngTolerance = 1e-8;

//_____________________________________________________________________________
XmlVGM::GDMLWriter::GDMLWriter(
  const std::string& unitName, const std::string& version)
  : IWriter(),
    fOutFile(),
    fUnitName(unitName),
    fVersion(version),
    fkBasicIndention("   "),
    fIndention(fkBasicIndention),
    fNW(fgkDefaultNumWidth),
    fNP(fgkDefaultNumPrecision),
    fGDMLNames(),
    fMaps(0),
    fFullLengths(true)
{
  /// Standard constructor
  /// \param unitName GDML unit name
  /// \param version GDML file version

  fOutFile.width(fgkDefaultNumWidth);
  fOutFile.precision(fgkDefaultNumPrecision);
}

//_____________________________________________________________________________
XmlVGM::GDMLWriter::GDMLWriter(const GDMLWriter& /*rhs*/) : IWriter()
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
XmlVGM::GDMLWriter::~GDMLWriter()
{
  //
}

//
// private methods
//

//_____________________________________________________________________________
double XmlVGM::GDMLWriter::UpdateAngle(double angle) const
{
  /// Check if the value of the angle is within (-360., 360.),
  /// and convert the value to fit within (0, 360.).

  if (angle < -360. || angle > 360.) {
    std::cerr << "+++ Warning +++: " << std::endl;
    std::cerr << "    XmlVGM::GDMLWriter::UpdateAngle:" << std::endl;
    std::cerr << "    Angle " << angle / AngleUnit()
              << " is outside <-360., 360.>" << std::endl;
    std::cerr << "    It was converted to 0." << std::endl;
    return 0.;
  }

  if (angle < 0.) return angle + 360.;

  return angle;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::RegisterName(const std::string& name, bool warning)
{
  /// Register the given name
  /// and give a warning if a duplicated name occurs

  // Check if the name is unique
  if (fGDMLNames.find(name) == fGDMLNames.end())
    fGDMLNames.insert(name);
  else if (warning) {
    std::cerr << "+++ Warning +++: " << std::endl;
    std::cerr << "    Duplicated name has occured: \"" << name << "\""
              << " in geometry." << std::endl;
    std::cerr << "    Duplicated names are not allowed in GDML." << std::endl;
  }
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteBooleanSolid(
  std::string lvName, const VGM::IBooleanSolid* booleanSolid)
{
  /// Write Boolean solid

  // Get constituent solids
  VGM::ISolid* solidA = booleanSolid->ConstituentSolidA();
  VGM::ISolid* solidB = booleanSolid->ConstituentSolidB();

  // Write constituent solids
  std::string nameA = StripName(lvName, fgkSolidNameExtension) + "_constA";
  std::string nameB = StripName(lvName, fgkSolidNameExtension) + "_constB";
  WriteSolid(nameA, solidA, "");
  WriteSolid(nameB, solidB, "");

  // Update names
  nameA = UpdateName(nameA, fgkSolidNameExtension);
  nameB = UpdateName(nameB, fgkSolidNameExtension);

  // Get displacement
  VGM::Transform transform = booleanSolid->Displacement();
  VGM::Transform invTransform = ClhepVGM::Inverse(transform);
  std::string positionName = fMaps->AddBooleanPosition();
  std::string rotationName = fMaps->AddBooleanRotation();

  // Get boolean type
  VGM::BooleanType boolType = booleanSolid->BoolType();

  // compose element string template
  //
  std::string element1;
  std::string element6;
  switch (boolType) {
    case VGM::kIntersection:
      element1 = "<intersection name=\"";
      element6 = "</intersection>";
      break;
    case VGM::kSubtraction:
      element1 = "<subtraction name=\"";
      element6 = "</subtraction>";
      break;
    case VGM::kUnion:
      element1 = "<union name=\"";
      element6 = "</union>";
      break;
    case VGM::kUnknownBoolean:
      break;
  }
  std::string element2 = "\" >";
  std::string element3 = "<first  ref=\"";
  std::string element4 = "\" />";
  std::string element5 = "<second ref=\"";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << lvName << element2 << std::endl
           << indention << element3 << nameA << element4 << std::endl
           << indention << element5 << nameB << element4 << std::endl;

  fOutFile << fkBasicIndention;
  WritePosition(positionName, transform);

  fOutFile << fkBasicIndention;
  WriteRotation(rotationName, invTransform);

  fOutFile << fIndention << element6 << std::endl << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteBox(
  std::string name, double hx, double hy, double hz)
{
  /// Write box solid

  // get parameters
  double x = hx / LengthUnit();
  double y = hy / LengthUnit();
  double z = hz / LengthUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    x *= 2.;
    y *= 2.;
    z *= 2.;
  }

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
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << x << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << y << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << z << element6
           << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteArb8(std::string name, const VGM::IArb8* arb8)
{
  /// Write VGM::ITessellatedSolid solid

  // get parameters
  double hz = arb8->ZHalfLength() / LengthUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    hz *= 2.;
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<arb8  lunit=\"cm\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "dz=\"";
  std::string element4 = "v";
  std::string element5 = "x=\"";
  std::string element6 = "y=\"";
  std::string element7 = "  />";
  std::string indention = fIndention + fkBasicIndention;

  // write openning element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << hz << quota;

  // write vertices
  for (int i = 0; i < arb8->NofVertices(); ++i) {
    VGM::TwoVector vertex = arb8->Vertex(i);
    double dx = vertex.first / LengthUnit();
    double dy = vertex.second / LengthUnit();

    fOutFile << std::endl
             << indention << element4 << std::setw(1) << i + 1 << element5
             << std::setw(fNW) << std::setprecision(fNP) << dx << quota << "  "
             << element4 << std::setw(1) << i + 1 << element6 << std::setw(fNW)
             << std::setprecision(fNP) << dy << quota;
  }
  fOutFile << element7 << std::endl << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteBox(std::string name, const VGM::IBox* box)
{
  /// Write box solid

  WriteBox(name, box->XHalfLength(), box->YHalfLength(), box->ZHalfLength());
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteCons(std::string name, const VGM::ICons* cons)
{
  /// Write cons solid

  // get parameters
  double rmin1 = cons->InnerRadiusMinusZ() / LengthUnit();
  double rmax1 = cons->OuterRadiusMinusZ() / LengthUnit();
  double rmin2 = cons->InnerRadiusPlusZ() / LengthUnit();
  double rmax2 = cons->OuterRadiusPlusZ() / LengthUnit();
  double hz = cons->ZHalfLength() / LengthUnit();
  double sphi = UpdateAngle(cons->StartPhi()) / AngleUnit();
  double dphi = UpdateAngle(cons->DeltaPhi()) / AngleUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    hz *= 2.;
  }

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
           << indention << element2 << std::endl
           << indention << element4 << std::setw(fNW) << std::setprecision(fNP)
           << rmin1 << quota << "  " << element5 << std::setw(fNW)
           << std::setprecision(fNP) << rmin2 << quota << "  " << element6
           << std::setw(fNW) << std::setprecision(fNP) << rmax1 << quota << "  "
           << element7 << std::setw(fNW) << std::setprecision(fNP) << rmax2
           << quota << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << hz << quota << std::endl
           << indention << element8 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element9 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << element10 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteCtubs(std::string name, const VGM::ICtubs* ctubs)
{
  /// Write ctubs solid

  // get parameters
  double rmin = ctubs->InnerRadius() / LengthUnit();
  double rmax = ctubs->OuterRadius() / LengthUnit();
  double hz = ctubs->ZHalfLength() / LengthUnit() * 2.;
  double sphi = ctubs->StartPhi() / AngleUnit();
  double dphi = ctubs->DeltaPhi() / AngleUnit();
  double nxl = ctubs->NxLow();
  double nyl = ctubs->NyLow();
  double nzl = ctubs->NzLow();
  double nxh = ctubs->NxHigh();
  double nyh = ctubs->NyHigh();
  double nzh = ctubs->NzHigh();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<cutTube  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "z=\"";
  std::string element4 = "rmin=\"";
  std::string element5 = "rmax=\"";
  std::string element6 = "startphi=\"";
  std::string element7 = "deltaphi=\"";
  std::string element8 = "lowX=\"";
  std::string element9 = "lowY=\"";
  std::string element10 = "lowZ=\"";
  std::string element11 = "highX=\"";
  std::string element12 = "highY=\"";
  std::string element13 = "highZ=\"";
  std::string element14 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element4 << std::setw(fNW) << std::setprecision(fNP)
           << rmin << quota << "  " << element5 << std::setw(fNW)
           << std::setprecision(fNP) << rmax << quota << "  " << element3
           << std::setw(fNW) << std::setprecision(fNP) << hz << quota
           << std::endl
           << indention << element6 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << quota << std::endl
           << indention << element8 << std::setw(fNW) << std::setprecision(fNP)
           << nxl << quota << "  " << element9 << std::setw(fNW)
           << std::setprecision(fNP) << nyl << quota << "  " << element10
           << std::setw(fNW) << std::setprecision(fNP) << nzl << quota
           << std::endl
           << indention << element11 << std::setw(fNW) << std::setprecision(fNP)
           << nxh << quota << "  " << element12 << std::setw(fNW)
           << std::setprecision(fNP) << nyh << quota << "  " << element13
           << std::setw(fNW) << std::setprecision(fNP) << nzh << element14
           << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteEllipsoid(
  std::string name, const VGM::IEllipsoid* ellipsoid)
{
  /// Write elliptical tube solid

  // get parameters
  double dx = ellipsoid->XSemiAxis() / LengthUnit();
  double dy = ellipsoid->YSemiAxis() / LengthUnit();
  double dz = ellipsoid->ZSemiAxis() / LengthUnit();
  double zbCut = ellipsoid->ZBottomCut() / LengthUnit();
  double ztCut = ellipsoid->ZTopCut() / LengthUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<ellipsoid  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "ax=\"";
  std::string element4 = "by=\"";
  std::string element5 = "cz=\"";
  std::string element6 = "zcut1=\"";
  std::string element7 = "zcut2=\"";
  std::string element8 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << dx << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << dy << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << dz << quota << "  "
           << element6 << std::setw(fNW) << std::setprecision(fNP) << zbCut
           << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << ztCut << element8 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteEllipticalTube(
  std::string name, const VGM::IEllipticalTube* eltu)
{
  /// Write elliptical tube solid

  // get parameters
  double dx = eltu->Dx() / LengthUnit();
  double dy = eltu->Dy() / LengthUnit();
  double hz = eltu->ZHalfLength() / LengthUnit();

  // convert half lengths to full lengths
  /*
    if (fFullLengths) {
      hz *= 2.;
    }
  */
  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<eltube  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "dx=\"";
  std::string element4 = "dy=\"";
  std::string element5 = "dz=\"";
  std::string element6 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << dx << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << dy << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << hz << element6
           << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteExtrudedSolid(
  std::string name, const VGM::IExtrudedSolid* extruded)
{
  /// Write VGM::IExtrudedSolid solid

  // get vertices
  int nofVertices = extruded->NofVertices();
  double* xvertArray = new double[nofVertices];
  double* yvertArray = new double[nofVertices];
  for (int i = 0; i < nofVertices; i++) {
    xvertArray[i] = extruded->Vertex(i).first / LengthUnit();
    yvertArray[i] = extruded->Vertex(i).second / LengthUnit();
  }

  // get Z sections parameters
  int nofZSections = extruded->NofZSections();
  double* zArray = new double[nofZSections];
  double* xoffsetArray = new double[nofZSections];
  double* yoffsetArray = new double[nofZSections];
  double* scaleArray = new double[nofZSections];
  for (int i = 0; i < nofZSections; i++) {
    zArray[i] = extruded->ZPosition(i) / LengthUnit();
    xoffsetArray[i] = extruded->Offset(i).first / LengthUnit();
    yoffsetArray[i] = extruded->Offset(i).second / LengthUnit();
    scaleArray[i] = extruded->Scale(i);
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<xtru  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = " >";
  std::string element4 = "<twoDimVertex  x=\"";
  std::string element5 = "y=\"";
  std::string element6 = "\" />";
  std::string element7 = "<section  zPosition=\"";
  std::string element8 = "zOrder=\"";
  std::string element9 = "xOffset=\"";
  std::string element10 = "yOffset=\"";
  std::string element11 = "scalingFactor=\"";
  std::string element12 = "</xtru>";
  std::string indention = fIndention + fkBasicIndention;

  // write xtru element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << element3 << std::endl;

  // write vertices
  for (int i = 0; i < nofVertices; i++) {
    fOutFile << indention << element4 << std::setw(fNW)
             << std::setprecision(fNP) << xvertArray[i] << quota << "  "
             << element5 << std::setw(fNW) << std::setprecision(fNP)
             << yvertArray[i] << element6 << std::endl;
  }

  // write polyplane elements
  for (int i = 0; i < nofZSections; i++) {
    fOutFile << indention << element7 << std::setw(fNW)
             << std::setprecision(fNP) << zArray[i] << quota << "  " << element8
             << std::setw(3) << i << quota << "  " << element9 << std::setw(fNW)
             << std::setprecision(fNP) << xoffsetArray[i] << quota << "  "
             << element10 << std::setw(fNW) << std::setprecision(fNP)
             << yoffsetArray[i] << quota << "  " << element11 << std::setw(fNW)
             << std::setprecision(fNP) << scaleArray[i] << element6
             << std::endl;
  }

  // close pcon element
  fOutFile << fIndention << element12 << std::endl << std::endl;

  delete[] xvertArray;
  delete[] yvertArray;
  delete[] zArray;
  delete[] xoffsetArray;
  delete[] yoffsetArray;
  delete[] scaleArray;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteHype(std::string name, const VGM::IHype* hype)
{
  /// Write VGM::IPara solid

  // get parameters
  double rin = hype->InnerRadius() / LengthUnit();
  double rout = hype->OuterRadius() / LengthUnit();
  double dz = hype->ZHalfLength() / LengthUnit();
  double stereoin = hype->InnerStereoAngle() / AngleUnit();
  double stereoout = hype->OuterStereoAngle() / AngleUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    dz *= 2.;
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<hype  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "rmin=\"";
  std::string element4 = "rmax=\"";
  std::string element5 = "inst=\"";
  std::string element6 = "outst=\"";
  std::string element7 = "z=\"";
  std::string element8 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << rin << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << rout << quota << std::endl
           << indention << element5 << std::setw(fNW) << std::setprecision(fNP)
           << stereoin << quota << "  " << element6 << std::setw(fNW)
           << std::setprecision(fNP) << stereoout << quota << std::endl
           << indention << element7 << std::setw(fNW) << std::setprecision(fNP)
           << dz << element8 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePara(std::string name, const VGM::IPara* para)
{
  /// Write VGM::IPara solid

  // get parameters
  double dx = para->XHalfLength() / LengthUnit();
  double dy = para->YHalfLength() / LengthUnit();
  double dz = para->ZHalfLength() / LengthUnit();
  double alpha = para->Alpha() / AngleUnit();
  double theta = UpdateAngle(para->Theta()) / AngleUnit();
  double phi = UpdateAngle(para->Phi()) / AngleUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    dx *= 2.;
    dy *= 2.;
    dz *= 2.;
  }

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
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << dx << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << dy << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << dz << quota
           << std::endl
           << indention << element6 << std::setw(fNW) << std::setprecision(fNP)
           << alpha << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << theta << quota << "  " << element8
           << std::setw(fNW) << std::setprecision(fNP) << phi << element9
           << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteParaboloid(
  std::string name, const VGM::IParaboloid* paraboloid)
{
  /// Write VGM::IPara solid

  // get parameters
  double rlo = paraboloid->RadiusMinusZ() / LengthUnit();
  double rhi = paraboloid->RadiusPlusZ() / LengthUnit();
  double dz = paraboloid->ZHalfLength() / LengthUnit();

  // switch rlo, rhi if rhi < rlo
  // to make sure that GDML can be loaded by Geant4, which does not allow rhi <
  // rlo
  if (rhi < rlo) {
    double tmp = rlo;
    rlo = rhi;
    rhi = tmp;
  }

  // convert half lengths to full lengths
  // if (fFullLengths) {
  //  dz *= 2.;
  //}

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<paraboloid  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "rlo=\"";
  std::string element4 = "rhi=\"";
  std::string element5 = "dz=\"";
  std::string element6 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << rlo << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << rhi << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << dz << element6
           << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePolycone(
  std::string name, const VGM::IPolycone* polycone)
{
  /// Write VGM::IPolycone solid

  // get profile parameters
  double sphi = polycone->StartPhi() / AngleUnit();
  double dphi = polycone->DeltaPhi() / AngleUnit();

  // get polycone Z planes parameters
  int nofZPlanes = polycone->NofZPlanes();
  double* rminArray = new double[nofZPlanes];
  double* rmaxArray = new double[nofZPlanes];
  double* zArray = new double[nofZPlanes];
  for (int i = 0; i < nofZPlanes; i++) {
    rminArray[i] = polycone->InnerRadiusValues()[i] / LengthUnit();
    rmaxArray[i] = polycone->OuterRadiusValues()[i] / LengthUnit();
    zArray[i] = polycone->ZValues()[i] / LengthUnit();
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<polycone  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "startphi=\"";
  std::string element4 = "deltaphi=\"";
  std::string element5 = "\" >";
  std::string element6 = "<zplane  z=\"";
  std::string element7 = "rmin=\"";
  std::string element8 = "rmax=\"";
  std::string element9 = "\" />";
  std::string element10 = "</polycone>";
  std::string indention = fIndention + fkBasicIndention;

  // write pcon element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << element5 << std::endl;

  // write polyplane elements
  for (int j = 0; j < nofZPlanes; j++) {

    fOutFile << indention << element6 << std::setw(fNW)
             << std::setprecision(fNP) << zArray[j] << quota << "  " << element7
             << std::setw(fNW) << std::setprecision(fNP) << rminArray[j]
             << quota << "  " << element8 << std::setw(fNW)
             << std::setprecision(fNP) << rmaxArray[j] << element9 << std::endl;
  }

  // close pcon element
  fOutFile << fIndention << element10 << std::endl << std::endl;

  delete[] rminArray;
  delete[] rmaxArray;
  delete[] zArray;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePolyhedra(
  std::string name, const VGM::IPolyhedra* polyhedra)
{
  /// Write VGM::IPolyhedra solid

  // get profile parameters
  double sphi = UpdateAngle(polyhedra->StartPhi()) / AngleUnit();
  double dphi = UpdateAngle(polyhedra->DeltaPhi()) / AngleUnit();

  // get polyhedra Z planes parameters
  int nofZPlanes = polyhedra->NofZPlanes();
  int nofSides = polyhedra->NofSides();
  double* rminArray = new double[nofZPlanes];
  double* rmaxArray = new double[nofZPlanes];
  double* zArray = new double[nofZPlanes];
  for (int i = 0; i < nofZPlanes; i++) {
    rminArray[i] = polyhedra->InnerRadiusValues()[i] / LengthUnit();
    rmaxArray[i] = polyhedra->OuterRadiusValues()[i] / LengthUnit();
    zArray[i] = polyhedra->ZValues()[i] / LengthUnit();
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<polyhedra  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "numsides=\"";
  std::string element4 = "startphi=\"";
  std::string element5 = "deltaphi=\"";
  std::string element6 = "\" >";
  std::string element7 = "<zplane  z=\"";
  std::string element8 = "rmin=\"";
  std::string element9 = "rmax=\"";
  std::string element10 = "\" />";
  std::string element11 = "</polyhedra>";
  std::string indention = fIndention + fkBasicIndention;

  // write polyhedra element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << nofSides << quota << std::endl
           << indention << element4 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element5 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << element6 << std::endl;

  // write polyplane elements
  for (int j = 0; j < nofZPlanes; j++) {

    fOutFile << indention << element7 << std::setw(fNW)
             << std::setprecision(fNP) << zArray[j] << quota << "  " << element8
             << std::setw(fNW) << std::setprecision(fNP) << rminArray[j]
             << quota << "  " << element9 << std::setw(fNW)
             << std::setprecision(fNP) << rmaxArray[j] << element10
             << std::endl;
  }

  // close pcon element
  fOutFile << fIndention << element11 << std::endl << std::endl;

  delete[] rminArray;
  delete[] rmaxArray;
  delete[] zArray;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteSphere(
  std::string name, const VGM::ISphere* sphere)
{
  /// Write VGM::ISphere solid

  // get parameters
  double rmin = sphere->InnerRadius() / LengthUnit();
  double rmax = sphere->OuterRadius() / LengthUnit();
  double sphi = UpdateAngle(sphere->StartPhi()) / AngleUnit();
  double dphi = UpdateAngle(sphere->DeltaPhi()) / AngleUnit();
  double stheta = UpdateAngle(sphere->StartTheta()) / AngleUnit();
  double dtheta = UpdateAngle(sphere->DeltaTheta()) / AngleUnit();

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
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << rmin << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << rmax << quota << std::endl
           << indention << element5 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element6 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << quota << "  " << element7
           << std::setw(fNW) << std::setprecision(fNP) << stheta << quota
           << "  " << element8 << std::setw(fNW) << std::setprecision(fNP)
           << dtheta << element9 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTessellatedSolid(
  std::string name, const VGM::ITessellatedSolid* tessellated)
{
  /// Write VGM::ITessellatedSolid solid

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<tessellated name=\"" + name + "\">";
  std::string element2 = "<triangular   ";
  std::string element3 = "<quadrangular ";
  std::string element4 = "  vertex";
  std::string element5 = "=\"";
  std::string element6 = "/>";
  std::string element8 = "</tessellated>";
  std::string indention = fIndention + fkBasicIndention;

  // write openning element
  fOutFile << fIndention << element1 << std::endl;

  // write triangular facets
  for (int i = 0; i < tessellated->NofFacets(); ++i) {
    int nofVertices = tessellated->NofVertices(i);
    if (nofVertices == 3)
      fOutFile << indention << element2;
    else
      fOutFile << indention << element3;

    for (int j = 0; j < nofVertices; ++j) {
      // Vertex position
      VGM::ThreeVector vertex = tessellated->Vertex(i, j);
      std::string positionRef = fMaps->FindPositionName(vertex);

      fOutFile << element4 << std::setw(1) << j + 1 << element5 << positionRef
               << quota;
    }
    fOutFile << element6 << std::endl;
  }

  // write closing element
  fOutFile << fIndention << element8 << std::endl << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTorus(std::string name, const VGM::ITorus* torus)
{
  /// Write VGM::ITorus solid

  // get parameters
  double rmin = torus->InnerRadius() / LengthUnit();
  double rmax = torus->OuterRadius() / LengthUnit();
  double rax = torus->AxialRadius() / LengthUnit();
  double sphi = UpdateAngle(torus->StartPhi()) / AngleUnit();
  double dphi = UpdateAngle(torus->DeltaPhi()) / AngleUnit();

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<torus  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "rmin=\"";
  std::string element4 = "rmax=\"";
  std::string element5 = "rtor=\"";
  std::string element6 = "startphi=\"";
  std::string element7 = "deltaphi=\"";
  std::string element8 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << rmin << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << rmax << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << rax << quota
           << std::endl
           << indention << element6 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << element8 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTrap(std::string name, const VGM::ITrap* trap)
{
  /// Write VGM::ITrap solid

  // get parameters
  double dz = trap->ZHalfLength() / LengthUnit();
  double theta = UpdateAngle(trap->Theta()) / AngleUnit();
  double phi = UpdateAngle(trap->Phi()) / AngleUnit();
  double y1 = trap->YHalfLengthMinusZ() / LengthUnit();
  double x1 = trap->XHalfLengthMinusZMinusY() / LengthUnit();
  double x2 = trap->XHalfLengthMinusZPlusY() / LengthUnit();
  double alpha1 = trap->AlphaMinusZ() / AngleUnit();
  double y2 = trap->YHalfLengthPlusZ() / LengthUnit();
  double x3 = trap->XHalfLengthPlusZMinusY() / LengthUnit();
  double x4 = trap->XHalfLengthPlusZPlusY() / LengthUnit();
  double alpha2 = trap->AlphaPlusZ() / AngleUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    dz *= 2.;
    y1 *= 2.;
    x1 *= 2.;
    x2 *= 2.;
    y2 *= 2.;
    x3 *= 2.;
    x4 *= 2.;
  }

  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<trap  lunit=\"cm\" aunit=\"degree\"";
  std::string element2 = "name=\"" + name + quota;
  std::string element3 = "z=\"";
  std::string element4 = "theta=\"";
  std::string element5 = "phi=\"";
  std::string element6 = "y1=\"";
  std::string element7 = "x1=\"";
  std::string element8 = "x2=\"";
  std::string element9 = "alpha1=\"";
  std::string element10 = "y2=\"";
  std::string element11 = "x3=\"";
  std::string element12 = "x4=\"";
  std::string element13 = "alpha2=\"";
  std::string element14 = "\" />";
  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << dz << quota << std::endl
           << indention << element4 << std::setw(fNW) << std::setprecision(fNP)
           << theta << quota << "  " << element5 << std::setw(fNW)
           << std::setprecision(fNP) << phi << quota << std::endl
           << indention << element6 << std::setw(fNW) << std::setprecision(fNP)
           << y1 << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << x1 << quota << "  " << element8
           << std::setw(fNW) << std::setprecision(fNP) << x2 << quota << "  "
           << element9 << std::setw(fNW) << std::setprecision(fNP) << alpha1
           << quota << std::endl
           << indention << element10 << std::setw(fNW) << std::setprecision(fNP)
           << y2 << quota << "  " << element11 << std::setw(fNW)
           << std::setprecision(fNP) << x3 << quota << "  " << element12
           << std::setw(fNW) << std::setprecision(fNP) << x4 << quota << "  "
           << element13 << std::setw(fNW) << std::setprecision(fNP) << alpha2
           << element14 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTrd(std::string name, const VGM::ITrd* trd)
{
  /// Write VGM::ITrd solid

  // get parameters
  double x1 = trd->XHalfLengthMinusZ() / LengthUnit();
  double x2 = trd->XHalfLengthPlusZ() / LengthUnit();
  double y1 = trd->YHalfLengthMinusZ() / LengthUnit();
  double y2 = trd->YHalfLengthPlusZ() / LengthUnit();
  double hz = trd->ZHalfLength() / LengthUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    x1 *= 2.;
    x2 *= 2.;
    y1 *= 2.;
    y2 *= 2.;
    hz *= 2.;
  }

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
           << indention << element2 << std::endl
           << indention << element3 << std::setw(fNW) << std::setprecision(fNP)
           << x1 << quota << "  " << element4 << std::setw(fNW)
           << std::setprecision(fNP) << x2 << quota << "  " << element5
           << std::setw(fNW) << std::setprecision(fNP) << y1 << quota << "  "
           << element6 << std::setw(fNW) << std::setprecision(fNP) << y2
           << quota << std::endl
           << indention << element7 << std::setw(fNW) << std::setprecision(fNP)
           << hz << element8 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteTubs(std::string name, const VGM::ITubs* tubs)
{
  /// Write tubs solid

  // get parameters
  double rmin = tubs->InnerRadius() / LengthUnit();
  double rmax = tubs->OuterRadius() / LengthUnit();
  double hz = tubs->ZHalfLength() / LengthUnit();
  double sphi = UpdateAngle(tubs->StartPhi()) / AngleUnit();
  double dphi = UpdateAngle(tubs->DeltaPhi()) / AngleUnit();

  // convert half lengths to full lengths
  if (fFullLengths) {
    hz *= 2.;
  }

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
           << indention << element2 << std::endl
           << indention << element4 << std::setw(fNW) << std::setprecision(fNP)
           << rmin << quota << "  " << element5 << std::setw(fNW)
           << std::setprecision(fNP) << rmax << quota << "  " << element3
           << std::setw(fNW) << std::setprecision(fNP) << hz << quota
           << std::endl
           << indention << element6 << std::setw(fNW) << std::setprecision(fNP)
           << sphi << quota << "  " << element7 << std::setw(fNW)
           << std::setprecision(fNP) << dphi << element8 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteNotSupportedSolid(std::string name)
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
  WriteBox(name, 1.0, 1.0, 1.0);
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteSimplePlacement(const std::string& volumeName,
  const std::string& positionRef, const std::string& rotationRef,
  bool isReflection)
{
  /// Write position with rotation with a given volume name

  // Update name
  std::string name = UpdateName(volumeName);

  // Compose element strings
  //
  std::string element0 = "\"/>";
  std::string element1 = "<physvol>";

  std::string element2 = "<volumeref ref=\"";
  element2.append(name);
  element2.append(element0);

  std::string element3 = "<positionref ref=\"";
  element3.append(positionRef);
  element3.append(element0);

  std::string element4 = "<rotationref ref=\"";
  element4.append(rotationRef);
  element4.append(element0);

  std::string element5 = "<scaleref    ref=\"";
  element5.append(std::string("scale_0"));
  element5.append(element0);

  std::string element6 = "</physvol>";

  std::string indention1 = fIndention + fkBasicIndention;
  std::string indention2 = fIndention + fkBasicIndention + fkBasicIndention;

  // Write element
  fOutFile << fIndention << element1 << std::endl
           << indention1 << element2 << std::endl
           << indention2 << element3 << std::endl
           << indention2 << element4 << std::endl;

  if (isReflection) fOutFile << indention2 << element5 << std::endl;

  fOutFile << fIndention << element6 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteMultiplePlacement(const std::string& volumeName,
  VGM::Axis axis, int nofReplicas, double width, double offset)
{
  /// Write multiple position

  std::string axisName;
  switch (axis) {
    case VGM::kXAxis:
      axisName = "kXAxis";
      break;
    case VGM::kYAxis:
      axisName = "kYAxis";
      break;
    case VGM::kZAxis:
      axisName = "kZAxis";
      break;
    case VGM::kRho:
      axisName = "kRho";
      break;
    case VGM::kPhi:
      axisName = "kPhi";
      break;
    case VGM::kRadial3D:
      axisName = "Undefined";
      break; // ADD WARNING HERE
    case VGM::kSphTheta:
      axisName = "Undefined";
      break;
    case VGM::kUnknownAxis:
      axisName = "Undefined";
      break;
  }

  // set units
  double width2;
  double offset2;
  std::string unit;
  if (axis != VGM::kPhi && axis != VGM::kSphTheta) {
    width2 = width / LengthUnit();
    offset2 = offset / LengthUnit();
    unit = "cm";
  }
  else {
    width2 = width / AngleUnit();
    offset2 = offset / AngleUnit();
    unit = "degree";
  }

  // Compose element strings
  //
  // compose element string template
  std::string quota = "\"";
  std::string element1 = "<divisionvol unit=\"";
  std::string element2 = "axis=\"";
  std::string element3 = "number=\"";
  std::string element4 = "offset=\"";
  std::string element5 = "width=\"";
  std::string element6 = "\">";

  std::string element7 = "<volumeref ref=\"";
  std::string element8 = "\"/>";
  std::string element9 = "</divisionvol>";

  std::string indention1 = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << unit << quota << std::endl
           << indention1 << element2 << axisName + quota << "  " << element3
           << nofReplicas << quota << "  " << element4 << std::setw(fNW + 1)
           << std::setprecision(fNP) << offset2 << quota << "  " << element5
           << std::setw(fNW + 1) << std::setprecision(fNP) << width2 << element6
           << std::endl
           << indention1 << element7 << volumeName << element8 << std::endl
           << fIndention << element9 << std::endl;
}

//
// public methods
//

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenFile(std::string filePath)
{
  // Opens output file

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
void XmlVGM::GDMLWriter::OpenDocument()
{
  // Write document opening;
  // Could be made customizable in future

  fOutFile
    << "<?xml version=\"1.0\" encoding=\"UTF-8\"\?>" << std::endl
    << "<gdml xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\""
    << std::endl
    << "      "
       "xsi:noNamespaceSchemaLocation=\"http://service-spi.web.cern.ch/"
       "service-spi/app/releases/GDML/GDML_2_10_0/src/GDMLSchema/gdml.xsd\">"
    << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenSection(const std::string& /*topVolume*/)
{
  // Write section opening

  // nothing to be done in GDML
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenPositions()
{
  // Open element for general definitions
  // (positions and rotations for generated XML files.)

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
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenMaterials()
{
  // Write materials opening

  std::string element = "<materials>";

  // write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenSolids()
{
  // Write solids opening

  std::string element = "<solids>";

  // write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenStructure()
{
  // Write structure opening.

  std::string element = "<structure>";

  // Write element
  fOutFile << fIndention << element << std::endl;

  // increase indention
  IncreaseIndention();
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::OpenComposition(
  const std::string& name, const std::string& materialName)
{
  // Write composition opening.

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

  std::string indention = fIndention + fkBasicIndention;

  // write element
  fOutFile << fIndention << element1 << std::endl
           << indention << element2 << std::endl
           << indention << element3 << std::endl;

  // increase indention
  IncreaseIndention();
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseFile()
{
  // Closes output file

  fOutFile.close();
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseDocument()
{
  // Write document closing

  fOutFile << "</gdml>" << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseSection(const std::string& topVolume)
{
  // Write section closing

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
  fOutFile << fIndention << element2 << fkBasicIndention << element3 << ">"
           << std::endl
           << indention << element4 << "/>" << std::endl
           << fIndention << element5 << std::endl
           << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::ClosePositions()
{
  // Do not close the element.
  // Rotations will be written in the same element as positions.
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseRotations()
{
  // Close element for general definitions
  // (positions and rotations for generated XML files.)

  // decrease indention
  DecreaseIndention();

  std::string element1 = "</define>";

  // write element
  fOutFile << fIndention << element1 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseMaterials()
{
  // Write materials closing

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
  // Close element for solids

  // decrease indention
  DecreaseIndention();

  std::string element1 = "</solids>";

  // write element
  fOutFile << fIndention << element1 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseStructure()
{
  // Close element for structure

  // decrease indention
  DecreaseIndention();

  std::string element = "</structure>";

  // write element
  fOutFile << fIndention << element << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::CloseComposition()
{
  // Write composition closing

  // decrease indention
  DecreaseIndention();

  // define element
  std::string element = "</volume>";

  // write element
  fOutFile << fIndention << element << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteIsotope(const VGM::IIsotope* isotope)
{
  // Write VGM::IElement

  std::string name = IsotopeName(isotope);
  name.append(fgkIsotopeNameExtension);
  RegisterName(name);

  // Get parameters
  int theZ = isotope->Z();
  int theN = isotope->N();
  double theA = isotope->A() / AtomicWeightUnit();

  // GDML does not allow N=0
  // Let's put =1 in this case
  if (theN == 0) theN = 1;

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<isotope  name=\"";

  std::string element2 = "Z=\"";
  std::string element3 = "N=\"";
  std::string element4 = "<atom type=\"A\" unit=\"g/mol\" value=\"";
  std::string element5 = "\" />";
  std::string element6 = "</isotope>";

  std::string indention = fIndention + fkBasicIndention;

  // Write isotope
  fOutFile << fIndention << element1 << name << quota1;
  for (int i = 0; i < 10 - int(name.size()); i++) fOutFile << " ";

  SmartPut(fOutFile, fNW - 2, fNP, 0, element2, theZ, quota2);

  // SmartPut(fOutFile, fNW-2, fNP, element3, theN, "\" >");
  // fOutFile << std::endl;
  fOutFile << element3 << std::setw(3) << theN << "\" >" << std::endl;

  fOutFile << indention;
  SmartPut(fOutFile, fNW - 2, fNP, 0, element4, theA, element5);
  fOutFile << std::endl;

  fOutFile << fIndention << element6 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteElement(const VGM::IElement* element)
{
  // Write VGM::IElement

  std::string name = UpdateName(element->Name(), fgkElementNameExtension);
  RegisterName(name);

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<element  name=\"";
  std::string element6 = "\" />";
  std::string element7 = "</element>";

  std::string indention = fIndention + fkBasicIndention;

  // Write element name
  fOutFile << fIndention << element1 << name << quota2;

  // Get parameters
  if (element->NofIsotopes() > 0) {

    std::string element2 = ">";
    std::string element3 = "<fraction n=\"";
    std::string element4 = "ref=\"";

    fOutFile << element2 << std::endl;
    for (int i = 0; i < element->NofIsotopes(); i++) {
      VGM::IIsotope* isotope = element->Isotope(i);
      std::string name2 = IsotopeName(isotope);
      name2.append(fgkIsotopeNameExtension);
      double natoms = element->RelAbundance(i);

      fOutFile << indention;
      SmartPut(fOutFile, fNW - 2, fNP, 0, element3, natoms, quota2);
      fOutFile << element4 << name2 << element6 << std::endl;
    }
  }
  else {
    double theZ = element->Z();
    int theN = (int)ClhepVGM::Round(element->N());
    double theA = element->A() / AtomicWeightUnit();

    // GDML does not allow N=0
    // Let's put =1 in this case
    if (theN == 0) theN = 1;

    std::string element3 = "Z=\"";
    std::string element4 = "N=\"";
    std::string element5 = "<atom type=\"A\" unit=\"g/mol\" value=\"";

    SmartPut(fOutFile, fNW - 2, fNP, 0, element3, theZ, quota2);
    // SmartPut(fOutFile, fNW-2, fNP, element3, theN, "\" >");
    // fOutFile << std::endl;
    fOutFile << element4 << std::setw(3) << theN << "\" >" << std::endl;

    fOutFile << indention;
    SmartPut(fOutFile, fNW - 2, fNP, 0, element5, theA, element6);
    fOutFile << std::endl;
  }

  fOutFile << fIndention << element7 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteMaterial(const VGM::IMaterial* material)
{
  // Write VGM::IMaterial

  std::string materialName = UpdateName(material->Name());
  RegisterName(materialName);

  // Get parameters
  double density = material->Density() / MassDensityUnit();
  std::string state;
  switch (material->State()) {
    case VGM::kSolid:
      state = "solid";
      break;
    case VGM::kLiquid:
      state = "liquid";
      break;
    case VGM::kGas:
      state = "gas";
      break;
    case VGM::kUndefined:
    default:
      state = "undefined";
  }
  double temperature = material->Temperature() / TemperatureUnit();
  double pressure = material->Pressure() / PressureUnit();

  // Compose material string template
  std::string quota = "\"  ";
  std::string element1 = "<material  name=\"";
  element1.append(materialName);
  element1.append(quota);

  std::string element2 = "state=\"";
  element2.append(state);
  element2.append(quota);
  element2.append(">");

  std::string element3 = "<D type=\"density\" unit=\"g/cm3\" value=\"";
  std::string element4 = "<T type=\"temperature\" unit=\"K\" value=\"";
  std::string element5 = "<P type=\"pressure\" unit=\"pascal\" value=\"";
  std::string element6 = "<fraction n=\"";
  std::string element7 = "ref=\"";
  std::string element8 = "\"/>";
  std::string element9 = "</material>";

  std::string indention = fIndention + fkBasicIndention;

  // Write element
  fOutFile << fIndention << element1 << element2 << std::endl;

  fOutFile << indention;
  SmartPut(fOutFile, fNW + 1, fNP, 0, element3, density, element8);
  fOutFile << std::endl;

  if (temperature != fgkSTPTemperature) {
    fOutFile << indention;
    SmartPut(fOutFile, fNW + 1, fNP, 0, element4, temperature, element8);
    fOutFile << std::endl;
  }

  if (pressure != fgkSTPPressure) {
    fOutFile << indention;
    SmartPut(fOutFile, fNW + 1, fNP, 0, element5, pressure, element8);
    fOutFile << std::endl;
  }

  for (int i = 0; i < int(material->NofElements()); i++) {
    double fraction = material->MassFraction(i);
    std::string elementName =
      UpdateName(material->Element(i)->Name(), fgkElementNameExtension);

    fOutFile << indention;
    SmartPut(fOutFile, fNW, fNP, 0, element6, fraction, quota);
    fOutFile << element7 << elementName << element8 << std::endl;
  }

  fOutFile << fIndention << element9 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteSolid(std::string volumeName,
  const VGM::ISolid* solid, std::string /*materialName*/)
{
  // Finds solid concrete type and calls writing function.
  // For not yet implemented solids, only XML comment element is written.

  std::string solidName = UpdateName(volumeName, fgkSolidNameExtension);
  RegisterName(solidName);

  VGM::SolidType solidType = solid->Type();
  if (solidType == VGM::kArb8) {
    const VGM::IArb8* arb8 = dynamic_cast<const VGM::IArb8*>(solid);
    WriteArb8(solidName, arb8);
    return;
  }
  else if (solidType == VGM::kBox) {
    const VGM::IBox* box = dynamic_cast<const VGM::IBox*>(solid);
    WriteBox(solidName, box);
    return;
  }
  else if (solidType == VGM::kCons) {
    const VGM::ICons* cons = dynamic_cast<const VGM::ICons*>(solid);
    WriteCons(solidName, cons);
    return;
  }
  else if (solidType == VGM::kCtubs) {
    const VGM::ICtubs* ctubs = dynamic_cast<const VGM::ICtubs*>(solid);
    WriteCtubs(solidName, ctubs);
    return;
  }
  else if (solidType == VGM::kEllipsoid) {
    const VGM::IEllipsoid* ellipsoid =
      dynamic_cast<const VGM::IEllipsoid*>(solid);
    WriteEllipsoid(solidName, ellipsoid);
    return;
  }
  else if (solidType == VGM::kEltu) {
    const VGM::IEllipticalTube* eltu =
      dynamic_cast<const VGM::IEllipticalTube*>(solid);
    WriteEllipticalTube(solidName, eltu);
    return;
  }
  else if (solidType == VGM::kExtruded) {
    const VGM::IExtrudedSolid* extruded =
      dynamic_cast<const VGM::IExtrudedSolid*>(solid);
    WriteExtrudedSolid(solidName, extruded);
    return;
  }
  else if (solidType == VGM::kHype) {
    const VGM::IHype* hype = dynamic_cast<const VGM::IHype*>(solid);
    WriteHype(solidName, hype);
    return;
  }
  else if (solidType == VGM::kPara) {
    const VGM::IPara* para = dynamic_cast<const VGM::IPara*>(solid);
    WritePara(solidName, para);
    return;
  }
  else if (solidType == VGM::kParaboloid) {
    const VGM::IParaboloid* paraboloid =
      dynamic_cast<const VGM::IParaboloid*>(solid);
    WriteParaboloid(solidName, paraboloid);
    return;
  }
  else if (solidType == VGM::kPolycone) {
    const VGM::IPolycone* polycone = dynamic_cast<const VGM::IPolycone*>(solid);
    WritePolycone(solidName, polycone);
    return;
  }
  else if (solidType == VGM::kPolyhedra) {
    const VGM::IPolyhedra* polyhedra =
      dynamic_cast<const VGM::IPolyhedra*>(solid);
    WritePolyhedra(solidName, polyhedra);
    return;
  }
  else if (solidType == VGM::kSphere) {
    const VGM::ISphere* sphere = dynamic_cast<const VGM::ISphere*>(solid);
    WriteSphere(solidName, sphere);
    return;
  }
  else if (solidType == VGM::kTessellated) {
    const VGM::ITessellatedSolid* tessellated =
      dynamic_cast<const VGM::ITessellatedSolid*>(solid);
    WriteTessellatedSolid(solidName, tessellated);
    return;
  }
  else if (solidType == VGM::kTorus) {
    const VGM::ITorus* torus = dynamic_cast<const VGM::ITorus*>(solid);
    WriteTorus(solidName, torus);
    return;
  }
  else if (solidType == VGM::kTrap) {
    const VGM::ITrap* trap = dynamic_cast<const VGM::ITrap*>(solid);
    WriteTrap(solidName, trap);
    return;
  }
  else if (solidType == VGM::kTrd) {
    const VGM::ITrd* trd = dynamic_cast<const VGM::ITrd*>(solid);
    WriteTrd(solidName, trd);
    return;
  }
  else if (solidType == VGM::kTubs) {
    const VGM::ITubs* tubs = dynamic_cast<const VGM::ITubs*>(solid);
    WriteTubs(solidName, tubs);
    return;
  }
  else if (solidType == VGM::kBoolean) {
    const VGM::IBooleanSolid* boolean =
      dynamic_cast<const VGM::IBooleanSolid*>(solid);
    WriteBooleanSolid(solidName, boolean);
    return;
  }

  // Not supported solid
  WriteNotSupportedSolid(solidName);
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePosition(
  const std::string& name, const VGM::Transform& transform)
{
  // Write position element with a given name

  // get parameters
  double x = transform[VGM::kDx] / LengthUnit();
  double y = transform[VGM::kDy] / LengthUnit();
  double z = transform[VGM::kDz] / LengthUnit();

  // compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<position  name=";
  std::string posName = AppendName(quota1 + name + quota1, 12);

  std::string element2 = "x=\"";
  std::string element3 = "y=\"";
  std::string element4 = "z=\"";
  std::string element5 = "\"  unit=\"cm\" />";

  // write element
  fOutFile << fIndention << element1 << posName;

  SmartPut(fOutFile, fNW + 1, fNP, fgkCarTolerance, element2, x, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, fgkCarTolerance, element3, y, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, fgkCarTolerance, element4, z, "");

  fOutFile << element5 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteRotation(
  const std::string& name, const VGM::Transform& transform)
{
  // Write rotation element with a given name

  VGM::Transform invTransform = ClhepVGM::Inverse(transform);

  // Get parameters
  double angleX = invTransform[VGM::kAngleX] / AngleUnit();
  double angleY = invTransform[VGM::kAngleY] / AngleUnit();
  double angleZ = invTransform[VGM::kAngleZ] / AngleUnit();

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<rotation  name=";
  std::string rotName = AppendName(quota1 + name + quota1, 12);

  std::string element2 = "x=\"";
  std::string element3 = "y=\"";
  std::string element4 = "z=\"";
  std::string element5 = "\"  unit=\"degree\" />";

  // Write element
  fOutFile << fIndention << element1 << rotName;

  SmartPut(fOutFile, fNW + 1, fNP, fgkAngTolerance, element2, angleX, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, fgkAngTolerance, element3, angleY, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, fgkAngTolerance, element4, angleZ, "");

  fOutFile << element5 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteScale(const std::string& name)
{
  // Write scale element with a given name with reflectionZ

  // Get parameters
  double scaleX = 1.0;
  double scaleY = 1.0;
  double scaleZ = -1.0;

  // Compose element string template
  std::string quota1 = "\"";
  std::string quota2 = "\"  ";
  std::string element1 = "<scale     name=";
  std::string rotName = AppendName(quota1 + name + quota1, 12);

  std::string element2 = "x=\"";
  std::string element3 = "y=\"";
  std::string element4 = "z=\"";
  std::string element5 = "\"  />";

  // Write element
  fOutFile << fIndention << element1 << rotName;

  SmartPut(fOutFile, fNW + 1, fNP, 0, element2, scaleX, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, 0, element3, scaleY, quota2);
  SmartPut(fOutFile, fNW + 1, fNP, 0, element4, scaleZ, "");

  fOutFile << element5 << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WritePlacement(const VGM::IPlacement& placement)
{

  VGM::PlacementType placementType = placement.Type();

  if (placementType == VGM::kSimplePlacement) {

    // simple placement
    VGM::Transform transform = placement.Transformation();

    // Get position
    std::string positionRef = fMaps->FindPositionName(transform);

    // Get rotation
    std::string rotationRef = fMaps->FindRotationName(transform);

    // If boolean solid that have to be reflected
    // set reflection to the transformation
    VGM::IBooleanSolid* booleanSolid =
      dynamic_cast<VGM::IBooleanSolid*>(placement.Volume()->Solid());
    if (booleanSolid && booleanSolid->ToBeReflected())
      transform[VGM::kReflZ] = 1;

    // If paraboloid that have to be reflected,
    // set reflection to the transformation
    VGM::IParaboloid* paraboloid =
      dynamic_cast<VGM::IParaboloid*>(placement.Volume()->Solid());
    if (paraboloid && paraboloid->RadiusPlusZ() <= paraboloid->RadiusMinusZ())
      transform[VGM::kReflZ] = 1;

    // Get info about reflection
    bool isReflection = ClhepVGM::HasReflection(transform);

    WriteSimplePlacement(
      placement.Volume()->Name(), positionRef, rotationRef, isReflection);
  }
  else if (placementType == VGM::kMultiplePlacement) {

    // get parameters
    VGM::Axis axis;
    int nReplicas;
    double width;
    double offset;
    double halfGap; // not supported
    placement.MultiplePlacementData(axis, nReplicas, width, offset, halfGap);

    if (halfGap != 0.) {
      std::cerr << "+++ Warning  +++" << std::endl;
      std::cerr << "  XmlVGM::Writer::WritePlacement: " << std::endl;
      std::cerr << "  Multiple placement with a half gap is not supported. "
                << std::endl;
      std::cerr << "  The half gap parameter will be ignored. " << std::endl;
    }

    // write multiple position
    WriteMultiplePlacement(
      placement.Volume()->Name(), axis, nReplicas, width, offset);
  }
  else {
    std::cerr << "+++ Warning  +++" << std::endl;
    std::cerr << "    XmlVGM::GDMLExporter::ProcessVolume: " << std::endl;
    std::cerr << "    Unknown placement type. " << std::endl;
    std::cerr << "    Volume \"" << placement.Name() << "\" was not converted."
              << std::endl;
  }
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::WriteEmptyLine()
{
  // Write empty line.

  fOutFile << std::endl;
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::IncreaseIndention()
{
  // Increase indention

  fIndention.append(fkBasicIndention);
}

//_____________________________________________________________________________
void XmlVGM::GDMLWriter::DecreaseIndention()
{
  // Decrease indention

  fIndention.replace(fIndention.find(fkBasicIndention), 3, "");
}
