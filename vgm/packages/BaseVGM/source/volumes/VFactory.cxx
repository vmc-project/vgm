// $Id$
//
// Class VFactory
// ---------------
// The interface to geometry factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/solids/IBooleanSolid.h"
#include "VGM/solids/IBox.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/IPara.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"
#include "VGM/solids/ISphere.h"
#include "VGM/solids/ITorus.h"
#include "VGM/solids/ITrap.h"
#include "VGM/solids/ITrd.h"
#include "VGM/solids/ITubs.h"
#include "VGM/volumes/IPlacement.h"
#include "VGM/volumes/IVolume.h"

#include "BaseVGM/volumes/VFactory.h"
#include "BaseVGM/common/utilities.h"

//_____________________________________________________________________________
BaseVGM::VFactory::VFactory(const std::string& name,
                           VGM::IMaterialFactory* materialFactory)
  : VGM::IFactory(),
    fDebug(0),
    fName(name),
    fSolids(),
    fVolumes(),
    fMaterialFactory(materialFactory)
{
//
}

//_____________________________________________________________________________
BaseVGM::VFactory::~VFactory() 
{
// Deletes all objects created by factory
// ---

  // Delete solids
  for (unsigned int i=0; i<fSolids.size(); i++) {
    delete fSolids[i];
  }  

  // Delete volumes
  for (unsigned int j=0; j<fVolumes.size(); j++) {
    delete fVolumes[j];
  }  
  
  // Placements are deleted together with volumes
  
  // Material factory
  delete fMaterialFactory;
}

//
// private functions
//

//_____________________________________________________________________________
VGM::ISolid*  
BaseVGM::VFactory::ExportBooleanSolid(VGM::IBooleanSolid* solid,
                                     VGM::IFactory* factory) const

{
// Exports specified Boolean solid to given factory
// ---

  // Export constituent solids first
  VGM::ISolid* solidA = ExportSolid(solid->ConstituentSolidA(), factory);
  VGM::ISolid* solidB = ExportSolid(solid->ConstituentSolidB(), factory);
        // Can lead to a duplication of solids in case
	// the solid has been already exported
	// Should not harm, but will be better to be avoided	


  VGM::BooleanType boolType = solid->BoolType();
  VGM::Transform transform =  solid->Displacement();

  VGM::ISolid* newSolid = 0;
  if (boolType == VGM::kIntersection) {
    newSolid = factory->CreateIntersectionSolid(
                               solid->Name(), solidA, solidB,
			       transform);
  }
  else if (boolType == VGM::kSubtraction) { 
    newSolid = factory->CreateSubtractionSolid(
                               solid->Name(), solidA, solidB,
			       transform);
  }
  else if (boolType == VGM::kUnion) { 
    newSolid = factory->CreateUnionSolid(
                               solid->Name(), solidA, solidB,
			       transform);
  }

  if (!newSolid) {
    std::cerr << "    BaseVGM::VFactory::ExportBooleanSolid:" << std::endl;
    std::cerr << "    Unknown Boolean type (solid \"" << solid->Name()
              << "\")" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }	      

  return newSolid;
}  

