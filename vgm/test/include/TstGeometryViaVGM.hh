// $Id$

// -----------------------------------------------------------------------
// The test program of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class TstGeometryViaVGM
// -------------------------------
// Class for building geometry vis VGM
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_GEOMETRY_VIA_VGM_H
#define TST_GEOMETRY_VIA_VGM_H

#include "TstVGeometry.hh"

namespace VGM {
  class IFactory;
  class IVolume;
}

class TstGeometryViaVGM : public TstVGeometry 
{
  public:
    TstGeometryViaVGM(VGM::IFactory* factory);
    virtual ~TstGeometryViaVGM();

    virtual void  DefineMaterials();
    
    virtual void* TestSolids(bool fullPhi);
    virtual void* TestExtraSolid(VGM::SolidType solidType);
    virtual void* TestNewSolid();
    virtual void* TestNewSolid2();
    virtual void* TestPlacements();
    virtual void* TestReflections(bool fullPhi);
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();

  private:
    // methods
    VGM::IVolume* CreateWorld(double x, double y, double z);
    VGM::IVolume* CreateNewSolid();
    VGM::IVolume* CreateArb8();
    void          CreateArb8Solids(std::vector<VGM::IVolume*>& volumes);
    VGM::IVolume* CreateBox();
    VGM::IVolume* CreateCons(double sphi, double dphi);
    VGM::IVolume* CreateEllipticalTube();
    VGM::IVolume* CreateExtrudedSolid1();
    VGM::IVolume* CreateExtrudedSolid2();
    VGM::IVolume* CreatePara();
    VGM::IVolume* CreatePolycone(double sphi, double dphi);
    VGM::IVolume* CreatePolyhedra(double sphi, double dphi);
    VGM::IVolume* CreateSphere(double sphi, double dphi);
    VGM::IVolume* CreateTessellatedSolid();
    VGM::IVolume* CreateTorus(double sphi, double dphi);
    VGM::IVolume* CreateTrap();
    VGM::IVolume* CreateTrd();
    VGM::IVolume* CreateTubs(double sphi, double dphi);
    VGM::IVolume* CreateCtubs(double sphi, double dphi);
    void* PlaceSolids(VGM::IVolume* mother,
                      bool fullPhi, bool reflect, double zpos);
    void  PlaceSolids(const std::vector<VGM::IVolume*>& volumes,
                      VGM::IVolume* mother);
    void  PlaceExtraSolid(VGM::SolidType solidType, 
                      VGM::IVolume* motherVGM);
 
    // data members
    VGM::IFactory*  fFactory;
    
    const double    fCm;
    const double    fDeg;
    const double    fGcm3;
    const double    fGmole;
    const double    fKelvin;
    const double    fAtm;
};

#endif //TST_GEOMETRY_VIA_VGM_H

