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
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test detector construction
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
    virtual void* TestNewSolid();
    virtual void* TestPlacements();
    virtual void* TestReflections(Bool_t fullPhi);
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();
    virtual void* TestBooleanSolids4();
    virtual void* TestBooleanSolids5();
    virtual void* TestSpecial();

  private:
    TGeoVolume* CreateWorld(Double_t x, Double_t y, Double_t z);
    TGeoVolume* CreateNewSolid();
    TGeoVolume* CreateBox();
    TGeoVolume* CreateCons(Double_t sphi, Double_t dphi);
    TGeoVolume* CreateEllipticalTube();
    TGeoVolume* CreateExtrudedSolid1();
    TGeoVolume* CreateExtrudedSolid2();
    TGeoVolume* CreatePara();
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

    // data members
    TGeoManager* fGeoManager;		      
    TGeoMedium*  fBasicMedium;
};

#endif //TST_GEOMETRY_VIA_ROOT_H

