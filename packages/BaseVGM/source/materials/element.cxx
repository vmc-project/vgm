// $Id$
//
// VGM::IElement output stream
// ------------------------
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IElement.h"
#include "VGM/materials/IIsotope.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IElement& element)
{
  out << "Element: " 
      << "\"" << element.Name() << "\"  "
      << "\"" << element.Symbol() << "\""
      << "  Z = "  << element.Z()
      << "  N = "  << element.N()
      << "  A = "  << element.A() << " g/mole";

  for ( int i=0; i<element.NofIsotopes(); i++ ) {
    if ( i == 0 ) out << std::endl;
    out << "     "
        << i << "th isotope: " << *element.Isotope(i)
        << "  abundance: " << element.RelAbundance(i) * 100. << "%";
    if ( i<element.NofIsotopes()-1 ) out << std::endl;    
  }       
    
  return out;    
}
