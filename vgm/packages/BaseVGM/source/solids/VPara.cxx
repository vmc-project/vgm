// $Id$
//
// Class VPara
// ---------------
// The ABC for para solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

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
  : VGM::IPara() 
{
/// Default constructor  
}

//_____________________________________________________________________________
BaseVGM::VPara::~VPara() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VPara::Put(std::ostream& out) const
{
  out << "  hx = "    << XHalfLength() << "mm" 
      << "  hy = "    << YHalfLength() << "mm" 
      << "  hz = "    << ZHalfLength() << "mm" 
      << "  alpha = " << Alpha()       << "deg"
      << "  theta = " << Theta()       << "deg"
      << "  phi = "   << Phi()         << "deg";
  return out; 
}

