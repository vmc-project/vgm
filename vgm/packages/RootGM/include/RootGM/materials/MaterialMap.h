// $Id$
//
// Class MaterialMap
// ------------------
// The map between VGM and Root material.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_MAP_H
#define ROOT_GM_MATERIAL_MAP_H

#include <map>

#include "TGeoMaterial.h"

#include "VGM/materials/IMaterial.h"

namespace RootGM {

  class MaterialMap;

  class MaterialMap
  {
    public:
      typedef std::map<VGM::IMaterial*, TGeoMaterial*>  RootMaterialMap;
      typedef RootMaterialMap::const_iterator           RootMaterialMapCIterator;

      typedef std::map<TGeoMaterial*, VGM::IMaterial*>  VgmMaterialMap;
      typedef VgmMaterialMap::const_iterator            VgmMaterialMapCIterator;

    public:
      MaterialMap();
      virtual ~MaterialMap();

      // static access methods
      static MaterialMap* Instance(); 

      // methods
      void  AddMaterial(VGM::IMaterial*, TGeoMaterial*); 
      void  Print() const;

      // get methods
      TGeoMaterial*   GetMaterial(VGM::IMaterial* iMaterial) const;
      VGM::IMaterial* GetMaterial(TGeoMaterial* rootMaterial) const;

    private:
      MaterialMap(const MaterialMap&) {}

      // static data members
     static MaterialMap*  fgInstance;
  
      // data members
      RootMaterialMap  fRootMaterials;
      VgmMaterialMap   fVgmMaterials;
  };

}

#endif //ROOT_GM_MATERIAL_MAP_H
