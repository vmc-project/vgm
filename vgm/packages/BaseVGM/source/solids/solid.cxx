// $Id$
//
// VGM::ISolid output stream and utility function
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/ISolid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ISolid& solid)
{
  out << VGM::SolidTypeName(solid.Type()) << "  \""
      << solid.Name() << "\"";     
  return solid.Put(out); 
}

//_____________________________________________________________________________
std::string VGM::SolidTypeName(VGM::SolidType typeId)
{
  // Returns the solid type name for specified typeId
  switch (typeId) {
    case kBox:          return "Box";       break;
    case kCons:         return "Cons";      break;
    case kPara:         return "Para";      break;
    case kPolycone:     return "Polycone";  break;
    case kPolyhedra:    return "Polygone";  break;
    case kSphere:       return "Sphere";    break;
    case kTorus:        return "Torus" ;    break;
    case kTrap:         return "Trap";      break;
    case kTrd:          return "Trd";       break;
    case kTubs:         return "Tubs";      break;
    case kBoolean:      return "Boolean";   break;
    case kUnknownSolid: return "Unknown";   break;
    default:            return "Undefined"; break;
  };
}   
