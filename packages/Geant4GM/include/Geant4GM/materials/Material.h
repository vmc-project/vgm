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
/// \class Geant4GM::Material
///
/// VGM implementation for Geant4 material.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MATERIAL_H
#define GEANT4_GM_MATERIAL_H

#include "VGM/materials/IMaterial.h"

#include "G4Material.hh"

#include <string>

namespace Geant4GM {

class Material : public virtual VGM::IMaterial
{
 public:
  Material(const std::string& name, double density, VGM::IElement* element,
    bool isVacuum = false);

  Material(const std::string& name, double density, VGM::IElement* element,
    VGM::MaterialState state, double temperature, double pressure,
    bool isVacuum = false);

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

  Material(G4Material* material);
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
  G4State GetG4State(VGM::MaterialState state) const;
  VGM::MaterialState GetVGMState(G4State state) const;

  G4Material* fMaterial;
};

} // namespace Geant4GM

#endif // GEANT4_GM_MATERIAL_H
