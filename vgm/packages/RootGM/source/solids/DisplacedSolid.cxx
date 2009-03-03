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
// Class DisplacedSolid
// ---------------------
// VGM implementation for Root displaced solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"

#include "RootGM/solids/DisplacedSolid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/solids/Box.h"
#include "RootGM/common/transform.h"

#include "TGeoCompositeShape.h"
#include "TGeoBoolNode.h"
#include "TGeoBBox.h"
#include "TGeoMatrix.h"
#include "TString.h"

#include <cstdlib>

const std::string RootGM::DisplacedSolid::fgkNameExtension = "_displ"; 

//_____________________________________________________________________________
RootGM::DisplacedSolid::DisplacedSolid(
                             const std::string& name, 
                             VGM::ISolid* solid,
			     TGeoMatrix* displacement) 
  : VGM::ISolid(),
    VGM::IDisplacedSolid(),
    BaseVGM::VDisplacedSolid(),
    fCompositeShape(0),
    fConstituentSolid(solid) 
{
/// Standard constructor to define Displaced solids via constituents
/// \param boolType type of Displaced operation (kIntersection, kSubtraction,
///        kUnion)
/// \param solid constituent solids
/// \param displacement the Root 3D transformation that defines the
///        displacement of the solid

  // Get solid from the solid map
  TGeoShape* rootSolid = RootGM::SolidMap::Instance()->GetSolid(solid);

  // Define new name
  // std::string newName = name + fgkNameExtension;  // ??
  std::string newName = name; 

  // Register TGeo matrix 
  displacement->SetName(newName.data());
  displacement->RegisterYourself();

  TGeoBoolNode* boolNode 
    = new TGeoUnion(rootSolid, rootSolid, displacement, 0); 
  
  fCompositeShape = new TGeoCompositeShape(newName.data(), boolNode);
 
  RootGM::SolidMap::Instance()->AddSolid(this, fCompositeShape); 
}

//_____________________________________________________________________________
RootGM::DisplacedSolid:: DisplacedSolid(TGeoBBox* box)
  : VGM::ISolid(),
    VGM::IDisplacedSolid(),
    BaseVGM::VDisplacedSolid(),
    fCompositeShape(0),
    fConstituentSolid(0) 
{
/// Standard constructor to define Displaced solid via Root object.
/// Only TGeoBBox can include displacement in its definition.
/// If

  // Give exception if box does not include offset
  const Double_t* origin = box->GetOrigin();
  if ( ! origin ) {
    std::cerr << "    RootGM::DisplacedSolid::DisplacedSolid: " << std::endl; 
    std::cerr << "    Cannot create displaced solid from a box without offset." << std::endl; 
    std::cerr << "    (TGeoBBox name = " << box->GetName() << ")" << std::endl; 
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
  
  // Define new name  
  std::string newName = std::string(box->GetName()) + fgkNameExtension ;
  
  // Create VGM box for constituent solid not registered in solid map
  fConstituentSolid = new RootGM::Box(box, false);
  
  // Create and register TGeo matrix
  TGeoMatrix* displacement 
    = new TGeoTranslation(origin[0], origin[1], origin[2]);
  displacement->SetName(newName.data());
  displacement->RegisterYourself();

  TGeoBoolNode* boolNode 
    = new TGeoUnion(box, box, displacement, 0); 
    
  fCompositeShape = new TGeoCompositeShape(newName.data(), boolNode);
 
  RootGM::SolidMap::Instance()->AddSolid(this, fCompositeShape); 
}

//_____________________________________________________________________________
RootGM::DisplacedSolid::DisplacedSolid() 
  : VGM::ISolid(),
    VGM::IDisplacedSolid(),
    BaseVGM::VDisplacedSolid() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::DisplacedSolid::DisplacedSolid(const DisplacedSolid& rhs) 
  : VGM::ISolid(rhs),
    VGM::IDisplacedSolid(rhs),
    BaseVGM::VDisplacedSolid(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::DisplacedSolid::~DisplacedSolid() {
//
}

// 
// public methods
//

//_____________________________________________________________________________
std::string 
RootGM::DisplacedSolid::Name() const
{
// Returns the Displaced solid name
// ---

  return fCompositeShape->GetName();
}  

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::DisplacedSolid::ConstituentSolid() const
{
// Returns the second constituent solid.
// ---

  return fConstituentSolid;
} 

//_____________________________________________________________________________
VGM::Transform  
RootGM::DisplacedSolid::Displacement() const
{
// Returns the solid displacemnt transformation
// in the frame of the first (left) solid.
// ---

  TGeoBoolNode* boolNode = fCompositeShape->GetBoolNode();
  
  TGeoMatrix* matrixB = boolNode->GetLeftMatrix();
  TGeoHMatrix transformB(*matrixB);
  
  return Transform(transformB);
}  
