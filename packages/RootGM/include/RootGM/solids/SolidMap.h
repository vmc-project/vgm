// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM::SolidMap
///
/// The map between VGM and Root solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_SOLID_MAP_H
#define ROOT_GM_SOLID_MAP_H

#include <map>

class TGeoShape;

namespace VGM {
  class ISolid;
}

namespace RootGM {

  class SolidMap;

  class SolidMap
  {
    public:
      typedef std::map<VGM::ISolid*, TGeoShape*>  RootSolidMap;
      typedef RootSolidMap::const_iterator        RootSolidMapCIterator;

      typedef std::map<TGeoShape*, VGM::ISolid*>  VgmSolidMap;
      typedef VgmSolidMap::const_iterator         VgmSolidMapCIterator;

    public:
      SolidMap();
      virtual ~SolidMap();

      // static access methods
      static SolidMap* Instance();

      // methods
      void  AddSolid(VGM::ISolid*, TGeoShape*);
      void  AddSolidInRootMapOnly(VGM::ISolid*, TGeoShape*);
      void  AddSolidInVGMMapOnly(VGM::ISolid*, TGeoShape*);

      // get methods
      TGeoShape*    GetSolid(VGM::ISolid* iSolid) const;
      VGM::ISolid*  GetSolid(TGeoShape* solid) const;

    private:
      SolidMap(const SolidMap&);

      // static data members
      static SolidMap*  fgInstance;

      // data members
      RootSolidMap  fRootSolids;
      VgmSolidMap   fVgmSolids;
  };

}

#endif //ROOT_GM_SOLID_MAP_H
