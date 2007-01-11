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
#include "RootGM/common/Units.h"

const double  RootGM::Material::fgkVacuumDensity = 1.e-25;       // g/cm3
const double  RootGM::Material::fgkVacuumTemperature = 2.73;     // kelvin
const double  RootGM::Material::fgkVacuumPressure = 2.96077e-23; // atmosphere  

//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name, 
                           double density, 
		           VGM::IElement* element,
			   double radlen, double intlen)
 :  VGM::IMaterial(),
    fMaterial(0),
    fElements()

{
/// Standard constructor to define material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param element element constituing this material
/// \param radlen radiation length in mm
/// \param intlen nuclear interaction length in mm

  if ( ! element ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No element defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Create vacuum if density is lower than universe mean density
  // or Z < 1.0
  if ( density < fgkVacuumDensity || element->Z() < 1.0 ) {
    fMaterial = new TGeoMaterial(name.data(), 
                                 element->A(), 
                                 element->Z(),
                                 fgkVacuumDensity  / RootGM::Units::MassDensity(),
                                 TGeoMaterial::kMatStateGas,
                                 fgkVacuumTemperature,
                                 fgkVacuumPressure / RootGM::Units::Pressure());
  }
  else {
    fMaterial = new TGeoMaterial(name.data(), 
                                 element->A(), 
                                 element->Z(),
                                 density / RootGM::Units::MassDensity());
  }

  // Add element
  fElements.push_back(element);
  
  // Set parameters
  fMaterial->SetRadLen(radlen, intlen);
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name, 
                           double density, 
		           VGM::IElement* element,
			   double radlen, double intlen,
 	                   VGM::MaterialState state,
	                   double temperature, double pressure)
 :  VGM::IMaterial(),
    fMaterial(0),
    fElements()
{
/// Standard constructor to define material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param element element constituing this material
/// \param radlen radiation length in mm
/// \param intlen nuclear interaction length in mm
/// \param state material state (not defined in Root material)
/// \param temperature material temperature (not defined in Root material)
/// \param pressure material pressure (not defined in Root material)

  if ( ! element ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No element defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Create vacuum if density is lower than universe mean density
  // or Z < 1.0
  if ( density < fgkVacuumDensity || element->Z() < 1.0 ) {
    fMaterial = new TGeoMaterial(
                        name.data(), 
                        element->A(), 
                        element->Z(),
                        fgkVacuumDensity     / RootGM::Units::MassDensity(),
                        TGeoMaterial::kMatStateGas,
                        fgkVacuumTemperature / RootGM::Units::Temperature(),
                        fgkVacuumPressure    / RootGM::Units::Pressure());
  }
  else {
    fMaterial = new TGeoMaterial(
                        name.data(), 
                        element->A(), 
                        element->Z(),
                        density     / RootGM::Units::MassDensity(),
                        GetGeoState(state),
                        temperature / RootGM::Units::Temperature(),
                        pressure    / RootGM::Units::Pressure());
  }                        

  // Add element
  fElements.push_back(element);
  
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
    fMaterial(0),
    fElements()
{
/// Standard constructor to define compound material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param elements vector of elements constituing 
///	   this material
/// \param fractions vector of mass fractions of
///	   elements constituing this material

  if ( ! elements.size() ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

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
    VGM::IElement* element = elements[i];
    mixture->AddElement(element->A(), element->Z(), fractions[i]);
    fElements.push_back(element);
  }			    			    
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name,
                           double density, 
		           const VGM::ElementVector& elements,
                           const VGM::MassFractionVector& fractions,
 	                   VGM::MaterialState state,
	                   double temperature, double pressure)
  : VGM::IMaterial(),
    fMaterial(0),
    fElements()
{
/// Standard constructor to define compound material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param elements vector of elements constituing 
///	   this material
/// \param fractions vector of mass fractions of
///	   elements constituing this material

  if ( ! elements.size() ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (elements.size() != fractions.size()) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    Elements size and fractions size differ." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  fMaterial = new TGeoMixture(
                      name.data(), 
                      elements.size(),
		      density     / RootGM::Units::MassDensity());

  fMaterial->SetState(GetGeoState(state));
  fMaterial->SetTemperature(temperature / RootGM::Units::Temperature());
  fMaterial->SetPressure(pressure / RootGM::Units::Pressure());
			      
  TGeoMixture* mixture = (TGeoMixture*)fMaterial;			      			      

  // Add elements
  for (UInt_t i=0; i<elements.size(); i++) {
    VGM::IElement* element = elements[i];
    mixture->AddElement(element->A(), element->Z(), fractions[i]);
    fElements.push_back(element);
  }			    			    
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name,
                           double density, 
		           const VGM::ElementVector& elements,
                           const VGM::AtomCountVector& atomCounts)
  : VGM::IMaterial(),
    fMaterial(0),
    fElements()
{
/// Standard constructor to define compound material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param elements vector of elements constituing 
///	   this material
/// \param atomCounts vector of atom counts of
///	   elements constituing this material

  if ( ! elements.size() ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (elements.size() != atomCounts.size()) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    Elements size and atomCounts size differ." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  fMaterial = new TGeoMixture(name.data(), 
                              elements.size(),
			      density / RootGM::Units::MassDensity());
			      
  TGeoMixture* mixture = (TGeoMixture*)fMaterial;			      			      

  // Calculate molecule mass to get mass fractions of elements
  // (As we cannot add element via a, z, atomCount to mixture
  //  directly)

  double amol = 0;
  for ( unsigned i=0; i<elements.size(); i++) 
    amol += elements[i]->A()*atomCounts[i];

  // Add elements
  for ( unsigned i=0; i<elements.size(); i++) {
    VGM::IElement* element = elements[i];
    double fraction = atomCounts[i] * element->A()/amol;
    mixture->AddElement(element->A(), element->Z(), fraction);
    fElements.push_back(element);
  }			    			    
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name,
                           double density, 
		           const VGM::ElementVector& elements,
                           const VGM::AtomCountVector& atomCounts,
 	                   VGM::MaterialState state,
	                   double temperature, double pressure)
  : VGM::IMaterial(),
    fMaterial(0),
    fElements()
{
/// Standard constructor to define compound material from parameters 
/// \param name its name
///	   (must be unique in the factory)
/// \param density in g/cm3
/// \param elements vector of elements constituing 
///	   this material
/// \param atomCounts vector of atom counts of
///	   elements constituing this material

  if ( ! elements.size() ) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    No elements defined.";
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }

  // Check coherence
  if (elements.size() != atomCounts.size()) {
    std::cerr << "    RootGM::Material::Material: " << std::endl; 
    std::cerr << "    Elements size and atomCounts size differ." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }
    
  fMaterial = new TGeoMixture(
                      name.data(), 
                      elements.size(),
		      density     / RootGM::Units::MassDensity());

  fMaterial->SetState(GetGeoState(state));
  fMaterial->SetTemperature(temperature / RootGM::Units::Temperature());
  fMaterial->SetPressure(pressure / RootGM::Units::Pressure());
			      
  TGeoMixture* mixture = (TGeoMixture*)fMaterial;			      			      

  // Calculate molecule mass to get mass fractions of elements
  // (As we cannot add element via a, z, atomCount to mixture
  //  directly)

  double amol = 0;
  for ( unsigned i=0; i<elements.size(); i++) 
    amol += elements[i]->A()*atomCounts[i];

  // Add elements
  for (UInt_t i=0; i<elements.size(); i++) {
    VGM::IElement* element = elements[i];
    double fraction = atomCounts[i] * element->A()/amol;
    mixture->AddElement(element->A(), element->Z(), fraction);
    fElements.push_back(element);
  }			    			    
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}
			   
//_____________________________________________________________________________
RootGM::Material::Material(TGeoMaterial* material,
                           const VGM::ElementVector& elements)
  : VGM::IMaterial(),
    fMaterial(material),
    fElements(elements)
{
/// Standard constructor to define material from the Root object

  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}    		  

//_____________________________________________________________________________
RootGM::Material::Material() 
  : VGM::IMaterial(),
    fMaterial(0), 
    fElements()
{
/// Protected default constructor
}  

//_____________________________________________________________________________
RootGM::Material::Material(const Material& rhs) 
  : VGM::IMaterial(rhs), 
    fMaterial(rhs.fMaterial),
    fElements(rhs.fElements)
{
/// Protected copy constructor
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

//_____________________________________________________________________________
TGeoMaterial::EGeoMaterialState 
RootGM::Material::GetGeoState(VGM::MaterialState state) const
{
  switch ( state ) {
    case VGM::kUndefined: return TGeoMaterial::kMatStateUndefined;
    case VGM::kSolid:     return TGeoMaterial::kMatStateSolid;
    case VGM::kLiquid:    return TGeoMaterial::kMatStateLiquid;
    case VGM::kGas:       return TGeoMaterial::kMatStateGas;
    default:              return TGeoMaterial::kMatStateUndefined;
  }
  
  return TGeoMaterial::kMatStateUndefined;
}  


//_____________________________________________________________________________
VGM::MaterialState 
RootGM::Material::GetVGMState(TGeoMaterial::EGeoMaterialState state) const
{
  switch ( state ) {
    case TGeoMaterial::kMatStateUndefined : return VGM::kUndefined;
    case TGeoMaterial::kMatStateSolid:      return VGM::kSolid;
    case TGeoMaterial::kMatStateLiquid:     return VGM::kLiquid;
    case TGeoMaterial::kMatStateGas:        return VGM::kGas;
    default:                                return VGM::kUndefined;
  }

  return VGM::kUndefined;
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
VGM::MaterialState  RootGM::Material::State() const
{
  return GetVGMState(fMaterial->GetState()); 
}    

//_____________________________________________________________________________
double  RootGM::Material::Temperature() const
{
  return fMaterial->GetTemperature() * RootGM::Units::Temperature();
}
  
//_____________________________________________________________________________
double  RootGM::Material::Pressure() const
{
  return fMaterial->GetPressure() * RootGM::Units::Pressure();
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

  return fElements[iel];
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

//_____________________________________________________________________________
int  RootGM::Material::AtomCount(int iel) const
{
  CheckIndex(iel);
  
  if (!fMaterial->IsMixture())
    return 1;
  else  
    return ((TGeoMixture*)fMaterial)->GetNmixt()[iel];
}


