// $Id$
//
// Class VSphere
// ---------------
// The ABC for sphere solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

#include "BaseVGM/solids/VSphere.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ISphere& sphere)
{
  const VGM::ISolid& sphereSolid = sphere;
  out << sphereSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VSphere::VSphere()
  : VGM::ISphere() {
//  
}


//_____________________________________________________________________________
BaseVGM::VSphere::~VSphere() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VSphere::Put(std::ostream& out) const
{
  out << "  rin = "    << InnerRadius()/mm << "mm" 
      << "  rout = "   << OuterRadius()/mm << "mm" 
      << "  sphi = "   << StartPhi()/deg   << "deg"
      << "  dphi = "   << DeltaPhi()/deg   << "deg"
      << "  stheta = " << StartTheta()/deg << "deg"
      << "  dtheta = " << DeltaTheta()/deg << "deg";
  return out; 
}

