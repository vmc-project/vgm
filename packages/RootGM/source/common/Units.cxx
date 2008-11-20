// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Units
// ------------------
// Conversion from Root physical units to VGM units.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/common/Units.h"

#include <iostream>
#include <cstdlib>

//
// static const data members
//

const double RootGM::Units::fgkLength       = 10.;          // cm 
const double RootGM::Units::fgkAngle        = 1.;           // deg
const double RootGM::Units::fgkMassDensity  = 1.;           // g/cm3;
const double RootGM::Units::fgkAtomicWeight = 1.;           // g/mole;
const double RootGM::Units::fgkTemperature  = 1.;           // kelvin
const double RootGM::Units::fgkPressure     = 1./6.32420e+8;// MeV/mm3

//_____________________________________________________________________________
RootGM::Units::Units() 
{
/// Protected default constructor
}
  
//_____________________________________________________________________________
RootGM::Units::~Units() {
//
}

//
// public functions
//

//_____________________________________________________________________________
double RootGM::Units::AxisUnit(VGM::Axis axis)
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
  std::cerr << "    RootGM::Units::AxisUnit:"       << std::endl; 
  std::cerr << "    Undefined axis"                 << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);
}
