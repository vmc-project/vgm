// $Id$
//
// Class VTubs
// ---------------
// The ABC for tubs solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VTubs.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITubs& tubs)
{
  const VGM::ISolid& tubsSolid = tubs;
  out << tubsSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VTubs::VTubs()
  : VGM::ITubs() {
//  
}


//_____________________________________________________________________________
BaseVGM::VTubs::~VTubs() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTubs::Put(std::ostream& out) const
{
  out << "  rin = "  << InnerRadius()  << "mm" 
      << "  rout = " << OuterRadius()  << "mm" 
      << "  hz = "   << ZHalfLength()  << "mm" 
      << "  sphi = " << StartPhi()     << "deg" 
      << "  dphi = " << DeltaPhi()     << "deg";
  return out; 
}

