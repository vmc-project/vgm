// $Id$
//
// VGM::IElement output stream
// ------------------------
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IElement.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IElement& element)
{
  out << "Element: " 
      << "\"" << element.Name() << "\"  "
      << "\"" << element.Symbol() << "\""
      << "  Z = "  << element.Z()
      << "  N = "  << element.N()
      << "  A = "  << element.A() << " g/mole";  
    
  return out;    
}
