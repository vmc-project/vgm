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
	     const std::string& materialName,
             const std::string& mediumName );
      Volume(VGM::ISolid* solid, 
             G4LogicalVolume* lv,
	     const std::string& mediumName );
      virtual ~Volume();
    
      // methods
      virtual std::string  Name() const;
      virtual std::string  MaterialName() const;
      virtual std::string  MediumName() const;
    
    protected:    
      Volume();
      Volume(const Volume& rhs);
    
    private:
      G4LogicalVolume* fLogicalVolume;   
      std::string      fMediumName;   
  };

}

#endif //GEANT4_GM_VOLUME_H
