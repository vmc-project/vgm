// $Id$
//
// Class Factory
// ---------------
// VGM factory for Geant4.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_FACTORY_H
#define GEANT4_GM_FACTORY_H

#include <string>

#include "BaseVGM/volumes/VFactory.h"

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4BooleanSolid;

class VGM::ISolid;
class VGM::IVolume;
class VGM::IPlacement;

namespace Geant4GM {

  class Factory : public BaseVGM::VFactory
  {
    public:
      Factory();
      virtual ~Factory();
    
      //
      // methods
      //
    
      // solids
      //
      virtual VGM::ISolid*  CreateBox(
                                 const std::string& name, 
                                 double hx, double hy, double hz);

      virtual VGM::ISolid*  CreateCons(
                                 const std::string& name, 
                                 double rin1, double rout1, 
			         double rin2, double rout2, double hz,
	                         double sphi, double dphi);
			        
      virtual VGM::ISolid*  CreatePara(
                                 const std::string& name, 
                                 double dx, double dy, double dz,
	                         double alpha, double theta, double phi);
			       
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
                                 HepRotation* rotation, 
			         const Hep3Vector& translation);
			       
      virtual VGM::ISolid*  CreateIntersectionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB,
			         const HepTransform3D& transform3D);
			       
      virtual VGM::ISolid*  CreateSubtractionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
                                 HepRotation* rotation, 
 			         const Hep3Vector& translation);
			       
      virtual VGM::ISolid*  CreateSubtractionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
			         const HepTransform3D& transform3D);

      virtual VGM::ISolid*  CreateUnionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
                                 HepRotation* rotation, 
			         const Hep3Vector& translation);
			       
      virtual VGM::ISolid*  CreateUnionSolid(
                                 const std::string& name, 
                                 VGM::ISolid* solidA, VGM::ISolid* solidB, 
			         const HepTransform3D& transform3D);


      // volumes
      //
      virtual VGM::IVolume* CreateVolume(
                                 const std::string& name, 
                                 VGM::ISolid* solid, 
                                 const std::string& materialName);

      // placements
      //
      virtual VGM::IPlacement* CreatePlacement(
                                 const std::string& name, 
                                 int copyNo,
                                 VGM::IVolume* volume, 
			         VGM::IVolume* motherVolume,
                                 HepRotation* rotation, 
			         const Hep3Vector& translation);

      virtual VGM::IPlacement* CreatePlacement(
                                 const std::string& name, 
                                 int copyNo,
                                 VGM::IVolume* volume, 
			         VGM::IVolume* motherVolume,
			         const HepTransform3D& transformation);

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
      virtual bool CLHEPRotations() const;		       

      // import/export
      //
      bool Import(G4VPhysicalVolume* topVolume);

    protected:
      Factory(const Factory& rhs) : BaseVGM::VFactory(rhs) {} 

    private:
      // methods
    
      void          ImportConstituentSolid(int index, G4BooleanSolid* solid);
      VGM::ISolid*  ImportSolid(G4VSolid* solid);
      VGM::IVolume* ImportLV(G4LogicalVolume* lv);
      void          ImportDaughters(G4LogicalVolume* lv);
      void          ImportPositions();
      void          ImportPositions(G4LogicalVolume* lv);
    
      // import/export
      //
      virtual bool Import(void* topVolume);

      // data members
      VGM::IPlacement*  fTop; 
  };

}

#endif //GEANT4_GM_FACTORY_H
