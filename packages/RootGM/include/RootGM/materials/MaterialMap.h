// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_materials
//
/// \class RootGM::MaterialMap
///
/// The map between VGM and Root material.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_MAP_H
#define ROOT_GM_MATERIAL_MAP_H

#include <map>

class TGeoMaterial;

namespace VGM {
class IMaterial;
}

namespace RootGM {

class MaterialMap;

class MaterialMap
{
 public:
  typedef std::map<VGM::IMaterial*, TGeoMaterial*> RootMaterialMap;
  typedef RootMaterialMap::const_iterator RootMaterialMapCIterator;

  typedef std::map<TGeoMaterial*, VGM::IMaterial*> VgmMaterialMap;
  typedef VgmMaterialMap::const_iterator VgmMaterialMapCIterator;

 public:
  MaterialMap();
  virtual ~MaterialMap();

  // static access methods
  static MaterialMap* Instance();

  // methods
  void AddMaterial(VGM::IMaterial*, TGeoMaterial*);
  void Print() const;

  // get methods
  TGeoMaterial* GetMaterial(VGM::IMaterial* iMaterial) const;
  VGM::IMaterial* GetMaterial(TGeoMaterial* rootMaterial) const;

 private:
  MaterialMap(const MaterialMap&);

  // static data members
  static MaterialMap* fgInstance;

  // data members
  RootMaterialMap fRootMaterials;
  VgmMaterialMap fVgmMaterials;
};

} // namespace RootGM

#endif // ROOT_GM_MATERIAL_MAP_H
