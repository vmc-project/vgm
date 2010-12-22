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
// Class MaterialFactory
// ------------------------
// The interface to material factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"

#include "ClhepVGM/Units.h"

#include "BaseVGM/common/utilities.h"

#include "Geant4GM/materials/MaterialFactory.h"
#include "Geant4GM/materials/IsotopeMap.h"
#include "Geant4GM/materials/Isotope.h"
#include "Geant4GM/materials/ElementMap.h"
#include "Geant4GM/materials/Element.h"
#include "Geant4GM/materials/MaterialMap.h"
#include "Geant4GM/materials/Material.h"
#include "Geant4GM/materials/Medium.h"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"

const double Geant4GM::MaterialFactory::fgkTolerance = 1e-09; 

//_____________________________________________________________________________
Geant4GM::MaterialFactory::MaterialFactory()
  : VGM::IMaterialFactory(),
    BaseVGM::VMaterialFactory("Geant4_GM_Material_Factory"),
    fVacuumElements()
{  
/// Standard default constructor
}

//_____________________________________________________________________________
Geant4GM::MaterialFactory::MaterialFactory(const MaterialFactory& rhs)
  : VGM::IMaterialFactory(rhs),
    BaseVGM::VMaterialFactory(rhs),
    fVacuumElements(rhs.fVacuumElements)
    
{  
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::MaterialFactory::~MaterialFactory() {
//
  
  // delete map singletons

  delete Geant4GM::ElementMap::Instance();
  delete Geant4GM::MaterialMap::Instance();
              // There is inconsistence in using the singleton maps
	      // via a factory which is not a singleton
	      // TO DO: to be improved later

}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::MaterialFactory::ImportIsotope(G4Isotope* isotope)
{
/// Import the specified G4 isotope.

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing isotope: "; 
    if (Debug()>1) {
      void* isotopePtr = (void*)isotope;
      std::cout << isotopePtr;
    }  
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *isotope << std::endl;
  }	      

  VGM::IIsotope* vgmIsotope = new Geant4GM::Isotope(isotope);
  IsotopeStore().push_back(vgmIsotope);
}

//_____________________________________________________________________________
void Geant4GM::MaterialFactory::ImportElement(G4Element* element)
{
/// Import the specified G4 element.

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing element: "; 
    if (Debug()>1) {
      void* elementPtr = (void*)element;
      std::cout << elementPtr;
    }  
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *element << std::endl;
  }	      

  VGM::IElement* vgmElement = new Geant4GM::Element(element);
  ElementStore().push_back(vgmElement);
}

//_____________________________________________________________________________
void Geant4GM::MaterialFactory::ImportMaterial(G4Material* material)
{
/// Import the specified G4 material.

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing material: "; 
    if (Debug()>1) {
      void* materialPtr = (void*)material;
      std::cout << materialPtr;
    }  
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    std::cout << *material << std::endl;
  }	      

  VGM::IMaterial* vgmMaterial = new Geant4GM::Material(material);
  MaterialStore().push_back(vgmMaterial);
}

//_____________________________________________________________________________
bool Geant4GM::MaterialFactory::CompareIsotopes(const G4Element* g4Element, 
                           const VGM::IsotopeVector& isotopes,
                           const VGM::RelAbundanceVector& relAbundances)
{
/// Compare the VGM isotope vector with the isotope vector in the given g4Element;
/// return true if the isotope composition is identical within the defined tolerance

  if ( isotopes.size() != g4Element->GetNumberOfIsotopes() ) return false;

  for ( G4int i=0; i<G4int(g4Element->GetNumberOfIsotopes()); ++i ) {

    const G4Isotope* g4Isotope = g4Element->GetIsotope(i);
    double g4RelAbundance = g4Element->GetRelativeAbundanceVector()[i];
    G4bool match = false;

    for ( G4int j=0; j<G4int(isotopes.size()); ++j ) {
      VGM::IIsotope* vgmIsotope = isotopes[j];
      if ( fabs ( vgmIsotope->Z() - g4Isotope->GetZ() ) < fgkTolerance &&
           fabs ( vgmIsotope->N() - g4Isotope->GetN() ) < fgkTolerance &&
           fabs ( vgmIsotope->A() - g4Isotope->GetA()/(g/mole) ) < fgkTolerance &&
           fabs ( relAbundances[j] - g4RelAbundance ) < fgkTolerance ) {
        match = true;
        break;
      }  
    }
    if ( ! match ) return false;         
  }
  
  // All isotopes were matched
  return true;  
}                              
      
