// $Id$

// -----------------------------------------------------------------------
// The AgddGM package of the Virtual Geometry Model
// Copyright (C) 2007, Brett Viren              
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: bv@bnl.gov
// -----------------------------------------------------------------------

#include "AgddGM/volumes/Factory.h"

#include <cassert>

// FIXME: need to fill this in....

// solids
//
VGM::ISolid*  
AgddGM::Factory::CreateArb8(const std::string& /*name*/, double /*hz*/, 
                            std::vector<VGM::TwoVector> /*vertices*/ ){assert(0); return 0;}

VGM::ISolid*  
AgddGM::Factory::CreateBox(const std::string& /*name*/, 
			    double /*hx*/, double /*hy*/, double /*hz*/){assert(0); return 0;}

VGM::ISolid*  
AgddGM::Factory::CreateCons(const std::string& /*name*/, 
			     double /*rin1*/, double /*rout1*/, 
			     double /*rin2*/, double /*rout2*/, double /*hz*/,
			     double /*sphi*/, double /*dphi*/){assert(0); return 0;}
			        
VGM::ISolid*  
AgddGM::Factory::CreateCtubs(const std::string& /*name*/, 
			      double /*rin*/, double /*rout*/, double /*hz*/, 
			      double /*sphi*/, double /*dphi*/,
			      double /*nxlow*/, double /*nylow*/, double /*nzlow*/,
			      double /*nxhigh*/, double /*nyhigh*/, double /*nzhigh*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreateEllipticalTube(const std::string& /*name*/, 
				       double /*dx*/, double /*dy*/, double /*hz*/){assert(0); return 0;} 

VGM::ISolid*  
AgddGM::Factory::CreateExtrudedSolid(const std::string& /*name*/, 
                                     std::vector< VGM::TwoVector > /*polygon*/,
                                     std::vector< std::vector<double> > /*zsections*/){assert(0); return 0;}
VGM::ISolid*  
AgddGM::Factory::CreatePara(const std::string& /*name*/, 
			     double /*dx*/, double /*dy*/, double /*dz*/,
			     double /*alpha*/, double /*theta*/, double /*phi*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreatePolycone(const std::string& /*name*/, 
				 double /*sphi*/, double /*dphi*/, int /*nofZplanes*/,
				 double* /*z*/, double* /*rin*/, double* /*rout*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreatePolyhedra(const std::string& /*name*/, 
				  double /*sphi*/, double /*dphi*/, 
				  int /*nofSides*/, int /*nofZplanes*/,
				  double* /*z*/, double* /*rin*/, double* /*rout*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreateSphere(const std::string& /*name*/, 
			       double /*rin*/, double /*rout*/, 
			       double /*sphi*/, double /*dphi*/, 
			       double /*stheta*/, double /*dtheta*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreateTessellatedSolid(const std::string& /*name*/, 
                              std::vector< std::vector<VGM::ThreeVector> > /*facets*/){assert(0); return 0;}

VGM::ISolid*
AgddGM::Factory::CreateTorus(const std::string& /*name*/, 
			      double /*rin*/, double /*rout*/, double /*rax*/, 
			      double /*sphi*/, double /*dphi*/){assert(0); return 0;}
			       
VGM::ISolid*
AgddGM::Factory::CreateTrap(const std::string& /*name*/, 
			     double /*hz*/, double /*theta*/, double /*phi*/,
			     double /*dy1*/, double /*dx1*/, double /*dx2*/, 
			     double /*alpha1*/, 
			     double /*dy2*/, double /*dx3*/, double /*dx4*/, 
			     double /*alpha2*/){assert(0); return 0;}
			       
VGM::ISolid*
AgddGM::Factory::CreateTrd(const std::string& /*name*/, 
			    double /*hx1*/, double /*hx2*/, double /*hy1*/, double /*hy2*/, 
			    double /*hz*/){assert(0); return 0;}
			       
VGM::ISolid*
AgddGM::Factory::CreateTubs(const std::string& /*name*/, 
			     double /*rin*/, double /*rout*/, double /*hz*/, 
			     double /*sphi*/, double /*dphi*/){assert(0); return 0;}

// Boolean solids			       
// 
VGM::ISolid*
AgddGM::Factory::CreateIntersectionSolid(const std::string& /*name*/, 
					  VGM::ISolid* /*solidA*/, VGM::ISolid* /*solidB*/, 
					  const VGM::Transform& /*transform*/){assert(0); return 0;}
			       
VGM::ISolid*  
AgddGM::Factory::CreateSubtractionSolid(const std::string& /*name*/, 
					 VGM::ISolid* /*solidA*/, VGM::ISolid* /*solidB*/, 
					 const VGM::Transform& /*transform*/){assert(0); return 0;}

VGM::ISolid*
AgddGM::Factory::CreateUnionSolid(const std::string& /*name*/, 
				   VGM::ISolid* /*solidA*/, VGM::ISolid* /*solidB*/, 
				   const VGM::Transform& /*transform*/){assert(0); return 0;}


// volumes
//
VGM::IVolume*
AgddGM::Factory::CreateVolume(const std::string& /*name*/, 
			       VGM::ISolid* /*solid*/, 
			       const std::string& /*mediumName*/){assert(0); return 0;}

// placements
//
VGM::IPlacement*
AgddGM::Factory::CreatePlacement(const std::string& /*name*/, 
				  int /*copyNo*/,
				  VGM::IVolume* /*volume*/, 
				  VGM::IVolume* /*motherVolume*/,
				  const VGM::Transform& /*transform*/){assert(0); return 0;}

VGM::IPlacement*
AgddGM::Factory::CreateMultiplePlacement(const std::string& /*name*/, 
					  VGM::IVolume* /*volume*/, 
					  VGM::IVolume* /*motherVolume*/,
					  VGM::Axis /*axis*/,
					  int /*nofItems*/,
					  double  /*width*/,
					  double  /*offset*/){assert(0); return 0;}
