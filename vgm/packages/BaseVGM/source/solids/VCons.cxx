// $Id$
//
// Class VCons
// ---------------
// The ABC for cons solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

#include "BaseVGM/solids/VCons.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ICons& cons)
{
  const VGM::ISolid& consSolid = cons;
  out << consSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VCons::VCons()
  : VGM::ICons() {
//  
}


//_____________________________________________________________________________
BaseVGM::VCons::~VCons() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VCons::Put(std::ostream& out) const
{
  out << "  rin1 = "  << InnerRadiusMinusZ()/mm << "mm" 
      << "  rout1 = " << OuterRadiusMinusZ()/mm << "mm" 
      << "  rin2 = "  << InnerRadiusPlusZ()/mm  << "mm" 
      << "  rout2 = " << OuterRadiusPlusZ()/mm  << "mm" 
      << "  hz = "    << ZHalfLength()/mm       << "mm" 
      << "  sphi = "  << StartPhi()/deg         << "deg"
      << "  dphi = "  << DeltaPhi()/deg         << "deg";
  return out; 
}

