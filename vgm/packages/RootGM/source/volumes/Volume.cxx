// $Id$
//
// Class Volume
// ---------------
// VGM implementation for Root volume.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>

#include "TGeoManager.h"
#include "TGeoShape.h"
#include "TGeoMedium.h"

#include "RootGM/volumes/Volume.h"
#include "RootGM/volumes/VolumeMap.h"
#include "RootGM/solids/SolidMap.h"

//_____________________________________________________________________________
RootGM::Volume::Volume(const std::string& name,
                       VGM::ISolid* solid, 
                       const std::string& mediumName) 
  : BaseVGM::VVolume(solid),
    fGeoVolume(0) {
//

  // Get solid from the solid map
  TGeoShape* geoSolid = RootGM::SolidMap::Instance()->GetSolid(solid);
  
  // Get medium from Root
  TGeoMedium* geoMedium = gGeoManager->GetMedium(mediumName.data());
  
  if (!geoMedium) {
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    RootGM::Volume::Volume:" << std::endl;
    std::cerr << "    Medium \"" << mediumName << "\" not found." << std::endl;
    
  }	      
  
  // Create logical volume
  fGeoVolume = new TGeoVolume(name.data(), geoSolid, geoMedium);
  
  // Register logical volume in the map
  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume); 
}

//_____________________________________________________________________________
RootGM::Volume::Volume(VGM::ISolid* solid, TGeoVolume* volume)
  : BaseVGM::VVolume(solid),
    fGeoVolume(volume)
{
  // Register logical volume in the map
  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume); 
}  

//_____________________________________________________________________________
RootGM::Volume::~Volume() {
//
}

//
// public functions
//

//_____________________________________________________________________________
std::string  RootGM::Volume::Name() const
{
//
  return std::string(fGeoVolume->GetName());
}  

//_____________________________________________________________________________
std::string  RootGM::Volume::MaterialName() const
{
//
  // Root volumes may not have medium
  //
  if (!fGeoVolume->GetMedium() ||
       fGeoVolume->GetMedium() && ! fGeoVolume->GetMedium()->GetMaterial() )
    return "None";

  return std::string(fGeoVolume->GetMedium()->GetMaterial()->GetName());
}

//_____________________________________________________________________________
std::string  RootGM::Volume::MediumName() const
{
//
  // Root volumes may not have medium
  //
  if (!fGeoVolume->GetMedium())
    return "None";

  return std::string(fGeoVolume->GetMedium()->GetName());
}

//_____________________________________________________________________________
void RootGM::Volume::ResetVolume(TGeoVolume* volume) 
{
  fGeoVolume = volume; 
  RootGM::VolumeMap::Instance()->AddVolume(this, fGeoVolume);
      // Check solid for this case
 }
    