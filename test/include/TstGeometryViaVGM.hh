// $Id$
//
// Class TstPrimaryGeneratorAction
// -------------------------------
// The test detector construction
//
// Author: Ivana Hrivnacova; IPN Orsay


#ifndef TST_GEOMETRY_VIA_VGM_H
#define TST_GEOMETRY_VIA_VGM_H

#include "TstVGeometry.hh"

class VGM::IFactory;
class VGM::IVolume;

class TstGeometryViaVGM : public TstVGeometry 
{
  public:
    TstGeometryViaVGM(VGM::IFactory* factory);
    virtual ~TstGeometryViaVGM();

    virtual void  DefineMaterials();
    
    virtual void* TestSolids(bool fullPhi);
    virtual void* TestPlacements();
    virtual void* TestReflections(bool fullPhi);
    virtual void* TestAssemblies();
    virtual void* TestAssemblies2();
    virtual void* TestBooleanSolids1();
    virtual void* TestBooleanSolids2();
    virtual void* TestBooleanSolids3();

  private:
    // methods
    VGM::IVolume* CreateWorld();
    VGM::IVolume* CreateBox();
    VGM::IVolume* CreateCons(double sphi, double dphi);
    VGM::IVolume* CreateEllipticalTube();
    VGM::IVolume* CreatePara();
    VGM::IVolume* CreatePolycone(double sphi, double dphi);
    VGM::IVolume* CreatePolyhedra(double sphi, double dphi);
    VGM::IVolume* CreateSphere(double sphi, double dphi);
    VGM::IVolume* CreateTorus(double sphi, double dphi);
    VGM::IVolume* CreateTrap();
    VGM::IVolume* CreateTrd();
    VGM::IVolume* CreateTubs(double sphi, double dphi);
    VGM::IVolume* CreateCtubs(double sphi, double dphi);
    void* PlaceSolids(VGM::IVolume* mother,
                      bool fullPhi, bool reflect, double zpos);
 
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

