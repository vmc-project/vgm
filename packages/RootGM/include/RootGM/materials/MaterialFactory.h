// $Id$
/// \ingroup RootGM_materials
//
/// \class RootGM:: MaterialFactory
///
/// VGM material factory for Root.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_FACTORY_H
#define ROOT_GM_MATERIAL_FACTORY_H

#include "VGM/materials/IMaterial.h"

#include "BaseVGM/materials/VMaterialFactory.h"

class TGeoElement;
class TGeoElementTable;
class TGeoMaterial;
class TGeoMedium;

namespace RootGM {

  class MaterialFactory : public BaseVGM::VMaterialFactory
  {
    public:
      MaterialFactory();
      virtual ~MaterialFactory();
    
      //
      // methods
      //
      virtual VGM::IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
                                 double z, double a);

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name,      
			         double density, 
                                 VGM::IElement* element,
			         double radlen, double intlen);

      virtual VGM::IMaterial* CreateMaterial(
                                 const std::string& name, 
	  		         double density, 
			         VGM::IElement* element,     
			         double radlen, double intlen,
				 VGM::MaterialState state,
				 double temperature, double pressure);

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions);

      virtual VGM::IMaterial* CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions,
				 VGM::MaterialState state,
				 double temperature, double pressure);

      virtual VGM::IMedium*    CreateMedium(
                                 const std::string& name,
			         int mediumId,
			         VGM::IMaterial* material,
			         int nofParameters,
			         double* parameters);      
      // import/export
      //
      virtual bool Import();			       
 
    protected:
      MaterialFactory(const MaterialFactory& rhs);
    
    private:
      // methods
      void  ImportElement(TGeoElement* element);
      void  ImportMaterial(TGeoMaterial* material);
      void  ImportMedium(TGeoMedium* medium);
  };

}

#endif //ROOT_GM_MATERIAL_FACTORY_H
