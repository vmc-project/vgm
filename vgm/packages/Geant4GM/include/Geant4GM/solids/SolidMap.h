// $Id$
//
// Class SolidMap
// ------------------
// The map between VGM and Geant4 solids.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_SOLID_MAP_H
#define GEANT4_GM_SOLID_MAP_H

#include <map>

#include "G4VSolid.hh"

#include "VGM/solids/ISolid.h"

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
      SolidMap(const SolidMap&) {}

      // static data members
      static SolidMap*  fgInstance;
  
      // data members
      G4SolidMap    fG4Solids;
      VgmSolidMap   fVgmSolids;
  };

}

#endif //GEANT4_GM_SOLID_MAP_H
