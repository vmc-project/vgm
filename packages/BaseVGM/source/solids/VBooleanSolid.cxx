// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VBooleanSolid
// --------------------
// The ABC for Boolean solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <math.h>

#include "BaseVGM/common/utilities.h"
#include "BaseVGM/solids/VBooleanSolid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IBooleanSolid& boolean)
{
  const VGM::ISolid& booleanSolid = boolean;
  out << booleanSolid;
  return out; 
}

//_____________________________________________________________________________
std::string VGM::BooleanTypeName(VGM::BooleanType typeId)
{
  // Returns the Boolean solid type name for specified typeId
  switch (typeId) {
    case kIntersection:   return "Intersection"; break;
    case kSubtraction:    return "Subtraction";  break;
    case kUnion:          return "Union";        break;
    case kUnknownBoolean: return "Unknown";      break;
    default:              return "Undefined";    break;
  };
}   

//_____________________________________________________________________________
BaseVGM::VBooleanSolid::VBooleanSolid()
  : VGM::IBooleanSolid() 
{
/// Default constructor  
}

//_____________________________________________________________________________
BaseVGM::VBooleanSolid::~VBooleanSolid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VBooleanSolid::Put(std::ostream& out) const
{
  out << "  "
      << VGM::BooleanTypeName(BoolType()) << ": " << std:: endl
      << "  ConstituentA = " << *ConstituentSolidA() << std:: endl
      << "  ConstituentB = " << *ConstituentSolidB() << std:: endl 
      << "  Displacement translation (object):  ( " 
      << Displacement()[VGM::kDx] << ",  "
      << Displacement()[VGM::kDy]  << ",  "
      << Displacement()[VGM::kDz] << ") mm " << std:: endl
      << "  Displacement rotation (object):  (" 
      << Displacement()[VGM::kAngleX] << ",  "
      << Displacement()[VGM::kAngleY] << ",  "
      << Displacement()[VGM::kAngleZ] << ") deg  ";
  
  if ( Round(Displacement()[6]) == 0 )
    out << "  no reflectionZ";
  else
    out << "  reflectionZ";
       
      
  return out; 
}

