// $Id$

// -----------------------------------------------------------------------
// The BaseVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class VMaterialFactory
// ---------------
// The abstract base class to material factory.
// It owns the material stores and implements the export
// to other factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IIsotope.h"
#include "VGM/materials/IElement.h"
#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IMedium.h"

#include "BaseVGM/materials/VMaterialFactory.h"
#include "BaseVGM/common/utilities.h"


//_____________________________________________________________________________
BaseVGM::VMaterialFactory::VMaterialFactory(const std::string& name)
  : VGM::IMaterialFactory(),
    fDebug(0),
    fName(name),
    fIsotopes(),
    fElements(),
    fMaterials(),
    fMedia()
{
/// Standard constructor
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::VMaterialFactory()
  : VGM::IMaterialFactory()
{
/// Protected default constructor
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::VMaterialFactory(const VMaterialFactory& rhs)
  : VGM::IMaterialFactory(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::~VMaterialFactory()
{
// Deletes all objects created via material factory

  // Delete isotopes
  for (unsigned int i=0; i<fIsotopes.size(); i++) {
    delete fIsotopes[i];
  }

  // Delete elements
  for (unsigned int i=0; i<fElements.size(); i++) {
    delete fElements[i];
  }

  // Delete materials
  for (unsigned int j=0; j<fMaterials.size(); j++) {
    delete fMaterials[j];
  }

  // Delete media
  for (unsigned int k=0; k<fMedia.size(); k++) {
    delete fMedia[k];
  }
}

//
// private functions
//

//_____________________________________________________________________________
VGM::IIsotope*
BaseVGM::VMaterialFactory::ExportIsotope(
                                 VGM::IIsotope* isotope,
                                 VGM::IMaterialFactory* factory) const
{
// Exports specified material to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting isotope: ";
    if (Debug()>1) std::cout << isotope;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *isotope << std::endl;
  }

  VGM::IIsotope* newIsotope
    =  factory->CreateIsotope(
                        isotope->Name(),
                        isotope->Z(),
                        isotope->N(),
                        isotope->A());
  return newIsotope;
}

//_____________________________________________________________________________
VGM::IElement*
BaseVGM::VMaterialFactory::ExportElement(
                                 VGM::IElement* element,
                                 VGM::IMaterialFactory* factory,
			         IsotopeMap* isotopeMap) const
{
// Exports specified element to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting element: ";
    if (Debug()>1) std::cout << element;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *element << std::endl;
  }

  VGM::IElement* newElement;
  if ( ! element->NofIsotopes() ) {
    newElement
      =  factory->CreateElement(
                          element->Name(),
                          element->Symbol(),
                          element->Z(),
                          element->A());
  }
  else {
    // Fill isotopes vector
    VGM::IsotopeVector isotopes;
    VGM::RelAbundanceVector relAbundances;
    for ( int i=0; i<element->NofIsotopes(); i++ ) {
      VGM::IIsotope* isotope = element->Isotope(i);
      VGM::IIsotope* newIsotope = (*isotopeMap)[isotope];
      double relAbundance =  element->RelAbundance(i);

      isotopes.push_back(newIsotope);
      relAbundances.push_back(relAbundance);
    }
    newElement
      =  factory->CreateElement(
                          element->Name(),
                          element->Symbol(),
                          isotopes,
                          relAbundances);
  }

  return newElement;
}

//_____________________________________________________________________________
VGM::IMaterial*
BaseVGM::VMaterialFactory::ExportMaterial(
                                  VGM::IMaterial* material,
                                  VGM::IMaterialFactory* factory,
			          ElementMap* elementMap) const
{
// Exports specified material to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting material: ";
    if (Debug()>1) std::cout << material;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *material << std::endl;
  }

  VGM::IMaterial* newMaterial;
  int nofElements = material->NofElements();
  if (nofElements == 1) {
    VGM::IElement* newElement = (*elementMap)[material->Element(0)];
    newMaterial
      = factory->CreateMaterial(
                        material->Name(),
                        material->Density(),
			newElement,
			material->RadiationLength(),
			material->NuclearInterLength(),
			material->State(),
			material->Temperature(),
			material->Pressure());
  }
  else {
    // Fill elements vector
    VGM::ElementVector elements;
    VGM::MassFractionVector massFractions;
    for (int i=0; i<material->NofElements(); i++) {
      VGM::IElement* element = material->Element(i);
      VGM::IElement* newElement = (*elementMap)[element];
      double massFraction =  material->MassFraction(i);

      elements.push_back(newElement);
      massFractions.push_back(massFraction);
    }

    newMaterial
      = factory->CreateMaterial(
                        material->Name(),
			material->Density(),
			elements,
			massFractions,
			material->State(),
			material->Temperature(),
			material->Pressure());
  }

  return newMaterial;
}

