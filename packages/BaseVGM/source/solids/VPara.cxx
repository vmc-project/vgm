// $Id$
//
// Class VPara
// ---------------
// The ABC for para solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

#include "BaseVGM/solids/VPara.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IPara& para)
{
  const VGM::ISolid& paraSolid = para;
  out << paraSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VPara::VPara()
  : VGM::IPara() {
//  
}

//_____________________________________________________________________________
BaseVGM::VPara::~VPara() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VPara::Put(std::ostream& out) const
{
  out << "  hx = "    << XHalfLength()/mm << "mm" 
      << "  hy = "    << YHalfLength()/mm << "mm" 
      << "  hz = "    << ZHalfLength()/mm << "mm" 
      << "  alpha = " << Alpha()/deg      << "deg"
      << "  theta = " << Theta()/deg      << "deg"
      << "  phi = "   << Phi()/deg        << "deg";
  return out; 
}

