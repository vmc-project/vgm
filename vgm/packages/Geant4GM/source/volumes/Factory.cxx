// $Id$
//
// Class Factory
// ---------------
// The interface to geometry factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "G4ReflectionFactory.hh"
#include "G4ReflectedSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4VSolid.hh"
#include "G4BooleanSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Para.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"

#include "ClhepVGM/utilities.h"
#include "BaseVGM/common/utilities.h"

#include "Geant4GM/volumes/Factory.h"
#include "Geant4GM/volumes/PlacementMap.h"
#include "Geant4GM/volumes/VolumeMap.h"
#include "Geant4GM/volumes/Volume.h"
#include "Geant4GM/volumes/Placement.h"
#include "Geant4GM/materials/MaterialFactory.h"
#include "Geant4GM/solids/SolidMap.h"
#include "Geant4GM/solids/BooleanSolid.h"
#include "Geant4GM/solids/Box.h"
#include "Geant4GM/solids/Cons.h"
#include "Geant4GM/solids/Para.h"
#include "Geant4GM/solids/Polycone.h"
#include "Geant4GM/solids/Polyhedra.h"
#include "Geant4GM/solids/Sphere.h"
#include "Geant4GM/solids/Torus.h"
#include "Geant4GM/solids/Trap.h"
#include "Geant4GM/solids/Trd.h"
#include "Geant4GM/solids/Tubs.h"

//_____________________________________________________________________________
Geant4GM::Factory::Factory()
  : BaseVGM::VFactory("Geant4_GM_Factory", 
                     new Geant4GM::MaterialFactory()),
    fTop(0)
{
//
}

//_____________________________________________________________________________
Geant4GM::Factory::~Factory() 
{
//
  // delete map singletons
  delete Geant4GM::SolidMap::Instance();
  delete Geant4GM::VolumeMap::Instance();
  delete Geant4GM::PlacementMap::Instance();
              // There is inconsistence in using the singleton maps
	      // via a factory which is not a singleton
	      // TO DO: to be improved later
}

//
// private functions
//

//_____________________________________________________________________________
void Geant4GM::Factory::ImportConstituentSolid(int index, 
                                               G4BooleanSolid* solid)
{
// Imports constituents of G4 Boolean solid into VGM
// ---

  G4VSolid* consSolid 
    = Geant4GM::BooleanSolid::GetConstituentSolid(index, solid);

  if (!Geant4GM::SolidMap::Instance()->GetSolid(consSolid))
    ImportSolid(consSolid);
}

