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
// Class Polyhedra
// ------------------
// VGM implementation for Root polyhedra solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Polyhedra.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoPgon.h"

#include <iostream>
#include <math.h>

const int RootGM::Polyhedra::fgkMaxNofZPlanes = 50;
double*   RootGM::Polyhedra::fgZBuffer = 0;
double*   RootGM::Polyhedra::fgRinBuffer = 0;
double*   RootGM::Polyhedra::fgRoutBuffer = 0;

//_____________________________________________________________________________
RootGM::Polyhedra::Polyhedra(
                       const std::string& name, 
                       double sphi, double dphi, 
		       int nofSides, int nofZPlanes,
                       double* z, double* rin, double* rout)
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra(),
    fPolyhedra(0)
{
/// Standard constructor to define polyhedra from parameters
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg
/// \param nofSides number of sides of the cross section
///	   between the given phi limits
/// \param nofZplanes number of planes perpendicular to the
///	   z axis (has to be >= 2)
/// \param z  array of z positions of the planes in mm 
/// \param rin array of inside radius of the planes in mm 
/// \param rout array of outside radius of the planes in mm 
// 
  double* param = new double[4+3*nofZPlanes]; 
          // number of parameters: sphi, dphi, nz + 3*nofZPlanes
 
  param[0] = sphi/RootGM::Units::Angle();
  param[1] = dphi/RootGM::Units::Angle();
  param[2] = nofSides;
  param[3] = nofZPlanes;
  
  for (int i=0; i<nofZPlanes; i++) {
    int j = 4 + 3*i; 
    param[j]   = z[i]   / RootGM::Units::Length();
    param[j+1] = rin[i] / RootGM::Units::Length();
    param[j+2] = rout[i]/ RootGM::Units::Length();
  }

  fPolyhedra = new TGeoPgon(param);
  fPolyhedra->SetName(name.data());
  
  RootGM::SolidMap::Instance()->AddSolid(this, fPolyhedra); 
  CreateBuffers();

  delete [] param;
}


//_____________________________________________________________________________
RootGM::Polyhedra::Polyhedra(TGeoPgon* polyhedra)
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra(),
    fPolyhedra(polyhedra)
{    
/// Standard constructor to define polyhedra from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fPolyhedra); 
  CreateBuffers();
}

//_____________________________________________________________________________
RootGM::Polyhedra::Polyhedra() 
  : VGM::ISolid(),
    VGM::IPolyhedra(),
    BaseVGM::VPolyhedra() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Polyhedra::Polyhedra(const Polyhedra& rhs) 
  : VGM::ISolid(rhs),
    VGM::IPolyhedra(rhs),
    BaseVGM::VPolyhedra(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Polyhedra::~Polyhedra() {
//
}    

//_____________________________________________________________________________
void  RootGM::Polyhedra::CreateBuffers()
{
  if (!fgZBuffer)    fgZBuffer    = new double [fgkMaxNofZPlanes];
  if (!fgRinBuffer)  fgRinBuffer  = new double [fgkMaxNofZPlanes];
  if (!fgRoutBuffer) fgRoutBuffer = new double [fgkMaxNofZPlanes];
}

//_____________________________________________________________________________
std::string RootGM::Polyhedra::Name() const
{
  return fPolyhedra->GetName();
}  
  
//_____________________________________________________________________________
double RootGM::Polyhedra::StartPhi() const
{
  return fPolyhedra->GetPhi1()*RootGM::Units::Angle();
}  

//_____________________________________________________________________________
double RootGM::Polyhedra::DeltaPhi() const
{
  return fPolyhedra->GetDphi()*RootGM::Units::Angle();
}  

//_____________________________________________________________________________
int RootGM::Polyhedra::NofSides() const
{
  return fPolyhedra->GetNedges();
}  

//_____________________________________________________________________________
int RootGM::Polyhedra::NofZPlanes() const
{
  return fPolyhedra->GetNz();
}  

//_____________________________________________________________________________
double* RootGM::Polyhedra::ZValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgZBuffer[i] = fPolyhedra->GetZ(i) * RootGM::Units::Length();

  return fgZBuffer;
}  

//_____________________________________________________________________________
double* RootGM::Polyhedra::InnerRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgRinBuffer[i] = fPolyhedra->GetRmin(i) * RootGM::Units::Length();

  return fgRinBuffer;
}  

//_____________________________________________________________________________
double* RootGM::Polyhedra::OuterRadiusValues() const
{
  int nofZPlanes = NofZPlanes();
  if (nofZPlanes > fgkMaxNofZPlanes) {
    nofZPlanes = fgkMaxNofZPlanes;
    std::cerr << "+++ Warning  +++" << std::endl; 
    std::cerr << "    Number of Zplanes > size of buffer." << std::endl;
    std::cerr << "    only " << nofZPlanes << " values are returned." << std::endl;
  }  

  for (int i=0; i<nofZPlanes; i++)
    fgRoutBuffer[i] = fPolyhedra->GetRmax(i) * RootGM::Units::Length();

  return fgRoutBuffer;
}  
