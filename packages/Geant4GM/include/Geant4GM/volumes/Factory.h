// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_volumes
//
/// \class Geant4GM::Factory
///
/// VGM factory for Geant4.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_FACTORY_H
#define GEANT4_GM_FACTORY_H

#include "BaseVGM/volumes/VFactory.h"

#include "G4ReflectionFactory.hh"

#include <string>

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4BooleanSolid;

namespace VGM {
  class ISolid;
  class IVolume;
  class IPlacement;
  class IExtrudedSolid;
}

namespace Geant4GM {

  class Factory : public BaseVGM::VFactory
  {
    public:
      Factory();
      virtual ~Factory();
    
      // static methods
      static void SetSurfCheck(bool surfCheck);
      static bool GetSurfCheck();

      //
      // methods
      //
    
      // solids
      //
      virtual VGM::ISolid*  CreateArb8(const std::string& name, 
                               double hz, 
                               std::vector<VGM::TwoVector> vertices );

      virtual VGM::ISolid*  CreateBox(
                                 const std::string& name, 
                                 double hx, double hy, double hz);

      virtual VGM::ISolid*  CreateCons(
                                 const std::string& name, 
                                 double rin1, double rout1, 
			         double rin2, double rout2, double hz,
	                         double sphi, double dphi);
			        
      virtual VGM::ISolid*  CreateCtubs(const std::string& name, 
                                 double rin, double rout, double hz, 
			         double sphi, double dphi,
			         double nxlow, double nylow, double nzlow,
			         double nxhigh, double nyhigh, double nzhigh);
			       
      virtual VGM::ISolid*  CreateEllipticalTube(
                                 const std::string& name, 
                                 double dx, double dy, double hz); 

      virtual VGM::ISolid*  CreateExtrudedSolid(const std::string& name, 
                                 std::vector< VGM::TwoVector > polygon,
                                 std::vector< std::vector<double> > zsections);

      virtual VGM::ISolid*  CreateHype(const std::string& name, 
                                 double r1, double r2, double stereo1, double stereo2, 
                                 double hz);

      virtual VGM::ISolid*  CreatePara(
                                 const std::string& name, 
                                 double dx, double dy, double dz,
	                         double alpha, double theta, double phi);
			       
      virtual VGM::ISolid*  CreateParaboloid(const std::string& name, 
                                 double r1, double r2, double hz);
                                 
      virtual VGM::ISolid*  CreatePolycone(
                                 const std::string& name, 
                                 double sphi, double dphi, int nofZplanes,
                                 double* z, double* rin, double* rout);
			       
      virtual VGM::ISolid*  CreatePolyhedra(
                                 const std::string& name, 
                                 double sphi, double dphi, 
			         int nofSides, int nofZplanes,
                                 double* z, double* rin, double* rout);
			       
      virtual VGM::ISolid*  CreateSphere(
                                 const std::string& name, 
                                 double rin, double rout, 
			         double sphi, double dphi, 
	                         double stheta, double dtheta);
			       
      virtual VGM::ISolid*  CreateTessellatedSolid(const std::string& name, 
                                 std::vector< std::vector<VGM::ThreeVector> > facets);

      virtual VGM::ISolid*  CreateTorus(
                                 const std::string& name, 
                                 double rin, double rout, double rax, 
			         double sphi, double dphi);
			       
      virtual VGM::ISolid*  CreateTrap(
                                 const std::string& name, 
                                 double hz, double theta, double phi,
                                 double dy1, double dx1, double dx2, 
			         double alpha1, 
                                 double dy2, double dx3, double dx4, 
			         double alpha2);
			       
      virtual VGM::ISolid*  CreateTrd(
                                 const std::string& name, 
                                 double hx1, double hx2, double hy1, double hy2, 
			         double hz);
			       
      virtual VGM::ISolid*  CreateTubs(
                                 const std::string& name, 
                                 double rin, double rout, double hz, 
			         double sphi, double dphi);
     
      // Boolean solids			       
      // 
      virtual VGM::ISolid*  CreateIntersectionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
                                 const VGM::Transform& transform);
			       
       virtual VGM::ISolid*  CreateSubtractionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
                                 const VGM::Transform& transform);

      virtual VGM::ISolid*  CreateUnionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
                                 const VGM::Transform& transform);

      virtual VGM::ISolid*  CreateDisplacedSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solid,
                                 const VGM::Transform& transform);

      // volumes
      //
      virtual VGM::IVolume* CreateVolume(
                                 const std::string& name, 
                                 VGM::ISolid* solid, 
                                 const std::string& mediumName);

      // placements
      //
      virtual VGM::IPlacement* CreatePlacement(
                                 const std::string& name, 
                                 int copyNo,
                                 VGM::IVolume* volume, 
			         VGM::IVolume* motherVolume,
                                 const VGM::Transform& transform);

      virtual VGM::IPlacement* CreateMultiplePlacement(
                                 const std::string& name, 
                                 VGM::IVolume* volume, 
			         VGM::IVolume* motherVolume,
			         VGM::Axis axis,
                                 int nofItems,
                                 double  width,
                                 double  offset);

      // top volume
      //
      virtual VGM::IPlacement* Top() const;	
      G4VPhysicalVolume*     World() const;	       

      // import/export
      //
      bool Import(G4VPhysicalVolume* topVolume);

    protected:
      Factory(const Factory& rhs); 

    private:
      // methods
    
      void          ImportConstituentSolid(int index, G4BooleanSolid* solid);
      VGM::ISolid*  ImportSolid(G4VSolid* solid);
      VGM::IVolume* ImportLV(G4LogicalVolume* lv);
      VGM::IVolume* ImportLV(G4LogicalVolume* lv, const std::string& mediumName);
      void          ImportDaughters(G4LogicalVolume* lv);
      void          ImportPositions();
      void          ImportPositions(G4LogicalVolume* lv);
      VGM::IPlacement* ImportPVPair(VGM::IVolume* volume, 
			            VGM::IVolume* motherVolume,
                                    G4PhysicalVolumesPair pvPair);
      bool          SwitchSolid(VGM::IVolume* volume,
                                G4LogicalVolume* g4LV,
                                G4LogicalVolume* g4Mother);
                                
      // import/export
      //
      virtual bool Import(void* topVolume);

      // static data members
      static bool  fgSurfCheck;

      // data members
      VGM::IPlacement*  fTop; 
  };

}

#endif //GEANT4_GM_FACTORY_H
