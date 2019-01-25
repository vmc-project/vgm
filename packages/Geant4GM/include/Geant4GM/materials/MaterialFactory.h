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
/// \class Geant4GM::MaterialFactory
///
/// VGM material factory for Geant4.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MATERIAL_FACTORY_H
#define GEANT4_GM_MATERIAL_FACTORY_H

#include "BaseVGM/materials/VMaterialFactory.h"

#include <set>

class G4Isotope;
class G4Element;
class G4Material;

namespace VGM {
  class IMaterial;
}

namespace Geant4GM {

  class MaterialFactory : public BaseVGM::VMaterialFactory
  {
    public:
      MaterialFactory();
      virtual ~MaterialFactory();

      //
      // methods
      //
      virtual VGM::IIsotope*  CreateIsotope(
                                 const std::string& name,
                                 int z, int n, double a);

      virtual VGM::IElement*  CreateElement(
                                 const std::string& name,
                                 const std::string& symbol,
                                 double z, double a);

      virtual VGM::IElement*  CreateElement(
                                 const std::string& name,
                                 const std::string& symbol,
	                         const VGM::IsotopeVector& isotopes,
                                 const VGM::RelAbundanceVector& relAbundances);

      virtual VGM::IElement*  CreateElement(
                                 int z, bool isotopes);

      virtual VGM::IMaterial* CreateMaterial(
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

      virtual VGM::IMaterial* CreateMaterial(
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

      virtual VGM::IMaterial*  CreateMaterial(
                                 const std::string& name,
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts);

      virtual VGM::IMaterial* CreateMaterial(
                                 const std::string& name,
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts,
				 VGM::MaterialState state,
				 double temperature, double pressure);

      virtual VGM::IMedium*   CreateMedium(
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
      void  ImportIsotope(G4Isotope* element);
      void  ImportElement(G4Element* element);
      void  ImportMaterial(G4Material* material);

      bool CompareIsotopes(const G4Element* g4Element,
                           const VGM::IsotopeVector& isotopes,
                           const VGM::RelAbundanceVector& relAbundances);

      // data members
      std::set<VGM::IElement*>  fVacuumElements;

      // data members
      static const double fgkTolerance;
  };
}

#endif //GEANT4_GM_MATERIAL_FACTORY_H
