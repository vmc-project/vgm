// $Id$
//
// Class Volume
// ---------------
// VGM implementation for Root volume.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_VOLUME_H
#define ROOT_GM_VOLUME_H

#include <string>

#include "TGeoVolume.h"

#include "BaseVGM/volumes/VVolume.h"
#include "RootGM/volumes/VolumeMap.h"

class VGM::ISolid;

namespace RootGM {

  class Volume : public BaseVGM::VVolume
  {
    public:
      Volume(const std::string& name, 
             VGM::ISolid* solid, 
             const std::string& mediumName );
      Volume(VGM::ISolid* solid, 
             TGeoVolume* volume);
      virtual ~Volume();
    
      // methods
      virtual std::string  Name() const;
      virtual std::string  MaterialName() const;
      virtual std::string  MediumName() const;
    
      void ResetVolume(TGeoVolume* rootVolume);
        
    protected:
      Volume();
      Volume(const Volume& rhs);      
    
    private:
      TGeoVolume* fGeoVolume;   
  };

}

#endif //ROOT_GM_VOLUME_H
