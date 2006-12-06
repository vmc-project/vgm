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
  : VGM::IMaterialFactory(),
    BaseVGM::VMaterialFactory("Root_GM_Material_Factory"),
    fUseTGeoElementTable(true)    
{  
/// Standard default constructor
  
  if (!gGeoManager)
    new TGeoManager("VGM Root geometry", "VGM Root geometry");  
}

//_____________________________________________________________________________
RootGM::MaterialFactory::MaterialFactory(const MaterialFactory& rhs) 
  : VGM::IMaterialFactory(rhs),
    BaseVGM::VMaterialFactory(rhs), 
    fUseTGeoElementTable(rhs.fUseTGeoElementTable)    
{
/// Protected copy constructor
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
VGM::IElement* 
RootGM::MaterialFactory::ImportElement(TGeoElement* rootElement)
{
/// Import the specified Root element

  VGM::IElement* vgmElement
    = RootGM::ElementMap::Instance()->GetElement(rootElement);
  if ( vgmElement ) return vgmElement;

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing element: "; 
    if (Debug()>1) std::cout << rootElement;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    // std::cout << *element << std::endl;
    rootElement->Print();
  }	      
      
  vgmElement = new RootGM::Element(rootElement);
  ElementStore().push_back(vgmElement);
  
  return vgmElement;
}

//_____________________________________________________________________________
VGM::IElement* 
RootGM::MaterialFactory::ImportElement(TGeoElement* element,
                                       int index, TGeoMaterial* material)
{
/// Import the element with given index from the given material 

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing " << index 
              << "th element of material \"" << material->GetName() << "\"  ";
    if (Debug()>1) std::cout << material;
    std::cout << std::endl;
    BaseVGM::DebugInfo();
    // std::cout << *element << std::endl;
    material->Print();
  }	      

  double z;
  double a;
  if ( ! material->IsMixture() ) { 
    z = material->GetZ();
    a = material->GetA();
  }
  else {
    z = ((TGeoMixture*)material)->GetZmixt()[index];
    a = ((TGeoMixture*)material)->GetAmixt()[index];
  }  
  
  std::string name = element->GetName();
  name += material->GetName();

  VGM::IElement* vgmElement = new RootGM::Element(element, name, z, a);
  ElementStore().push_back(vgmElement);
  
  return vgmElement;
}

//_____________________________________________________________________________
void RootGM::MaterialFactory::ImportMaterial(TGeoMaterial* material)
{
/// Import the specified Root material

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
  if (! gGeoManager->GetElementTable() ) new TGeoElementTable(200);
  
  // Import elements
  std::vector<VGM::IElement*> elements;
  for (Int_t i=0; i<nofElements; i++) {
    TGeoElement* rootElement = material->GetElement(i);
    VGM::IElement* vgmElement;
    if ( fUseTGeoElementTable ) 
      vgmElement = ImportElement(rootElement);
    else 
      vgmElement = ImportElement(rootElement, i, material);
    elements.push_back(vgmElement);  
  }               

   // Create material
  VGM::IMaterial* vgmMaterial = new RootGM::Material(material, elements);
  MaterialStore().push_back(vgmMaterial);
}

//_____________________________________________________________________________
void RootGM::MaterialFactory::ImportMedium(TGeoMedium* medium)
{
/// Imports the specified TGeo medium

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

  // Check first if the element with this name already exists
  VGM::IElement* vgmElement = 0;
  for ( unsigned int i=0; i<ElementStore().size(); i++) {
    VGM::IElement* element = ElementStore()[i];
    if ( element->Name() == name ) vgmElement = element;
  }
  if ( vgmElement ) return vgmElement;

  // The element is not yet defined - create a new one
  vgmElement = new RootGM::Element(name, symbol, z, a);
  ElementStore().push_back(vgmElement);

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
		               VGM::IElement* element,
		               double radlen, double intlen,
			       VGM::MaterialState state,
			       double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial 
    = new RootGM::Material(name, density, element, radlen, intlen, 
                           state, temperature, pressure);
		      
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
VGM::IMaterial* 
RootGM::MaterialFactory::CreateMaterial(
                               const std::string& name, 
                               double density,
			       const VGM::ElementVector& elements,
                               const VGM::MassFractionVector& fractions,
			       VGM::MaterialState state,
			       double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new RootGM::Material(name, density, elements, fractions,
                           state, temperature, pressure);
		      
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
/// Import all elements, materials and media from TGeoManager
/// (Elements are imported during import of materials)

  TList* materials = gGeoManager->GetListOfMaterials();
  TIter next(materials);
  while (TObject *obj = next()) {
    TGeoMaterial* material = (TGeoMaterial*)obj;    
    ImportMaterial(material);
  }

  TList* media = gGeoManager->GetListOfMedia();
  TIter next2(media);
  while (TObject *obj = next2()) {
    TGeoMedium* medium = (TGeoMedium*)obj;    
    ImportMedium(medium);
  }

  return true;
}			      


//_____________________________________________________________________________
void RootGM::MaterialFactory::UseTGeoElementTable(bool useTGeoElementTable)
{
/// Set option to use TGeo element table for elements definition
/// (this will set the A to elements defined in TGeo table instead
/// of that defined bu user and can reduce the number of elements
/// in case the same element is defined with different precision
/// in material definition)

  fUseTGeoElementTable = useTGeoElementTable;
}  

  		       
