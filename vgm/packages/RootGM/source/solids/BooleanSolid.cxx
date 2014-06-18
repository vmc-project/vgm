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
// Class BooleanSolid
// ---------------------
// VGM implementation for Root Boolean solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/solids/IDisplacedSolid.h"
#include "BaseVGM/common/utilities.h"

#include "RootGM/solids/BooleanSolid.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/common/transform.h"

#include "TGeoCompositeShape.h"
#include "TGeoBoolNode.h"
#include "TGeoMatrix.h"

#include <cstdlib>

const char RootGM::BooleanSolid::fgkIntersectionChar = '*'; 
const char RootGM::BooleanSolid::fgkSubtractionChar = '-'; 
const char RootGM::BooleanSolid::fgkUnionChar = '+'; 
const char RootGM::BooleanSolid::fgkSeparator = ':'; 

//_____________________________________________________________________________
RootGM::BooleanSolid::BooleanSolid(
                             const std::string& name, 
                             VGM::BooleanType boolType,
                             VGM::ISolid* solidA, VGM::ISolid* solidB,
			     TGeoMatrix* displacementB) 
  : VGM::ISolid(),
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid(),
    fCompositeShape(0) 
{
/// Standard constructor to define Boolean solids via constituents
/// \param boolType type of Boolean operation (kIntersection, kSubtraction,
///        kUnion)
/// \param solidA, solidB constituent solids
/// \param displacementB the Root 3D transformation that defines the
///        displacement of the solidB with respect to solidA

  // Get solid displacement, if present, and update transformation
  // which will be used in Root node
  //  
  TGeoHMatrix matrixA;
  VGM::ISolid* constSolidA = solidA;
  if ( constSolidA->Type() == VGM::kDisplaced ) { 
    VGM::IDisplacedSolid* displacedSolid
      = dynamic_cast<VGM::IDisplacedSolid*>(constSolidA);
    TGeoHMatrix displacement(*RootGM::CreateTransform(displacedSolid->Displacement()));   
    matrixA = matrixA * displacement;    
    constSolidA = displacedSolid->ConstituentSolid();
  } 

  TGeoHMatrix matrixB;
  VGM::ISolid* constSolidB = solidB;
  if ( constSolidB->Type() == VGM::kDisplaced ) { 
    VGM::IDisplacedSolid* displacedSolid
      = dynamic_cast<VGM::IDisplacedSolid*>(constSolidB);
    TGeoHMatrix displacement(*RootGM::CreateTransform(displacedSolid->Displacement()));   
    matrixB = matrixB * displacement;    
    constSolidB = displacedSolid->ConstituentSolid();
  }  

  // Get solids from the volumes map
  TGeoShape* rootSolidA = RootGM::SolidMap::Instance()->GetSolid(constSolidA);
  TGeoShape* rootSolidB = RootGM::SolidMap::Instance()->GetSolid(constSolidB);

  // Create new TGeo matrices
  TGeoMatrix* newMatrixA = 0;
  if ( ! matrixA.IsIdentity() )  
    newMatrixA = new TGeoHMatrix(matrixA);

  TGeoMatrix* newMatrixB = displacementB;
  if ( ! matrixB.IsIdentity() )  
    newMatrixB = new TGeoHMatrix(TGeoHMatrix(*displacementB) * matrixB);
 
  TGeoBoolNode* boolNode = 0;
  switch (boolType) {
    case VGM::kIntersection:  
      boolNode = new TGeoIntersection(rootSolidA, rootSolidB, newMatrixA, newMatrixB); 
      break;					 
    case VGM::kSubtraction:
      boolNode = new TGeoSubtraction(rootSolidA, rootSolidB, newMatrixA, newMatrixB); 
      break;
    case VGM::kUnion:         
      boolNode = new TGeoUnion(rootSolidA, rootSolidB, newMatrixA, newMatrixB); 
      break;
    case VGM::kUnknownBoolean:
    default:
      std::cerr << "    RootGM::BooleanSolid::BooleanSolid: "<< std::endl;
      std::cerr << "    Unknown Boolean solid type" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
  }  
  
  fCompositeShape = new TGeoCompositeShape(name.data(), boolNode);

  RootGM::SolidMap::Instance()->AddSolid(this, fCompositeShape); 
}

//_____________________________________________________________________________
RootGM::BooleanSolid::BooleanSolid(TGeoCompositeShape* compositeShape)
  : VGM::ISolid(),
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid(),
    fCompositeShape(compositeShape) 
{
/// Standard constructor to define Boolean solid via Root object 

  RootGM::SolidMap::Instance()->AddSolid(this, fCompositeShape); 
}


