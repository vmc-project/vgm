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
/// \class RootGM::Material
///
/// VGM implementation for Root material.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MATERIAL_H
#define ROOT_GM_MATERIAL_H

#include "VGM/materials/IMaterial.h"

#include "TGeoMaterial.h"

#include <string>

namespace RootGM {

class Material : public virtual VGM::IMaterial
{
 public:
  Material(const std::string& name, double density, VGM::IElement* element,
    double radlen, double intlen);

  Material(const std::string& name, double density, VGM::IElement* element,
    double radlen, double intlen, VGM::MaterialState state, double temperature,
    double pressure);

  Material(const std::string& name, double density,
    const VGM::ElementVector& elements,
    const VGM::MassFractionVector& fractions);

  Material(const std::string& name, double density,
    const VGM::ElementVector& elements,
    const VGM::MassFractionVector& fractions, VGM::MaterialState state,
    double temperature, double pressure);

  Material(const std::string& name, double density,
    const VGM::ElementVector& elements, const VGM::AtomCountVector& atomCounts);

  Material(const std::string& name, double density,
    const VGM::ElementVector& elements, const VGM::AtomCountVector& atomCounts,
    VGM::MaterialState state, double temperature, double pressure);

  Material(TGeoMaterial* material, const VGM::ElementVector& elements);
  virtual ~Material();

  // methods
  virtual std::string Name() const;

  virtual double Density() const;
  virtual double RadiationLength() const;
  virtual double NuclearInterLength() const;
  virtual VGM::MaterialState State() const;
  virtual double Temperature() const;
  virtual double Pressure() const;

  virtual int NofElements() const;
  virtual VGM::IElement* Element(int iel) const;
  virtual double MassFraction(int iel) const;
  virtual double AtomCount(int iel) const;

 protected:
  Material();
  Material(const Material& rhs);

 private:
  void CheckIndex(int iel) const;
  TGeoMaterial::EGeoMaterialState GetGeoState(VGM::MaterialState state) const;
  VGM::MaterialState GetVGMState(TGeoMaterial::EGeoMaterialState state) const;

  static const double fgkVacuumDensity;
  static const double fgkVacuumTemperature;
  static const double fgkVacuumPressure;

  TGeoMaterial* fMaterial;
  VGM::ElementVector fElements;
};

} // namespace RootGM

#endif // ROOT_GM_MATERIAL_H
