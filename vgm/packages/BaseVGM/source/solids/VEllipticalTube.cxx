// $Id$
//
// Class VEllipticalTube
// ---------------------
// The ABC for elliptical tube solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VEllipticalTube.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IEllipticalTube& eltu)
{
  const VGM::ISolid& eltuSolid = eltu;
  out << eltuSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VEllipticalTube::VEllipticalTube()
  : VGM::IEllipticalTube() 
{
/// Default constructor  
}

//_____________________________________________________________________________
BaseVGM::VEllipticalTube::~VEllipticalTube() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VEllipticalTube::Put(std::ostream& out) const
{
  out << "  dx = "  << Dx()  << "mm" 
      << "  dy = "  << Dy()  << "mm" 
      << "  hz = "  << ZHalfLength()  << "mm"; 
  return out; 
}

