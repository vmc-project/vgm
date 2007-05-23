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
// Class VPlacement
// -----------------
// The abstract base class to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/volumes/IVolume.h"

#include "BaseVGM/volumes/VPlacement.h"

#include <iostream>

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement(VGM::IVolume* volume, 
                                VGM::IVolume* motherVolume)
  : VGM::IPlacement(),
    fVolume(volume),
    fMotherVolume(motherVolume) 
{
/// Standard constructor

  // Update mother volume 
  if (motherVolume)
    motherVolume->AddDaughter(this);
  else
    // check if top volume not yet set and
    // set top volume here  
    ;
}

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement() 
  : VGM::IPlacement() 
{
/// Protected default constructor
} 

//_____________________________________________________________________________
BaseVGM::VPlacement::VPlacement(const VPlacement& rhs) 
  : VGM::IPlacement(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VPlacement::~VPlacement() {
//
}

//_____________________________________________________________________________
VGM::IVolume* BaseVGM::VPlacement::Volume() const
{
//
  return fVolume;
}  

//_____________________________________________________________________________
VGM::IVolume* BaseVGM::VPlacement::Mother() const
{
//
  return fMotherVolume;
}  

//_____________________________________________________________________________
void BaseVGM::VPlacement::SetVolume(VGM::IVolume* volume)
{
/// Set the associated volume 
/// (Needed in a special case when a volume is
///  created only when it is being placed)
///		    

  fVolume = volume;
}   			       
