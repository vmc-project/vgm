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
// Class Placement
// -------------------
// The interface to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/volumes/IVolume.h"
#include "VGM/solids/IDisplacedSolid.h"

#include "BaseVGM/common/utilities.h"

#include "RootGM/volumes/Placement.h"
#include "RootGM/volumes/VolumeMap.h"
#include "RootGM/volumes/PlacementMap.h"
#include "RootGM/common/Units.h"
#include "RootGM/common/transform.h"
#include "RootGM/common/axis.h"

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoVolume.h"
#include "TGeoNode.h"
#include "TGeoCompositeShape.h"
#include "TGeoBoolNode.h"

bool RootGM::Placement::fgIncludeAssembliesInNames = true; 
char RootGM::Placement::fgNameSeparator = '%'; 
char RootGM::Placement::fgNamePrefix = '&'; 

//
// static methods
//

//_____________________________________________________________________________
void RootGM::Placement::SetIncludeAssembliesInNames(bool includeAssembliesInNames)
{
/// Set the option to include assemblies names in the name of
/// placement 

 fgIncludeAssembliesInNames = includeAssembliesInNames;
}  

//_____________________________________________________________________________
bool RootGM::Placement::GetIncludeAssembliesInNames()
{
/// Return the option to include assemblies names in the name of
/// placement 

  return fgIncludeAssembliesInNames;
}  

//_____________________________________________________________________________
void RootGM::Placement::SetNameSeparator(char nameSeparator)
{
/// Set the separator for assemblies names

  fgNameSeparator = nameSeparator;
}  

//_____________________________________________________________________________
void RootGM::Placement::SetNamePrefix(char namePrefix)
{
/// Set the prefix for assemblies names

  fgNamePrefix = namePrefix;
}  

//_____________________________________________________________________________
char RootGM::Placement::GetNameSeparator()
{
/// Return the separator for assemblies names

  return fgNameSeparator;
}  

//_____________________________________________________________________________
char RootGM::Placement::GetNamePrefix()
{
/// Return the prefix for assemblies names

  return fgNamePrefix;
}  

//
// ctors, dtor
//

//_____________________________________________________________________________
RootGM::Placement::Placement(
                      const std::string& name, 
		      int copyNo,
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
		      TGeoMatrix* transformation)
  : VGM::IPlacement(),
    BaseVGM::VPlacement(volume, motherVolume),
    fName(name),       
    fGeoNode(0),
    fVGMMatrix(transformation),
    fAssemblyNodes()
{
/// Standard constructor to define a simple placement via parameters
/// \param copyNo the copy number of this placement
/// \param volume the associated volume
/// \param motherVolume the associated mother volume
/// \param transformation the 3D transformation of the volume 
///	   with respect to its mother
  
  if ( ! motherVolume ) {

    // Set top volume to TGeo
    gGeoManager
      ->SetTopVolume(RootGM::VolumeMap::Instance()->GetVolume(volume));

    // Get top node 
    fGeoNode = gGeoManager->GetTopNode();
  }  
  else {  

    // Get solid displacement, if present, and update transformation
    // which will be used in Root node
    //  
    TGeoMatrix* totalMatrix = transformation;
    if ( volume->Solid()->Type() == VGM::kDisplaced ||
         motherVolume->Solid()->Type() == VGM::kDisplaced) { 

      totalMatrix = ComposeMatrix(volume, motherVolume, transformation);
      totalMatrix->SetName(name.data());
      totalMatrix->RegisterYourself();
    }  

    // Get TGeo volumes from the volumes map
    TGeoVolume* geoVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(volume);
    
    TGeoVolume* geoMotherVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(motherVolume);

    // Create TGeo node
    geoMotherVolume->AddNode(geoVolume, copyNo, totalMatrix);
  
    // Retrieve the node created
    fGeoNode = geoMotherVolume->GetNode(geoMotherVolume->GetNdaughters()-1);
  }

  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}  

