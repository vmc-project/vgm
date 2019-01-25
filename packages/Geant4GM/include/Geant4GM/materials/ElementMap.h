// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::ElementMap
///
/// The map between VGM and Geant4 elements.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ELEMENT_MAP_H
#define GEANT4_GM_ELEMENT_MAP_H

#include <map>

class G4Element;

namespace VGM {
  class IElement;
}

namespace Geant4GM {

  class ElementMap;

  class ElementMap
  {
    public:
      typedef std::map<VGM::IElement*, G4Element*>  G4ElementMap;
      typedef G4ElementMap::const_iterator          G4ElementMapCIterator;

      typedef std::map<G4Element*, VGM::IElement*>  VgmElementMap;
      typedef VgmElementMap::const_iterator         VgmElementMapCIterator;

    public:
      ElementMap();
      virtual ~ElementMap();

      // static access methods
      static ElementMap* Instance();

      // methods
      void  AddElement(VGM::IElement*, G4Element*);
      void  Print() const;

      // get methods
      G4Element*     GetElement(VGM::IElement* iElement) const;
      VGM::IElement* GetElement(G4Element* g4Element) const;

    protected:
      ElementMap(const ElementMap&);

    private:
      // static data members
      static ElementMap*  fgInstance;

      // data members
      G4ElementMap   fG4Elements;
      VgmElementMap  fVgmElements;
  };

}

#endif //GEANT4_GM_ELEMENT_MAP_H
