// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class MaterialFactory
// ------------------------
// VGM material factory for Root.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterial.h"
#include "VGM/materials/IIsotope.h"

#include "BaseVGM/common/utilities.h"

#include "RootGM/materials/MaterialFactory.h"
#include "RootGM/materials/Element.h"
#include "RootGM/materials/ElementGeo.h"
#include "RootGM/materials/Isotope.h"
#include "RootGM/materials/Material.h"
#include "RootGM/materials/MaterialMap.h"
#include "RootGM/materials/Medium.h"

#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoElement.h"
#include "TList.h"

#include <math.h>

const double RootGM::MaterialFactory::fgkTolerance = 1e-09; 

//_____________________________________________________________________________
RootGM::MaterialFactory::MaterialFactory()
  : VGM::IMaterialFactory(),
    BaseVGM::VMaterialFactory("Root_GM_Material_Factory")
{  
/// Standard default constructor
  
  if (!gGeoManager)
    new TGeoManager("VGM Root geometry", "VGM Root geometry");  
}

//_____________________________________________________________________________
RootGM::MaterialFactory::MaterialFactory(const MaterialFactory& rhs) 
  : VGM::IMaterialFactory(rhs),
    BaseVGM::VMaterialFactory(rhs)
{
/// Protected copy constructor
} 

//_____________________________________________________________________________
RootGM::MaterialFactory::~MaterialFactory() {
//
  
  // delete map singletons
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
RootGM::MaterialFactory::GetElement(double z, double a) const
{
/// Find element with given z, a in the element store

  for ( unsigned i=0; i<Elements().size(); i++ ) {
    VGM::IElement* element = Elements()[i];
    
    if ( fabs(z - element->Z()) < fgkTolerance &&
         fabs(a - element->A()) < fgkTolerance ) return element;
  }
  
  return 0;
}   


//_____________________________________________________________________________
VGM::IIsotope* 
RootGM::MaterialFactory::GetIsotope(double z, double n) const
{
/// Find isotope with given z, n in the isotope store

  for ( unsigned i=0; i<Isotopes().size(); i++ ) {
    VGM::IIsotope* isotope = Isotopes()[i];
    
    if ( z == isotope->Z() && n == isotope->N() ) return isotope;
  }
  
  return 0;
}   


//_____________________________________________________________________________
void 
RootGM::MaterialFactory::ImportElements(TGeoMaterial* material,
                                        std::vector<VGM::IElement*>& elements)
{
/// Import elements from given Root material
/// (We do not use TGeoElementTable as the elements here may
/// differ from those defined in material


  int nofElements = 1;
  if ( material->IsMixture() ) 
    nofElements = ((TGeoMixture*)material)->GetNelements();

  for (Int_t i=0; i<nofElements; i++) {
   
    double z = material->GetZ();
    double a = material->GetA();
    if ( material->IsMixture() ) {
      z = ((TGeoMixture*)material)->GetZmixt()[i];
      a = ((TGeoMixture*)material)->GetAmixt()[i];
    }  

    // Get element from element store it it already exists
    VGM::IElement* vgmElement = GetElement(z, a);

    // Create VGM element if it does not exist  
    if ( ! vgmElement ) {
      // Get element name & symbol from Root element table
      TGeoElementTable* elementTable = gGeoManager->GetElementTable();
      TGeoElement* geoElement = elementTable->GetElement((int)z);
      std::string name = geoElement->GetTitle();
      std::string symbol = geoElement->GetName();

      bool isFromTable = 
             fabs(geoElement->Z() - z ) < fgkTolerance &&
             fabs(geoElement->A() - a ) < fgkTolerance;
      std::string from;           

      if ( isFromTable ) {
        vgmElement = new RootGM::ElementGeo(geoElement);
        from = "from TGeoTable";
      }  
      else  { 
        vgmElement = new RootGM::Element(name, symbol, z, a);
        from = "from material";
      }  
        
      if (Debug()>0) {
        BaseVGM::DebugInfo();
        std::cout << "Importing element: "; 
        std::cout << name << " " << symbol << " " << from << std::endl;
      }             
      
      ElementStore().push_back(vgmElement);
    }
    elements.push_back(vgmElement); 
  }
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

  // Import elements
  std::vector<VGM::IElement*> elements;
  ImportElements(material, elements);

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
VGM::IIsotope*   
RootGM::MaterialFactory::CreateIsotope(
                               const std::string& name,      
                               int z, int n, double a)
{
// Create isotope if it does not yet exists

  // Check first if the isotope with given z, n already exists
  VGM::IIsotope* vgmIsotope = GetIsotope(z, n);
  if ( vgmIsotope ) return vgmIsotope;

  // The isotope is not yet defined - create a new one
  vgmIsotope = new RootGM::Isotope(name, z, n, a);
  IsotopeStore().push_back(vgmIsotope);

  return vgmIsotope; 
}			       

                               

//_____________________________________________________________________________
VGM::IElement* 
RootGM::MaterialFactory::CreateElement(
                               const std::string& name,      
                               const std::string& symbol,      
                               double z, double a)
{
// Create element if such element with specified properties does not
// yet exist

  // Check first if the element with this z, a already exists
  VGM::IElement* vgmElement = GetElement(z, a);
  if ( vgmElement ) return vgmElement;

  // The element is not yet defined - create a new one
  vgmElement = new RootGM::Element(name, symbol, z, a);
  ElementStore().push_back(vgmElement);

  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IElement* 
RootGM::MaterialFactory::CreateElement(
                               const std::string& name,      
                               const std::string& symbol,      
 	                       const VGM::IsotopeVector& isotopes,
                               const VGM::RelAbundanceVector& relAbundances)
{
// Create element from isotopes

  // Create element 
  VGM::IElement* vgmElement 
    = new RootGM::Element(name, symbol, isotopes, relAbundances);
  ElementStore().push_back(vgmElement);

  return vgmElement; 
}			       

//_____________________________________________________________________________
VGM::IElement* 
RootGM::MaterialFactory::CreateElement(int z, bool /*isotopes*/)
{
// Create element using TGeoElementTable
// if such element with specified properties does not yet exist


  TGeoElementTable* elementTable = gGeoManager->GetElementTable();
  TGeoElement* geoElement = elementTable->GetElement(z);
  if ( ! geoElement ) {
    std::cerr << "No element with z=" << z << " defined." << std::endl;
    return 0;
  }  
  
  // Check first if the element with this name already exists
  VGM::IElement* vgmElement = GetElement(z, geoElement->A());
  if ( vgmElement ) return vgmElement;

  // The element is not yet defined - create a new one
  vgmElement = new RootGM::ElementGeo(geoElement);
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
VGM::IMaterial* 
RootGM::MaterialFactory::CreateMaterial(
                               const std::string& name, 
                               double density,
			       const VGM::ElementVector& elements,
                               const VGM::AtomCountVector& atomCounts)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new RootGM::Material(name, density, elements, atomCounts);
		      
  MaterialStore().push_back(vgmMaterial);
  return vgmMaterial; 
}			       

//_____________________________________________________________________________
VGM::IMaterial* 
RootGM::MaterialFactory::CreateMaterial(
                               const std::string& name, 
                               double density,
			       const VGM::ElementVector& elements,
                               const VGM::AtomCountVector& atomCounts,
			       VGM::MaterialState state,
			       double temperature, double pressure)
{
// Create material 

  VGM::IMaterial* vgmMaterial
    = new RootGM::Material(name, density, elements, atomCounts,
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
