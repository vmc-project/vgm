// $Id$
//
// VGM::IMaterial output stream
// ------------------------
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IElement.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IMaterial& material)
{
  out << "Material: " << "\"" << material.Name() << "\""
      << "  density " << material.Density() << " g/cm3"
      << "  radlen "  << material.RadiationLength()/10.  << " cm"
      << "  intlen "  << material.NuclearInterLength()/10. << " cm"
      << std::endl;
      
  for (int i=0; i<material.NofElements(); i++) {
    out << "   "
        << i << "th element: "        
        << "  Z = "  << material.Element(i)->Z() \
        << "  A = "  << material.Element(i)->A() << " g/mole"  
        << "  fractionMass = " << material.MassFraction(i)*100. << " %";
    if (i<material.NofElements()-1) out <<std::endl;
  }       
    
  return out;    
}
