// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Material
// ---------------
// The interface to materials.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "BaseVGM/common/utilities.h"

#include "Geant4GM/materials/Element.h"
#include "Geant4GM/materials/ElementMap.h"
#include "Geant4GM/materials/Material.h"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  VGM::IElement* element, bool isVacuum)
  : VGM::IMaterial(), fMaterial(0)

{
  /// Standard constructor to define material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param element element constituing this material
  /// \param isVacuum the flag for Vacuum material

  if (!element) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No element defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();

  // Create vacuum if not allowed low density or
  // if material was associated with an element with Z < 1.0
  //
  if (density < universe_mean_density || isVacuum) {
    // lower density not allowed in Geant4
    density = universe_mean_density;

    // Create vacuum
    fMaterial = new G4Material(
      name, density, 1, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
  }
  else {
    // Create normal material
    fMaterial = new G4Material(name, density, 1);
  }

  // Add element
  G4Element* g4Element = ElementMap::Instance()->GetElement(element);
  fMaterial->AddElement(g4Element, 1.);
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  VGM::IElement* element, VGM::MaterialState state, double temperature,
  double pressure, bool isVacuum)
  : VGM::IMaterial(), fMaterial(0)

{
  /// Standard constructor to define material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param element element constituing this material
  /// \param state  the material state
  /// \param temperature the temperature in Kelvin
  /// \param pressure the pressure in atmosphere
  /// \param isVacuum the flag for Vacuum material

  if (!element) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No element defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();
  temperature /= ClhepVGM::Units::Temperature();
  pressure /= ClhepVGM::Units::Pressure();
  G4State g4State = GetG4State(state);

  // Create vacuum if not allowed low density or
  // if material was associated with an element with Z < 1.0
  //
  if (density < universe_mean_density || isVacuum) {
    // lower density not allowed in Geant4
    density = universe_mean_density;

    // Create vacuum
    fMaterial = new G4Material(
      name, density, 1, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
  }
  else {
    // Create normal material
    fMaterial =
      new G4Material(name, density, 1, g4State, temperature, pressure);
  }

  // Add element
  G4Element* g4Element = ElementMap::Instance()->GetElement(element);
  fMaterial->AddElement(g4Element, 1.);
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  const VGM::ElementVector& elements, const VGM::MassFractionVector& fractions)
  : VGM::IMaterial(), fMaterial(0)
{
  /// Standard constructor to define compound material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param elements vector of elements constituing
  ///	   this material
  /// \param fractions vector of mass fractions of
  ///	   elements constituing this material

  //

  if (!elements.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Check coherence
  if (elements.size() != fractions.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    Elements size and fractions size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();

  // Update density if lower than universe_mean_density
  if (density < universe_mean_density) {
    // lower density not allowed in Geant4
    density = universe_mean_density;
  }

  // Create material
  fMaterial = new G4Material(name, density, elements.size());

  // Add elements
  for (unsigned int i = 0; i < elements.size(); i++) {
    G4Element* g4Element = ElementMap::Instance()->GetElement(elements[i]);
    fMaterial->AddElement(g4Element, fractions[i]);
  }
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  const VGM::ElementVector& elements, const VGM::MassFractionVector& fractions,
  VGM::MaterialState state, double temperature, double pressure)
  : VGM::IMaterial(), fMaterial(0)
{
  /// Standard constructor to define compound material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param elements vector of elements constituing
  ///	   this material
  /// \param fractions vector of mass fractions of
  ///	   elements constituing this material
  /// \param state  the material state
  /// \param temperature the temperature in Kelvin
  /// \param pressure the pressure in atmosphere

  //

  if (!elements.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Check coherence
  if (elements.size() != fractions.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    Elements size and fractions size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();
  temperature /= ClhepVGM::Units::Temperature();
  pressure /= ClhepVGM::Units::Pressure();
  G4State g4State = GetG4State(state);

  // Update density if lower than universe_mean_density
  if (density < universe_mean_density) {
    // lower density not allowed in Geant4
    density = universe_mean_density;
  }

  // Create material
  fMaterial = new G4Material(
    name, density, elements.size(), g4State, temperature, pressure);

  // Add elements
  for (unsigned int i = 0; i < elements.size(); i++) {
    G4Element* g4Element = ElementMap::Instance()->GetElement(elements[i]);
    fMaterial->AddElement(g4Element, fractions[i]);
  }
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  const VGM::ElementVector& elements, const VGM::AtomCountVector& atomCounts)
  : VGM::IMaterial(), fMaterial(0)
{
  /// Standard constructor to define compound material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param elements vector of elements constituing
  ///	   this material
  /// \param atomCounts vector of atom counts of
  ///	   elements constituing this material

  //

  if (!elements.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Check coherence
  if (elements.size() != atomCounts.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    Elements size and atomCounts size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();

  // Update density if lower than universe_mean_density
  if (density < universe_mean_density) {
    // lower density not allowed in Geant4
    density = universe_mean_density;
  }

  // Create material
  fMaterial = new G4Material(name, density, elements.size());

  // Add elements
  for (unsigned int i = 0; i < elements.size(); i++) {
    G4Element* g4Element = ElementMap::Instance()->GetElement(elements[i]);
    fMaterial->AddElement(g4Element, atomCounts[i]);
  }
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, double density,
  const VGM::ElementVector& elements, const VGM::AtomCountVector& atomCounts,
  VGM::MaterialState state, double temperature, double pressure)
  : VGM::IMaterial(), fMaterial(0)
{
  /// Standard constructor to define compound material from parameters
  /// \param name its name
  ///	   (must be unique in the factory)
  /// \param density in g/cm3
  /// \param elements vector of elements constituing
  ///	   this material
  /// \param atomCounts vector of atom counts of
  ///	   elements constituing this material
  /// \param state  the material state
  /// \param temperature the temperature in Kelvin
  /// \param pressure the pressure in atmosphere

  //

  if (!elements.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Check coherence
  if (elements.size() != atomCounts.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl;
    std::cerr << "    Elements size and atomCounts size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }

  // Convert units
  density /= ClhepVGM::Units::MassDensity();
  temperature /= ClhepVGM::Units::Temperature();
  pressure /= ClhepVGM::Units::Pressure();
  G4State g4State = GetG4State(state);

  // Update density if lower than universe_mean_density
  if (density < universe_mean_density) {
    // lower density not allowed in Geant4
    density = universe_mean_density;
  }

  // Create material
  fMaterial = new G4Material(
    name, density, elements.size(), g4State, temperature, pressure);

  // Add elements
  for (unsigned int i = 0; i < elements.size(); i++) {
    G4Element* g4Element = ElementMap::Instance()->GetElement(elements[i]);
    fMaterial->AddElement(g4Element, atomCounts[i]);
  }
}

//_____________________________________________________________________________
Geant4GM::Material::Material(G4Material* material)
  : VGM::IMaterial(), fMaterial(material)
{
  /// Standard constructor to define material from the G4 object
}

//_____________________________________________________________________________
Geant4GM::Material::Material() : VGM::IMaterial()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Material::Material(const Material& rhs) : VGM::IMaterial(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Material::~Material()
{
  //
}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::Material::CheckIndex(int iel) const
{
  if (iel < 0 || iel >= NofElements()) {
    std::cerr << "    Geant4GM::Material::CheckIndex: " << std::endl;
    std::cerr << "    In material: " << Name() << std::endl;
    std::cerr << "    Index of element " << iel << " outside limits."
              << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl;
    exit(1);
  }
}

//_____________________________________________________________________________
G4State Geant4GM::Material::GetG4State(VGM::MaterialState state) const
{
  switch (state) {
    case VGM::kUndefined:
      return kStateUndefined;
    case VGM::kSolid:
      return kStateSolid;
    case VGM::kLiquid:
      return kStateLiquid;
    case VGM::kGas:
      return kStateGas;
    default:
      return kStateUndefined;
  }

  return kStateUndefined;
}

//_____________________________________________________________________________
VGM::MaterialState Geant4GM::Material::GetVGMState(G4State state) const
{
  switch (state) {
    case kStateUndefined:
      return VGM::kUndefined;
    case kStateSolid:
      return VGM::kSolid;
    case kStateLiquid:
      return VGM::kLiquid;
    case kStateGas:
      return VGM::kGas;
    default:
      return VGM::kUndefined;
  }

  return VGM::kUndefined;
}

//
// public functions
//

//_____________________________________________________________________________
std::string Geant4GM::Material::Name() const { return fMaterial->GetName(); }

//_____________________________________________________________________________
double Geant4GM::Material::Density() const
{
  return fMaterial->GetDensity() * ClhepVGM::Units::MassDensity();
}

//_____________________________________________________________________________
double Geant4GM::Material::RadiationLength() const
{
  return fMaterial->GetRadlen() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Material::NuclearInterLength() const
{
  return fMaterial->GetNuclearInterLength() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
VGM::MaterialState Geant4GM::Material::State() const
{
  return GetVGMState(fMaterial->GetState());
}

//_____________________________________________________________________________
double Geant4GM::Material::Temperature() const
{
  return fMaterial->GetTemperature() * ClhepVGM::Units::Temperature();
}

//_____________________________________________________________________________
double Geant4GM::Material::Pressure() const
{
  return fMaterial->GetPressure() * ClhepVGM::Units::Pressure();
}

//_____________________________________________________________________________
int Geant4GM::Material::NofElements() const
{
  return fMaterial->GetNumberOfElements();
}

//_____________________________________________________________________________
VGM::IElement* Geant4GM::Material::Element(int iel) const
{
  CheckIndex(iel);

  G4Element* g4Element = (*fMaterial->GetElementVector())[iel];
  return ElementMap::Instance()->GetElement(g4Element);
}

//_____________________________________________________________________________
double Geant4GM::Material::MassFraction(int iel) const
{
  CheckIndex(iel);

  return fMaterial->GetFractionVector()[iel];
}

//_____________________________________________________________________________
double Geant4GM::Material::AtomCount(int iel) const
{
  CheckIndex(iel);

  if (NofElements() == 1) return 1.0;

  return fMaterial->GetVecNbOfAtomsPerVolume()[iel] /
         fMaterial->GetTotNbOfAtomsPerVolume();
}
