// $Id$
/// \ingroup RootGM_materials
//
/// \class RootGM:: ElementMap
///
/// The map between VGM and Root elements.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_ELEMENT_MAP_H
#define ROOT_GM_ELEMENT_MAP_H

#include <map>

#include "TGeoElement.h"

#include "VGM/materials/IElement.h"

namespace RootGM {

  class ElementMap;

  class ElementMap
  {
    public:
      typedef std::map<VGM::IElement*, TGeoElement*>  RootElementMap;
      typedef RootElementMap::const_iterator          RootElementMapCIterator;

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
      VGM::IElement* GetElement(TGeoElement* rtElement) const;

    private:
      ElementMap(const ElementMap&);

      // static data members
      static ElementMap*  fgInstance;
  
      // data members
      RootElementMap  fRootElements;
      VgmElementMap   fVgmElements;
  };

}

#endif //ROOT_GM_ELEMENT_MAP_H
