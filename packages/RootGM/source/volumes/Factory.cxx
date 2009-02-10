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
// Class Factory
// ---------------
// The interface to geometry factory.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"

#include "RootGM/volumes/Factory.h"
#include "RootGM/volumes/VolumeMap.h"
#include "RootGM/volumes/Volume.h"
#include "RootGM/volumes/Placement.h"
#include "RootGM/volumes/PlacementMap.h"
#include "RootGM/common/transform.h"
#include "RootGM/common/axis.h"
#include "RootGM/materials/MaterialFactory.h"
#include "RootGM/solids/SolidMap.h"
#include "RootGM/solids/BooleanSolid.h"
#include "RootGM/solids/DisplacedSolid.h"
#include "RootGM/solids/Arb8.h"
#include "RootGM/solids/Box.h"
#include "RootGM/solids/Cons.h"
#include "RootGM/solids/Ctubs.h"
#include "RootGM/solids/EllipticalTube.h"
#include "RootGM/solids/ExtrudedSolid.h"
#include "RootGM/solids/Hype.h"
#include "RootGM/solids/Para.h"
#include "RootGM/solids/Paraboloid.h"
#include "RootGM/solids/Polycone.h"
#include "RootGM/solids/Polyhedra.h"
#include "RootGM/solids/Sphere.h"
#include "RootGM/solids/Torus.h"
#include "RootGM/solids/Trap.h"
#include "RootGM/solids/Trd.h"
#include "RootGM/solids/Tubs.h"

#include "TGeoManager.h"
#include "TGeoShape.h"
#include "TGeoShapeAssembly.h"
#include "TGeoCompositeShape.h"
#include "TGeoArb8.h"
#include "TGeoCone.h"
#include "TGeoEltu.h"
#include "TGeoPara.h"
#include "TGeoHype.h"
#include "TGeoParaboloid.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoSphere.h"
#include "TGeoTorus.h"
#include "TGeoTrd1.h"
#include "TGeoTrd2.h"
#include "TGeoXtru.h"
#include "TGeoVolume.h"
#include "TObjArray.h"

#include <algorithm>

//_____________________________________________________________________________
RootGM::Factory::Factory()
  : VGM::IFactory(),
    BaseVGM::VFactory("Root_GM_Factory",      
                     new RootGM::MaterialFactory()),
    fTop(0) 
{
/// Standard default constructor
  
  if (!gGeoManager)
    new TGeoManager("VGM Root geometry", "VGM Root geometry");  
}

//_____________________________________________________________________________
RootGM::Factory::Factory(const Factory& rhs) 
  : VGM::IFactory(rhs),
    BaseVGM::VFactory(rhs) 
{
/// Protected copy constructor
}      

//_____________________________________________________________________________
RootGM::Factory::~Factory() 
{
//
  
  // delete map singletons
  delete RootGM::SolidMap::Instance();
  delete RootGM::VolumeMap::Instance();
  delete RootGM::PlacementMap::Instance();
              // There is inconsistence in using the singleton maps
	      // via a factory which is not a singleton
	      // TO DO: to be improved later
}

//
// private functions
//

