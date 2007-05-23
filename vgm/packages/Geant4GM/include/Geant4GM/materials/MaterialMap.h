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
/// \class Geant4GM::MaterialMap
///
/// The map between VGM and Geant4 material.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_VOLUME_MAP_H
#define GEANT4_GM_VOLUME_MAP_H

#include <map>

#include "G4Material.hh"

#include "VGM/materials/IMaterial.h"

namespace Geant4GM {

  class MaterialMap;

  class MaterialMap
  {
    public:
      typedef std::map<VGM::IMaterial*, G4Material*>  G4MaterialMap;
      typedef G4MaterialMap::const_iterator           G4MaterialMapCIterator;

      typedef std::map<G4Material*, VGM::IMaterial*>  VgmMaterialMap;
      typedef VgmMaterialMap::const_iterator          VgmMaterialMapCIterator;

    public:
      MaterialMap();
      virtual ~MaterialMap();

      // static access methods
      static MaterialMap* Instance(); 

      // methods
      void  AddMaterial(VGM::IMaterial*, G4Material*); 
      void  Print() const;

      // get methods
      G4Material* GetMaterial(VGM::IMaterial* iMaterial) const;
      VGM::IMaterial* GetMaterial(G4Material* g4Material) const;

    protected:
      MaterialMap(const MaterialMap&);

    private:
      // static data members
      static MaterialMap*  fgInstance;
  
      // data members
      G4MaterialMap   fG4Materials;
      VgmMaterialMap  fVgmMaterials;
  };

}

#endif //GEANT4_GM_VOLUME_MAP_H
