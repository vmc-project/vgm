// $Id$
//
// Class Placement
// -------------------
// The interface to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "TGeoManager.h"
#include "TGeoMatrix.h"
#include "TGeoVolume.h"
#include "TGeoCompositeShape.h"
#include "TGeoBoolNode.h"

#include "BaseVGM/common/utilities.h"

#include "RootGM/volumes/Placement.h"
#include "RootGM/volumes/VolumeMap.h"
#include "RootGM/volumes/PlacementMap.h"
#include "RootGM/common/Units.h"
#include "RootGM/common/transform.h"
#include "RootGM/common/axis.h"

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
    fAssemblyNodes()
{
/// Standard constructor to define a simple placement via parameters
/// \param copyNo the copy number of this placement
/// \param volume the associated volume
/// \param motherVolume the associated mother volume
/// \param transformation the 3D transformation of the volume 
///	   with respect to its mother
  
  if (!motherVolume) {

    // Top volume is not placed in TGeo
    fGeoNode = 0;
    
    // Set top volume to TGeo
    gGeoManager
      ->SetTopVolume(RootGM::VolumeMap::Instance()->GetVolume(volume));
  }  
  else {  

    // Get TGeo volumes from the volumes map
    TGeoVolume* geoVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(volume);
    
    TGeoVolume* geoMotherVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(motherVolume);

    // Create TGeo node
    geoMotherVolume->AddNode(geoVolume, copyNo, transformation);
  
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
    fAssemblyNodes()
{
/// Standard constructor to define a multiple placement via parameters
/// \param volume the associated volume which will be replicated
/// \param motherVolume the associated mother volume
/// \param axis the replication axis
/// \param nofItems number of replications
/// \param with the replication width (the unit depends on the axis;
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
    fAssemblyNodes()
{
/// Standard constructor to define a multiple placement via Root object

  if (volume) fName = volume->Name();
      // Root nodes have not own name; 
      // use the volume name in this case 

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
    fAssemblyNodes(assemblyNodes)
{
/// Standard constructor to define a multiple placement via Root object

  if (volume) fName = volume->Name();
      // Root nodes have not own name; 
      // use the volume name in this case 

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
// public functions
//

//_____________________________________________________________________________
VGM::PlacementType RootGM::Placement::Type() const 
{
  // Check if division is present
  const TGeoPatternFinder* finder 
    = fGeoNode->GetMotherVolume()->GetFinder();    
  if (!finder) return VGM::kSimplePlacement;;
    
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
  return fName;
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