//_____________________________________________________________________________
VGM::ISolid* 
BaseVGM::VFactory::ExportSolid(VGM::ISolid* solid, 
                              VGM::IFactory* factory) const
{
// Exports specified solid to given factory
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting solid: ";
    if (Debug()>1) std::cout << solid;
    std::cout << std::endl;    
    BaseVGM::DebugInfo();
    std::cout << "   " << *solid << std::endl;
  }	      

  VGM::SolidType solidType = solid->Type();
  if (solidType == VGM::kBox) { 
    VGM::IBox* box = dynamic_cast<VGM::IBox*>(solid); 
    return factory->CreateBox(box->Name(), 
                              box->XHalfLength(), 
			      box->YHalfLength(), 
			      box->ZHalfLength());  
  }
  else if (solidType == VGM::kCons) { 
    VGM::ICons* cons = dynamic_cast<VGM::ICons*>(solid); 
    return factory->CreateCons(cons->Name(), 
                              cons->InnerRadiusMinusZ(),
			      cons->OuterRadiusMinusZ(), 
                              cons->InnerRadiusPlusZ(),
			      cons->OuterRadiusPlusZ(), 
			      cons->ZHalfLength(),  
			      cons->StartPhi(),
			      cons->DeltaPhi());  
  }
  else if (solidType == VGM::kPara) { 
    VGM::IPara* para = dynamic_cast<VGM::IPara*>(solid); 
    return factory->CreatePara(para->Name(), 
                              para->XHalfLength(), 
			      para->YHalfLength(), 
			      para->ZHalfLength(),  
                              para->Alpha(), 
			      para->Theta(), 
			      para->Phi());  
  }
  else if (solidType == VGM::kPolycone) { 
    VGM::IPolycone* polycone = dynamic_cast<VGM::IPolycone*>(solid); 
    return factory->CreatePolycone(polycone->Name(), 
                              polycone->StartPhi(),
                              polycone->DeltaPhi(),
			      polycone->NofZPlanes(),
			      polycone->ZValues(),
			      polycone->InnerRadiusValues(),
			      polycone->OuterRadiusValues());
  }
  else if (solidType == VGM::kPolyhedra) { 
    VGM::IPolyhedra* polyhedra = dynamic_cast<VGM::IPolyhedra*>(solid); 
    return factory->CreatePolyhedra(polyhedra->Name(), 
                              polyhedra->StartPhi(),
                              polyhedra->DeltaPhi(),
                              polyhedra->NofSides(),
			      polyhedra->NofZPlanes(),
			      polyhedra->ZValues(),
			      polyhedra->InnerRadiusValues(),
			      polyhedra->OuterRadiusValues());
  }
  else if (solidType == VGM::kSphere) { 
    VGM::ISphere* sphere = dynamic_cast<VGM::ISphere*>(solid); 
    return factory->CreateSphere(sphere->Name(), 
                              sphere->InnerRadius(),
			      sphere->OuterRadius(),  
                              sphere->StartPhi(),
                              sphere->DeltaPhi(),
                              sphere->StartTheta(),
                              sphere->DeltaTheta());
  }
  else if (solidType == VGM::kTorus) { 
    VGM::ITorus* torus = dynamic_cast<VGM::ITorus*>(solid); 
    return factory->CreateTorus(torus->Name(), 
                              torus->InnerRadius(),
			      torus->OuterRadius(),  
			      torus->AxialRadius(),  
                              torus->StartPhi(),
                              torus->DeltaPhi());
  }
  else if (solidType == VGM::kTrap) { 
    VGM::ITrap* trap = dynamic_cast<VGM::ITrap*>(solid); 
    return factory->CreateTrap(trap->Name(), 
			      trap->ZHalfLength(),  
			      trap->Theta(), 
			      trap->Phi(),
			      trap->YHalfLengthMinusZ(), 
                              trap->XHalfLengthMinusZMinusY(), 
                              trap->XHalfLengthMinusZPlusY(), 
                              trap->AlphaMinusZ(), 
			      trap->YHalfLengthPlusZ(), 
                              trap->XHalfLengthPlusZMinusY(), 
                              trap->XHalfLengthPlusZPlusY(), 
                              trap->AlphaPlusZ()); 
  }
  else if (solidType == VGM::kTrd) { 
    VGM::ITrd* trd = dynamic_cast<VGM::ITrd*>(solid); 
    return factory->CreateTrd(trd->Name(), 
                              trd->XHalfLengthMinusZ(), 
                              trd->XHalfLengthPlusZ(), 
			      trd->YHalfLengthMinusZ(), 
			      trd->YHalfLengthPlusZ(), 
			      trd->ZHalfLength());  
  }
  else if (solidType == VGM::kTubs) { 
    VGM::ITubs* tubs = dynamic_cast<VGM::ITubs*>(solid); 
    return factory->CreateTubs(tubs->Name(), 
                              tubs->InnerRadius(),
			      tubs->OuterRadius(), 
			      tubs->ZHalfLength(),  
			      tubs->StartPhi(),
			      tubs->DeltaPhi());  
  }
  else if (solidType == VGM::kBoolean) { 
    VGM::IBooleanSolid* boolean = dynamic_cast<VGM::IBooleanSolid*>(solid);
    return ExportBooleanSolid(boolean, factory);
  }

  std::cerr << "    BaseVGM::VFactory::ExportSolid:" << std::endl;
  std::cerr << "    Unknown solid type (solid \"" << solid->Name()
            << "\")" <<  std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);
  return 0;
}  

//_____________________________________________________________________________
BaseVGM::VFactory::VolumeMap* 
BaseVGM::VFactory::ExportVolumeStore(VGM::IFactory* factory) const
{
// Exports all volumes.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Exporting volume store: " << std::endl;
  }	      

  VolumeMap* volumeMap = new VolumeMap();

  for (unsigned int i=0; i<Volumes().size(); i++) {
  
    VGM::IVolume* volume = Volumes()[i];
    
    // Export solid
    VGM::ISolid* solid = ExportSolid(volume->Solid(), factory);

    // Create factory's volume 
    VGM::IVolume* newVolume 
      = factory->CreateVolume(volume->Name(), 
                              solid, 
		   	      volume->MaterialName());
			     
    // Map new volume to old volume
    (*volumeMap)[volume] = newVolume;			     

    // Debug info
    //
    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << "   " << i << "th volume: " << volume->Name();
      if (Debug()>1)
        std::cout << "   " << " oldVGM=" << volume << " newVGM=" << newVolume;
      std::cout << std::endl;
    }		
  } 
  
  return volumeMap;
}
  
