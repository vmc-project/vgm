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
// Class VParaboloid
// -----------------
// The ABC for paraboloid solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/solids/VParaboloid.h"

//_____________________________________________________________________________
std::ostream& operator<<(std::ostream& out, const VGM::IParaboloid& paraboloid)
{
  const VGM::ISolid& paraboloidSolid = paraboloid;
  out << paraboloidSolid;
  return out; 
}

//_____________________________________________________________________________
BaseVGM::VParaboloid::VParaboloid()
  : VGM::IParaboloid() 
{
/// Default constructor  
}


//_____________________________________________________________________________
BaseVGM::VParaboloid::~VParaboloid() {
//
}

//_____________________________________________________________________________
std::ostream& BaseVGM::VParaboloid::Put(std::ostream& out) const
{
  out << "  r1 = "  << RadiusMinusZ() << "mm" 
      << "  r2 = "  << RadiusPlusZ()  << "mm" 
      << "  hz = "  << ZHalfLength()  << "mm"; 
  return out; 
}