//_____________________________________________________________________________
void RootGM::Factory::ImportConstituentSolid(
                                  int index, 
                                  TGeoCompositeShape* solid)
{
/// Import constituents of Root Boolean solid into VGM

  TGeoShape* consSolid 
    = RootGM::BooleanSolid::GetConstituentSolid(index, solid);

  if (!RootGM::SolidMap::Instance()->GetSolid(consSolid))
    ImportSolid(consSolid);
}

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::Factory::ImportSolid(TGeoShape* shape)
{
/// Convert TGeo shape into VGM solid

  // Do not import the same solid twice
  //
  VGM::ISolid* importedSolid 
    = RootGM::SolidMap::Instance()->GetSolid(shape);
  if (importedSolid) return importedSolid;

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Importing shape: "; 
    if (Debug()>1) std::cout << shape << "  ";
    std::cout << shape->GetName() << std::endl;
  }	      

  TGeoBBox* box = dynamic_cast<TGeoBBox*>(shape);
  if (box && 
      std::string(shape->ClassName()) == std::string("TGeoBBox")) { 
     
    // Import box itself
    VGM::IBox* vgmBox = new RootGM::Box(box);
    SolidStore().push_back(vgmBox);

    // Return box if it has not offset defined
    const Double_t* origin = box->GetOrigin();
    if ( ! origin ||
         ( origin[0] == 0.0 && origin[1]== 0.0 && origin[2] == 0.0 ) ) 
      return vgmBox;
  
    // Import offset via displaced solid
    VGM::IDisplacedSolid* vgmDisplacedSolid = new RootGM::DisplacedSolid(box);
    SolidStore().push_back(vgmDisplacedSolid);
    
    return vgmDisplacedSolid; 
  }

  TGeoConeSeg* cons = dynamic_cast<TGeoConeSeg*>(shape);
  if (cons) { 
    VGM::ICons* vgmCons = new RootGM::Cons(cons);
    SolidStore().push_back(vgmCons);
    return vgmCons; 
  }

  TGeoEltu* eltu = dynamic_cast<TGeoEltu*>(shape);
  if (eltu ) { 
     
    VGM::IEllipticalTube* vgmEltu = new RootGM::EllipticalTube(eltu);
    SolidStore().push_back(vgmEltu);
    return vgmEltu; 
  }

  TGeoCone* cone = dynamic_cast<TGeoCone*>(shape);
  if (cone) { 
    VGM::ICons* vgmCons = new RootGM::Cons(cone);
    SolidStore().push_back(vgmCons);
    return vgmCons; 
  }

  TGeoHype* hype = dynamic_cast<TGeoHype*>(shape);
  if (hype) { 
    VGM::IHype* vgmHype = new RootGM::Hype(hype);
    SolidStore().push_back(vgmHype);
    return vgmHype; 
  }

  TGeoPara* para = dynamic_cast<TGeoPara*>(shape);
  if (para) { 
    VGM::IPara* vgmPara = new RootGM::Para(para);
    SolidStore().push_back(vgmPara);
    return vgmPara; 
  }

  TGeoParaboloid* paraboloid = dynamic_cast<TGeoParaboloid*>(shape);
  if (paraboloid) { 
    VGM::IParaboloid* vgmParaboloid = new RootGM::Paraboloid(paraboloid);
    SolidStore().push_back(vgmParaboloid);
    return vgmParaboloid; 
  }

  TGeoPgon* polyhedra = dynamic_cast<TGeoPgon*>(shape);
  if (polyhedra) { 
    VGM::IPolyhedra* vgmPolyhedra = new RootGM::Polyhedra(polyhedra);
    SolidStore().push_back(vgmPolyhedra);
    return vgmPolyhedra; 
  }

  TGeoPcon* polycone = dynamic_cast<TGeoPcon*>(shape);
  if (polycone) { 
    VGM::IPolycone* vgmPolycone = new RootGM::Polycone(polycone);
    SolidStore().push_back(vgmPolycone);
    return vgmPolycone; 
  }

  TGeoSphere* sphere = dynamic_cast<TGeoSphere*>(shape);
  if (sphere) { 
    VGM::ISphere* vgmSphere = new RootGM::Sphere(sphere);
    SolidStore().push_back(vgmSphere);
    return vgmSphere; 
  }

  TGeoTorus* torus = dynamic_cast<TGeoTorus*>(shape);
  if (torus) { 
    VGM::ITorus* vgmTorus = new RootGM::Torus(torus);
    SolidStore().push_back(vgmTorus);
    return vgmTorus; 
  }

  TGeoTrap* trap = dynamic_cast<TGeoTrap*>(shape);
  if (trap) { 
    VGM::ITrap* vgmTrap = new RootGM::Trap(trap);
    SolidStore().push_back(vgmTrap);
    return vgmTrap; 
  }

  TGeoTrd1* trd1 = dynamic_cast<TGeoTrd1*>(shape);
  if (trd1) { 
    VGM::ITrd* vgmTrd = new RootGM::Trd(trd1);
    SolidStore().push_back(vgmTrd);
    return vgmTrd; 
  }

  TGeoTrd2* trd2 = dynamic_cast<TGeoTrd2*>(shape);
  if (trd2) { 
    VGM::ITrd* vgmTrd = new RootGM::Trd(trd2);
    SolidStore().push_back(vgmTrd);
    return vgmTrd; 
  }

  TGeoArb8* arb8 = dynamic_cast<TGeoArb8*>(shape);
  if (arb8) { 
    VGM::IArb8* vgmArb8 = new RootGM::Arb8(arb8);
    SolidStore().push_back(vgmArb8);
    return vgmArb8; 
  }

  TGeoCtub* ctubs = dynamic_cast<TGeoCtub*>(shape);
  if (ctubs) { 
    VGM::ICtubs* vgmCtubs = new RootGM::Ctubs(ctubs);
    SolidStore().push_back(vgmCtubs);
    return vgmCtubs; 
  }

  TGeoTubeSeg* tubs = dynamic_cast<TGeoTubeSeg*>(shape);
  if (tubs) { 
    VGM::ITubs* vgmTubs = new RootGM::Tubs(tubs);
    SolidStore().push_back(vgmTubs);
    return vgmTubs; 
  }

  TGeoTube* tube = dynamic_cast<TGeoTube*>(shape);
  if (tube) { 
    VGM::ITubs* vgmTubs = new RootGM::Tubs(tube);
    SolidStore().push_back(vgmTubs);
    return vgmTubs; 
  }

  TGeoXtru* xtru = dynamic_cast<TGeoXtru*>(shape);
  if (xtru) { 
    VGM::IExtrudedSolid* vgmXtru = new RootGM::ExtrudedSolid(xtru);
    SolidStore().push_back(vgmXtru);
    return vgmXtru; 
  }

  TGeoShapeAssembly* assembly = dynamic_cast<TGeoShapeAssembly*>(shape);
  if (assembly) { 
    return 0; 
  }

  TGeoCompositeShape* composite = dynamic_cast<TGeoCompositeShape*>(shape);
  if (composite) { 
    ImportConstituentSolid(0, composite);
    ImportConstituentSolid(1, composite);
    VGM::IBooleanSolid* vgmBoolean = new RootGM::BooleanSolid(composite);
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

  std::cerr << "    RootGM::Factory::ImportSolid: " << std::endl; 
  std::cerr << "    Unsupported solid type (solid \"" 
            << shape->GetName() << "\"" 
            << "   type \"" << shape->ClassName() << "\")"
	    << std::endl;
	    
  if ( Ignore() ) {
    std::cerr << "*** Warning: Using a box instead  ***" << std::endl; 
    VGM::IBox* vgmBox 
      = new RootGM::Box(shape->GetName(), 1., 1., 1.);
    SolidStore().push_back(vgmBox);
    RootGM::SolidMap::Instance()->AddSolid(vgmBox, shape); 
    return vgmBox; 
  }
  else {	    
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}

//_____________________________________________________________________________
VGM::IVolume* 
RootGM::Factory::ImportVolume(TGeoVolume* rootVolume)
{
  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "Importing volume: " << rootVolume->GetName() << std::endl;
  }  

  // Import solid
  VGM::ISolid* solid = ImportSolid(rootVolume->GetShape());
  
  // Do not import assembly volumes
  if (dynamic_cast<TGeoVolumeAssembly*>(rootVolume) ) return 0;
    
  // Create vgm volume 
  VGM::IVolume* volume = new RootGM::Volume(solid, rootVolume);
  VolumeStore().push_back(volume);
  return volume;
}
  

