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

const VGM::MaterialState
              RootGM::Material::fgkDefaultState = VGM::kUndefined;
const double  RootGM::Material::fgkDefaultTemperature = 275.13;  // kelvin
const double  RootGM::Material::fgkDefaultPressure = 1.0;        // atmosphere  
const double  RootGM::Material::fgkVacuumDensity = 1.e-25;       // g/cm3
const double  RootGM::Material::fgkVacuumTemperature = 2.73;     // kelvin
const double  RootGM::Material::fgkVacuumPressure = 2.96077e-23; // atmosphere  

//_____________________________________________________________________________
RootGM::Material::Material(const std::string& name, 
                           double density, 
		           VGM::IElement* element,
			   double radlen, double intlen,
 	                   VGM::MaterialState state,
	                   double temperature, double pressure)
 :  VGM::IMaterial(),
    fMaterial(0),
    fState(state),
    fTemperature(temperature),
    fPressure(pressure)
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

  // Update parameters if vacuum
  density = UpdateParametersIfVacuum(density);
  
  fMaterial = new TGeoMixture(name.data(), 1, density / RootGM::Units::MassDensity());
			      
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
                           const VGM::MassFractionVector& fractions,
 	                   VGM::MaterialState state,
	                   double temperature, double pressure)
  : VGM::IMaterial(),
    fMaterial(0),
    fState(state),
    fTemperature(temperature),
    fPressure(pressure)
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
    
  // Update parameters if vacuum
  density = UpdateParametersIfVacuum(density);
  
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
    fMaterial(material),	
    fState(fgkDefaultState),
    fTemperature(fgkDefaultTemperature),
    fPressure(fgkDefaultPressure)
{
/// Standard constructor to define material from the Root object

  // Update parameters if vacuum
  UpdateParametersIfVacuum(Density());
  
  // Register material in the map
  RootGM::MaterialMap::Instance()->AddMaterial(this, fMaterial); 
}    		  

//_____________________________________________________________________________
RootGM::Material::Material() 
  : VGM::IMaterial(),
    fMaterial(0), 
    fState(fgkDefaultState),
    fTemperature(fgkDefaultTemperature),
    fPressure(fgkDefaultPressure)
{
/// Protected default constructor
}  

//_____________________________________________________________________________
RootGM::Material::Material(const Material& rhs) 
  : VGM::IMaterial(rhs), 
    fMaterial(0), 
    fState(fgkDefaultState),
    fTemperature(fgkDefaultTemperature),
    fPressure(fgkDefaultPressure)
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
double RootGM::Material::UpdateParametersIfVacuum(double density)
{
  if ( density < fgkVacuumDensity ) {
    fTemperature = fgkVacuumTemperature;
    fPressure = fgkVacuumPressure;
    return fgkVacuumDensity;
  }
  else
    return density;
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
  return fState; 
}    

//_____________________________________________________________________________
double  RootGM::Material::Temperature() const
{
  return fTemperature;
}
  
//_____________________________________________________________________________
double  RootGM::Material::Pressure() const
{
  return fPressure;
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


