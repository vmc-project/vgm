// $Id$
//
// Class Factory
// ----------------
// VGM factory for Root.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_FACTORY_H
#define ROOT_GM_FACTORY_H

#include <string>

#include "BaseVGM/volumes/VFactory.h"

class TGeoShape;
class TGeoVolume;
class TGeoCompositeShape;

class VGM::ISolid;
class VGM::IVolume;
class VGM::IPlacement;

namespace RootGM {

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
			       
      virtual VGM::ISolid*  CreatePara(const std::string& name, 
                               double dx, double dy, double dz,
	                       double alpha, double theta, double phi);
			       
      virtual VGM::ISolid*  CreatePolycone(const std::string& name, 
                               double sphi, double dphi, 
			       int nofZplanes,
                               double* z, double* rin, double* rout);
			       
      virtual VGM::ISolid*  CreatePolyhedra(const std::string& name, 
                               double sphi, double dphi, 
			       int nofSides, int nofZplanes,
                               double* z, double* rin, double* rout);
			       
      virtual VGM::ISolid*  CreateSphere(const std::string& name, 
                               double rin, double rout, 
			       double sphi, double dphi, 
	                       double stheta, double dtheta);
			       
      virtual VGM::ISolid*  CreateTorus(const std::string& name, 
                               double rin, double rout, double rax, 
			       double sphi, double dphi);
			       
      virtual VGM::ISolid*  CreateTrap(const std::string& name, 
                               double hz, double theta, double phi,
                               double dy1, double dx1, double dx2, 
			       double alpha1, 
                               double dy2, double dx3, double dx4, 
			       double alpha2);
			       
      virtual VGM::ISolid*  CreateTrd(const std::string& name, 
                               double hx1, double hx2, double hy1, double hy2, 
			       double hz);
			       
      virtual VGM::ISolid*  CreateTubs(const std::string& name, 
                               double rin, double rout, double hz, 
			       double sphi, double dphi);

      // Boolean solids			       
      // 
      virtual VGM::ISolid*  CreateIntersectionSolid(const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Transform& transform); 
 			       
      virtual VGM::ISolid*  CreateSubtractionSolid(const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
                               const VGM::Transform& transform); 
			       
      virtual VGM::ISolid*  CreateUnionSolid(const std::string& name, 
                               VGM::ISolid* solidA, VGM::ISolid* solidB, 
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
      TGeoVolume*  World() const;	       

      // import/export
      //
      bool Import(TGeoVolume* topVolume);			       
			       
    protected:
      Factory(const Factory& rhs);

    private:
      void          ImportConstituentSolid(int index, TGeoCompositeShape* solid);      
      VGM::ISolid*  ImportSolid(TGeoShape* shape);
      VGM::IVolume* ImportVolume(TGeoVolume* rootVolume);
      void          ImportPlacements(
                                const TGeoVolume* rootVolume, 
                                VGM::IVolume* volume);
      void          ImportDivision(
                                const TGeoVolume* rootVolume, 
                                VGM::IVolume* volume);
      void          ImportDaughters(TGeoVolume* rootVolume);
      void          ImportPositions();
      bool          IsDivided(const TGeoVolume* volume) const;

      // import/export
      //
      virtual bool Import(void* topVolume);			       
    
      VGM::IPlacement* fTop;      
  };

}

#endif //ROOT_GM_FACTORY_H
