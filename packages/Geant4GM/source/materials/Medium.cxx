// $Id$
//
// Class Medium
// ---------------
// The VGM implementation of interface to tracking medium.
// As there is no equivalent object in Geant4, the tracking medium
// parameters are store in data members of this class.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4Material.hh"

#include "VGM/materials/IMaterial.h"

#include "Geant4GM/materials/Medium.h"
#include "Geant4GM/materials/MaterialMap.h"

const int Geant4GM::Medium::fgkParamSize = 20;  

//_____________________________________________________________________________
Geant4GM::Medium::Medium(const std::string& name, 
                         int mediumId,
                         VGM::IMaterial* material,
                         int nofParameters, double* parameters)
  : BaseVGM::VMedium(material),
    fName(name),
    fMaterial(MaterialMap::Instance()->GetMaterial(material)), 
    fId(mediumId),
    fParameters(new G4double[fgkParamSize])
{
  for (G4int i=0; i<fgkParamSize; i++) {
    if (i<nofParameters) 
      fParameters[i] = parameters[i];
    else  
      fParameters[i] = 0;
  }   
}
			   
//_____________________________________________________________________________
Geant4GM::Medium::~Medium() {
//
  delete [] fParameters;
}

//
// private functions
//
//_____________________________________________________________________________
void Geant4GM::Medium::CheckIndex(int i) const
{
  if (i<0 || i >= NofParameters()) {  
    std::cerr << "    Geant4GM::Medium::CheckIndex: " << std::endl;
    std::cerr << "    Index of parameter outside limits." << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
std::string Geant4GM::Medium::Name() const
{
  return fName;
}  

//_____________________________________________________________________________
int Geant4GM::Medium::Id() const
{
//
  return fId;
}  

//_____________________________________________________________________________
double  Geant4GM::Medium::Parameter(int i) const
{
  CheckIndex(i);
  
  return fParameters[i];
}   
