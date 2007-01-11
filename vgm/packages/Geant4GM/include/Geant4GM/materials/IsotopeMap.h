// $Id$
/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::IsotopeMap
///
/// The map between VGM and Geant4 isotopes.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ISOTOPE_MAP_H
#define GEANT4_GM_ISOTOPE_MAP_H

#include <map>

#include "G4Isotope.hh"

#include "VGM/materials/IIsotope.h"

namespace Geant4GM {

  class IsotopeMap;

  class IsotopeMap
  {
    public:
      typedef std::map<VGM::IIsotope*, G4Isotope*>  G4IsotopeMap;
      typedef G4IsotopeMap::const_iterator          G4IsotopeMapCIterator;

      typedef std::map<G4Isotope*, VGM::IIsotope*>  VgmIsotopeMap;
      typedef VgmIsotopeMap::const_iterator         VgmIsotopeMapCIterator;

    public:
      IsotopeMap();
      virtual ~IsotopeMap();

      // static access methods
      static IsotopeMap* Instance(); 

      // methods
      void  AddIsotope(VGM::IIsotope*, G4Isotope*); 
      void  Print() const;
  
      // get methods
      G4Isotope*     GetIsotope(VGM::IIsotope* iIsotope) const;
      VGM::IIsotope* GetIsotope(G4Isotope* g4Isotope) const;

    protected:
      IsotopeMap(const IsotopeMap&);

    private:
      // static data members
      static IsotopeMap*  fgInstance;
  
      // data members
      G4IsotopeMap   fG4Isotopes;
      VgmIsotopeMap  fVgmIsotopes;
  };

}

#endif //GEANT4_GM_ISOTOPE_MAP_H