//_____________________________________________________________________________
VGM::ISolid* 
Geant4GM::Factory::ImportSolid(G4VSolid* solid)
{
// Import G4 solid into VGM
// ---

  // Do not import the same solid twice
  //
  VGM::ISolid* importedSolid 
    = Geant4GM::SolidMap::Instance()->GetSolid(solid);
  if (importedSolid) return importedSolid;

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing solid: "; 
    if (Debug()>1) std::cout << solid << "  ";
    std::cout << solid->GetName() << std::endl;
  }	      

  G4VSolid* consSolid = solid;

  // Get constituent solid if the solid is a reflected solid
  //
  G4ReflectedSolid* reflSolid
    = dynamic_cast<G4ReflectedSolid*>(solid);
  if (reflSolid) 
    consSolid = reflSolid->GetConstituentMovedSolid();
  
  G4Box* box = dynamic_cast<G4Box*>(consSolid);
  if (box) { 
    VGM::IBox* vgmBox = new Geant4GM::Box(box, reflSolid);
    SolidStore().push_back(vgmBox);
    return vgmBox; 
  }

  G4Cons* cons = dynamic_cast<G4Cons*>(consSolid);
  if (cons) { 
    //VGM::ICons* vgmCons = new Geant4GM::Cons(cons, isReflected);
    VGM::ICons* vgmCons = new Geant4GM::Cons(cons, reflSolid);
    SolidStore().push_back(vgmCons);
    return vgmCons; 
  }

  G4Para* para = dynamic_cast<G4Para*>(consSolid);
  if (para) { 
    VGM::IPara* vgmPara = new Geant4GM::Para(para, reflSolid);
    SolidStore().push_back(vgmPara);
    return vgmPara; 
  }

  G4Polycone* polycone = dynamic_cast<G4Polycone*>(consSolid);
  if (polycone) { 
    VGM::IPolycone* vgmPolycone 
      = new Geant4GM::Polycone(polycone, reflSolid);
    SolidStore().push_back(vgmPolycone);
    return vgmPolycone; 
  }

  G4Polyhedra* polyhedra = dynamic_cast<G4Polyhedra*>(consSolid);
  if (polyhedra) { 
    VGM::IPolyhedra* vgmPolyhedra 
      = new Geant4GM::Polyhedra(polyhedra, reflSolid);
    SolidStore().push_back(vgmPolyhedra);
    return vgmPolyhedra; 
  }

  G4Sphere* sphere = dynamic_cast<G4Sphere*>(consSolid);
  if (sphere) { 
    VGM::ISphere* vgmSphere = new Geant4GM::Sphere(sphere, reflSolid);
    SolidStore().push_back(vgmSphere);
    return vgmSphere; 
  }

  G4Torus* torus = dynamic_cast<G4Torus*>(consSolid);
  if (torus) { 
    VGM::ITorus* vgmTorus = new Geant4GM::Torus(torus, reflSolid);
    SolidStore().push_back(vgmTorus);
    return vgmTorus; 
  }

  G4Trap* trap = dynamic_cast<G4Trap*>(consSolid);
  if (trap) { 
    VGM::ITrap* vgmTrap = new Geant4GM::Trap(trap, reflSolid);
    SolidStore().push_back(vgmTrap);
    return vgmTrap; 
  }

  G4Trd* trd = dynamic_cast<G4Trd*>(consSolid);
  if (trd) { 
    VGM::ITrd* vgmTrd = new Geant4GM::Trd(trd, reflSolid);
    SolidStore().push_back(vgmTrd);
    return vgmTrd; 
  }

  G4Tubs* tubs = dynamic_cast<G4Tubs*>(consSolid);
  if (tubs) { 
    VGM::ITubs* vgmTubs = new Geant4GM::Tubs(tubs, reflSolid);
    SolidStore().push_back(vgmTubs);
    return vgmTubs; 
  }

  G4DisplacedSolid* displaced = dynamic_cast<G4DisplacedSolid*>(consSolid);
  if (displaced) {
    // Only constituent solid is imported in VGM
    return ImportSolid(displaced->GetConstituentMovedSolid());
  }  

  G4BooleanSolid* boolean = dynamic_cast<G4BooleanSolid*>(consSolid);
  if (boolean) { 
    ImportConstituentSolid(0, boolean);
    ImportConstituentSolid(1, boolean);
    VGM::IBooleanSolid* vgmBoolean = new Geant4GM::BooleanSolid(boolean);
    SolidStore().push_back(vgmBoolean);

    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << "Imported Boolean solid: ";
      if (Debug()>1) std::cout << vgmBoolean;
      std::cout  << std::endl;
      BaseVGM::DebugInfo();
      std::cout << *vgmBoolean << std::endl;
    }		

    return vgmBoolean; 
  }

  std::cerr << "    Geant4GM::Factory::ImportSolid: " << std::endl; 
  std::cerr << "    Unsupported solid type (solid \'" 
            << solid->GetName() << "\")" << std::endl;
  std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
  exit(1);
}

//_____________________________________________________________________________
VGM::IVolume* 
Geant4GM::Factory::ImportLV(G4LogicalVolume* lv)
{
  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "Importing LV: " << lv->GetName() << std::endl;
  }  

  // Import solid
  VGM::ISolid* solid = ImportSolid(lv->GetSolid());
    
  // Create vgm volume 
  VGM::IVolume* volume = new Geant4GM::Volume(solid,lv);
  VolumeStore().push_back(volume);
  return volume;
}
  

