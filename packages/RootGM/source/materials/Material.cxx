// $Id$
//
// Class Material
// ---------------
// VGM implementations for Root material.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/materials/Material.h"
#include "RootGM/materials/MaterialMap.h"
#include "RootGM/materials/Element.h"
#include "RootGM/materials/ElementMap.h"
#include "RootGM/common/Units.h"


//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name, 
                           double density, 
		           VGM::IElement* element,
			   double radlen, double intlen)
  : VGM::IMaterial(),
    fMaterial(0)
{
//
  fMaterial = new TGeoMixture(name.data(), 1,
	 		      density / RootGM::Units::MassDensity());
			      
  TGeoMixture* mixture = (TGeoMixture*)fMaterial;			      			      

  // Add element
  TGeoElement* rootElement 
    = RootGM::ElementMap::Instance()->GetElement(element);
  mixture->DefineElement(0, rootElement, 1.0);
  
  // Set parameters
  fMaterial->SetRadLen(radlen, intlen);
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name,
                           double density, 
		           const VGM::ElementVector& elements,
                           const VGM::MassFractionVector& fractions)
  : VGM::IMaterial(),
    fMaterial(0)
{
//
  // Check coherence
  if (elements.size() != fractions.size()) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    Elements size and fractions size differ." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  fMaterial = new TGeoMixture(name.data(), 
                              elements.size(),
			      density / RootGM::Units::MassDensity());
			      
  TGeoMixture* mixture = (TGeoMixture*)fMaterial;			      			      

  // Add elements
  for (UInt_t i=0; i<elements.size(); i++) {
    TGeoElement* rootElement 
      = RootGM::ElementMap::Instance()->GetElement(elements[i]);
    mixture->DefineElement(i, rootElement, fractions[i]);
  }			    			    
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(TGeoMaterial* material)
  : VGM::IMaterial(),
    fMaterial(material)	
{
//
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}    		  

//_____________________________________________________________________________
RootGM::Material::~Material() {
//
}

//
// private functions
//
//_____________________________________________________________________________
void RootGM::Material::CheckIndex(int iel) const
{
  if (iel<0 || iel >= NofElements()) {  
    std::cerr << "    RootGM::Material::CheckIndex: " << std::endl;
    std::cerr << "    Index of element outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution ***" << std::endl;;
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Material::Name() const
{
  return std::string(fMaterial->GetName());
}  

//_____________________________________________________________________________
double  RootGM::Material::Density() const
{
  return fMaterial->GetDensity() * RootGM::Units::MassDensity();
}

//_____________________________________________________________________________
double  RootGM::Material::RadiationLength() const
{
  return fMaterial->GetRadLen() * RootGM::Units::Length();
}

//_____________________________________________________________________________
double  RootGM::Material::NuclearInterLength() const
{
  return fMaterial->GetIntLen() * RootGM::Units::Length();
}
    
//_____________________________________________________________________________
int  RootGM::Material::NofElements() const
{
  if (!fMaterial->IsMixture())
    return 1;
  else  
    return ((TGeoMixture*)fMaterial)->GetNelements();
}

//_____________________________________________________________________________
VGM::IElement*  
RootGM::Material::Element(int iel) const
{
  CheckIndex(iel);

  TGeoElement* rootElement = fMaterial->GetElement(iel);
  return RootGM::ElementMap::Instance()->GetElement(rootElement);
}



//_____________________________________________________________________________
double  RootGM::Material::MassFraction(int iel) const
{
  CheckIndex(iel);

  if (!fMaterial->IsMixture())
    return 1.0;
  else  
    return ((TGeoMixture*)fMaterial)->GetWmixt()[iel];
}