//_____________________________________________________________________________
void RootGM::Factory::ImportDaughters(TGeoVolume* rootVolume)
{
/// Imports recursively all daughters volumes

  if (Debug()) {
    BaseVGM::DebugInfo();
    std::cout << "ImportDaughters for " << rootVolume->GetName() 
              << std::endl;
  }	       

  for (int i=0; i<rootVolume->GetNdaughters(); i++) {
  
    TGeoVolume* rootDVolume = rootVolume->GetNode(i)->GetVolume();

    VGM::IVolume* dVolume
      = RootGM::VolumeMap::Instance()->GetVolume(rootDVolume);
      
    if (!dVolume) {
      // Import logical volume 
      dVolume = ImportVolume(rootDVolume);
     
      // Process its daughters
      ImportDaughters(rootDVolume); 
    }    
  }  
}

//_____________________________________________________________________________
void RootGM::Factory::ImportAssembly(const TGeoVolume* rootVolume,
                                     VGM::IVolume* volume,
                                     const TGeoNode* rootAssemblyNode,
				     std::vector<const TGeoNode*>& assemblyNodes)
{
/// Import an assembly daughter of the rootVolume.                            \n
/// Called recursively if the daughter of assembly is again assembly.

  TGeoVolume* rootAssemblyVolume = rootAssemblyNode->GetVolume();

  if ( ! rootAssemblyVolume->IsAssembly()) return;
  
  assemblyNodes.push_back(rootAssemblyNode);
    
  for (int i=0; i<rootAssemblyVolume->GetNdaughters(); i++) {
       
    TGeoNode* dNode = rootAssemblyVolume->GetNode(i);
    TGeoVolume* dRootVolume = dNode->GetVolume();
    
    if ( ! dRootVolume->IsAssembly() ) {
      VGM::IVolume* dVolume 
        = RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);
	 
      if (Debug()>0) {
         BaseVGM::DebugInfo();
         std::cout << "   " << i << "th assembly daughter  rtVol = ";
         if (Debug()>1) std::cout << dRootVolume << "  "; 
         std::cout << dRootVolume->GetName() << " vgmVol = "; 
         if (Debug()>1) std::cout << dVolume << "  "; 
         std::cout << dVolume->Name() << std::endl;
      }
      // Create placement	    
      new RootGM::Placement(dVolume, volume, dNode, assemblyNodes);
    }  
    else {
      std::vector<const TGeoNode*> assemblyNodes2(assemblyNodes.size());
      copy (assemblyNodes.begin(), assemblyNodes.end(),
            assemblyNodes2.begin());

      ImportAssembly(rootVolume, volume, dNode, assemblyNodes2);
    }
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportPlacements(const TGeoVolume* rootVolume, 
                                       VGM::IVolume* volume)
{
/// Build Root geometry for the daughters of the specified volume

  for (int i=0; i<rootVolume->GetNdaughters(); i++) {
    
    TGeoNode* dNode = rootVolume->GetNode(i);
    TGeoVolume* dRootVolume = dNode->GetVolume();
    
    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << "   " << i << "th daughter  rtVol = ";
      if (Debug()>1) std::cout << dRootVolume << "  "; 
      std::cout << dRootVolume->GetName();    
    }	    
	    
    if ( ! dRootVolume->IsAssembly()) {
    
      VGM::IVolume* dVolume= RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);
      
      if (Debug()>0) {
        std::cout << " vgmVol = "; 
        if (Debug()>1) std::cout << dVolume << "  "; 
        std::cout << dVolume->Name() << std::endl;
      }	    
	    
      // Create placement
      new RootGM::Placement(dVolume, volume, dNode);
    }
    else {
      std::vector<const TGeoNode*> assemblyNodes;
      ImportAssembly(rootVolume, volume, dNode, assemblyNodes);
    } 
  }
}

