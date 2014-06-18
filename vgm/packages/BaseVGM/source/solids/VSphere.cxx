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
// Class VSphere
// ---------------
// The ABC for sphere solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

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
  : VGM::ISphere()
{
/// Default constructor  
}


//_____________________________________________________________________________
BaseVGM::VSphere::~VSphere() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VSphere::Put(std::ostream& out) const
{
  out << "  rin = "    << InnerRadius() << "mm" 
      << "  rout = "   << OuterRadius() << "mm" 
      << "  sphi = "   << StartPhi()    << "deg"
      << "  dphi = "   << DeltaPhi()    << "deg"
      << "  stheta = " << StartTheta()  << "deg"
      << "  dtheta = " << DeltaTheta()  << "deg";
  return out; 
}