//_____________________________________________________________________________
VGM::IMedium*
BaseVGM::VMaterialFactory::ExportMedium(
                                VGM::IMedium* medium,
                                VGM::IMaterialFactory* factory,
				MaterialMap* materialMap) const
{
// Exports specified material to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting medium: ";
    if (Debug()>1)  std::cout << medium;
    std::cout  << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *medium << std::endl;
  }

  VGM::IMaterial* material = medium->Material();
  VGM::IMaterial* newMaterial
    = (*materialMap)[material];

  int nofParameters  = medium->NofParameters();
  double* parameters = new double[nofParameters];
  for (int i=0; i<nofParameters; i++)
    parameters[i] = medium->Parameter(i);

  VGM::IMedium* newMedium
    = factory->CreateMedium(medium->Name(),
                            medium->Id(),
                            newMaterial,
			    nofParameters, parameters);

  delete [] parameters;

  return  newMedium;
}

//_____________________________________________________________________________
VGM::IMedium*
BaseVGM::VMaterialFactory::GenerateMedium(
                                  VGM::IMaterial* material,
                                  int mediumId,
                                  VGM::IMaterialFactory* factory,
				  MaterialMap* materialMap) const
{
// Exports specified material to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Generation medium for material: ";
    if (Debug()>1)  std::cout << material;
    std::cout  << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *material << std::endl;
  }

  VGM::IMaterial* newMaterial = (*materialMap)[material];

  int nofParameters  = 0;
  double* parameters = new double[nofParameters];

  VGM::IMedium* newMedium
    = factory->CreateMedium(material->Name(),
                            mediumId,
                            newMaterial,
			    nofParameters, parameters);

  delete [] parameters;

  return  newMedium;
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::IsotopeMap*
BaseVGM::VMaterialFactory::ExportIsotopes(VGM::IMaterialFactory* factory) const
{
// Export the whole isotope store to the given factory.
// ---

  IsotopeMap* isotopeMap = new IsotopeMap();

  for (unsigned int i=0; i<Isotopes().size(); i++) {

    VGM::IIsotope* isotope = Isotopes()[i];
    VGM::IIsotope* newIsotope = ExportIsotope(isotope, factory);

    // Map new isotope to old isotope
    (*isotopeMap)[isotope] = newIsotope;
  }

  return isotopeMap;
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::ElementMap*
BaseVGM::VMaterialFactory::ExportElements(VGM::IMaterialFactory* factory,
                                          IsotopeMap* isotopeMap) const
{
// Export the whole element store to the given factory.
// ---

  ElementMap* elementMap = new ElementMap();

  for (unsigned int i=0; i<Elements().size(); i++) {

    VGM::IElement* element = Elements()[i];
    VGM::IElement* newElement = ExportElement(element, factory, isotopeMap);

    // Map new element to old element
    (*elementMap)[element] = newElement;
  }

  return elementMap;
}

//_____________________________________________________________________________
BaseVGM::VMaterialFactory::MaterialMap*
BaseVGM::VMaterialFactory::ExportMaterials(
                                   VGM::IMaterialFactory* factory,
                                   ElementMap* elementMap) const
{
// Export the whole material store to the given factory.
// ---

  MaterialMap* materialMap = new MaterialMap();

  for (unsigned int i=0; i<Materials().size(); i++) {

    VGM::IMaterial* material = Materials()[i];
    VGM::IMaterial* newMaterial = ExportMaterial(material, factory, elementMap);

    // Map new material to old material
    (*materialMap)[material] = newMaterial;
  }

  return materialMap;
}

//_____________________________________________________________________________
void BaseVGM::VMaterialFactory::ExportMedia(
                                    VGM::IMaterialFactory* factory,
                                    MaterialMap* materialMap) const
{
// Export the whole media store to the given factory.
// ---

  for (unsigned int i=0; i<Media().size(); i++) {
    VGM::IMedium* medium = Media()[i];
    ExportMedium(medium, factory, materialMap);
  }

  delete materialMap;
}

//_____________________________________________________________________________
void BaseVGM::VMaterialFactory::GenerateMedia(
                                      VGM::IMaterialFactory* factory,
                                      MaterialMap* materialMap) const
{
// Generate media from materials.
// (Use this fuinction if the given factory has not defined media.)
// ---

  for (unsigned int i=0; i<Materials().size(); i++) {
    VGM::IMaterial* material = Materials()[i];
    GenerateMedium(material, i, factory, materialMap);
  }

  delete materialMap;
}

//
// public functions
//

//_____________________________________________________________________________
const VGM::IIsotope*
BaseVGM::VMaterialFactory::Isotope(const std::string& name) const
{
/// Finds the VGM isotope specified by name;
/// returns 0 if isotope is not found.

  for (unsigned int i=0; i<Isotopes().size(); i++) {
    const VGM::IIsotope* isotope = Isotopes()[i];
    if (isotope->Name() == name) return isotope;
  }

  return 0;
}

//_____________________________________________________________________________
const VGM::IElement*
BaseVGM::VMaterialFactory::Element(const std::string& name) const
{
/// Finds the VGM element specified by name;
/// returns 0 if element is not found.

  for (unsigned int i=0; i<Elements().size(); i++) {
    const VGM::IElement* element = Elements()[i];
    if (element->Name() == name) return element;
  }

  return 0;
}

//_____________________________________________________________________________
const VGM::IMaterial*
BaseVGM::VMaterialFactory::Material(const std::string& name) const
{
/// Finds the VGM material specified by name;
/// returns 0 if material is not found.

  for (unsigned int i=0; i<Materials().size(); i++) {
    const VGM::IMaterial* material = Materials()[i];
    if (material->Name() == name) return material;
  }

  return 0;
}

//_____________________________________________________________________________
const VGM::IMedium*
BaseVGM::VMaterialFactory::Medium(const std::string& name) const
{
/// Finds the VGM medium specified by name;
/// returns 0 if medium is not found.

  for (unsigned int i=0; i<Media().size(); i++) {
    const VGM::IMedium* medium = Media()[i];
    if (medium->Name() == name) return medium;
  }

  return 0;
}

//_____________________________________________________________________________
bool BaseVGM::VMaterialFactory::Export(VGM::IMaterialFactory* factory) const
{
/// Export the whole material and media store to the given factory.

  IsotopeMap* isotopeMap = ExportIsotopes(factory);
  ElementMap* elementMap = ExportElements(factory, isotopeMap);
  MaterialMap* materialMap = ExportMaterials(factory, elementMap);
  if  (Media().size()>0)
    ExportMedia(factory, materialMap);
  else
    GenerateMedia(factory, materialMap);

  return true;
}

//_____________________________________________________________________________
void  BaseVGM::VMaterialFactory::PrintIsotopes() const
{
/// Print all isotopes.

  const VGM::IsotopeStore& isotopes = Isotopes();

  for (unsigned i=0; i<isotopes.size(); i++) {

    std::cout << i << "th isotope: " << std::endl;
    std::cout << *isotopes[i] << std::endl;
  }
}

//_____________________________________________________________________________
void  BaseVGM::VMaterialFactory::PrintElements() const
{
/// Print all elements.

  const VGM::ElementStore& elements = Elements();

  for (unsigned i=0; i<elements.size(); i++) {

    std::cout << i << "th element: " << std::endl;
    std::cout << *elements[i] << std::endl;
  }
}

//_____________________________________________________________________________
void  BaseVGM::VMaterialFactory::PrintMaterials() const
{
/// Print all materials.

  const VGM::MaterialStore& materials = Materials();

  for (unsigned i=0; i<materials.size(); i++) {

    std::cout << i << "th material: " << std::endl;
    std::cout << *materials[i] << std::endl;
  }
}

//_____________________________________________________________________________
void  BaseVGM::VMaterialFactory::PrintMedia() const
{
/// Print all media

  const VGM::MediumStore& media = Media();

  for (unsigned i=0; i<media.size(); i++) {

    std::cout << i << "th medium: " << std::endl;
    std::cout << *media[i] << std::endl;
  }
}