//_____________________________________________________________________________
void RootGM::Factory::ImportDivision(const TGeoVolume* rootVolume,
                                     VGM::IVolume* volume)
{
/// Import division

  // Get  pattern finder
  TGeoPatternFinder* finderNonConst = rootVolume->GetFinder();    

  // Get the first division volume
  TGeoNode* dNode = finderNonConst->GetNodeOffset(0);
  TGeoVolume* dRootVolume = dNode->GetVolume();
  VGM::IVolume* dVolume= RootGM::VolumeMap::Instance()->GetVolume(dRootVolume);
      
  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "   " << "0th daughter (division) rtVol = ";
    if (Debug()>1) std::cout << dRootVolume << "  "; 
    std::cout << dRootVolume->GetName() << " vgmVol = "; 
    if (Debug()>1) std::cout << dVolume << "  "; 
    std::cout << dVolume->Name() << std::endl;
  }	    
	    
  // Create placement
  new RootGM::Placement(dVolume, volume, dNode);
}

//_____________________________________________________________________________
void RootGM::Factory::ImportPositions()
{
/// Imports placements for all volumes imported

  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "Import positions: " << std::endl;
  }    

  TObjArray* rootVolumes = gGeoManager->GetListOfVolumes();

  for (int i=0; i<rootVolumes->GetEntriesFast(); i++) {
  
    TGeoVolume* rootVolume = (TGeoVolume*)rootVolumes->At(i);
    if (rootVolume->IsAssembly()) continue;
    
    VGM::IVolume* volume= RootGM::VolumeMap::Instance()->GetVolume(rootVolume);
    
    if ( !volume ) continue;
      // There may be defined volumes which are placed
      // or not placed withing this top volume
      // Hence they were not imported and we skip them

    if (Debug()>0) {
      BaseVGM::DebugInfo();
      std::cout << i << "th volume: " << rootVolume->GetName() << "  "; 
      if (Debug()>1) 
        std::cout << "   rt : " << rootVolume << "  " 
                  << "  vgm: " << volume;  
      std::cout << std::endl; 
    }		
     
    if (IsDivided(rootVolume))
      ImportDivision(rootVolume, volume);
    else  
      ImportPlacements(rootVolume, volume);
  }    	
}

