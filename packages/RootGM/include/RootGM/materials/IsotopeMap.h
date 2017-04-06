// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2010 Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_materials
//
/// \class RootGM::IsotopeMap
///
/// The map between VGM and Root isotopes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ISOTOPE_MAP_H
#define ROOT_GM_ISOTOPE_MAP_H

#include <map>

class TGeoIsotope;

namespace VGM {
  class IIsotope;
}  

namespace RootGM {

  class IsotopeMap;

  class IsotopeMap
  {
    public:
      typedef std::map<VGM::IIsotope*, TGeoIsotope*>  TGeoIsotopeMap;
      typedef TGeoIsotopeMap::const_iterator          TGeoIsotopeMapCIterator;

      typedef std::map<TGeoIsotope*, VGM::IIsotope*>  VgmIsotopeMap;
      typedef VgmIsotopeMap::const_iterator           VgmIsotopeMapCIterator;

    public:
      IsotopeMap();
      virtual ~IsotopeMap();

      // static access methods
      static IsotopeMap* Instance(); 

      // methods
      void  AddIsotope(VGM::IIsotope*, TGeoIsotope*); 
      void  Print() const;
  
      // get methods
      TGeoIsotope*   GetIsotope(VGM::IIsotope* iIsotope) const;
      VGM::IIsotope* GetIsotope(TGeoIsotope* tgeoIsotope) const;

    protected:
      IsotopeMap(const IsotopeMap&);

    private:
      // static data members
      static IsotopeMap*  fgInstance;
  
      // data members
      TGeoIsotopeMap  fTGeoIsotopes;
      VgmIsotopeMap   fVgmIsotopes;
  };

}

#endif //GEANT4_GM_ISOTOPE_MAP_H