//_____________________________________________________________________________
RootGM::Placement::Placement(
                      const std::string& name, 
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
                      VGM::Axis axis, 
		      int nofItems, double  width, double  offset)
  : VGM::IPlacement(),
    BaseVGM::VPlacement(volume, motherVolume),
    fName(name), 
    fGeoNode(0),
    fVGMMatrix(0),
    fAssemblyNodes()
{
/// Standard constructor to define a multiple placement via parameters
/// \param volume the associated volume which will be replicated
/// \param motherVolume the associated mother volume
/// \param axis the replication axis
/// \param nofItems number of replications
/// \param width the replication width (the unit depends on the axis;
///	   can be mm or deg)
///  \param offset the replication offset (the unit depends on the axis;
///	   can be mm or deg)

  // Get TGeo volumes from the volumes map
  TGeoVolume* geoMotherVolume 
    = RootGM::VolumeMap::Instance()->GetVolume(motherVolume);

  // Apply units
  width  /= RootGM::Units::AxisUnit(axis);
  offset /= RootGM::Units::AxisUnit(axis);

 // Convert VGM parameters to TGeo
  Int_t iAxis = RootGM::Axis(axis);
  Double_t xlo, xhi;
  geoMotherVolume->GetShape()->GetAxisRange(iAxis, xlo, xhi);
  Double_t start = xlo + offset;

  // Root division
  geoMotherVolume->Divide(name.data(), iAxis, nofItems, start, width); 

  // Retrieve the node created
  fGeoNode = geoMotherVolume->GetNode(geoMotherVolume->GetNdaughters()-1);

  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}    
          
//_____________________________________________________________________________
RootGM::Placement::Placement(
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
                      TGeoNode* node)
  : VGM::IPlacement(),
    BaseVGM::VPlacement(volume, motherVolume),
    fName(),       
    fGeoNode(node),    
    fVGMMatrix(0),
    fAssemblyNodes()
{
/// Standard constructor to define a multiple placement via Root object

  if (volume) fName = volume->Name();
      // Root nodes have not own name; 
      // use the volume name in this case

  fVGMMatrix = node->GetMatrix();
  
  // print warning if node includes overlaps
  Int_t novlp;
  node->GetOverlaps(novlp);
  if ( novlp ) {
    std::cerr << "*** Warning: node with overlaps ***" << std::endl 
              << "*** Overlaps may not be supported in exported geometry!!! ***" << std::endl
              << "    Volume: " << volume->Name()
              << "  in mother: " << motherVolume->Name()
              << "  (TGeoNode name: " << node->GetName() <<  ")" << std::endl;
  }     
      
  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}

//_____________________________________________________________________________
RootGM::Placement::Placement(
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
                      TGeoNode* node, 
		      std::vector<const TGeoNode*> assemblyNodes)
  : VGM::IPlacement(),
    BaseVGM::VPlacement(volume, motherVolume),
    fName(),       
    fGeoNode(node),
    fVGMMatrix(0),
    fAssemblyNodes(assemblyNodes)
{
/// Standard constructor to define a multiple placement via Root object

  if (volume) fName = volume->Name();
      // Root nodes have not own name; 
      // use the volume name in this case 

  fVGMMatrix = node->GetMatrix();
      
  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}

//_____________________________________________________________________________
RootGM::Placement::Placement() 
  : VGM::IPlacement(),
    BaseVGM::VPlacement() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
RootGM::Placement::Placement(const Placement& rhs) 
  : VGM::IPlacement(rhs),
    BaseVGM::VPlacement(rhs) 
{
/// Protected copy constructor
}      

//_____________________________________________________________________________
RootGM::Placement::~Placement() {
//
}

//
// private functions
//


//_____________________________________________________________________________
TGeoMatrix*
RootGM::Placement::ComposeMatrix(VGM::IVolume* volume, VGM::IVolume* motherVolume,
		                 TGeoMatrix* transformation) const
{
/// Get composed matrix by taking into account solid displacements. 

  TGeoHMatrix motherTransform;
  VGM::ISolid* mConstSolid = motherVolume->Solid();
  while ( mConstSolid->Type() == VGM::kDisplaced ) {
    VGM::IDisplacedSolid* displacedSolid 
      = dynamic_cast<VGM::IDisplacedSolid*>(mConstSolid);
    TGeoHMatrix displacement(*RootGM::CreateTransform(displacedSolid->Displacement()));   
    motherTransform = motherTransform * displacement;

    mConstSolid = displacedSolid->ConstituentSolid();
  }      

  TGeoHMatrix solidTransform;
  VGM::ISolid* constSolid = volume->Solid();
  while ( constSolid->Type() == VGM::kDisplaced ) {
    VGM::IDisplacedSolid* displacedSolid 
      = dynamic_cast<VGM::IDisplacedSolid*>(constSolid);
    TGeoHMatrix displacement(*RootGM::CreateTransform(displacedSolid->Displacement()));   
    solidTransform = solidTransform * displacement;

    constSolid = displacedSolid->ConstituentSolid();
  }      

  TGeoHMatrix totalTransform
    = motherTransform.Inverse() * TGeoHMatrix(*transformation) * solidTransform;

  return new TGeoHMatrix(totalTransform);
}  