//_____________________________________________________________________________
bool RootGM::Factory::Import(void* topNode)
{
//
  TGeoNode* rootNode
    = static_cast<TGeoNode*>(topNode);

  return Import(rootNode);

}			      

//_____________________________________________________________________________
bool RootGM::Factory::IsDivided(const TGeoVolume* volume) const
{
/// Returns true if the volume is divided
/// and division is known to VGM.

  // Check if division is present
  const TGeoPatternFinder* finder = volume->GetFinder();    
  if (!finder) return false;
    
  // Get division axis
  VGM::Axis axis = Axis(finder);
  if (axis == VGM::kUnknownAxis) return false;
  
  // Volume can be processed as VGM division
  return true;
}  

//
// public functions
//

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::Factory::CreateArb8(const std::string& name, 
                            double hz, 
                            std::vector<VGM::TwoVector> vertices)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Arb8(name, hz, vertices);
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid* 
RootGM::Factory::CreateBox(const std::string& name, 
                           double hx, double hy, double hz)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Box(name, hx, hy, hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateCons(const std::string& name, 
                            double rin1, double rout1, 
			    double rin2, double rout2, double hz,
	                    double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Cons(name, rin1, rout1, rin2, rout2, hz, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateCtubs(const std::string& name, 
                            double rin, double rout, double hz, 
			    double sphi, double dphi,
			    double nxlow, double nylow, double nzlow,
			    double nxhigh, double nyhigh, double nzhigh)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Ctubs(name, rin, rout, hz, sphi, dphi, 
                        nxlow, nylow, nzlow, nxhigh, nyhigh, nzhigh);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateEllipticalTube(const std::string& name, 
                              double dx, double dy, double hz)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::EllipticalTube(name, dx, dy,  hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateHype(const std::string& name, 
                            double r1, double r2, double stereo1, double stereo2,
                            double hz)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Hype(name, r1, r2, stereo1, stereo2, hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreatePara(const std::string& name, 
                            double dx, double dy, double dz,
	                    double alpha, double theta, double phi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Para(name, dx, dy, dz, alpha, theta, phi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateParaboloid(const std::string& name, 
                            double r1, double r2, double hz)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Paraboloid(name, r1, r2, hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreatePolycone(
                           const std::string& name, 
                           double sphi, double dphi, int nofZplanes,
                           double* z, double* rin, double* rout)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Polycone(name, sphi, dphi, nofZplanes, z, rin, rout);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreatePolyhedra(
                           const std::string& name, 
                           double sphi, double dphi, 
			   int nofSides, int nofZplanes,
                           double* z, double* rin, double* rout)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Polyhedra(name, sphi, dphi, nofSides, nofZplanes, 
                            z, rin, rout);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}
  			     			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateSphere(const std::string& name, 
                              double rin, double rout, 
			      double sphi, double dphi, 
	                      double stheta, double dtheta)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Sphere(name, rin, rout, sphi, dphi, stheta, dtheta);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateTessellatedSolid(const std::string& name, 
                               std::vector< std::vector<VGM::ThreeVector> > /*facets*/)
{
// Not supported solid in Root

  std::cerr << "*** Error: Cannot create Tessellated solid in Root ***" << std::endl; 
  if ( Ignore() ) {
    std::cerr << "*** Warning: Using a box instead  ***" << std::endl; 
    std::cerr << std::endl; 
    VGM::IBox* vgmBox 
      = new RootGM::Box(name, 1., 1., 1.);
    SolidStore().push_back(vgmBox);
    return vgmBox; 
  }
  else {	    
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }  
}                               

//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateTorus(const std::string& name, 
                             double rin, double rout, double rax, 
			     double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Torus(name, rin, rout, rax, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateTrap(const std::string& name, 
                            double hz, double theta, double phi,
                            double dy1, double dx1, double dx2, 
			    double alpha1, 
                            double dy2, double dx3, double dx4, 
			    double alpha2)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Trap(name, hz, theta, phi, 
                  dy1, dx1, dx2, alpha1, dy2, dx3, dx4, alpha2);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateTrd(const std::string& name, 
                           double hx1, double hx2, double hy1, double hy2, 
			   double hz)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Trd(name, hx1, hx2, hy1, hy2, hz);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateTubs(const std::string& name, 
                            double rin, double rout, double hz, 
			    double sphi, double dphi)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::Tubs(name, rin, rout, hz, sphi, dphi);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateExtrudedSolid(const std::string& name, 
                            std::vector< VGM::TwoVector > polygon,
                            std::vector< std::vector<double> > zsections)
{			       
//
  VGM::ISolid* vgmSolid 
    = new RootGM::ExtrudedSolid(name, polygon, zsections);

  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     
			       
//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateIntersectionSolid(
                             const std::string& name, 
                             VGM::ISolid* solidA, VGM::ISolid* solidB, 
                             const VGM::Transform& transform)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::BooleanSolid(
                         name, 
                         VGM::kIntersection, 
			 solidA, solidB, 
                         CreateTransform(transform));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateSubtractionSolid(
                             const std::string& name, 
                             VGM::ISolid* solidA, VGM::ISolid* solidB, 
                             const VGM::Transform& transform)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::BooleanSolid(
                         name, 
			 VGM::kSubtraction,
			 solidA, solidB, 
                         CreateTransform(transform));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateUnionSolid(
                             const std::string& name, 
                             VGM::ISolid* solidA, VGM::ISolid* solidB, 
                             const VGM::Transform& transform)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::BooleanSolid(
                         name, 
			 VGM::kUnion, 
			 solidA, solidB, 
                         CreateTransform(transform));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::ISolid*  
RootGM::Factory::CreateDisplacedSolid(
                             const std::string& name, 
                             VGM::ISolid* solid, 
                             const VGM::Transform& transform)
{
//
  VGM::ISolid* vgmSolid 
    = new RootGM::DisplacedSolid(
                         name, 
			 solid, 
                         CreateTransform(transform));
    
  SolidStore().push_back(vgmSolid);
  return vgmSolid; 
}  			     

//_____________________________________________________________________________
VGM::IVolume* 
RootGM::Factory::CreateVolume(const std::string& name, 
                              VGM::ISolid* solid, 
                              const std::string& mediumName)
{
//
  VGM::IVolume* volume
    = new RootGM::Volume(name, solid, mediumName);

  VolumeStore().push_back(volume);
  return volume;
}  			       

//_____________________________________________________________________________
VGM::IPlacement* 
RootGM::Factory::CreatePlacement(
                               const std::string& name, 
                               int copyNo,
                               VGM::IVolume* volume, 
			       VGM::IVolume* motherVolume,
                               const VGM::Transform& transform)
{
//
  VGM::IPlacement* placement
    = new RootGM::Placement(
                       name, 
                       copyNo, 
		       volume, motherVolume, 
		       CreateTransform(transform)); 
		       
  // Top volume
  if (!motherVolume) {
    if (!fTop)
      fTop = placement;
    else {
      std::cerr << "    RootGM::Factory::CreatePlacement:" << std::endl;
      std::cerr << "    Top volume defided twice!" << std::endl;
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }		  
  }
  
  return placement;
}			  			       

//_____________________________________________________________________________
VGM::IPlacement* 
RootGM::Factory::CreateMultiplePlacement(
                               const std::string& name, 
                               VGM::IVolume* volume, 
			       VGM::IVolume* motherVolume,
			       VGM::Axis axis,
                               int nofItems,
                               double  width,
                               double  offset)
{
//
  // Cannot be top volume
  if (!motherVolume) {
    std::cerr << "    RootGM::Factory::CreateMultiplePlacement:" << std::endl;
    std::cerr << "    Mother volume not defined!" << std::endl;
    std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
    exit(1);
  }		  

  // Create TGeo division
  BaseVGM::VPlacement* placement
    = new RootGM::Placement(name, volume, motherVolume, axis, nofItems, width, offset);
     
  // Import divison volume
  // (The VGM::IVolume* volume is ignored)
  TGeoNode* node = RootGM::PlacementMap::Instance()->GetPlacement(placement);
  TGeoVolume* rootVolume = node->GetVolume();
  rootVolume->SetName(volume->Name().data());
      // Now we should copy old root volume daughters to this new one
      // but there is no way to do it
      // For the time being only check if it happens 
      
  TGeoVolume* oldVolume 
      = RootGM::VolumeMap::Instance()->GetVolume(volume);
  oldVolume->SetName("volumeNotPlacedInGeometry");    
  if (oldVolume->GetNdaughters()>0) {
    std::cerr << "*** Limitation  ***" << std::endl; 
    std::cerr << "    RootGM::Factory::CreateMultiplePlacement: " <<  std::endl;
    std::cerr << "    Daughters of divided volume can be set " <<  std::endl
              << "    only after multiple placement definition." << std::endl   
	      << "    Geometry would be incomplete." << std::endl;
    exit(1);	      
  }	      

  (dynamic_cast<RootGM::Volume*>(volume))->ResetVolume(rootVolume);

  return placement;
}			  			       

//_____________________________________________________________________________
VGM::IPlacement* 
RootGM::Factory::Top() const 
{
/// Returns the top volume (VGM placement)

  return fTop;
}  		       

//_____________________________________________________________________________
TGeoNode*  
RootGM::Factory:: World() const
{
/// Returns the world volume (Root node)

  return RootGM::PlacementMap::Instance()->GetPlacement(fTop);
}


//_____________________________________________________________________________
bool RootGM::Factory::Import(TGeoNode* topNode)
{
/// Import Root native geometry


  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import started ...";
    if (Debug()>1)  std::cout << topNode;
    std::cout << std::endl;
  }  
 
  // Import materials
  // 
  MaterialFactory()->Import();
  
  // Get top volume
  TGeoVolume* topVolume = topNode->GetVolume();

  // Import the top volume 
  VGM::IVolume* worldVolume = ImportVolume(topVolume);
  
  // Import recursively all daughters
  ImportDaughters(topVolume);
  
  // Import positions
  ImportPositions();
  
  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << std::endl;
    PrintSolids();
    PrintVolumes();
    if (Debug()>1) 
      RootGM::VolumeMap::Instance()->Print();
  }  
  
  // Position the top volume
  fTop = new RootGM::Placement(worldVolume, 0, topNode);
  
  if (Debug()>0) {
    BaseVGM::DebugInfo();
    std::cout << "RootGM::Factory::Import finished." << std::endl;
  }  
 
  return true;
}
			       

