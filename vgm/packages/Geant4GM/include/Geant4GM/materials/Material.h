// $Id$
/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::Material
///
/// VGM implementation for Geant4 material.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MATERIAL_H
#define GEANT4_GM_MATERIAL_H

#include <string>

#include "G4Material.hh"

#include "VGM/materials/IMaterial.h"

namespace Geant4GM {

  class Material : public virtual VGM::IMaterial
  {
    public:
      Material(const std::string& name,
               double density,
               VGM::IElement* element);
      Material(const std::string& name,
               double density,
               VGM::IElement* element,
	       VGM::MaterialState state,
	       double temperature, double pressure);
      Material(const std::string& name, 
               double density,
	       const VGM::ElementVector& elements,
               const VGM::MassFractionVector& fractions);
      Material(const std::string& name, 
               double density,
	       const VGM::ElementVector& elements,
               const VGM::MassFractionVector& fractions,
	       VGM::MaterialState state,
	       double temperature, double pressure);
      Material(G4Material* material);		
      virtual ~Material();
    
      // methods
      virtual std::string Name() const;

      virtual double  Density() const;
      virtual double  RadiationLength() const;
      virtual double  NuclearInterLength() const;
      virtual VGM::MaterialState  State() const;
      virtual double  Temperature() const;
      virtual double  Pressure() const;			  
    
      virtual int     NofElements() const;
      virtual VGM::IElement*  Element(int iel) const;
      virtual double  MassFraction(int iel) const;

    protected:  
      Material();  
      Material(const Material& rhs);
     
    private:
      void CheckIndex(int iel) const;
      G4State GetG4State(VGM::MaterialState state) const;
      VGM::MaterialState GetVGMState(G4State state) const;
  
      G4Material*  fMaterial;  
  };

}

#endif //GEANT4_GM_MATERIAL_H
