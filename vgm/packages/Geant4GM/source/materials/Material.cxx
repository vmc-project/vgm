// $Id$
//
// Class Material
// ---------------
// The interface to materials.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/materials/Material.h"
#include "Geant4GM/materials/Element.h"
#include "Geant4GM/materials/ElementMap.h"

//_____________________________________________________________________________
Geant4GM::Material::Material(const std::string& name, 
                             double density,
			     VGM::IElement* element) 
  : VGM::IMaterial(),
    fMaterial(0)
			       			  
{

  if ( density == universe_mean_density ) {
    // Create Vacuum material
    fMaterial = new G4Material(name, density, 1,
                               kStateGas, 3.e-18*pascal, 2.73*kelvin);
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
Geant4GM::Material::Material(const std::string& name,
                             double density,
		             const VGM::ElementVector& elements,
                             const VGM::MassFractionVector& fractions)
  : VGM::IMaterial(),
    fMaterial(0)
{
//
  // Check coherence
  if (elements.size() != fractions.size()) {
    std::cerr << "    Geant4GM::Material::Material: " << std::endl; 
    std::cerr << "    Elements size and fractions size differ.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  // Create material 
  fMaterial = new G4Material(name, density, elements.size());

  // Add elements
  for (unsigned int i=0; i<elements.size(); i++) {
    G4Element* g4Element 
      = ElementMap::Instance()->GetElement(elements[i]);
    fMaterial->AddElement(g4Element, fractions[i]);    
  }
}
			   
//_____________________________________________________________________________
Geant4GM::Material::Material(G4Material* material)
  : VGM::IMaterial(),
    fMaterial(material)	
{
//
}    		  

//_____________________________________________________________________________
Geant4GM::Material::~Material() {
//
}

//
// private functions
//
//_____________________________________________________________________________
void Geant4GM::Material::CheckIndex(int iel) const
{
  if (iel<0 || iel >= NofElements()) {  
    std::cerr << "    Geant4GM::Material::CheckIndex: " << std::endl;
    std::cerr << "    Index of element outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string Geant4GM::Material::Name() const
{
  return fMaterial->GetName();
}  

//_____________________________________________________________________________
double  Geant4GM::Material::Density() const
{
  return fMaterial->GetDensity();
}

//_____________________________________________________________________________
double  Geant4GM::Material::RadiationLength() const
{
  return fMaterial->GetRadlen();
}

//_____________________________________________________________________________
double  Geant4GM::Material::NuclearInterLength() const
{
  return fMaterial->GetNuclearInterLength();
}
    
//_____________________________________________________________________________
int  Geant4GM::Material::NofElements() const
{
  return fMaterial->GetNumberOfElements();
}

//_____________________________________________________________________________
VGM::IElement*  
Geant4GM::Material::Element(int iel) const
{
  CheckIndex(iel);

  G4Element* g4Element = (*fMaterial->GetElementVector())[iel];
  return ElementMap::Instance()->GetElement(g4Element);
}

//_____________________________________________________________________________
double  Geant4GM::Material::MassFraction(int iel) const
{
  CheckIndex(iel);
  return fMaterial->GetFractionVector()[iel];
}

