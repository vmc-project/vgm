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
#include "RootGM/common/utilities.h"

//_____________________________________________________________________________
RootGM::Placement::Placement(
                      const std::string& name, 
		      int copyNo,
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
		      TGeoMatrix* transformation)
  : BaseVGM::VPlacement(volume, motherVolume),
    fGeoNode(0),
    fName(name)       
{
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
  : BaseVGM::VPlacement(volume, motherVolume),
    fGeoNode(0),
    fName(name) 
{
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
  : BaseVGM::VPlacement(volume, motherVolume),
    fGeoNode(node),
    fName()       
{
  if (volume) fName = volume->Name();
      // Root nodes have not own name; 
      // use the volume name in this case 

  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}

//_____________________________________________________________________________
RootGM::Placement::~Placement() {
//
}

//
// private functions
//

//_____________________________________________________________________________
TGeoHMatrix RootGM::Placement::ObjectTransform() const
{
// Returns the object transfomation.
// ---

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
  
  return transform3D;  
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
VGM::Rotation RootGM::Placement::ObjectRotation() const
{
//
  return Rotation(ObjectTransform());
}  
    
//_____________________________________________________________________________
VGM::Rotation RootGM::Placement::FrameRotation() const
{
//
  return Rotation(ObjectTransform().Inverse());
}  
    
//_____________________________________________________________________________
VGM::ThreeVector  RootGM::Placement::ObjectTranslation() const 
{
//
  return Translation(ObjectTransform());
}

//_____________________________________________________________________________
VGM::ThreeVector  RootGM::Placement::FrameTranslation() const 
{
//
  
  VGM::ThreeVector objTranslation = ObjectTranslation();
  for (Int_t i=0; i<3; i++) objTranslation[i] = - objTranslation[i];
   
  return objTranslation;
}

//_____________________________________________________________________________
bool RootGM::Placement::ReflectionZ() const
{
//
  return HasReflection(ObjectTransform()); 
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
