// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

/// \ingroup AgddGM_volumes
//
/// \class AgddGM::Factory
///
/// VGM factory for AGDD.
///
/// Author: bv@bnl.gov

#ifndef AGDD_GM_FACTORY_H
#define AGDD_GM_FACTORY_H

#include <string>
#include <map>

#include <BaseVGM/volumes/VFactory.h>

namespace HepGeom { class Transform3D; }
class VGM::ISolid;
class VGM::IVolume;
class VGM::IPlacement;
class VGM::IExtrudedSolid;

namespace agdd {

    // User doesn't strictly need to know these...
    // from AGDD_Material_Model.hh
    class AGDD_Materials;

    // from AGDD_Model.hh
    class AGDD;
    class AGDD_Section;
    class AGDD_Materials;
    class AGDD_Section;
    class AGDD_Volume;
    class AGDD_Solid;
    class AGDD_Position;
    class AGDD_SinglePosition;
    class AGDD_MultiplePosition;
    class AGDD_RelativePositoin;
    class AGDD_MPosWedge;
    class AGDD_Composition;
    class AGDD_Stack;
    class AGDD_BooleanVolume;
} // namespace agdd

namespace AgddGM {

class BooleanSolid;
class Volume;

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
    virtual VGM::ISolid*  
    CreateBox(const std::string& name, 
	      double hx, double hy, double hz);

    virtual VGM::ISolid*  
    CreateCons(const std::string& name, 
	       double rin1, double rout1, 
	       double rin2, double rout2, double hz,
	       double sphi, double dphi);
			        
    virtual VGM::ISolid*  
    CreateCtubs(const std::string& name, 
		double rin, double rout, double hz, 
		double sphi, double dphi,
		double nxlow, double nylow, double nzlow,
		double nxhigh, double nyhigh, double nzhigh);
			       
    virtual VGM::ISolid*  
    CreateEllipticalTube(const std::string& name, 
			 double dx, double dy, double hz); 

    virtual VGM::ISolid*  
    CreateExtrudedSolid(const std::string& name, 
                        std::vector< VGM::TwoVector > polygon,
                        std::vector< std::vector<double> > zsections);
  
    virtual VGM::ISolid*  
    CreatePara(const std::string& name, 
	       double dx, double dy, double dz,
	       double alpha, double theta, double phi);
			       
    virtual VGM::ISolid*  
    CreatePolycone(const std::string& name, 
		   double sphi, double dphi, int nofZplanes,
		   double* z, double* rin, double* rout);
			       
    virtual VGM::ISolid*  
    CreatePolyhedra(const std::string& name, 
		    double sphi, double dphi, 
		    int nofSides, int nofZplanes,
		    double* z, double* rin, double* rout);
			       
    virtual VGM::ISolid*  
    CreateSphere(const std::string& name, 
		 double rin, double rout, 
		 double sphi, double dphi, 
		 double stheta, double dtheta);
			       
    virtual VGM::ISolid*
    CreateTorus(const std::string& name, 
		double rin, double rout, double rax, 
		double sphi, double dphi);
			       
    virtual VGM::ISolid*
    CreateTrap(const std::string& name, 
	       double hz, double theta, double phi,
	       double dy1, double dx1, double dx2, 
	       double alpha1, 
	       double dy2, double dx3, double dx4, 
	       double alpha2);
			       
    virtual VGM::ISolid*
    CreateTrd(const std::string& name, 
	      double hx1, double hx2, double hy1, double hy2, 
	      double hz);
			       
    virtual VGM::ISolid*
    CreateTubs(const std::string& name, 
	       double rin, double rout, double hz, 
	       double sphi, double dphi);

    // Boolean solids			       
    // 
    virtual VGM::ISolid*
    CreateIntersectionSolid(const std::string& name, 
			    VGM::ISolid* solidA, VGM::ISolid* solidB, 
			    const VGM::Transform& transform);
			       
    virtual VGM::ISolid*  
    CreateSubtractionSolid(const std::string& name, 
			   VGM::ISolid* solidA, VGM::ISolid* solidB, 
			   const VGM::Transform& transform);

    virtual VGM::ISolid*
    CreateUnionSolid(const std::string& name, 
		     VGM::ISolid* solidA, VGM::ISolid* solidB, 
		     const VGM::Transform& transform);


    // volumes
    //
    virtual VGM::IVolume*
    CreateVolume(const std::string& name, 
		 VGM::ISolid* solid, 
		 const std::string& mediumName);

    // placements
    //
    virtual VGM::IPlacement*
    CreatePlacement(const std::string& name, 
		    int copyNo,
		    VGM::IVolume* volume, 
		    VGM::IVolume* motherVolume,
		    const VGM::Transform& transform);

    virtual VGM::IPlacement*
    CreateMultiplePlacement(const std::string& name, 
			    VGM::IVolume* volume, 
			    VGM::IVolume* motherVolume,
			    VGM::Axis axis,
			    int nofItems,
			    double  width,
			    double  offset);

    // top volume
    //
    virtual VGM::IPlacement* Top() const;	

    // import/export
    //
    bool Import(agdd::AGDD* agdd);
    bool Import(void* blech);

protected:
    Factory(const Factory& rhs);

private:
    // methods
    bool ImportMaterials(agdd::AGDD_Materials* mat);
    bool ImportSection(agdd::AGDD_Section* sec);

    // see comments in FactoryImport.cxx on this method    
    AgddGM::Volume* ImportComposition(agdd::AGDD_Composition* comp,
				      const HepGeom::Transform3D& transform,
				      AgddGM::Volume* parent_vol);

    // Like composition, but never will have an envelope.
    // Currently underlying AGDD_Model doesn't support stacks.
    AgddGM::Volume* ImportStack(agdd::AGDD_Stack* stk,
				const HepGeom::Transform3D& transform,
				AgddGM::Volume* parent_vol);

    AgddGM::Volume* ImportBoolean(agdd::AGDD_BooleanVolume* bol);
    AgddGM::BooleanSolid* BuildBoolean(agdd::AGDD_BooleanVolume* bol, int index);


    // need to pass in parent/transform because a composition IsA volume.
    AgddGM::Volume* ImportVolume(agdd::AGDD_Volume* vol,
				 AgddGM::Volume* parent,
				 const HepGeom::Transform3D& transform);

    // copy_number gives initial copy numbr to use
    int ImportPosition(const agdd::AGDD_Position* pos, 
		       AgddGM::Volume* parent,
		       const HepGeom::Transform3D& transform);

    AgddGM::Volume* ImportSolid(agdd::AGDD_Solid* sol);


    // data members
    VGM::IPlacement*  fTop;
    agdd::AGDD* fAgdd;

    AgddGM::Volume* FindVolume(std::string name);
    VGM::ISolid* FindSolid(std::string name);
    VGM::ISolid* MakeSolid(agdd::AGDD_Solid* solid);

    // cache the vgm volume built with a given vgm solid/boolean
    std::map<agdd::AGDD_Volume*, AgddGM::Volume*> fV2V;
    std::map<const agdd::AGDD_Position*, int> fP2C;
};

} // namespace AgddGM

#endif //AGDD_GM_FACTORY_H
