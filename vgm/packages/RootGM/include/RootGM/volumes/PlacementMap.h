// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_volumes
//
/// \class RootGM::PlacementMap
///
/// The map between VGM and Root placements.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_PLACEMENT_MAP_H
#define ROOT_GM_PLACEMENT_MAP_H

#include <map>

class TGeoNode;

namespace VGM {
  class IPlacement;
}

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
      PlacementMap(const PlacementMap&);

    private:
      // static data members
      static PlacementMap*  fgInstance;
   
      // data members
      RootPlacementMap  fPlacements;
  };
  
}  

#endif //ROOT_GM_PLACEMENT_MAP_H
