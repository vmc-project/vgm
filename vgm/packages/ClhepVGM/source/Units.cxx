// $Id$

// -----------------------------------------------------------------------
// The ClhepVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Units
// ------------------
// Conversion from CLHEP physical units to VGM units..
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "CLHEP/Units/SystemOfUnits.h" 

#include <iostream>
#include <cstdlib>

using CLHEP::mm;
using CLHEP::cm;
using CLHEP::cm3;
using CLHEP::deg;
using CLHEP::g;
using CLHEP::mole;
using CLHEP::kelvin;
using CLHEP::atmosphere;

//
// static const data members
//

const double ClhepVGM::Units::fgkLength       = 1./mm;
const double ClhepVGM::Units::fgkAngle        = 1./deg;
const double ClhepVGM::Units::fgkMassDensity  = 1./(g/cm3);
const double ClhepVGM::Units::fgkAtomicWeight = 1./(g/mole);
const double ClhepVGM::Units::fgkTemperature  = 1./kelvin;
const double ClhepVGM::Units::fgkPressure     = 1./atmosphere;

//_____________________________________________________________________________
ClhepVGM::Units::Units() 
{
/// Protected default constructor
}
  
//_____________________________________________________________________________
ClhepVGM::Units::~Units() {
//
}

//
// public functions
//

//_____________________________________________________________________________
double ClhepVGM::Units::AxisUnit(VGM::Axis axis)
{
  if (axis == VGM::kXAxis || 
      axis == VGM::kYAxis || 
      axis == VGM::kZAxis ||
      axis == VGM::kRho   || 
      axis == VGM::kRadial3D) { 
    
    return Length();
  }  

  if (axis == VGM::kPhi || 
      axis == VGM::kSphTheta) {
    return Angle();
  }  

  // axis == kUndefined  
  std::cerr << "    ClhepVGM::Units::AxisUnit:"       << std::endl; 
  std::cerr << "    Undefined axis"                 << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);
}

//_____________________________________________________________________________
double ClhepVGM::Units::Length()       
{ 
  return fgkLength; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Length(double clhepUnit)       
{ 
  return fgkLength * clhepUnit; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Angle()        
{ 
  return fgkAngle; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Angle(double clhepUnit)        
{ 
  return fgkAngle * clhepUnit; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::MassDensity()  
{ 
  return fgkMassDensity; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::MassDensity(double clhepUnit)  
{ 
  return fgkMassDensity * clhepUnit; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::AtomicWeight() 
{ 
  return fgkAtomicWeight; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::AtomicWeight(double clhepUnit) 
{ 
  return fgkAtomicWeight * clhepUnit; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Temperature() 
{ 
  return fgkTemperature; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Temperature(double clhepUnit) 
{ 
  return fgkTemperature * clhepUnit; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Pressure() 
{ 
  return fgkPressure; 
}

//_____________________________________________________________________________
double ClhepVGM::Units::Pressure(double clhepUnit) 
{ 
  return fgkPressure * clhepUnit; 
}

