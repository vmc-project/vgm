// $Id$
//
// Class Medium
// ---------------
// VGM implementations for Root medium.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "TGeoMaterial.h"

#include "VGM/materials/IMaterial.h"

#include "RootGM/materials/Medium.h"
#include "RootGM/materials/MaterialMap.h"

//_____________________________________________________________________________
RootGM::Medium::Medium(const std::string& name, 
                       int mediumId,
                       VGM::IMaterial* material,
                       int nofParameters, double* parameters)
  : VGM::IMedium(),
    BaseVGM::VMedium(material),
    fMedium(0)
{

  TGeoMaterial* geoMaterial
    = RootGM::MaterialMap::Instance()->GetMaterial(material);

  Double_t param[fgkParamSize];
  for (Int_t i=0; i<fgkParamSize; i++) {
    if (i<nofParameters) 
      param[i] = parameters[i];
    else  
      param[i] = 0;
  }   

  fMedium = new TGeoMedium(name.data(), mediumId, geoMaterial, param);
}
			   
//_____________________________________________________________________________
RootGM::Medium::Medium(TGeoMedium* medium)
  : VGM::IMedium(),
    BaseVGM::VMedium(RootGM::MaterialMap::Instance()
                    ->GetMaterial(medium->GetMaterial())),
    fMedium(medium)
{
//
}
			   
//_____________________________________________________________________________
RootGM::Medium::Medium() 
  : VGM::IMedium(),
    BaseVGM::VMedium() 
{
//
}  

//_____________________________________________________________________________
RootGM::Medium::Medium(const Medium& rhs) 
  : VGM::IMedium(rhs),
    BaseVGM::VMedium(rhs) 
{
//
}

//_____________________________________________________________________________
RootGM::Medium::~Medium() {
//
}

//
// private functions
//
//_____________________________________________________________________________
void RootGM::Medium::CheckIndex(int i) const
{
  if (i<0 || i >= NofParameters()) {  
    std::cerr << "    RootGM::Medium::CheckIndex: " << std::endl;
    std::cerr << "    Index of parameter outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string RootGM::Medium::Name() const
{
  return std::string(fMedium->GetName());
}  

//_____________________________________________________________________________
int RootGM::Medium::Id() const
{
//
  return fMedium->GetId();
}  

//_____________________________________________________________________________
double  RootGM::Medium::Parameter(int i) const
{
  CheckIndex(i);
  
  return fMedium->GetParam(i);
}   

