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

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Polycone.h"
#include "Geant4GM/solids/SolidMap.h"

const int Geant4GM::Polycone::fgkMaxNofZPlanes = 50;
double*   Geant4GM::Polycone::fgZBuffer = 0;
double*   Geant4GM::Polycone::fgRinBuffer = 0;
double*   Geant4GM::Polycone::fgRoutBuffer = 0;

//_____________________________________________________________________________
Geant4GM::Polycone::Polycone(
                        const std::string& name, 
                        double sphi, double dphi, int nofZplanes,
                        double* z, double* rin, double* rout)
  : VGM::ISolid(),
    VGM::IPolycone(),
    BaseVGM::VPolycone(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolycone(0)
{
/// Standard constructor to define polycone from parameters
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg
/// \param nofZplanes number of planes perpendicular to the
///	   z axis (has to be >= 2)
/// \param z  array of z positions of the planes in mm
/// \param rin array of inside radius of the planes in mm
/// \param rout array of outside radius of the planes in mm

  // Apply units
  
  double* z2    = new double[nofZplanes];
  double* rin2  = new double[nofZplanes];
  double* rout2 = new double[nofZplanes];
  
  for (int i=0; i<nofZplanes; i++) {
    z2[i]     = z[i]    / ClhepVGM::Units::Length();
    rin2[i]   = rin[i]  / ClhepVGM::Units::Length();
    rout2[i]  = rout[i] / ClhepVGM::Units::Length();
  }  
  
  fPolycone = new G4Polycone(name,     
                           sphi / ClhepVGM::Units::Angle(), 
			   dphi / ClhepVGM::Units::Angle(), 
			   nofZplanes, 
			   z2, rin2, rout2);
  

  Geant4GM::SolidMap::Instance()->AddSolid(this, fPolycone); 

  CreateBuffers();
  
  delete [] z2;
  delete [] rin2;
  delete [] rout2;
}


//_____________________________________________________________________________
Geant4GM::Polycone::Polycone(
                        G4Polycone* polycone,
                        G4ReflectedSolid* reflPolycone)
  : VGM::ISolid(),
    VGM::IPolycone(),
    BaseVGM::VPolycone(),
    fIsReflected(false),
    fZValuesRefl(0),
    fPolycone(polycone)
{    
/// Standard constructor to define polycone from G4 object

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

  CreateBuffers();
}

//_____________________________________________________________________________
Geant4GM::Polycone::Polycone() 
  : VGM::ISolid(),
    VGM::IPolycone(),
    BaseVGM::VPolycone() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Polycone::Polycone(const Polycone& rhs) 
  : VGM::ISolid(rhs),
    VGM::IPolycone(rhs),
    BaseVGM::VPolycone(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Polycone::~Polycone() {
//
  delete [] fZValuesRefl;
}    

//_____________________________________________________________________________
void  Geant4GM::Polycone::CreateBuffers()
{
  if (!fgZBuffer)    fgZBuffer    = new double [fgkMaxNofZPlanes];
  if (!fgRinBuffer)  fgRinBuffer  = new double [fgkMaxNofZPlanes];
  if (!fgRoutBuffer) fgRoutBuffer = new double [fgkMaxNofZPlanes];
}

//_____________________________________________________________________________
std::string Geant4GM::Polycone::Name() const
{
  return fPolycone->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Polycone::StartPhi() const
{
  return fPolycone->GetStartPhi() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Polycone::DeltaPhi() const
{
  double deltaPhi = fPolycone->GetEndPhi() - fPolycone->GetStartPhi();
  
  return deltaPhi * ClhepVGM::Units::Angle() ;
}  

//_____________________________________________________________________________
int Geant4GM::Polycone::NofZPlanes() const
{
  return fPolycone->GetOriginalParameters()->Num_z_planes;
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::ZValues() const
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
      fgZBuffer[i] = fPolycone->GetOriginalParameters()->Z_values[i];
      fgZBuffer[i] *= ClhepVGM::Units::Length();
    }  
    else
      fgZBuffer[i] = fZValuesRefl[i] * ClhepVGM::Units::Length();

  return fgZBuffer;
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::InnerRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++) {
    fgRinBuffer[i] = fPolycone->GetOriginalParameters()->Rmin[i];
    fgRinBuffer[i] *= ClhepVGM::Units::Length();
  }  

  return fgRinBuffer;
}  

//_____________________________________________________________________________
double* Geant4GM::Polycone::OuterRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++) {
    fgRoutBuffer[i] = fPolycone->GetOriginalParameters()->Rmax[i];
    fgRoutBuffer[i] *= ClhepVGM::Units::Length();
  }  

  return fgRoutBuffer;
}  
