// $Id$
//
// Class VBooleanSolid
// --------------------
// The ABC for Boolean solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

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
  : VGM::IBooleanSolid() {
//  
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
      << Displacement()[0]/mm << ",  "
      << Displacement()[1]/mm  << ",  "
      << Displacement()[2]/mm << ") mm " << std:: endl
      << "  Displacement rotation (object):  (" 
      << Displacement()[3]/deg << ",  "
      << Displacement()[4]/deg << ",  "
      << Displacement()[5]/deg << ") deg  ";
  
  if (round(Displacement()[6]) == 0 )
    out << "  no reflectionZ";
  else
    out << "  reflectionZ";
       
      
  return out; 
}

