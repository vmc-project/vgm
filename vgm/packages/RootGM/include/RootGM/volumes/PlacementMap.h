// $Id$
//
// Class PlacementMap
// ---------------------
// The map between VGM and Root placements.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PLACEMENT_MAP_H
#define ROOT_GM_PLACEMENT_MAP_H

#include <map>

#include "TGeoNode.h"

#include "VGM/volumes/IPlacement.h"

namespace RootGM {

  class PlacementMap;

  class PlacementMap
  {
    public:
      typedef std::map<VGM::IPlacement*, TGeoNode*>  RootPlacementMap;
      typedef RootPlacementMap::const_iterator       RootPlacementMapCIterator;

    public:
      PlacementMap();
      virtual ~PlacementMap();

      // static access methods
      static PlacementMap* Instance(); 

      // methods
      void  AddPlacement(VGM::IPlacement*, TGeoNode*); 
      TGeoNode* GetPlacement(VGM::IPlacement* iPlacement) const;

    protected:
      PlacementMap(const PlacementMap&) {}

    private:
      // static data members
      static PlacementMap*  fgInstance;
   
      // data members
      RootPlacementMap  fPlacements;
  };
  
}  

#endif //ROOT_GM_PLACEMENT_MAP_H
