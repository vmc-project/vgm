// $Id$
//
// Class VTrd
// ---------------
// The ABC for trd solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

#include "BaseVGM/solids/VTrd.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ITrd& trd)
{
  const VGM::ISolid& trdSolid = trd;
  out << trdSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VTrd::VTrd()
  : VGM::ITrd() {
//  
}

//_____________________________________________________________________________
BaseVGM::VTrd::~VTrd() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VTrd::Put(std::ostream& out) const
{
  out << "  hx1 = " << XHalfLengthMinusZ()/mm << "mm" 
      << "  hx2 = " << XHalfLengthPlusZ()/mm  << "mm" 
      << "  hy1 = " << YHalfLengthMinusZ()/mm << "mm" 
      << "  hy2 = " << YHalfLengthPlusZ()/mm  << "mm" 
      << "  hz = "  << ZHalfLength()/mm       << "mm"; 
  return out; 
}

