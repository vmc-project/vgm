// $Id$
//
// Class Material
// ---------------
// VGM implementation for Geant4 material.
//
// Author: Ivana Hrivnacova; IPN Orsay

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
	       const VGM::ElementVector& elements,
               const VGM::MassFractionVector& fractions);
      Material(G4Material* material);		
      virtual ~Material();
    
      // methods
      virtual std::string Name() const;

      virtual double  Density() const;
      virtual double  RadiationLength() const;
      virtual double  NuclearInterLength() const;
    
      virtual int     NofElements() const;
      virtual VGM::IElement*  Element(int iel) const;
      virtual double  MassFraction(int iel) const;

    protected:  
      Material() : VGM::IMaterial() {}  
      Material(const Material& rhs) : VGM::IMaterial(rhs) {}
     
    private:
      bool CheckVacuum(const std::string& name, double density);
      void CheckIndex(int iel) const;
  
      G4Material*  fMaterial;  
  };

}

#endif //GEANT4_GM_MATERIAL_H
