// $Id$
//
// Class Volume
// ---------------
// VGM implementation for Geant4 volume.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_VOLUME_H
#define GEANT4_GM_VOLUME_H

#include <string>

#include "G4LogicalVolume.hh"

#include "BaseVGM/volumes/VVolume.h"

class VGM::ISolid;

namespace Geant4GM {

  class Volume : public BaseVGM::VVolume
  {
    public:
      Volume(const std::string& name, 
             VGM::ISolid* solid, 
             const std::string& materialName );
      Volume(VGM::ISolid* solid, 
             G4LogicalVolume* lv);
      virtual ~Volume();
    
      // methods
      virtual std::string  Name() const;
      virtual std::string  MaterialName() const;
    
    protected:    
      Volume() : BaseVGM::VVolume() {}
      Volume(const Volume& rhs) : BaseVGM::VVolume(rhs) {}
    
    private:
      G4LogicalVolume* fLogicalVolume;   
  };

}

#endif //GEANT4_GM_VOLUME_H