//_____________________________________________________________________________
VGM::IPlacement* 
BaseVGM::VFactory::ExportSimplePlacement(
                              VGM::IPlacement* placement,
                              VGM::IFactory* factory, 
			      VolumeMap* volumeMap) const
{
// Export simple placement.
// ---

  if (Debug()>0) {
    std::cout << "  simple placement: " 
              << placement->Name() << std::endl;
  }	      

  VGM::IVolume* newVolume = (*volumeMap)[placement->Volume()];
  VGM::IVolume* newMother = (*volumeMap)[placement->Mother()];
  
  VGM::IPlacement* newPlacement
    = factory->CreatePlacement(
                       placement->Name(), 
                       placement->CopyNo(),
	               newVolume,
		       newMother,
		       placement->Transformation());
      
  return newPlacement;
}

//_____________________________________________________________________________
VGM::IPlacement* 
BaseVGM::VFactory::ExportMultiplePlacement(
                              VGM::IPlacement* placement,
                              VGM::IFactory* factory, 
			      VolumeMap* volumeMap) const
{
// Exports multiple placement.
// ---

  VGM::IVolume* newVolume = (*volumeMap)[placement->Volume()];
  VGM::IVolume* newMother = (*volumeMap)[placement->Mother()];
  
  VGM::Axis axis;
  int nofItems;
  double width;
  double offset;
  placement->MultiplePlacementData(axis, nofItems, width, offset);
  
  if (Debug()>0) {
    std::cout << "  multiple placement - data: "
	      << axis  << ",  " << nofItems << ",  " 
	      << width << ",  " << offset << std::endl;
  }	      
  
  VGM::IPlacement* newPlacement
    = factory->CreateMultiplePlacement(
                     placement->Name(), 
		     newVolume,
		     newMother,
		     axis,
		     nofItems,
		     width,
		     offset);
		     			       
  return newPlacement;
}

//_____________________________________________________________________________
void BaseVGM::VFactory::ExportPlacements(
                                 VGM::IFactory* factory, 
                                 VolumeMap* volumeMap) const
{
// Exports all placements.
// ---

  for (unsigned int i=0; i<Volumes().size(); i++) {
  
    VGM::IVolume* volume = Volumes()[i];
    
    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << "ExportPlacements for "
                << i << "th volume ";
      if (Debug()>1) std::cout << volume << "  ";
      std::cout << volume->Name() << std::endl;
    }		

    for (int id=0; id<volume->NofDaughters(); id++) {
     
      VGM::IPlacement* daughter = volume->Daughter(id);

      if (Debug()>0) {
        BaseVGM::DebugInfo();
        std::cout << "   " << id << "th daughter vol = ";  
        if (Debug()>1) std::cout << daughter->Volume() << "  ";
	std::cout << daughter->Name();
      }		  


      if (daughter->Type() == VGM::kSimplePlacement) {
        ExportSimplePlacement(daughter, factory, volumeMap);
      }
      else if (daughter->Type() == VGM::kMultiplePlacement) {
        ExportMultiplePlacement(daughter, factory, volumeMap);
        }
	else  {
	  std::cout << std::endl;
          std::cerr << "    BaseVGM::VFactory::ExportPlacements:"<< std::endl;
	  std::cerr << "    Unknown placement type (placement \""
	            << daughter->Name() << "\")" << std::endl;
          std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
          exit(1); 		    
        }	   
    }
  }
  
  // Position the top volume
  // (top volume has no mother volume that's why it must be placed
  //  explicitely)
  
  VGM::IVolume* topVolume = (*volumeMap)[Top()->Volume()];
  
  factory->CreatePlacement("top", 0, topVolume, 0, Identity());
  
  delete volumeMap;
}

//_____________________________________________________________________________
VGM::Transform  BaseVGM::VFactory::Identity() const
{
//
  VGM::Transform transform(VGM::kSize);
  for (int i=0; i<7; i++) transform[i] = 0;

  return transform;
}

//
// public functions
//

//_____________________________________________________________________________
bool BaseVGM::VFactory::Export(VGM::IFactory* factory) const
{
// Export the whole geometry to the given factory.
// ---

  // Export materials
  //
  fMaterialFactory->Export(factory->MaterialFactory());
  
  // Export volumes 
  //
  VolumeMap* volumeMap = ExportVolumeStore(factory);
  ExportPlacements(factory, volumeMap);

  return true;  			       
}  

//_____________________________________________________________________________
void  BaseVGM::VFactory::PrintSolids() const
{
// Print all solids.
// ---			       

  std::cout << Name() << " factory solids store: " << std::endl;

  const VGM::SolidStore& solids = Solids();

  for (unsigned i=0; i<solids.size(); i++) {
    std::cout << "   " << i << "th solid: " << *solids[i] << std::endl;
  }   
}

//_____________________________________________________________________________
void  BaseVGM::VFactory::PrintVolumes() const
{	
// Print all volumes.
// ---			       

  std::cout << Name() << " factory volumes store: " << std::endl;

  const VGM::VolumeStore& volumes = Volumes();

  for (unsigned i=0; i<volumes.size(); i++) {
    std::cout << "   " << i << "th: " << *volumes[i] << std::endl;
  }   
}

//_____________________________________________________________________________
void BaseVGM::VFactory::SetDebug (int debug)
{ 
// Sets debug level; the same level is set to material factory.
// ---			       

  fDebug = debug; 
  MaterialFactory()->SetDebug(debug);
}
			       
