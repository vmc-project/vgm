// $Id$
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
//
  // Update mother volume 
  if (motherVolume)
    motherVolume->AddDaughter(this);
  else
    // check if top volume not yet set and
    // set top volume here  
    ;
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
HepRotation BaseVGM::VPlacement::FrameRotation() const
{
//
  return ObjectRotation().inverse();
}        

//_____________________________________________________________________________
Hep3Vector BaseVGM::VPlacement::FrameTranslation() const
{
//
  return -ObjectTranslation();
}  
        
//_____________________________________________________________________________
void BaseVGM::VPlacement::SetVolume(VGM::IVolume* volume)
{
//
  fVolume = volume;
}   			       