//_____________________________________________________________________________
RootGM::BooleanSolid::BooleanSolid() 
  : VGM::ISolid(),
    VGM::IBooleanSolid(),
    BaseVGM::VBooleanSolid() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::BooleanSolid::BooleanSolid(const BooleanSolid& rhs) 
  : VGM::ISolid(rhs),
    VGM::IBooleanSolid(rhs),
    BaseVGM::VBooleanSolid(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::BooleanSolid::~BooleanSolid() {
//
}

// 
// public methods
//

//_____________________________________________________________________________
std::string 
RootGM::BooleanSolid::Name() const
{
// Returns the Boolean solid name
// ---

  return fCompositeShape->GetName();
}  

//_____________________________________________________________________________
VGM::BooleanType 
RootGM::BooleanSolid::BoolType() const
{
// Returns the Boolean solid type name
// ---

  TGeoBoolNode* boolNode = fCompositeShape->GetBoolNode();

  if (boolNode->GetBooleanOperator() == TGeoBoolNode::kGeoIntersection) 
    return VGM::kIntersection;

  if (boolNode->GetBooleanOperator() == TGeoBoolNode::kGeoSubtraction) 
    return VGM::kSubtraction;

  if (boolNode->GetBooleanOperator() == TGeoBoolNode::kGeoUnion) 
    return VGM::kUnion;
    
  return VGM::kUnknownBoolean;
}    

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::BooleanSolid::ConstituentSolidA() const
{
// Returns the first constituent solid.
// ---

  TGeoBoolNode* boolNode = fCompositeShape->GetBoolNode();

  TGeoShape* rootSolidA = boolNode->GetLeftShape();
  VGM::ISolid* solidA = RootGM::SolidMap::Instance()->GetSolid(rootSolidA);
 
  return solidA;
} 

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::BooleanSolid::ConstituentSolidB() const
{
// Returns the second constituent solid.
// ---

  TGeoBoolNode* boolNode = fCompositeShape->GetBoolNode();

  TGeoShape* rootSolidB = boolNode->GetRightShape();
  VGM::ISolid* solidB = RootGM::SolidMap::Instance()->GetSolid(rootSolidB);
 
  return solidB;
} 

//_____________________________________________________________________________
VGM::Transform  
RootGM::BooleanSolid::Displacement() const
{
// Returns the solid displacemnt transformation
// in the frame of the first (left) solid.
// ---

  TGeoBoolNode* boolNode = fCompositeShape->GetBoolNode();
  
  TGeoMatrix* matrixA = boolNode->GetLeftMatrix();
  TGeoMatrix* matrixB = boolNode->GetRightMatrix();
  
  TGeoHMatrix transformA(*matrixA);
  TGeoHMatrix transformB(*matrixB);

  // If constituents are composite shapes,
  // the displacement have to take into account the transformation
  // of left constituent not passed to the solid

  TGeoHMatrix totalTransformA(transformA);
  TGeoShape* shapeA = boolNode->GetLeftShape();

  // Take into account shifted origin
  // totalTransformA = totalTransformA * RootGM::Displacement(shapeA);
  
  while (shapeA->IsComposite()) { 
      
     TGeoBoolNode* boolNodeAC 
       = ((TGeoCompositeShape*)shapeA)->GetBoolNode();
      
     TGeoShape* shapeAC = boolNodeAC->GetLeftShape();
          // left component of the shape A 

     TGeoMatrix* matrixAC = boolNodeAC->GetLeftMatrix();
     TGeoHMatrix transformAC(*matrixAC);
    
     totalTransformA = totalTransformA * transformAC;
     
     // Take into account shifted origin
     // totalTransformA = totalTransformA * RootGM::Displacement(shapeAC);

     shapeA = shapeAC;
  }
  
  TGeoHMatrix totalTransformB(transformB);
  TGeoShape* shapeB = boolNode->GetRightShape();
  // Take into account shifted origin
  //totalTransformB = totalTransformB * RootGM::Displacement(shapeB);
  
  while (shapeB->IsComposite()) { 
      
     TGeoBoolNode* boolNodeBC 
       = ((TGeoCompositeShape*)shapeB)->GetBoolNode();
      
     TGeoShape* shapeBC = boolNodeBC->GetLeftShape();
          // left component of the shape B 

     TGeoMatrix* matrixBC = boolNodeBC->GetLeftMatrix();
     TGeoHMatrix transformBC(*matrixBC);
    
     totalTransformB = totalTransformB * transformBC;
     
     // Take into account shifted origin
     // totalTransformB = totalTransformB * RootGM::Displacement(shapeBC);

     shapeB = shapeBC;
  }
  
  return Transform(totalTransformA.Inverse() * totalTransformB);
}  

//_____________________________________________________________________________
TGeoShape* 
RootGM::BooleanSolid::GetConstituentSolid(
                               int index, 
                               TGeoCompositeShape* compositeShape)
{
/// Return the constituent shape specified by index

  TGeoBoolNode* boolNode = compositeShape->GetBoolNode();

  if (index == 0)
    return boolNode->GetLeftShape();
  else if (index == 1)
    return boolNode->GetRightShape();
  else  {  
    std::cerr << "    RootGM::BooleanSolid::GetConstituentSolid: " << std::endl;
    std::cerr << "    Index out of scope <0, 1>" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1); 
  }   
}			       
			       

