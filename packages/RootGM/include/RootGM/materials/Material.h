// $Id$
/// \ingroup RootGM_materials
//
/// \class RootGM:: Material
///
/// VGM implementation for Root material.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_H
#define ROOT_GM_MATERIAL_H

#include <string>

#include "TGeoMaterial.h"

#include "VGM/materials/IMaterial.h"

namespace RootGM {

  class Material : public virtual VGM::IMaterial
  {
    public:
      Material(const std::string& name,      
               double density, 
	       VGM::IElement* element,
	       double radlen, double intlen,
	       VGM::MaterialState state = fgkDefaultState,
	       double temperature = fgkDefaultTemperature, 
	       double pressure = fgkDefaultPressure);
      Material(const std::string& name, 
               double density,
	       const VGM::ElementVector& elements,
               const VGM::MassFractionVector& fractions,
	       VGM::MaterialState state = fgkDefaultState,
	       double temperature = fgkDefaultTemperature, 
	       double pressure = fgkDefaultPressure);
      Material(TGeoMaterial* material);		
      virtual ~Material();
    
      // methods
      virtual std::string Name() const;

      virtual double  Density() const;
      virtual double  RadiationLength() const;
      virtual double  NuclearInterLength() const;
      virtual VGM::MaterialState  State() const;
      virtual double  Temperature() const;
      virtual double  Pressure() const;			  
    
      virtual int             NofElements() const;
      virtual VGM::IElement*  Element(int iel) const;     
      virtual double          MassFraction(int iel) const;

    protected:  
      Material(); 
      Material(const Material& rhs);
    
    private:
      void   CheckIndex(int iel) const;
      double UpdateParametersIfVacuum(double density);
      
      static const VGM::MaterialState  fgkDefaultState;
      static const double  fgkDefaultTemperature;
      static const double  fgkDefaultPressure; 
      static const double  fgkVacuumDensity;
      static const double  fgkVacuumTemperature;
      static const double  fgkVacuumPressure;  
  
      TGeoMaterial*       fMaterial; 
      VGM::MaterialState  fState;
      double              fTemperature;
      double              fPressure; 
  };

}

#endif //ROOT_GM_MATERIAL_H
