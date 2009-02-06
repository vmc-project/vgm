// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup BaseVGM_volumes
//
/// \class BaseVGM::VFactory
///
/// The abstract base class to geometry factory.
/// It owns the solids and volumes stores and
/// implements the export to other factory. 
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_FACTORY_H
#define BASE_VGM_V_FACTORY_H

#include "VGM/volumes/IFactory.h"

#include <map>

namespace VGM {
  class ISolid;
  class IBooleanSolid;
  class IDisplacedSolid;
  class IVolume;
  class IPlacement;
  class IMaterialFactory;
}

namespace BaseVGM {

  class VFactory : public virtual VGM::IFactory
  {
    public:
      VFactory(const std::string& name, 
                VGM::IMaterialFactory* materialFactory);
      virtual ~VFactory();
    
      //
      // methods
      //
      
      virtual std::string Name() const;
      virtual const VGM::SolidStore&   Solids() const;			       
      virtual const VGM::VolumeStore&  Volumes() const;			       
      virtual VGM::IMaterialFactory*   MaterialFactory() const;

      virtual bool  Export(VGM::IFactory* factory) const;			       

      virtual void  PrintSolids() const;			       
      virtual void  PrintVolumes() const;	

      virtual void  SetDebug (int debug);			       
      virtual int   Debug() const;

      virtual void  SetIgnore (bool ignore);			       
      virtual bool  Ignore() const;


    protected:
      VFactory();
      VFactory(const VFactory& rhs);

      virtual VGM::SolidStore&   SolidStore();			       
      virtual VGM::VolumeStore&  VolumeStore();

    private:
      // types
      typedef std::map<VGM::IVolume*, VGM::IVolume*>  VolumeMap;

      // methods
      VGM::ISolid*     ExportSolid(
                             VGM::ISolid* solid, 
                             VGM::IFactory* factory) const;
      VGM::ISolid*     ExportBooleanSolid(
                             VGM::IBooleanSolid* solid,
                             VGM::IFactory* factory) const;
      VGM::ISolid*     ExportDisplacedSolid(
                             VGM::IDisplacedSolid* solid,
                             VGM::IFactory* factory) const;
      VolumeMap*       ExportVolumeStore(VGM::IFactory* factory) const;

      VGM::IPlacement* ExportSimplePlacement(
                             VGM::IPlacement* placement, 
                             VGM::IFactory* factory, 
			     VolumeMap* volumeMap) const;
      VGM::IPlacement* ExportMultiplePlacement(
                             VGM::IPlacement* placement, 
                             VGM::IFactory* factory, 
			     VolumeMap* volumeMap) const;
      void             ExportPlacements(
                             VGM::IFactory* factory, 
			     VolumeMap* map) const;
  
      VGM::Transform   Identity() const;

      // data members
      int                     fDebug;
      bool                    fIgnore;
      std::string             fName;
      VGM::SolidStore         fSolids;
      VGM::VolumeStore        fVolumes;
      VGM::IMaterialFactory*  fMaterialFactory;
  };
  
}  

// inline functions

inline std::string 
BaseVGM::VFactory::Name() const
{ return fName; }

inline const VGM::SolidStore& 
BaseVGM::VFactory::Solids() const
{ return fSolids; }
			       
inline const VGM::VolumeStore& 
BaseVGM::VFactory::Volumes() const
{ return fVolumes; }

inline VGM::IMaterialFactory*  
BaseVGM::VFactory::MaterialFactory() const
{ return fMaterialFactory; }

inline VGM::SolidStore& 
BaseVGM::VFactory::SolidStore()
{ 
  /// Return the store of solids (non const)
  return fSolids; 
}
			       
inline VGM::VolumeStore& 
BaseVGM::VFactory::VolumeStore()
{ 
  /// Return the store of volumes (non const)
  return fVolumes;
}

inline int BaseVGM::VFactory::Debug() const
{ return fDebug; }
 
inline void BaseVGM::VFactory::SetIgnore (bool ignore)
{ fIgnore = ignore; }			       

inline bool BaseVGM::VFactory::Ignore() const
{ return fIgnore; }

#endif //BASE_VGM_V_FACTORY_H
