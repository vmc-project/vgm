// $Id$
//
// Class PlacementMap
// ---------------------
// The map between VGM and Geant4 placements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PLACEMENT_MAP_H
#define GEANT4_GM_PLACEMENT_MAP_H

#include <map>

#include "G4VPhysicalVolume.hh"

#include "VGM/volumes/IPlacement.h"

namespace Geant4GM {

  class PlacementMap;

  class PlacementMap
  {
    public:
      typedef std::map<VGM::IPlacement*, G4VPhysicalVolume*>  G4PlacementMap;
      typedef G4PlacementMap::const_iterator    G4PlacementMapCIterator;

      typedef std::map<G4VPhysicalVolume*, VGM::IPlacement*>  VgmPlacementMap;
      typedef VgmPlacementMap::const_iterator   VgmPlacementMapCIterator;

    public:
      PlacementMap();
      virtual ~PlacementMap();

      // static access methods
      static PlacementMap* Instance(); 

      // methods
      void  AddPlacement(VGM::IPlacement*, 
                         G4VPhysicalVolume*); 
      G4VPhysicalVolume* GetPlacement(VGM::IPlacement* iPlacement) const;
      VGM::IPlacement*   GetPlacement(G4VPhysicalVolume* pv) const;

    private:
      PlacementMap(const PlacementMap&) {}

      // static data members
      static PlacementMap*  fgInstance;
  
      // data members
      G4PlacementMap    fG4Placements;
      VgmPlacementMap   fVgmPlacements;
  };

}

#endif //GEANT4_GM_PLACEMENT_MAP_H
