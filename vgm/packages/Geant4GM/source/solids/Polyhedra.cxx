// $Id$
//
// Class Polyhedra
// ---------------
// VGM implementation for Geant4 polyhedra solid.
// If reflected, the parameters are changed as follows:
//    sphi, dphi  --> sphi', dphi'
//    nofSides    --> nofSides' 
//    nofZplanes  --> nofZplanes' 
//    z[i]        --> -z'[i]
//    rin, rout   --> rin', rout' 
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "Geant4GM/solids/Polyhedra.h"
#include "Geant4GM/solids/SolidMap.h"

//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra(
                         const std::string& name, 
                         double sphi, double dphi, int nofSides, int nofZplanes,
                         double* z, double* rin, double* rout)
  : BaseVGM::VPolyhedra(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolyhedra(new G4Polyhedra(name, sphi, dphi, nofSides, nofZplanes, 
                               z, rin, rout))
{
  Geant4GM::SolidMap::Instance()->AddSolid(this, fPolyhedra); 
}


//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra(
                         G4Polyhedra* phedra, 
			 G4ReflectedSolid* reflPhedra)
  : BaseVGM::VPolyhedra(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolyhedra(phedra)
{ 
  if (reflPhedra) {
    int     nofZplanes = phedra->GetOriginalParameters()->Num_z_planes;
    double* zValues    = phedra->GetOriginalParameters()->Z_values;
    fZValuesRefl = new double[nofZplanes];
    for (int i=0; i<nofZplanes; i++) fZValuesRefl[i] = - zValues[i];

    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflPhedra); 
  }
  else        
    Geant4GM::SolidMap::Instance()->AddSolid(this, phedra); 
}

//_____________________________________________________________________________
Geant4GM::Polyhedra::~Polyhedra() {
//
  delete [] fZValuesRefl;
}    

//_____________________________________________________________________________
std::string Geant4GM::Polyhedra::Name() const
{
  return fPolyhedra->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Polyhedra::StartPhi() const
{
  return fPolyhedra->GetStartPhi();
}  

//_____________________________________________________________________________
double Geant4GM::Polyhedra::DeltaPhi() const
{
  return fPolyhedra->GetEndPhi() - fPolyhedra->GetStartPhi();
}  

//_____________________________________________________________________________
int Geant4GM::Polyhedra::NofSides() const
{
  return fPolyhedra->GetOriginalParameters()->numSide;
}  

//_____________________________________________________________________________
int Geant4GM::Polyhedra::NofZPlanes() const
{
  return fPolyhedra->GetOriginalParameters()->Num_z_planes;
}  

//_____________________________________________________________________________
double* Geant4GM::Polyhedra::ZValues() const
{
  double* newZValues = new double[NofZPlanes()];
  if (!fIsReflected) {  
    for (int i=0; i<NofZPlanes(); i++)
      newZValues[i] = fPolyhedra->GetOriginalParameters()->Z_values[i];
  }    
  else {
    for (int i=0; i<NofZPlanes(); i++)
      newZValues[i] = fZValuesRefl[i];
  }    
  
  return newZValues;  
}  

//_____________________________________________________________________________
double* Geant4GM::Polyhedra::InnerRadiusValues() const
{
  double* newRinValues = new double[NofZPlanes()];
  for (int i=0; i<NofZPlanes(); i++) {
    newRinValues[i] = fPolyhedra->GetOriginalParameters()->Rmin[i] 
                    * ConvertRadiusFactor();
  }		    

  return newRinValues;
}  

//_____________________________________________________________________________
double* Geant4GM::Polyhedra::OuterRadiusValues() const
{
  double* newRoutValues = new double[NofZPlanes()];
  for (int i=0; i<NofZPlanes(); i++) {
    newRoutValues[i] = fPolyhedra->GetOriginalParameters()->Rmax[i] 
                     * ConvertRadiusFactor();
  }  		     

  return newRoutValues;
}  
