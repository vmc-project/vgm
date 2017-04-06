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
/// \class RootGM::ElementMap
///
/// The map between VGM and Root elements.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_MAP_H
#define ROOT_GM_ELEMENT_MAP_H

#include <map>

class TGeoElement;

namespace VGM {
  class IElement;
}  

namespace RootGM {

  class ElementMap;

  class ElementMap
  {
    public:
      typedef std::map<VGM::IElement*, TGeoElement*>  TGeoElementMap;
      typedef TGeoElementMap::const_iterator          TGeoElementMapCIterator;

      typedef std::map<TGeoElement*, VGM::IElement*>  VgmElementMap;
      typedef VgmElementMap::const_iterator           VgmElementMapCIterator;

    public:
      ElementMap();
      virtual ~ElementMap();

      // static access methods
      static ElementMap* Instance(); 

      // methods
      void  AddElement(VGM::IElement*, TGeoElement*); 
      void  Print() const;
  
      // get methods
      TGeoElement*   GetElement(VGM::IElement* iElement) const;
      VGM::IElement* GetElement(TGeoElement* tgeoElement) const;

    protected:
      ElementMap(const ElementMap&);

    private:
      // static data members
      static ElementMap*  fgInstance;
  
      // data members
      TGeoElementMap   fTGeoElements;
      VgmElementMap    fVgmElements;
  };

}

#endif //GEANT4_GM_ELEMENT_MAP_H
