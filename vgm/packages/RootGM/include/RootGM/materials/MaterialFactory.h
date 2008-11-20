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
/// \class RootGM:: MaterialFactory
///
/// VGM material factory for Root.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_FACTORY_H
#define ROOT_GM_MATERIAL_FACTORY_H

#include "BaseVGM/materials/VMaterialFactory.h"

class TGeoElement;
class TGeoMaterial;
class TGeoMedium;

namespace VGM {
  class IMaterial;
  class IIsotope;
}

namespace RootGM {

  class MaterialFactory : public BaseVGM::VMaterialFactory
  {
    public:
      MaterialFactory();
      virtual ~MaterialFactory();
    
      //
      // methods
      //
      virtual VGM::IIsotope*   CreateIsotope(
                                 const std::string& name,      
                                 int z, int n, double a = 0.);

      virtual VGM::IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
                                 double z, double a);

      virtual VGM::IElement*   CreateElement(
                                 const std::string& name,      
                                 const std::string& symbol,      
	                         const VGM::IsotopeVector& isotopes,
                                 const VGM::RelAbundanceVector& relAbundances);

      virtual VGM::IElement*   CreateElement(
                                 int z, bool isotopes);

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name,      
			         double density, 
                                 VGM::IElement* element,
			         double radlen, double intlen);

      virtual VGM::IMaterial*  CreateMaterial(
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

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions,
				 VGM::MaterialState state,
				 double temperature, double pressure);

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts);

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts,
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
      VGM::IElement* GetElement(double z, double a) const;
      VGM::IIsotope* GetIsotope(double z, double n) const;

      void  ImportElements(TGeoMaterial* material,
                           std::vector<VGM::IElement*>& elements);
      void  ImportMaterial(TGeoMaterial* material);
      void  ImportMedium(TGeoMedium* medium);
      
      // data members
      static const double fgkTolerance; 
  };

}

#endif //ROOT_GM_MATERIAL_FACTORY_H
