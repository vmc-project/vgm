// $Id$
//
// Class IFactory
// ---------------
// The VGM interface to geometry factory providing
// functions for geometry construction and conversions.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_FACTORY_H
#define VGM_I_FACTORY_H

#include <string>
#include <vector>

#include "VGM/common/Axis.h"
#include "VGM/common/Transform.h"

namespace VGM {

  class ISolid;
  class IVolume;
  class IPlacement;
  class IMaterialFactory;

  typedef std::vector<ISolid*>   SolidStore;
  typedef std::vector<IVolume*>  VolumeStore;

  class IFactory
  {
    public:
      virtual ~IFactory() {}
    
      //
      // methods
      //
    
      // solids
      //
      virtual ISolid*  CreateBox(const std::string& name, 
                               double x, double y, double z) = 0;
      virtual ISolid*  CreateCons(const std::string& name, 
                               double rin1, double rout1, 
			       double rin2, double rout2, double hz,
	                       double sphi, double dphi) = 0; 
      virtual ISolid*  CreatePara(const std::string& name, 
                               double dx, double dy, double dz,
	                       double alpha, double theta, double phi) = 0;
      virtual ISolid*  CreatePolycone(const std::string& name, 
                               double sphi, double dphi, int nofZplanes,
                               double* z, double* rin, double* rout) = 0;
      virtual ISolid*  CreatePolyhedra(const std::string& name, 
                               double sphi, double dphi, 
			       int nofSides, int nofZplanes,
                               double* z, double* rin, double* rout) = 0;
      virtual ISolid*  CreateSphere(const std::string& name, 
                               double rin, double rout, 
			       double sphi, double dphi, 
	                       double stheta, double dtheta) = 0;
      virtual ISolid*  CreateTorus(const std::string& name, 
                               double rin, double rout, double rax, 
			       double sphi, double dphi) = 0;
      virtual ISolid*  CreateTrap(const std::string& name, 
                               double hz, double theta, double phi,
                               double dy1, double dx1, double dx2, 
			       double alpha1, 
                               double dy2, double dx3, double dx4, 
			       double alpha2) = 0;
      virtual ISolid*  CreateTrd(const std::string& name, 
                               double hx1, double hx2, double hy1, double hy2, 
			       double hz) = 0;
      virtual ISolid*  CreateTubs(const std::string& name, 
                               double rin, double rout, double hz, 
			       double sphi, double dphi) = 0;

      // Boolean solids			       
      // 
      virtual ISolid*  CreateIntersectionSolid(const std::string& name, 
                               ISolid* solidA, ISolid* solidB, 
                               const VGM::Transform& transform) = 0;
 
      virtual ISolid*  CreateSubtractionSolid(const std::string& name, 
                               ISolid* solidA, ISolid* solidB, 
                               const VGM::Transform& transform) = 0;

      virtual ISolid*  CreateUnionSolid(const std::string& name, 
                               ISolid* solidA, ISolid* solidB, 
                               const VGM::Transform& transform) = 0;


      // volumes
      //
      virtual IVolume* CreateVolume(
                               const std::string& name, 
                               ISolid* solid, 
                               const std::string& materialName) = 0;

      // placements
      //
      virtual IPlacement* CreatePlacement(
                               const std::string& name, 
                               int copyNo,
                               IVolume* volume, 
			       IVolume* motherVolume,
			       const Transform& transform) = 0;

      virtual IPlacement* CreateMultiplePlacement(
                               const std::string& name, 
                               IVolume* volume, 
			       IVolume* motherVolume,
			       Axis axis,
                               int nofItems,
                               double  width,
                               double  offset) = 0;
			       
            // TO DO: IVolume* volume parameter is redundant;
	    // IVolume and ISolid should be created automatically
	    // via factory; this is however not available in
	    // Geant4 now (it would have to be done on the VGM level)
	    // - should be possible with G4Division class, so lets wait
	    // for it 	     			       			       
			       
      // top volume
      //
      virtual IPlacement* Top() const = 0;		       
			       
      // access
      //
      virtual std::string Name() const = 0;
      virtual const SolidStore&   Solids() const = 0;			       
      virtual const VolumeStore&  Volumes() const = 0;	
      virtual IMaterialFactory*   MaterialFactory() const = 0;

      // listings
      //
      virtual void  PrintSolids() const = 0;			       
      virtual void  PrintVolumes() const = 0;	

      // export
      //
      virtual bool Export(IFactory* factory) const = 0;			       

      // debug
      //
      virtual void SetDebug (int debug) = 0;			       
      virtual int  Debug() const = 0;

    private:
  
      // import
      //
      virtual bool Import(void* /*topVolume*/) = 0;
  };
  
}  

#endif //VGM_I_FACTORY_H
