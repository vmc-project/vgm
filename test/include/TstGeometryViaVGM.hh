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
    virtual void* TestPlacements2(bool bestMatch);
    virtual void* TestReflections(bool fullPhi);
    virtual void* TestScaledSolids(bool fullPhi);
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();
    virtual void* TestDisplacedSolids1();
    virtual void* TestDisplacedSolids2();

  private:
    // methods
    VGM::IVolume* CreateWorld(double x, double y, double z,
                              const std::string& materialName = "Basic");
    VGM::ISolid* CreateNewSolid();
    VGM::ISolid* CreateArb8();
    void          CreateArb8Solids(std::vector<VGM::IVolume*>& volumes);
    VGM::ISolid* CreateBox();
    VGM::ISolid* CreateCons(double sphi, double dphi);
    VGM::ISolid* CreateEllipsoid();
    VGM::ISolid* CreateEllipticalTube();
    VGM::ISolid* CreateExtrudedSolid1();
    VGM::ISolid* CreateExtrudedSolid2();
    VGM::ISolid* CreateHype();
    VGM::ISolid* CreatePara();
    VGM::ISolid* CreateParaboloid();
    VGM::ISolid* CreatePolycone(double sphi, double dphi);
    VGM::ISolid* CreatePolyhedra(double sphi, double dphi);
    VGM::ISolid* CreateSphere(double sphi, double dphi);
    VGM::ISolid* CreateTessellatedSolid();
    VGM::ISolid* CreateTorus(double sphi, double dphi);
    VGM::ISolid* CreateTrap();
    VGM::ISolid* CreateTrd();
    VGM::ISolid* CreateTubs(double sphi, double dphi);
    VGM::ISolid* CreateCtubs(double sphi, double dphi);
    VGM::IVolume* CreateVolume(VGM::ISolid* solid, bool scale = false);
    void* PlaceSolids(VGM::IVolume* mother,
                      bool fullPhi, bool reflect, bool scale, double zpos);
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

