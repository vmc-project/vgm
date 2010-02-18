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
// Class Arb8
// --------------------
// VGM implementation for Root Arb8 solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/Arb8.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/Units.h"

#include "TGeoArb8.h"
#include "TMath.h"

#include <iostream>
#include <math.h>
#include <cstdlib>

const int RootGM::Arb8::Arb8::fgkNofVertices = 8;

//_____________________________________________________________________________
RootGM::Arb8::Arb8(const std::string& name, 
                             double hz,
                             std::vector<VGM::TwoVector> vertices)
  : VGM::ISolid(),
    VGM::IArb8(),
    BaseVGM::VArb8(),
    fArb8(0)
{
/// Standard constructor to define Arb8 from parameters
/// \param hz half-length along the z axis in mm
/// \param vertices vector of (x,y) coordinates of vertices
/// - first four points are the (x,y) 
///   coordinates of the vertices sitting on the -dz plane;
/// - last four points are the (x,y) 
///   coordinates of the vertices sitting on the +dz plane;
///
/// The order of defining the vertices of an arb8 is the following:
/// - point 0 is connected with points 1,3,4
/// - point 1 is connected with points 0,2,5
/// - point 2 is connected with points 1,3,6
/// - point 3 is connected with points 0,2,7
/// - point 4 is connected with points 0,5,7
/// - point 5 is connected with points 1,4,6
/// - point 6 is connected with points 2,5,7
/// - point 7 is connected with points 3,4,6
///
/// Points can be identical in order to create shapes with less than 
/// vertices.

  fArb8 = new TGeoArb8(hz / RootGM::Units::Length());
  fArb8->SetName(name.c_str());

  // set vertices
  for (unsigned int i=0; i<vertices.size(); ++i ) {
    fArb8->SetVertex( i, 
                      vertices[i].first  / RootGM::Units::Length(),
                      vertices[i].second / RootGM::Units::Length());
  }  

  RootGM::SolidMap::Instance()->AddSolid(this, fArb8); 
}


//_____________________________________________________________________________
RootGM::Arb8::Arb8(TGeoArb8* arb8)
  : VGM::ISolid(),
    VGM::IArb8(),
    BaseVGM::VArb8(),
    fArb8(arb8)
{    
/// Standard constructor to define Arb8 from Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fArb8); 
}

//_____________________________________________________________________________
RootGM::Arb8::Arb8() 
  : VGM::ISolid(),
    VGM::IArb8(),
    BaseVGM::VArb8(),
    fArb8(0)
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Arb8::Arb8(const Arb8& rhs) 
  : VGM::ISolid(rhs),
    VGM::IArb8(rhs),
    BaseVGM::VArb8(rhs), 
    fArb8(0)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::Arb8::~Arb8() 
{
//
}    

//_____________________________________________________________________________
std::string RootGM::Arb8::Name() const
{
  return fArb8->GetName();
}  
  
//_____________________________________________________________________________
int RootGM::Arb8::NofVertices() const
{
  return fgkNofVertices;
}  

//_____________________________________________________________________________
VGM::TwoVector  RootGM::Arb8::Vertex(int index) const
{
  if ( index < 0 || index >= fgkNofVertices ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong vertex index: " << index << std::endl;
    exit(1);
  }  
  
  Double_t* xy = fArb8->GetVertices();
/*
  for ( int i=0; i< 2*fgkNofVertices; i++ )
    std::cout << xy[i]  <<  ", ";
  std::cout << std::endl;  
*/ 
  // CHECK !!!
  return VGM::TwoVector(
                 xy[2*index] * RootGM::Units::Length(),
                 xy[2*index+1] * RootGM::Units::Length());
}           

//_____________________________________________________________________________
double  RootGM::Arb8::TwistAngle(int index) const
{
  if ( index < 0 || index >= 4  ) {
    std::cerr << "+++ Error  +++" << std::endl; 
    std::cerr << "    Wrong twist angle index: " << index << std::endl;
    exit(1);
  }  
  
  Double_t twistAngle 
    = TMath::ATan(fArb8->GetTwist(index)) * TMath::RadToDeg();

  return  twistAngle * RootGM::Units::Angle();
}           

//_____________________________________________________________________________
double RootGM::Arb8::ZHalfLength() const
{
  return fArb8->GetDZ() * RootGM::Units::Length(); 
}  
