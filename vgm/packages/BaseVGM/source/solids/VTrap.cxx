// $Id$
//
// Class VTrap
// ---------------
// The ABC for trap solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

#include "BaseVGM/solids/VTrap.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITrap& trap)
{
  const VGM::ISolid& trapSolid = trap;
  out << trapSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VTrap::VTrap()
  : VGM::ITrap() {
//  
}


//_____________________________________________________________________________
BaseVGM::VTrap::~VTrap() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTrap::Put(std::ostream& out) const
{
  out << "  hz = "     << ZHalfLength()/mm             << "mm" 
      << "  theta = "  << Theta()/deg                  << "deg" 
      << "  phi = "    << Phi()/deg                    << "deg" 
      << "  hy1 = "    << YHalfLengthMinusZ()/mm       << "mm" 
      << "  hx1 = "    << XHalfLengthMinusZMinusY()/mm << "mm" 
      << "  hx2 = "    << XHalfLengthMinusZPlusY()/mm  << "mm" 
      << "  alpha1 = " << AlphaMinusZ()                << "deg" 
      << "  hy2 = "    << YHalfLengthPlusZ()/mm        << "mm" 
      << "  hx3 = "    << XHalfLengthPlusZMinusY()/mm  << "mm" 
      << "  hx4 = "    << XHalfLengthPlusZPlusY()/mm   << "mm"
      << "  alpha2 = " << AlphaPlusZ()                 << "deg"; 
  return out; 
}

