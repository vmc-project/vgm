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
// Class TstGeometryViaRoot
// -------------------------------
// Class for building geometry via Root
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_GEOMETRY_VIA_ROOT_H
#define TST_GEOMETRY_VIA_ROOT_H

#include "Rtypes.h"

#include "TstVGeometry.hh"

class TGeoManager;
class TGeoVolume;
class TGeoMedium;

class TstGeometryViaRoot : public TstVGeometry 
{
  public:
    TstGeometryViaRoot();
    virtual ~TstGeometryViaRoot();

    virtual void  DefineMaterials();

    virtual void* TestSolids(Bool_t fullPhi);
    virtual void* TestExtraSolid(VGM::SolidType solidType);
    virtual void* TestNewSolid();
    virtual void* TestNewSolid2();
    virtual void* TestPlacements();
    virtual void* TestReflections(Bool_t fullPhi);
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();
    virtual void* TestBooleanSolids4();
    virtual void* TestBooleanSolids5();
    virtual void* TestBooleanSolids6();
    virtual void* TestBooleanSolids7();
    virtual void* TestDisplacedSolids1();
    virtual void* TestSpecial();

  private:
    TGeoVolume* CreateWorld(Double_t x, Double_t y, Double_t z);
    TGeoVolume* CreateNewSolid();
    TGeoVolume* CreateArb8();
    void        CreateArb8Solids(std::vector<TGeoVolume*>& volumes);
    TGeoVolume* CreateBox();
    TGeoVolume* CreateCons(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateEllipticalTube();
    TGeoVolume* CreateExtrudedSolid1();
    TGeoVolume* CreateExtrudedSolid2();
    TGeoVolume* CreateHype();
    TGeoVolume* CreatePara();
    TGeoVolume* CreateParaboloid();
    TGeoVolume* CreatePolycone(Double_t sphi, Double_t dphi);
    TGeoVolume* CreatePolyhedra(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateSphere(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateTorus(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateTrap();
    TGeoVolume* CreateTrd();
    TGeoVolume* CreateTubs(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateCtubs(Double_t sphi, Double_t dphi);
    TGeoVolume* PlaceSolids(TGeoVolume* mother,
                     Bool_t fullPhi, Bool_t reflect, Double_t zpos);
    void PlaceSolids(const std::vector<TGeoVolume*>& volumes,
                     TGeoVolume* mother);
    void PlaceExtraSolid(VGM::SolidType solidType, TGeoVolume* mother);

    // data members
    TGeoManager* fGeoManager;		      
    TGeoMedium*  fBasicMedium;
};

#endif //TST_GEOMETRY_VIA_ROOT_H

