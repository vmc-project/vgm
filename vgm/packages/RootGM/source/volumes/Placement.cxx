// $Id$
//
// Class Placement
// -------------------
// The interface to positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "CLHEP/Units/SystemOfUnits.h"

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
                      const std::string& name, int copyNo,
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
                      HepRotation* rotation, 
		      const Hep3Vector& translation)
  : BaseVGM::VPlacement(volume, motherVolume),
    fGeoNode(0),
    fName(name)       
{
  // Create TGeo matrix
  TGeoMatrix* geoMatrix = RootGM::Convert(rotation, translation);

  // Create TGeo node
  CreateNode(copyNo, volume, motherVolume, geoMatrix);  
}  

//_____________________________________________________________________________
RootGM::Placement::Placement(
                      const std::string& name, int copyNo,
                      VGM::IVolume* volume, VGM::IVolume* motherVolume,
                      const HepTransform3D& transformation)
  : BaseVGM::VPlacement(volume, motherVolume),
    fGeoNode(0),
    fName(name)       
{
  
  // Create TGeo matrix
  TGeoMatrix* geoMatrix = RootGM::Convert(transformation);
  
  // Create TGeo node
  CreateNode(copyNo, volume, motherVolume, geoMatrix);  
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
  Int_t iAxis = RootGM::GetAxis(axis);
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
void RootGM::Placement::CreateNode(
                              int copyNo,
                              VGM::IVolume* volume, VGM::IVolume* motherVolume, 
			      TGeoMatrix* matrix)
{	
  if (!motherVolume) {

    // Top volume is not placed in TGeo
    fGeoNode = 0;
    
    // Set top volume to TGeo
    gGeoManager->SetTopVolume(RootGM::VolumeMap::Instance()->GetVolume(volume));
  }  
  else {  

    // Get TGeo volumes from the volumes map
    TGeoVolume* geoVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(volume);
    
    TGeoVolume* geoMotherVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(motherVolume);

    // Create TGeo node
    geoMotherVolume->AddNode(geoVolume, copyNo, matrix);
  
    // Retrieve the node created
    fGeoNode = geoMotherVolume->GetNode(geoMotherVolume->GetNdaughters()-1);
  }

  // Register physical volume in the map
  RootGM::PlacementMap::Instance()->AddPlacement(this, fGeoNode); 
}
  
//_____________________________________________________________________________
HepTransform3D RootGM::Placement::ObjectTransform3D() const
{
// Returns the object transfomation.
// ---

  HepTransform3D transform3D;
  if (fGeoNode->GetVolume()->GetShape()->IsComposite()) 
  {
    TGeoCompositeShape* composite 
      = (TGeoCompositeShape*)fGeoNode->GetVolume()->GetShape();
    TGeoMatrix* leftMatrix = composite->GetBoolNode()->GetLeftMatrix();    
   
    HepTransform3D t1 = RootGM::Convert(leftMatrix);  
    HepTransform3D t2 = RootGM::Convert(fGeoNode->GetMatrix());
   
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
      HepTransform3D transformAC = RootGM::Convert(matrixAC);
    
      transform3D = transform3D * transformAC;
     
      shapeA = shapeAC;
    }
  }  
  else {
    transform3D = RootGM::Convert(fGeoNode->GetMatrix());
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
  VGM::Axis axis = RootGM::GetAxis(finder);
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
HepRotation RootGM::Placement::ObjectRotation() const
{
//
/*
  return RootGM::GetRotation(fGeoNode->GetMatrix());
*/
/*
  // If Boolean shape, take into account eventuel 
  // displacement of the left constituent
  if (fGeoNode->GetVolume()->GetShape()->IsComposite()) {
    TGeoCompositeShape* composite 
      = (TGeoCompositeShape*)fGeoNode->GetVolume()->GetShape();
    TGeoMatrix* leftMatrix = composite->GetBoolNode()->GetLeftMatrix();    
   
    HepTransform3D t1 = RootGM::Convert(leftMatrix);  
    HepTransform3D t2 = RootGM::Convert(fGeoNode->GetMatrix());
   
    HepTransform3D composed = t2 * t1;

    HepScale3D     scale3D;
    HepRotate3D    rotate3D;
    HepTranslate3D translate3D;
    composed.getDecomposition(scale3D, rotate3D, translate3D);
   
    return rotate3D.getRotation();
  }
  else   
   return RootGM::GetRotation(fGeoNode->GetMatrix());
*/
  return BaseVGM::GetRotation(ObjectTransform3D());
}  
    
//_____________________________________________________________________________
Hep3Vector  RootGM::Placement::ObjectTranslation() const 
{
//
/*
  // If Boolean shape, take into account eventuel 
  // displacement of the left constituent
  if (fGeoNode->GetVolume()->GetShape()->IsComposite()) {
    TGeoCompositeShape* composite 
      = (TGeoCompositeShape*)fGeoNode->GetVolume()->GetShape();
    TGeoMatrix* leftMatrix = composite->GetBoolNode()->GetLeftMatrix();    
   
    HepTransform3D t1 = RootGM::Convert(leftMatrix);  
    HepTransform3D t2 = RootGM::Convert(fGeoNode->GetMatrix());
   
    HepTransform3D composed = t2 * t1;

    HepScale3D     scale3D;
    HepRotate3D    rotate3D;
    HepTranslate3D translate3D;
    composed.getDecomposition(scale3D, rotate3D, translate3D);

    return translate3D.getTranslation();
  }
  else
   return  RootGM::GetTranslation(fGeoNode->GetMatrix()); 
*/
  return BaseVGM::GetTranslation( ObjectTransform3D());
}

//_____________________________________________________________________________
bool RootGM::Placement::ReflectionZ() const
{
//
  return RootGM::HasReflection(fGeoNode->GetMatrix()); 
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
  axis = RootGM::GetAxis(finder);
  nofItems = finder->GetNdiv();
  Double_t start = finder->GetStart();
  Double_t xlo, xhi;
  fGeoNode->GetMotherVolume()->GetShape()
    ->GetAxisRange(RootGM::GetAxis(axis), xlo, xhi);
  offset = start - xlo;
  width  = finder->GetStep();

  // Convert units
  offset *= RootGM::Units::AxisUnit(axis);
  width  *= RootGM::Units::AxisUnit(axis);

  return true;  
}
