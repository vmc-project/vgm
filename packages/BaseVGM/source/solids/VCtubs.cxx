// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VCtubs
// ---------------
// The ABC for cut tubs solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VCtubs.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::ICtubs& ctubs)
{
  const VGM::ISolid& ctubsSolid = ctubs;
  out << ctubsSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VCtubs::VCtubs()
  : VGM::ICtubs() 
{
/// Default constructor  
}

//_____________________________________________________________________________
BaseVGM::VCtubs::~VCtubs() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VCtubs::Put(std::ostream& out) const
{
  out << "  rin = "    << InnerRadius()  << "mm" 
      << "  rout = "   << OuterRadius()  << "mm" 
      << "  hz = "     << ZHalfLength()  << "mm" 
      << "  sphi = "   << StartPhi()     << "deg" 
      << "  dphi = "   << DeltaPhi()     << "deg"
      << "  nlow = ("  << NxLow() << ", " << NyLow() << ", " << NzLow() << ")"
      << "  nhigh = (" << NxHigh() << ", " << NyHigh() << ", " << NzHigh() << ")";
      
  return out; 
}

