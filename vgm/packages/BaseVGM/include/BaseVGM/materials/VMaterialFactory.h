// $Id$
/// \ingroup BaseVGM_materials
//
/// \class BaseVGM::VMaterialFactory
///
/// The abstract base class to material factory.
/// It owns the material stores and implements the export 
/// to other factory. 
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef BASE_VGM_V_MATERIAL_FACTORY_H
#define BASE_VGM_V_MATERIAL_FACTORY_H

#include <string>
#include <map>

#include "VGM/materials/IMaterialFactory.h"

namespace BaseVGM {

  class VMaterialFactory : public virtual VGM::IMaterialFactory
  {
    public:
      VMaterialFactory(const std::string& name);
      virtual ~VMaterialFactory();
    
      //
      // methods
      //
    
      // access  
      //
      virtual std::string Name() const;

      virtual const VGM::ElementStore&   Elements() const;	
      virtual const VGM::MaterialStore&  Materials() const;	
      virtual const VGM::MediumStore&    Media() const;	

      virtual const VGM::IElement*   Element(const std::string& name) const;	
      virtual const VGM::IMaterial*  Material(const std::string& name) const;	
      virtual const VGM::IMedium*    Medium(const std::string& name) const;	

      // import/export
      //
      virtual bool Export(VGM::IMaterialFactory* factory) const;			       
 
      // listings
      //
      virtual void  PrintElements() const;			       
      virtual void  PrintMaterials() const;
      virtual void  PrintMedia() const;
    
      // debug
      //
      virtual void SetDebug (int debug);			       
      virtual int  Debug() const;

    protected:
      VMaterialFactory();
      VMaterialFactory(const VMaterialFactory& rhs); 

      virtual VGM::ElementStore&    ElementStore();			       
      virtual VGM::MaterialStore&   MaterialStore();			       
      virtual VGM::MediumStore&     MediumStore();			       

    private:
      // types
      typedef std::map<VGM::IElement*,  VGM::IElement*>   ElementMap;
      typedef std::map<VGM::IMaterial*, VGM::IMaterial*>  MaterialMap;

      VGM::IElement*  ExportElement(VGM::IElement* element, 
                              VGM::IMaterialFactory* factory) const;
      VGM::IMaterial* ExportMaterial(VGM::IMaterial* material, 
                              VGM::IMaterialFactory* factory,
			      ElementMap* map) const;
      VGM::IMedium*   ExportMedium(VGM::IMedium* medium, 
                              VGM::IMaterialFactory* factory,
			      MaterialMap* map) const;
      VGM::IMedium*   GenerateMedium(VGM::IMaterial* material, 
                              int mediumId,
                              VGM::IMaterialFactory* factory,
			      MaterialMap* map) const;

      ElementMap*  ExportElements(VGM::IMaterialFactory* factory) const;			       
      MaterialMap* ExportMaterials(VGM::IMaterialFactory* factory, 
                                ElementMap* map) const;			       
      void         ExportMedia(VGM::IMaterialFactory* factory, 
                                 MaterialMap* map) const;			       
      void         GenerateMedia(VGM::IMaterialFactory* factory, 
                                MaterialMap* map) const;			       

      // data members
      bool                fDebug;
      std::string         fName;
      VGM::ElementStore   fElements;
      VGM::MaterialStore  fMaterials;
      VGM::MediumStore    fMedia;
  };
  
}  

// inline functions

inline std::string 
BaseVGM::VMaterialFactory::Name() const
{ return fName; }

inline const VGM::ElementStore& 
BaseVGM::VMaterialFactory::Elements() const
{ return fElements; }

inline const VGM::MaterialStore& 
BaseVGM::VMaterialFactory::Materials() const
{ return fMaterials; }

inline const VGM::MediumStore& 
BaseVGM::VMaterialFactory::Media() const
{ return fMedia; }

inline VGM::ElementStore& 
BaseVGM::VMaterialFactory::ElementStore()
{  
  /// Return the store of elements (non const)
  return fElements; 
}
			       
inline VGM::MaterialStore& 
BaseVGM::VMaterialFactory::MaterialStore()
{   
  /// Return the store of materials (non const)
  return fMaterials; 
}
			       
inline VGM::MediumStore& 
BaseVGM::VMaterialFactory::MediumStore()
{
  /// Return the store of media (non const)
  return fMedia; 
}
			       
inline void 
BaseVGM::VMaterialFactory::SetDebug (int debug)
{ fDebug = debug; }
			       
inline int 
BaseVGM::VMaterialFactory::Debug() const
{ return fDebug; }

#endif //BASE_VGM_V_FACTORY_H
