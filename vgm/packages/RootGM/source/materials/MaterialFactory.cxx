// $Id$
//
// Class MaterialFactory
// ------------------------
// VGM material factory for Root.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoElement.h"
#include "TList.h"

#include "BaseVGM/common/utilities.h"

#include "RootGM/materials/MaterialFactory.h"
#include "RootGM/materials/Element.h"
#include "RootGM/materials/ElementMap.h"
#include "RootGM/materials/Material.h"
#include "RootGM/materials/MaterialMap.h"
#include "RootGM/materials/Medium.h"

//_____________________________________________________________________________
RootGM::MaterialFactory::MaterialFactory()
  : BaseVGM::VMaterialFactory("Root_GM_Material_Factory")
{  
//
  
  if (!gGeoManager)
    new TGeoManager("VGM Root geometry", "VGM Root geometry");  
}

//_____________________________________________________________________________
RootGM::MaterialFactory::~MaterialFactory() {
//
  
  // delete map singletons
  delete RootGM::ElementMap::Instance();
  delete RootGM::MaterialMap::Instance();
              // There is inconsistence in using the singleton maps
	      // via a factory which is not a singleton
	      // TO DO: to be improved later
}

//
// private functions
//

//_____________________________________________________________________________
void RootGM::MaterialFactory::ImportElement(TGeoElement* element)
{
// Imports the specified Root element.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing element: "; 
    if (Debug()>1) std::cout << element;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    // std::cout << *element << std::endl;
    element->Print();
  }	      

  VGM::IElement* vgmElement = new RootGM::Element(element);
  ElementStore().push_back(vgmElement);
}

//_____________________________________________________________________________
void RootGM::MaterialFactory::ImportMaterial(TGeoMaterial* material)
{
// Imports the specified Root material.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing material: "; 
    if (Debug()>1) std::cout << material;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    //std::cout << *material << std::endl;
    material->Print();
  }	      

  // Number of elements
  Int_t nofElements = 1;
  if (material->IsMixture()) 
    nofElements = ((TGeoMixture*)material)->GetNelements();

  // To be removed when fixed in Root
  if (! TGeoElementTable::Instance() ) new TGeoElementTable(1);
  
  // Import elements
  for (Int_t i=0; i<nofElements; i++) {
    TGeoElement* rootElement = material->GetElement(i);
    if (!RootGM::ElementMap::Instance()->GetElement(rootElement))
      ImportElement(rootElement);
  }    

   // Create material
  VGM::IMaterial* vgmMaterial = new RootGM::Material(material);
  MaterialStore().push_back(vgmMaterial);
}

//_____________________________________________________________________________
void RootGM::MaterialFactory::ImportMedium(TGeoMedium* medium)
{
// Imports the specified TGeo medium.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing medium: "; 
    if (Debug()>1) std::cout << medium;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    //std::cout << *medium << std::endl;
    medium->Print();
  }	      

  VGM::IMedium* vgmMedium = new RootGM::Medium(medium);
  MediumStore().push_back(vgmMedium);
}

//
// public functions
//

//_____________________________________________________________________________
VGM::IElement* 
RootGM::MaterialFactory::CreateElement(
                               const std::string& name,      
                               const std::string& symbol,      
                               double z, double a)
{
// Create element if such element with specified properties does not
// yet exist

  VGM::IElement* vgmElement = 0;

  TGeoElement* rootElement 
    = TGeoElementTable::Instance()->GetElement((int)z);
    
  if (!rootElement) {
    // The element is not defined in Root table - create a new one
    vgmElement = new RootGM::Element(name, symbol, z, a);
  }
  else {
    // The element is already defined in Root table
    vgmElement =  RootGM::ElementMap::Instance()->GetElement(rootElement);
    
    if (!vgmElement) {
      vgmElement = new RootGM::Element(rootElement);
      ElementStore().push_back(vgmElement);
    }  
  }    

  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
RootGM::MaterialFactory::CreateMaterial(     
                               const std::string& name,      
                               double density, 
		               VGM::IElement* element,
		               double radlen, double intlen)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new RootGM::Material(name, density, element, radlen, intlen);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
RootGM::MaterialFactory::CreateMaterial(
                               const std::string& name, 
                               double density,
			       const VGM::ElementVector& elements,
                               const VGM::MassFractionVector& fractions)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new RootGM::Material(name, density, elements, fractions);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMedium*  
RootGM::MaterialFactory::CreateMedium(
                               const std::string& name,
                               int mediumId,
			       VGM::IMaterial* material,
			       int nofParameters,
			       double* parameters)
{
// Create medium
 				    
  VGM::IMedium* vgmMedium
    = new RootGM::Medium(name, mediumId, material, nofParameters, parameters);
		      
  MediumStore().push_back(vgmMedium);
  return vgmMedium; 
}			       


//_____________________________________________________________________________
bool RootGM::MaterialFactory::Import()
{
// Import all elements, materials end media from TGeoManager
// (Elements are imported duiring import of materials)
// ---

  TList* materials = gGeoManager->GetListOfMaterials();
  TIter next(materials);
  while (TObject *obj = next()) {
    TGeoMaterial* material = (TGeoMaterial*)obj;    
    ImportMaterial(material);
  }

  TList* media = gGeoManager->GetListOfMedia();
  TIter next2(media);
  while (TObject *obj = next()) {
    TGeoMedium* medium = (TGeoMedium*)obj;    
    ImportMedium(medium);
  }

  return true;
}			      