//_____________________________________________________________________________
void Geant4GM::Factory::ImportDaughters(G4LogicalVolume* lv)
{
// Imports recursively all daughters logical volumes.
// ---

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "ImportDaughters for " << lv->GetName() << std::endl;
  }	       

  for (int i=0; i<lv->GetNoDaughters(); i++) {
  
    G4LogicalVolume* dLV 
      = lv->GetDaughter(i)->GetLogicalVolume();

    VGM::IVolume* dVolume
      = Geant4GM::VolumeMap::Instance()->GetVolume(dLV);
      
    if (!dVolume) {
      // Import logical volume 
      dVolume = ImportLV(dLV);
     
      // Process its daughters
      ImportDaughters(dLV); 
    }    
  }  
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportPositions()
{
// Imports placements for all volumes imported.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Import positions: " << std::endl;
  }    

  for (unsigned int i=0; i<Volumes().size(); i++) {
    
    VGM::IVolume* volume = Volumes()[i];
    G4LogicalVolume* lv = Geant4GM::VolumeMap::Instance()->GetVolume(volume);

    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << i << "th volume: " << lv->GetName() << "  " ;
      if (Debug()>1) 
        std::cout << "   lv: " << lv << "  "  << "  vgm: " << volume;  
      std::cout << std::endl; 
    }		
     
    for (G4int id=0; id<lv->GetNoDaughters(); id++) {
    
      G4VPhysicalVolume* dPV = lv->GetDaughter(id);
      G4LogicalVolume* dLV = dPV->GetLogicalVolume();
      VGM::IVolume* dVolume= Geant4GM::VolumeMap::Instance()->GetVolume(dLV);

      if (Debug()>0) {
        BaseVGM::DebugInfo();
        std::cout << "   " << id << "th daughter  lv=";
	if (Debug()>1) std::cout << dLV << "  ";
	std::cout << dLV->GetName() << " vgmVol="; 
	if (Debug()>1) std::cout << dVolume << "  "; 
        std::cout << dVolume->Name() << std::endl;
      }
      	    
      // Create placement
      new Geant4GM::Placement(dVolume, volume, dPV);
    }
  }    	
}

//_____________________________________________________________________________
void Geant4GM::Factory::ImportPositions(G4LogicalVolume* lv)
{
// Imports placements for daughters tree of specified lv.
// Check if the placement has been already imported.
// ---

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "ImportPositions for lv " << lv->GetName() 
              << " nofDaughters: " << lv->GetNoDaughters()
              << std::endl;
  }	      

  VGM::IVolume* volume= Geant4GM::VolumeMap::Instance()->GetVolume(lv);
     
  for (G4int id=0; id<lv->GetNoDaughters(); id++) {
    
    G4VPhysicalVolume* dPV = lv->GetDaughter(id);
      
    if (Debug()) {
      BaseVGM::DebugInfo();
      std::cout << id << "th daugher: " << dPV->GetName() << std::endl;
    }		

    if (! Geant4GM::PlacementMap::Instance()->GetPlacement(dPV)) {
/*   
      if (Debug()>0) {
        BaseVGM::DebugInfo();
        std::cout << "Geant4GM::PlacementMap::Instance()->GetPlacement(dPV) *not* found" 
                  << std::endl;
        BaseVGM::DebugInfo();
        std::cout << "  go to import position" << std::endl;
      }
*/    
      G4LogicalVolume* dLV = dPV->GetLogicalVolume();
      VGM::IVolume* dVolume= Geant4GM::VolumeMap::Instance()->GetVolume(dLV);
      
      // Create placement
      new Geant4GM::Placement(dVolume, volume, dPV);
      
      // Recursively import positions of daughters
      ImportPositions(dLV);
    }
/*
    else
      if (Debug()>0) {
        BaseVGM::DebugInfo();
        std::cout << "Geant4GM::PlacementMap::Instance()->GetPlacement(dPV) found" 
	          << std::endl;
        BaseVGM::DebugInfo();
        std::cout << "  do not import position" << std::endl;
      }	
*/
  }    	
}