//
// public functions
//

//_____________________________________________________________________________
VGM::IIsotope*   
Geant4GM::MaterialFactory::CreateIsotope(
                                 const std::string& name,      
                                 int z, int n, double a) 
{
// Create isotope if isotope with given name does not yet exist

  G4Isotope* g4Isotope = G4Isotope::GetIsotope(name, false);

  // Do not take the isotope if its properties do not match
  if ( g4Isotope &&
       ( fabs ( g4Isotope->GetZ() - z ) >= fgkTolerance ||
         fabs ( g4Isotope->GetN() - n  ) >= fgkTolerance ||
         fabs ( g4Isotope->GetA()/(g/mole) - a ) >= fgkTolerance ) ) {
     g4Isotope = 0;
  }           

  VGM::IIsotope* vgmIsotope;
  if ( g4Isotope ) {
    vgmIsotope = Geant4GM::IsotopeMap::Instance()->GetIsotope(g4Isotope);
  }  
  else {
    vgmIsotope = new Geant4GM::Isotope(name, z, n, a);
    IsotopeStore().push_back(vgmIsotope);
  }
  
  return vgmIsotope; 
}			       
                                 
//_____________________________________________________________________________
VGM::IElement* 
Geant4GM::MaterialFactory::CreateElement(
                                  const std::string& name,      
                                  const std::string& symbol,      
                                  double z, double a)
{
// Create element if such element with specified properties does not
// yet exist

  G4Element* g4Element = G4Element::GetElement(name, false);
  
  // Do not take the element if its properties do not match
  if ( g4Element &&
       ( fabs ( g4Element->GetZ() - z ) >= fgkTolerance || 
         fabs ( g4Element->GetA()/(g/mole) - a ) >= fgkTolerance ) ) { 
     g4Element = 0;  
  }     
  
  VGM::IElement* vgmElement;
  if (g4Element) {
    vgmElement = Geant4GM::ElementMap::Instance()->GetElement(g4Element);
    if ( ! vgmElement ) {
      vgmElement = new Geant4GM::Element(g4Element);
      ElementStore().push_back(vgmElement);
    }  
  }  
  else  {
    if ( z < 1.0) {
      // special case (vacuum)
      // in Geant4 vacuum has element with z = 1.0, a = 1.01
      vgmElement 
       = new Geant4GM::Element(name, symbol, z = 1.0, a = 1.01);

      fVacuumElements.insert(vgmElement);                               
    }
    else  {
      vgmElement = new Geant4GM::Element(name, symbol, z, a);
    }  

    ElementStore().push_back(vgmElement);
  }    
  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IElement* 
Geant4GM::MaterialFactory::CreateElement(
                                  const std::string& name,      
                                  const std::string& symbol,      
	                          const VGM::IsotopeVector& isotopes,
                                  const VGM::RelAbundanceVector& relAbundances)
{
// Create element if such element with specified properties does not
// yet exist

  G4Element* g4Element = G4Element::GetElement(name, false);
  
  // Do not take the element if its properties do not match
  if ( g4Element &&
       ! CompareIsotopes(g4Element, isotopes, relAbundances ) ) {
     g4Element = 0;  
  }     
  
  VGM::IElement* vgmElement;
  if (g4Element)
    vgmElement = Geant4GM::ElementMap::Instance()->GetElement(g4Element);
  else  {
    vgmElement = new Geant4GM::Element(name, symbol, isotopes, relAbundances);
    ElementStore().push_back(vgmElement);
  }
    
  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IElement* 
Geant4GM::MaterialFactory::CreateElement(int z, bool isotopes)
{
// Create element using Nist manager,
// if such element with specified properties does not yet exist

  G4NistManager* nistManager = G4NistManager::Instance();
  G4Element* g4Element = nistManager->FindOrBuildElement(z, isotopes);
  if ( ! g4Element ) {
    std::cerr << "No element with z=" << z << " defined." << std::endl;
    return 0;
  }
  
  VGM::IElement* vgmElement
    = Geant4GM::ElementMap::Instance()->GetElement(g4Element);
    
  if ( ! vgmElement ) {
    
    for ( unsigned i=0; i<g4Element->GetNumberOfIsotopes(); i++ )
      ImportIsotope(const_cast<G4Isotope*>(g4Element->GetIsotope(i)));
  
    vgmElement = new Geant4GM::Element(g4Element);
    ElementStore().push_back(vgmElement);
  }    
  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(     
                                 const std::string& name,      
                                 double density, 
		                 VGM::IElement* element,
		                 double /*radlen*/, double /*intlen*/)
{
// Create material 

  bool isVacuum = false;
  if ( fVacuumElements.find(element) != fVacuumElements.end() ) isVacuum = true;

  VGM::IMaterial* vgmMaterial 
    = new Geant4GM::Material(name, density, element, isVacuum);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(     
                                 const std::string& name,      
                                 double density, 
                                 VGM::IElement* element,
                                 double /*radlen*/, double /*intlen*/,
                                 VGM::MaterialState state, 
                                 double temperature, double pressure)
{
// Create material 

  bool isVacuum = false;
  if ( fVacuumElements.find(element) != fVacuumElements.end() ) isVacuum = true;

  VGM::IMaterial* vgmMaterial 
    = new Geant4GM::Material(name, density, element, 
                             state, temperature, pressure, isVacuum);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, fractions);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::MassFractionVector& fractions,
                                 VGM::MaterialState state,
                                 double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, fractions,
                             state, temperature, pressure);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, atomCounts);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
Geant4GM::MaterialFactory::CreateMaterial(
                                 const std::string& name, 
                                 double density,
			         const VGM::ElementVector& elements,
                                 const VGM::AtomCountVector& atomCounts,
                                 VGM::MaterialState state,
                                 double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new Geant4GM::Material(name, density, elements, atomCounts,
                             state, temperature, pressure);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMedium*  
Geant4GM::MaterialFactory::CreateMedium(const std::string& name,
                                 int mediumId,
	  		         VGM::IMaterial* material,
			         int nofParameters,
			         double* parameters)
{
// Create medium
 				    
  VGM::IMedium* vgmMedium
    = new Geant4GM::Medium(name, mediumId, material, nofParameters, parameters);
		      
  MediumStore().push_back(vgmMedium);
  return vgmMedium; 
}			       

//_____________________________________________________________________________
bool Geant4GM::MaterialFactory::Import()
{
/// Import all isotopes, elements, materials from G4MaterialTable

  const G4IsotopeTable* isotopeTable = G4Isotope::GetIsotopeTable();
  
  for (G4int i=0; i<G4int(isotopeTable->size()); i++) {
    G4Isotope* isotope = (*isotopeTable)[i];
    ImportIsotope(isotope);
  }  

  const G4ElementTable* elementTable = G4Element::GetElementTable();
  
  for (G4int i=0; i<G4int(elementTable->size()); i++) {
    G4Element* element = (*elementTable)[i];
    ImportElement(element);
  }  

  const G4MaterialTable* materialTable = G4Material::GetMaterialTable();
  
  for (G4int j=0; j<G4int(materialTable->size()); j++) {
    G4Material* material = (*materialTable)[j];
    ImportMaterial(material);
  }  

  return true;
}			      


