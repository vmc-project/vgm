// $Id$
//
// Class Polycone
// ---------------
// VGM implementation for Root polycone solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include <iostream>

#include "RootGM/solids/Polycone.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

const int RootGM::Polycone::fgkMaxNofZPlanes = 50;
double*   RootGM::Polycone::fgZBuffer = 0;
double*   RootGM::Polycone::fgRinBuffer = 0;
double*   RootGM::Polycone::fgRoutBuffer = 0;

//_____________________________________________________________________________
RootGM::Polycone::Polycone(
                      const std::string& name, 
                      double sphi, double dphi, 
		      int nofZPlanes,
                      double* z, double* rin, double* rout)
  : BaseVGM::VPolycone(),
    fPolycone(0)
{
// 
  double* param = new double[3+3*nofZPlanes]; 
          // number of parameters: sphi, dphi, nz + 3*nofZPlanes
 
  param[0] = sphi/RootGM::Units::Angle();
  param[1] = dphi/RootGM::Units::Angle();
  param[2] = nofZPlanes;
  
  for (int i=0; i<nofZPlanes; i++) {
    int j = 3 + 3*i; 
    param[j]   = z[i]   / RootGM::Units::Length();
    param[j+1] = rin[i] / RootGM::Units::Length();
    param[j+2] = rout[i]/ RootGM::Units::Length();
  }

  fPolycone = new TGeoPcon(param);
  fPolycone->SetName(name.data());

  RootGM::SolidMap::Instance()->AddSolid(this, fPolycone); 
  CreateBuffers();

  delete [] param;
}


//_____________________________________________________________________________
RootGM::Polycone::Polycone(TGeoPcon* polycone)
  : BaseVGM::VPolycone(),
    fPolycone(polycone)
{    
  RootGM::SolidMap::Instance()->AddSolid(this, fPolycone); 
  CreateBuffers();
}

//_____________________________________________________________________________
RootGM::Polycone::~Polycone() {
//
}    

//_____________________________________________________________________________
void  RootGM::Polycone::CreateBuffers()
{
  if (!fgZBuffer)    fgZBuffer    = new double [fgkMaxNofZPlanes];
  if (!fgRinBuffer)  fgRinBuffer  = new double [fgkMaxNofZPlanes];
  if (!fgRoutBuffer) fgRoutBuffer = new double [fgkMaxNofZPlanes];
}

//_____________________________________________________________________________
std::string RootGM::Polycone::Name() const
{
  return fPolycone->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Polycone::StartPhi() const
{
  return fPolycone->GetPhi1()*RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Polycone::DeltaPhi() const
{
  return fPolycone->GetDphi()*RootGM::Units::Angle();
}  

//_____________________________________________________________________________
int RootGM::Polycone::NofZPlanes() const
{
  return fPolycone->GetNz();
}  

//_____________________________________________________________________________
double* RootGM::Polycone::ZValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgZBuffer[i] = fPolycone->GetZ(i) * RootGM::Units::Length();

  return fgZBuffer;
}  

//_____________________________________________________________________________
double* RootGM::Polycone::InnerRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgRinBuffer[i] = fPolycone->GetRmin(i) * RootGM::Units::Length();

  return fgRinBuffer;
}  

//_____________________________________________________________________________
double* RootGM::Polycone::OuterRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgRoutBuffer[i] = fPolycone->GetRmax(i) * RootGM::Units::Length();

  return fgRoutBuffer;
}  
