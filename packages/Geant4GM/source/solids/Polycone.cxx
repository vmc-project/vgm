// $Id$
//
// Class Polycone
// ---------------
// VGM implementation for Geant4 polycone solid.
// If reflected, the parameters are changed as follows:
//    sphi, dphi  --> sphi', dphi'
//    nofZplanes  --> nofZplanes' 
//    z[i]        --> -z'[i]
//    rin, rout   --> rin', rout' 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Polycone.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Polycone::Polycone(
                        const std::string& name, 
                        double sphi, double dphi, int nofZplanes,
                        double* z, double* rin, double* rout)
  : BaseVGM::VPolycone(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolycone(new G4Polycone(name, sphi, dphi, nofZplanes, z, rin, rout))
{
  Geant4GM::SolidMap::Instance()->AddSolid(this, fPolycone); 
}


//_____________________________________________________________________________
Geant4GM::Polycone::Polycone(
                        G4Polycone* polycone,
                        G4ReflectedSolid* reflPolycone)
  : BaseVGM::VPolycone(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolycone(polycone)
{    
  if (reflPolycone) {
    int     nofZplanes = polycone->GetOriginalParameters()->Num_z_planes;
    double* zValues    = polycone->GetOriginalParameters()->Z_values;
    fZValuesRefl = new double[nofZplanes];
    for (int i=0; i<nofZplanes; i++) fZValuesRefl[i] = - zValues[i];

    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflPolycone); 
  } 
  else   
    Geant4GM::SolidMap::Instance()->AddSolid(this, polycone); 
}

//_____________________________________________________________________________
Geant4GM::Polycone::~Polycone() {
//
  delete [] fZValuesRefl;
}    

//_____________________________________________________________________________
std::string Geant4GM::Polycone::Name() const
{
  return fPolycone->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Polycone::StartPhi() const
{
  return fPolycone->GetStartPhi();
}  

//_____________________________________________________________________________
double Geant4GM::Polycone::DeltaPhi() const
{
  return fPolycone->GetEndPhi() - fPolycone->GetStartPhi();
}  

//_____________________________________________________________________________
int Geant4GM::Polycone::NofZPlanes() const
{
  return fPolycone->GetOriginalParameters()->Num_z_planes;
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::ZValues() const
{
  if (!fIsReflected)
    return fPolycone->GetOriginalParameters()->Z_values;
  else
    return fZValuesRefl;  
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::InnerRadiusValues() const
{
  return fPolycone->GetOriginalParameters()->Rmin;
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::OuterRadiusValues() const
{
  return fPolycone->GetOriginalParameters()->Rmax;
}  
