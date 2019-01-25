// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::SolidMap
///
/// The map between VGM and Geant4 solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_SOLID_MAP_H
#define GEANT4_GM_SOLID_MAP_H

#include <map>

class G4VSolid;

namespace VGM {
  class ISolid;
}

namespace Geant4GM {

  class SolidMap;

  class SolidMap
  {
    public:
      typedef std::map<VGM::ISolid*, G4VSolid*>  G4SolidMap;
      typedef G4SolidMap::const_iterator         G4SolidMapCIterator;

      typedef std::map<G4VSolid*, VGM::ISolid*>  VgmSolidMap;
      typedef VgmSolidMap::const_iterator        VgmSolidMapCIterator;

    public:
      SolidMap();
      virtual ~SolidMap();

      // static access methods
      static SolidMap* Instance();

      // methods
      void  AddSolid(VGM::ISolid*, G4VSolid*);

      // get methods
      G4VSolid* GetSolid(VGM::ISolid* iSolid) const;
      VGM::ISolid*  GetSolid(G4VSolid* solid) const;

    private:
      SolidMap(const SolidMap&);

      // static data members
      static SolidMap*  fgInstance;

      // data members
      G4SolidMap    fG4Solids;
      VgmSolidMap   fVgmSolids;
  };

}

#endif //GEANT4_GM_SOLID_MAP_H