//
// public functions
//

//_____________________________________________________________________________
VGM::PlacementType RootGM::Placement::Type() const 
{
  // Top volume has not mother
  if ( ! Mother() ) return VGM::kSimplePlacement;

  // Check if division is present
  const TGeoPatternFinder* finder 
    = fGeoNode->GetMotherVolume()->GetFinder();    
  if (!finder) return VGM::kSimplePlacement;
    
  // Get division axis
  VGM::Axis axis = RootGM::Axis(finder);
  if (axis != VGM::kUnknownAxis) 
    return VGM::kMultiplePlacement;
  else 
    return VGM::kUnknownPlacement;
}  

//_____________________________________________________________________________
std::string  RootGM::Placement::Name() const
{
//
  TString name; 
  if ( fgIncludeAssembliesInNames ) {
    for ( unsigned i=0; i<fAssemblyNodes.size(); i++ ) {
      if ( i == 0 ) name += fgNamePrefix;
      name += fAssemblyNodes[i]->GetName();
      name += fgNameSeparator;
    }  
  }
  name += fName.c_str();
  
  return name.Data();
}  

//_____________________________________________________________________________
int RootGM::Placement::CopyNo() const
{
//
  return fGeoNode->GetNumber();
}  

//_____________________________________________________________________________
VGM::Transform
RootGM::Placement::Transformation() const
{
//
  // Boolean solids
  TGeoHMatrix transform3D;
  if (fGeoNode->GetVolume()->GetShape()->IsComposite()) 
  {
    TGeoCompositeShape* composite 
      = (TGeoCompositeShape*)fGeoNode->GetVolume()->GetShape();
    TGeoMatrix* leftMatrix = composite->GetBoolNode()->GetLeftMatrix();    
   
    TGeoHMatrix t1(*leftMatrix);  
    TGeoHMatrix t2(*(fGeoNode->GetMatrix()));
   
    transform3D = t2 * t1;
 
    // If constituents are composite shapes,
    // the displacement have to take into account the transformation
    // of left constituent not passed to the solid
  
    TGeoShape* shapeA = composite->GetBoolNode()->GetLeftShape();

    while (shapeA->IsComposite()) { 
      TGeoBoolNode* boolNodeAC 
        = ((TGeoCompositeShape*)shapeA)->GetBoolNode();
      
      TGeoShape* shapeAC = boolNodeAC->GetLeftShape();
          // left component of the shape A 

      TGeoMatrix* matrixAC = boolNodeAC->GetLeftMatrix();
      TGeoHMatrix transformAC(*matrixAC);
    
      transform3D = transform3D * transformAC;
     
      shapeA = shapeAC;
    }
  }  
  else {
    transform3D = fGeoNode->GetMatrix();
  }
 
  // Displaced solids
  if ( Volume()->Solid()->Type() == VGM::kDisplaced ||
       ( Mother() && Mother()->Solid()->Type() == VGM::kDisplaced ) ) { 
  
    transform3D = TGeoHMatrix(*fVGMMatrix);
  }   

  // Assemblies
  for (unsigned i=fAssemblyNodes.size(); i>0; i-- ) {
    TGeoMatrix* matrixAN =fAssemblyNodes[i-1]->GetMatrix();
    TGeoHMatrix transformAN(*matrixAN);
    transform3D = transformAN * transform3D;
  }    
  
  return Transform(transform3D);
}  

//_____________________________________________________________________________
bool RootGM::Placement::MultiplePlacementData(
                                VGM::Axis&  axis,
                                int&     nofItems,
                                double&  width,
                                double&  offset) const
{
  // Fill data only if multiple placement
  const TGeoPatternFinder* finder = fGeoNode->GetMotherVolume()->GetFinder();    
  if (!finder) return false;
    
  // Get division parameters
  axis = RootGM::Axis(finder);
  nofItems = finder->GetNdiv();
  Double_t start = finder->GetStart();
  Double_t xlo, xhi;
  fGeoNode->GetMotherVolume()->GetShape()
    ->GetAxisRange(RootGM::Axis(axis), xlo, xhi);
  offset = start - xlo;
  width  = finder->GetStep();

  // Convert units
  offset *= RootGM::Units::AxisUnit(axis);
  width  *= RootGM::Units::AxisUnit(axis);

  return true;  
}
