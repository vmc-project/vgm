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

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Polyhedra.h"
#include "Geant4GM/solids/SolidMap.h"

const int Geant4GM::Polyhedra::fgkMaxNofZPlanes = 50;
double*   Geant4GM::Polyhedra::fgZBuffer = 0;
double*   Geant4GM::Polyhedra::fgRinBuffer = 0;
double*   Geant4GM::Polyhedra::fgRoutBuffer = 0;

//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra(
                         const std::string& name, 
                         double sphi, double dphi, int nofSides, int nofZplanes,
                         double* z, double* rin, double* rout)
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolyhedra(0)
{
  // Apply units
  
  double* z2    = new double[nofZplanes];
  double* rin2  = new double[nofZplanes];
  double* rout2 = new double[nofZplanes];

  for (int i=0; i<nofZplanes; i++) {
    z2[i]     = z[i]    / ClhepVGM::Units::Length();
    rin2[i]   = rin[i]  / ClhepVGM::Units::Length();
    rout2[i]  = rout[i] / ClhepVGM::Units::Length();
  }  
  
  fPolyhedra = new G4Polyhedra(name, 
                               sphi / ClhepVGM::Units::Angle(), 
			       dphi / ClhepVGM::Units::Angle(), 
			       nofSides, nofZplanes, 
                               z2, rin2, rout2);
			       
  Geant4GM::SolidMap::Instance()->AddSolid(this, fPolyhedra); 

  CreateBuffers();
  
  delete [] z2;
  delete [] rin2;
  delete [] rout2;
}


//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra(
                         G4Polyhedra* phedra, 
			 G4ReflectedSolid* reflPhedra)
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra(),
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

  CreateBuffers();
}

//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra() 
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra() 
{
//
}

//_____________________________________________________________________________
Geant4GM::Polyhedra::Polyhedra(const Polyhedra& rhs) 
  : VGM::ISolid(rhs),
    VGM::IPolyhedra(rhs),
    BaseVGM::VPolyhedra(rhs) 
{
//
}

//_____________________________________________________________________________
Geant4GM::Polyhedra::~Polyhedra() {
//
  delete [] fZValuesRefl;
}    

//_____________________________________________________________________________
void  Geant4GM::Polyhedra::CreateBuffers()
{
  if (!fgZBuffer)    fgZBuffer    = new double [fgkMaxNofZPlanes];
  if (!fgRinBuffer)  fgRinBuffer  = new double [fgkMaxNofZPlanes];
  if (!fgRoutBuffer) fgRoutBuffer = new double [fgkMaxNofZPlanes];
}

//_____________________________________________________________________________
std::string Geant4GM::Polyhedra::Name() const
{
  return fPolyhedra->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Polyhedra::StartPhi() const
{
  return fPolyhedra->GetStartPhi() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Polyhedra::DeltaPhi() const
{
  double deltaPhi = fPolyhedra->GetEndPhi() - fPolyhedra->GetStartPhi();
  
  return deltaPhi * ClhepVGM::Units::Angle() ;
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
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    if (!fIsReflected) {
      fgZBuffer[i] = fPolyhedra->GetOriginalParameters()->Z_values[i];
      fgZBuffer[i] *= ClhepVGM::Units::Length();
    }  
    else
      fgZBuffer[i] = fZValuesRefl[i] * ClhepVGM::Units::Length();

  return fgZBuffer;
}  

//_____________________________________________________________________________
double* Geant4GM::Polyhedra::InnerRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++) {
    fgRinBuffer[i] = fPolyhedra->GetOriginalParameters()->Rmin[i];
    fgRinBuffer[i] *= ConvertRadiusFactor();
    fgRinBuffer[i] *= ClhepVGM::Units::Length();
  }  

  return fgRinBuffer;
}  

//_____________________________________________________________________________
double* Geant4GM::Polyhedra::OuterRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++) {
    fgRoutBuffer[i] = fPolyhedra->GetOriginalParameters()->Rmax[i];
    fgRoutBuffer[i] *= ConvertRadiusFactor();
    fgRoutBuffer[i] *= ClhepVGM::Units::Length();
  }  

  return fgRoutBuffer;
}  