//_____________________________________________________________________________
bool Geant4GM::Factory::Import(void* topVolume)
{
//
  G4VPhysicalVolume* worldPV
    = static_cast<G4VPhysicalVolume*>(topVolume);

  return Import(worldPV);

}			      

//
// public functions
//

//_____________________________________________________________________________
VGM::ISolid* 
Geant4GM::Factory::CreateBox(const std::string& name, 
                             double hx, double hy, double hz)
{
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Box(name, hx, hy, hz);
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateCons(const std::string& name, 
                              double rin1, double rout1, 
			      double rin2, double rout2, double hz,
	                      double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Cons(name, rin1, rout1, rin2, rout2, hz, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreatePara(const std::string& name, 
                              double dx, double dy, double dz,
	                      double alpha, double theta, double phi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Para(name, dx, dy, dz, alpha, theta, phi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreatePolycone(
                              const std::string& name, 
                              double sphi, double dphi, 
			      int nofZplanes,
                              double* z, double* rin, double* rout)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Polycone(name, sphi, dphi, nofZplanes, z, rin, rout);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreatePolyhedra(
                               const std::string& name, 
                               double sphi, double dphi, 
			       int nofSides, int nofZplanes,
                               double* z, double* rin, double* rout)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Polyhedra(name, sphi, dphi, 
                              nofSides, nofZplanes, z, rin, rout);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateSphere(const std::string& name, 
                                double rin, double rout, 
			        double sphi, double dphi, 
	                        double stheta, double dtheta)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Sphere(name, rin, rout, sphi, dphi, stheta, dtheta);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateTorus(const std::string& name, 
                               double rin, double rout, double rax, 
			       double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Torus(name, rin, rout, rax, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateTrap(const std::string& name, 
                              double hz, double theta, double phi,
                              double dy1, double dx1, double dx2, 
			      double alpha1, 
                              double dy2, double dx3, double dx4, 
			      double alpha2)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Trap(name, hz, theta, phi, 
                  dy1, dx1, dx2, alpha1, dy2, dx3, dx4, alpha2);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateTrd(const std::string& name, 
                             double hx1, double hx2, double hy1, double hy2, 
			     double hz)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Trd(name, hx1, hx2, hy1, hy2, hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateTubs(const std::string& name, 
                              double rin, double rout, double hz, 
			      double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::Tubs(name, rin, rout, hz, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateIntersectionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation)
{
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::BooleanSolid(
                          name, 
			  VGM::kIntersection, 
			  solidA, solidB, 
                          new HepRotation(ClhepVGM::Rotation(rotation)), 
			  ClhepVGM::Translation(translation));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateIntersectionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation,
			       bool hasReflectionZ)
{
//
  if (hasReflectionZ) {
    std::cerr << "    Geant4GM::Factory::CreateIntersectionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl; 
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  	      
               
  return CreateIntersectionSolid(name, solidA, solidB, rotation, translation);
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateSubtractionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation)
{
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::BooleanSolid(
                           name, 
			   VGM::kSubtraction, 
			   solidA, solidB, 
                           new HepRotation(ClhepVGM::Rotation(rotation)),
			   ClhepVGM::Translation(translation));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateSubtractionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation,
			       bool hasReflectionZ)
{
//
  if (hasReflectionZ) {
    std::cerr << "    Geant4GM::Factory::CreateSubtractionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl; 
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  	      
                
  return CreateSubtractionSolid(name, solidA, solidB, rotation, translation);
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateUnionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation)
{
//
  VGM::ISolid* vgmSolid 
    = new Geant4GM::BooleanSolid(
                           name, 
			   VGM::kUnion, 
			   solidA, solidB, 
                           new HepRotation(ClhepVGM::Rotation(rotation)),
			   ClhepVGM::Translation(translation));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
Geant4GM::Factory::CreateUnionSolid(
                               const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation,
			       bool hasReflectionZ)
{
//
  if (hasReflectionZ) {
    std::cerr << "    Geant4GM::Factory::CreateUnionSolid:" << std::endl;
    std::cerr << "    Reflection in Boolean solid not supported in Geant4."
              << std::endl; 
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  	      
               
  return CreateUnionSolid(name, solidA, solidB, rotation, translation);
}  			     

//_____________________________________________________________________________
VGM::IVolume* 
Geant4GM::Factory::CreateVolume(const std::string& name, 
                                VGM::ISolid* solid, 
                                const std::string& materialName)
{
//
  VGM::IVolume* volume 
    = new Geant4GM::Volume(name, solid, materialName);
    
  VolumeStore().push_back(volume);
  return volume;
}  			       

//_____________________________________________________________________________
VGM::IPlacement* 
Geant4GM::Factory::CreatePlacement(
                               const std::string& name, 
                               int copyNo,
                               VGM::IVolume* volume, 
			       VGM::IVolume* motherVolume,
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation)
{
//

  VGM::IPlacement* placement
    = new Geant4GM::Placement(name, 
                              copyNo, 
			      volume, motherVolume, 
                              new HepRotation(ClhepVGM::Rotation(rotation)), 
			      ClhepVGM::Translation(translation));
  			      
  // Top volume
  if (!motherVolume) 
    if (!fTop)
      fTop = placement;
    else {
      std::cerr << "    Geant4GM::Factory::CreatePlacement:" << std::endl; 
      std::cerr << "    Top volume defined twice!" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }		  
  
  return placement;
}			  			       

//_____________________________________________________________________________
VGM::IPlacement* 
Geant4GM::Factory::CreatePlacement(
                               const std::string& name, 
                               int copyNo,
                               VGM::IVolume* volume, 
			       VGM::IVolume* motherVolume,
                               const VGM::Rotation& rotation, 
			       const VGM::ThreeVector& translation,
			       bool hasReflectionZ)
{
//
  if (!hasReflectionZ) {
    return CreatePlacement(name, copyNo, volume, motherVolume, 
                           rotation, translation);
  }			   


  // Get logical volumes from the volumes map
  G4LogicalVolume* g4LV 
    = Geant4GM::VolumeMap::Instance()->GetVolume(volume);
    
  G4LogicalVolume* g4MotherLV 
    = Geant4GM::VolumeMap::Instance()->GetVolume(motherVolume);
    
  // Create PV placement
  // for a general transformation we have to use G4 reflection factory
  G4ReflectionFactory* g4ReflectionFactory = G4ReflectionFactory::Instance();

  G4PhysicalVolumesPair pvPair
    = g4ReflectionFactory
        ->Place(ClhepVGM::Transform(rotation, translation, hasReflectionZ),  
	        name, g4LV, g4MotherLV, false, copyNo);
	
  // Get info about created PV
  G4VPhysicalVolume* pv1 = pvPair.first;
  G4LogicalVolume*   lv1 = pv1->GetLogicalVolume();
  VGM::IVolume* iv1 = Geant4GM::VolumeMap::Instance()->GetVolume(lv1);
  if (!iv1) {
     // a new logical volume has been created by G4 reflection factory
     // has to be imported into VGM
     iv1 = ImportLV(lv1);
     ImportDaughters(lv1);
     ImportPositions(lv1);
  }    			
  VGM::IPlacement* placement1 
    = new Geant4GM::Placement(iv1, motherVolume, pv1);
  // Register physical volume in the map
  Geant4GM::PlacementMap::Instance()->AddPlacement(placement1, pv1); 

  G4VPhysicalVolume* pv2 = pvPair.second;
  if (pv2) {
    // mother volume is the other volume in the pair
    // constituen/reflected mother lv
    G4LogicalVolume* mlv2 = 0;
    if (g4ReflectionFactory->IsReflected(g4MotherLV))   
      mlv2 = g4ReflectionFactory->GetConstituentLV(g4MotherLV);
    if (g4ReflectionFactory->IsConstituent(g4MotherLV)) 
      mlv2 = g4ReflectionFactory->GetReflectedLV(g4MotherLV);
    if (!mlv2) {
      // should not happen
      std::cerr << "    Geant4GM::Factory::CreatePlacement: " << std::endl;
      std::cerr << "    Misundersood G4ReflectionFactory behavior " <<std::endl; 
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }
    else {
      VGM::IVolume* miv2 = Geant4GM::VolumeMap::Instance()->GetVolume(mlv2);
      if (!miv2) {
        // should not happen
        std::cerr << "    Geant4GM::Factory::CreatePlacement: " << std::endl;
        std::cerr << "    Missing mapping of existing LV to VGM" <<std::endl; 
        std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
        exit(1);
      }
      
      G4LogicalVolume* lv2 = pv2->GetLogicalVolume();
      VGM::IVolume* iv2 = Geant4GM::VolumeMap::Instance()->GetVolume(lv2);
      if (!iv2) {
        // a new logical volume has been created by G4 reflection factory
        // has to be imported into VGM
        iv2 = ImportLV(lv2);
        ImportDaughters(lv2);
	ImportPositions(lv2);
      }
      VGM::IPlacement* placement2 = new Geant4GM::Placement(iv2, miv2, pv2);
      // Register physical volume in the map
      Geant4GM::PlacementMap::Instance()->AddPlacement(placement2, pv2); 
    }
  }    			

  // Register physical volume in the map
  Geant4GM::PlacementMap::Instance()->AddPlacement(placement1, pv1); 

  // Top volume
  if (!motherVolume) 
    if (!fTop)
      fTop = placement1;
    else {
      std::cerr << "    Geant4GM::Factory::CreatePlacement:" << std::endl;
      std::cerr << "    Top volume defined twice!" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }		  
  
  return placement1;
     // should allow to retour a list of placements
}			  			       

//_____________________________________________________________________________
VGM::IPlacement* 
Geant4GM::Factory::CreateMultiplePlacement(
                               const std::string& name, 
                               VGM::IVolume* volume, 
			       VGM::IVolume* motherVolume,
			       VGM::Axis axis,
                               int nofItems,
                               double  width,
                               double  offset)
{
//

  // Top volume
  if (!motherVolume) {
    std::cerr <<     "Geant4GM::Factory::CreateMultiplePlacement: " 
              << "    Mother volume not defined!" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);	      
  }		  
  
  VGM::IPlacement* placement
    = new Geant4GM::Placement(name, volume, motherVolume, 
                       axis, nofItems, width, offset);

  return placement;
}			  			       

//_____________________________________________________________________________
VGM::IPlacement* 
Geant4GM::Factory::Top() const 
{
// Returns the top volume (VGM placement)
// ---

  return fTop;
}  		       

//_____________________________________________________________________________
G4VPhysicalVolume*  
Geant4GM::Factory:: World() const
{
// Returns the world volume (G4 physical volume)
// ---

  return Geant4GM::PlacementMap::Instance()->GetPlacement(fTop);
}


//_____________________________________________________________________________
bool Geant4GM::Factory::CLHEPRotations() const		       
{
// Returns true as Geant4 uses CLHEP rotations,
// No conversion needed.
// ---

  return true;
}  		       

//_____________________________________________________________________________
bool Geant4GM::Factory::Import(G4VPhysicalVolume* worldPV)
{
// Imports Geant4 native geometry
//

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import started ...";
    if (Debug()>1) std::cout << worldPV;
    std::cout << std::endl;
  }  
 
  // Import materials
  // 
  MaterialFactory()->Import();


  // Get logical volume
  G4LogicalVolume* worldLV = worldPV->GetLogicalVolume();

  // Import the top volume 
  VGM::IVolume* worldVolume = ImportLV(worldLV);
  
  // Import recursively all daughters
  ImportDaughters(worldLV);
  
  // Import positions
  ImportPositions();
  
  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << std::endl;
    PrintSolids();
    PrintVolumes();
    if (Debug()>1) 
      Geant4GM::VolumeMap::Instance()->Print();
  }  
  
 // Position the top volume
  fTop = new Geant4GM::Placement(worldVolume, 0, worldPV);
  
  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Geant4GM::Factory::Import finished." << std::endl;
  }  
 
  return true;
}			      
