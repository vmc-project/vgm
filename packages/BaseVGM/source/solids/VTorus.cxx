// $Id$
//
// Class VTorus
// ---------------
// The ABC for torus solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VTorus.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITorus& torus)
{
  const VGM::ISolid& torusSolid = torus;
  out << torusSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VTorus::VTorus()
  : VGM::ITorus() {
//  
}


//_____________________________________________________________________________
BaseVGM::VTorus::~VTorus() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTorus::Put(std::ostream& out) const
{
  out << "  rin = "  << InnerRadius() << "mm" 
      << "  rout = " << OuterRadius() << "mm" 
      << "  rtor = " << AxialRadius() << "mm" 
      << "  sphi = " << StartPhi()    << "deg" 
      << "  dphi = " << DeltaPhi()    << "deg"; 
  return out; 
}

