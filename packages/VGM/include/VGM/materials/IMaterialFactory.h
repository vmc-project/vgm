// $Id$
//
// Class IMaterialFactory
// ------------------------
// The VGM interface to material factory providing
// functions for material conversions.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_MATERIAL_FACTORY_H
#define VGM_I_MATERIAL_FACTORY_H

#include <vector>

#include "VGM/materials/IMaterial.h"

namespace VGM {

  class IElement;
  class IMedium;

  typedef std::vector<IElement*>  ElementStore;
  typedef std::vector<IMaterial*> MaterialStore;
  typedef std::vector<IMedium*>   MediumStore;

  class IMaterialFactory
  {
    public:
      virtual ~IMaterialFactory() {}
    
      //
      // methods
      //
      virtual IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
                                 double z, double a) = 0;

      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
	  		         double density, 
			         IElement* element,     
			         double radlen, double intlen) = 0;
      virtual IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const ElementVector& elements,
                                 const MassFractionVector& fractions) = 0;

      virtual IMedium*    CreateMedium(
                                 const std::string& name,
                                 int mediumId,
			         IMaterial* material,
			         int nofParameters,
			         double* parameters) = 0;      
    
      // access  
      virtual std::string Name() const = 0;
      virtual const ElementStore&   Elements() const = 0;	
      virtual const MaterialStore&  Materials() const = 0;	
      virtual const MediumStore&    Media() const = 0;	

      virtual const IElement*   Element(const std::string& name) const = 0;	
      virtual const IMaterial*  Material(const std::string& name) const = 0;	
      virtual const IMedium*    Medium(const std::string& name) const = 0;	

      // import/export
      //
      virtual bool Import() = 0;			       
      virtual bool Export(IMaterialFactory* factory) const = 0;			       

      // listings
      //
      virtual void PrintElements() const = 0;			       
      virtual void PrintMaterials() const = 0;			       
      virtual void PrintMedia() const = 0;			       

      // debug
      //
      virtual void SetDebug (int debug) = 0;			       
      virtual int  Debug() const = 0;
  };
}  

#endif //VGM_I_MATERIAL_FACTORY_H
