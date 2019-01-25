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
// Class ExtrudedSolid
// --------------------
// VGM implementation for Root ExtrudedSolid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/ExtrudedSolid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoXtru.h"

#include <iostream>
#include <math.h>
#include <cstdlib>

//_____________________________________________________________________________
RootGM::ExtrudedSolid::ExtrudedSolid(const std::string& name,
                               std::vector<VGM::TwoVector> polygon,
                               std::vector< std::vector<double> > zsections)
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(),
    fXtru(0)
{
/// Standard constructor to define ExtrudedSolid from parameters
/// \param polygon the outline polygon
/// \param zsections the z-sections defined by
///        z positions, polygon offset in x, y and scale

  if ( zsections.size() < 2 ) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Number of z-sections = " << zsections.size()
              << " has to be >= 2" << std::endl;
    exit(1);
  }

  fXtru = new TGeoXtru(zsections.size());
  fXtru->SetName(name.data());

  // set polygon
  Int_t   nv = polygon.size();
  double* xv = new double[nv];
  double* yv = new double[nv];
  for (unsigned int i=0; i<polygon.size(); ++i ) {
    xv[i] = polygon[i].first  / RootGM::Units::Length();
    yv[i] = polygon[i].second / RootGM::Units::Length();
  }
  fXtru->DefinePolygon(nv, xv, yv);

  // set z-sections
  for (unsigned int i=0; i<zsections.size(); ++i ) {
    fXtru->DefineSection(i,
                 zsections[i][0]/ RootGM::Units::Length(),
                 zsections[i][1]/ RootGM::Units::Length(),
                 zsections[i][2]/ RootGM::Units::Length(),
                 zsections[i][3]);
  }

  RootGM::SolidMap::Instance()->AddSolid(this, fXtru);

  delete [] xv;
  delete [] yv;
}


//_____________________________________________________________________________
RootGM::ExtrudedSolid::ExtrudedSolid(TGeoXtru* xtru)
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(),
    fXtru(xtru)
{
/// Standard constructor to define ExtrudedSolid from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fXtru);
}

//_____________________________________________________________________________
RootGM::ExtrudedSolid::ExtrudedSolid()
  : VGM::ISolid(),
    VGM::IExtrudedSolid(),
    BaseVGM::VExtrudedSolid(),
    fXtru(0)
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::ExtrudedSolid::ExtrudedSolid(const ExtrudedSolid& rhs)
  : VGM::ISolid(rhs),
    VGM::IExtrudedSolid(rhs),
    BaseVGM::VExtrudedSolid(rhs),
    fXtru(0)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::ExtrudedSolid::~ExtrudedSolid()
{
//
}

/*
//_____________________________________________________________________________
void  RootGM::ExtrudedSolid::AddZPlane(double zpos,
                                       VGM::TwoVector offset, double scale)
{
  if ( !fXtru ) {
    // add error
    return;
  }

  if ( fNofZSections == NofZSections() ) {
    // add error
    return;
  }

  Double_t z  = zpos          / RootGM::Units::Length();
  Double_t x0 = offset.first  / RootGM::Units::Length();
  Double_t y0 = offset.second / RootGM::Units::Length();

  fXtru->DefineSection(fNofZSections++, z, x0, y0, scale);
}
*/

//_____________________________________________________________________________
std::string RootGM::ExtrudedSolid::Name() const
{
  return fXtru->GetName();
}

//_____________________________________________________________________________
int RootGM::ExtrudedSolid::NofVertices() const
{
  return fXtru->GetNvert();
}

//_____________________________________________________________________________
VGM::TwoVector  RootGM::ExtrudedSolid::Vertex(int index) const
{
  if ( index < 0 || index > NofVertices() ) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong vertex index: " << index << std::endl;
    exit(1);
  }

  return VGM::TwoVector(
           fXtru->GetX(index) * RootGM::Units::Length(),
           fXtru->GetY(index) * RootGM::Units::Length());
}

//_____________________________________________________________________________
int RootGM::ExtrudedSolid::NofZSections() const
{
  return fXtru->GetNz();
}

//_____________________________________________________________________________
double RootGM::ExtrudedSolid::ZPosition(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }

  return fXtru->GetZ(iz) * RootGM::Units::Length();
}

//_____________________________________________________________________________
VGM::TwoVector RootGM::ExtrudedSolid::Offset(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }

  return VGM::TwoVector(fXtru->GetXOffset(iz) * RootGM::Units::Length(),
                        fXtru->GetYOffset(iz) * RootGM::Units::Length());
}

//_____________________________________________________________________________
double RootGM::ExtrudedSolid::Scale(int iz) const
{
  if ( iz < 0 || iz > NofZSections() ) {
    std::cerr << "+++ Error  +++" << std::endl;
    std::cerr << "    Wrong index: " << iz << std::endl;
    exit(1);
  }

  return fXtru->GetScale(iz);
}
