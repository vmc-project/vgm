// $Id$
//
// Class TstGeometryViaVGM
// ---------------
// The test for solids construction
//
// Author: Ivana Hrivnacova; IPN Orsay

// $Id$
// GEANT4 tag $Name$

//#include <iomanip>

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"

#include "TstGeometryViaVGM.hh"
#include "TstParameters.hh"

using namespace VGM;

//_____________________________________________________________________________
TstGeometryViaVGM::TstGeometryViaVGM(IFactory* factory)
  : TstVGeometry(),
    fFactory(factory)
{
//
}  

//_____________________________________________________________________________
TstGeometryViaVGM::~TstGeometryViaVGM()
{
}

//
// private methods
// 

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateWorld()
{
// Create world volume
// ---
  
  double wSize = TstParameters::WorldLength();
  ISolid* worldS
    = fFactory->CreateBox("worldS", wSize, wSize, wSize);

  return fFactory->CreateVolume("worldV", worldS, "Basic");
}    

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateBox()
{
  ISolid* boxS
    = fFactory->CreateBox("boxS", 20.*cm, 60.*cm, 50.*cm);
  
  return fFactory->CreateVolume("boxV", boxS, "Basic");
}  


//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateCons(double sphi, double dphi)
{
  ISolid* consS
    = fFactory->CreateCons("consS", 10.*cm, 40.*cm, 20.*cm, 60.*cm, 50*cm,
                          sphi, dphi);
  
  return fFactory->CreateVolume("consV", consS, "Basic");
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreatePara()
{
  ISolid* paraS
    = fFactory->CreatePara("paraS", 40.*cm, 60.*cm, 50.*cm, 
                           30.*deg, 30.*deg, 30.*deg);

  return fFactory->CreateVolume("paraV", paraS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreatePolycone(double sphi, double dphi)
{
  // Define parameters

  int nofPlanes = 3;
  double z[3];
  double rin[3];
  double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 50.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 30.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 60.*cm;
  
  ISolid* pconeS
    = fFactory->CreatePolycone("pconeS", sphi, dphi, nofPlanes, z, rin, rout);
  
  return fFactory->CreateVolume("pconeV", pconeS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreatePolyhedra(double sphi, double dphi)
{
  // Define parameters

  int nofSides = 4;
  int nofPlanes = 3;
  double z[3];
  double rin[3];
  double rout[3];

  z[0] = -50.*cm;
  rin[0] = 10.*cm;
  rout[0] = 40.*cm;
  
  z[1] = 10.*cm;
  rin[1] = 20.*cm;
  rout[1] = 20.*cm;
  
  z[2] = 40.*cm;
  rin[2] = 30.*cm;
  rout[2] = 50.*cm;
  

  ISolid* phedraS
    = fFactory->CreatePolyhedra("phedraS", sphi, dphi, 
                           nofSides, nofPlanes, z, rin, rout);

  return fFactory->CreateVolume("phedraV", phedraS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateSphere(double sphi, double dphi)
{
  ISolid* sphereS1
    = fFactory->CreateSphere("sphereS", 20.*cm, 60.*cm,
                            sphi, dphi, sphi/2., dphi/2.); 
			    
  return fFactory->CreateVolume("sphereV1", sphereS1, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTorus(double sphi, double dphi)
{
  ISolid* torusS
    = fFactory->CreateTorus("torusS", 20.*cm, 30.*cm, 40.*cm,
                            sphi, dphi);
			    
  return fFactory->CreateVolume("torusV", torusS, "Basic");  
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTrap()
{
  ISolid* trapS
    = fFactory->CreateTrap("trapS", 30.*cm, 25.*deg, 35.*deg,
		          20.*cm, 10.*cm, 15.*cm, 0.*deg,
		          20.*cm, 10.*cm, 15.*cm, 0.*deg);
  return fFactory->CreateVolume("trapV", trapS, "Basic");
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTrd()
{
  ISolid* trdS
    = fFactory->CreateTrd("trdS", 20.*cm, 30*cm, 40.*cm, 50.*cm, 50.*cm);

  return fFactory->CreateVolume("trdV", trdS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTubs(double sphi, double dphi)
{
  ISolid* tubsS
    = fFactory->CreateTubs("tubsS", 20.*cm, 40*cm, 50.*cm, sphi, dphi);

  return fFactory->CreateVolume("tubsV", tubsS, "Basic");
}  
 
//_____________________________________________________________________________
void* TstGeometryViaVGM::PlaceSolids(IVolume* mother,
                                     bool fullPhi, bool reflect, double zpos)
{
  double sphi =   0.*deg;
  double dphi = 360.*deg;
  if (!fullPhi) {
    sphi = 45.*deg;
    dphi = 90.*deg;
  }  
 
  int counter = 0;
  double wSize = TstParameters::WorldLength();
  double dz = wSize/6.;
  double dy = wSize/4.;
  
  HepReflectZ3D reflect3D;
 
  // Box
  //
  IVolume* boxV = CreateBox();
  fFactory->CreatePlacement("box", 0, boxV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, zpos)); 
  if (reflect)
    fFactory->CreatePlacement("box", 0, boxV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D); 

  // Cons 
  //
  IVolume* consV = CreateCons(sphi, dphi);
  fFactory->CreatePlacement("cons", 0, consV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("cons", 0, consV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D);

  // Para
  //
  IVolume* paraV = CreatePara();
  fFactory->CreatePlacement("para", 0, paraV, mother, 
                  HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("para", 0, paraV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D);
  
  // Polycone
  //
  IVolume* pconeV = CreatePolycone(sphi, dphi);
  fFactory->CreatePlacement("pcone", 0, pconeV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("pcone", 0, pconeV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D);

  // Polyhedra
  //
  IVolume* phedraV = CreatePolyhedra(sphi, dphi);
  fFactory->CreatePlacement("phedra", 0, phedraV, mother, 
                  HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("phedra", 0, phedraV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D);

  // Sphere 
  //
  IVolume* sphereV = CreateSphere(sphi, dphi);
  fFactory->CreatePlacement("sphere", 0, sphereV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("sphere", 0, sphereV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D);

  // Torus
  //
  IVolume* torusV = CreateTorus(sphi, dphi);
  fFactory->CreatePlacement("torus", 0, torusV, mother, 
                  HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("torus", 0, torusV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D);

  // Trap 
  //
  IVolume* trapV = CreateTrap();
  fFactory->CreatePlacement("trap", 0, trapV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("trap", 0, trapV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D);

  // Trd
  //
  IVolume* trdV = CreateTrd();
  fFactory->CreatePlacement("trd", 0, trdV, mother, 
                  HepTranslate3D(-wSize + (++counter)*dz,  -dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("trd", 0, trdV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D);
 
  // Trd
  //
  IVolume* tubsV = CreateTubs(sphi, dphi);
  fFactory->CreatePlacement("tubs", 0, tubsV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, zpos));
  if (reflect)
    fFactory->CreatePlacement("tubs", 0, tubsV, mother, 
                  HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D);

  return (void*) fFactory->Top();
 }

//
// public methods
// 

//_____________________________________________________________________________
void  TstGeometryViaVGM::DefineMaterials()
{
  // Get material factory
  IMaterialFactory* materialFactory = fFactory->MaterialFactory();

  // create elements
  double z, a, density, radlen, intlen; 
  IElement* elVacuum
    = materialFactory->CreateElement(" ",  "Vacuum",    z=1.,  a= 1.01*g/mole);
  IElement* elN
    = materialFactory->CreateElement("N",  "Nitrogen",  z=7.,  a=14.01*g/mole);
  IElement* elO
    = materialFactory->CreateElement("O",  "Oxygen",    z=8.,  a=16.00*g/mole);
  IElement* elAl
    = materialFactory->CreateElement("Al", "Aluminium", z=13., a=26.98*g/mole);


  // simple material (Al)
  //
  IMaterial* basic 
    = materialFactory
      ->CreateMaterial("Basic", density=2.700*g/cm3, elAl, radlen=0., intlen=0.);

  // compound/mixture material
  //
  density = 1.290*mg/cm3;
  ElementVector elements;
  MassFractionVector fractions;
  elements.push_back(elN);
  fractions.push_back(0.7);
  elements.push_back(elO);
  fractions.push_back(0.3);
    
  IMaterial* air 
    = materialFactory
      ->CreateMaterial("Air", density= 1.290*mg/cm3, elements, fractions);

  // vacuum
  //
  IMaterial* vacuum
    = materialFactory
      ->CreateMaterial("Vacuum", density = universe_mean_density,
                       elVacuum, radlen=0., intlen=0.);

  // Cannont pass state, pressure, temperature:
  //                kStateGas, 3.e-18*pascal, 2.73*kelvin
  // TO DO: to be improved later

  // define tracking media
  // with no parameters specified
  materialFactory->CreateMedium("Basic", 1, basic, 0, 0); 
  materialFactory->CreateMedium("Air",   1, air, 0, 0); 
  materialFactory->CreateMedium("Vacuum",1, vacuum, 0, 0); 
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestSolids(bool fullPhi)
{
  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
  
  PlaceSolids(worldV, fullPhi, false, 0.);

  return (void*) fFactory->Top();
 }

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestPlacements()
{
  // World
  //
  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
    
  // Big box A
  //
  ISolid * boxA
    = fFactory->CreateBox("boxA", 20.*cm, 60.*cm, 50.*cm);
  IVolume* volA
    = fFactory->CreateVolume("volA", boxA, "Basic");
  
  // Thick layer B (in A)
  //
  ISolid * boxB
    = fFactory->CreateBox("boxB", 20.*cm, 10.*cm, 50.*cm);
  IVolume * volB
    = fFactory->CreateVolume("volB", boxB, "Basic");

  // Thin layer C (in B)
  //
  ISolid * boxC
    = fFactory->CreateBox("boxC", 20.*cm, 0.2*cm, 50.*cm);
  IVolume * volC
    = fFactory->CreateVolume("volC", boxC, "Basic");

  // Place layers B   
  //
  //fFactory->CreateMultiplePlacement("layerB", volB, volA, 
  //                                 VGM::kYAxis, 6, 20.*mm, 0.);
             // division in the whole mother

  fFactory->CreateMultiplePlacement("layerB", volB, volA, 
                                   VGM::kYAxis, 3, 20.*cm, 60.*cm);
             // division with offset

	// If layers C placed first, they are not passed
	// in a new TGeo Volume if running with Root.
	// To be improved later.

  // Place layers C
  //
  fFactory->CreatePlacement("layerC", 0, volC, volB,  
                            0, Hep3Vector(0.,  9.8*cm, 0.));
  fFactory->CreatePlacement("layerC", 1, volC, volB, 
                            0, Hep3Vector(0., -9.8*cm, 0.));


  // Placements of A in a circle
  //
  for (int i=0; i<24; i++) {
   
     double x0 = 5. *m;
     double y0 = 0. *m;
     double dphi = 15.*deg;

     double phi = dphi*(i+1);
     double x = x0*cos(phi);
     double z = x0*sin(phi);

     HepRotation* rot = new HepRotation();
     rot->rotateY(phi);
     
     fFactory->CreatePlacement("layerA", i, volA, worldV,
                               rot, Hep3Vector(x, y0, z));
   }
   
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestReflections(bool fullPhi)
{
  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
  
  PlaceSolids(worldV, fullPhi, true, 1.*m);

  return (void*) fFactory->Top();
 }

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids1()
{
// Only translation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.*cm, 50.*cm, 50.*cm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                         10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV, 
                   0, Hep3Vector(-wSize/8., 0., -2.*m));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                   0, Hep3Vector( wSize/8., 0., -2.*m));


  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
                   0, Hep3Vector(-wSize/4., 0., 2.*m));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                   0, Hep3Vector(0., 0., 2.*m));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, 0, Hep3Vector(20.*cm, 0., 0.)); 
  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                   0, Hep3Vector( wSize/4., 0., 2.*m));
  
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids2()
{
// Translation + rotation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.*cm, 50.*cm, 50.*cm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                         10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV, 
                   0, Hep3Vector(-wSize/8., 0., -2.*m));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                   0, Hep3Vector( wSize/8., 0., -2.*m));


  // Define displacement transformations
  //
 
  // Rotate solid1  
  HepRotation* rot1 = new HepRotation();
  rot1->rotateY(-45.*deg);

  // Rotate + translate solid2
  //
  HepRotation* rot2 = new HepRotation();
  rot2->rotateX(-30.*deg);
  rot2->rotateY(45.*deg); 
       // apply inverse rotation to solid1 rotation
       // as this one will be applied with placement
  Hep3Vector tr2 = Hep3Vector(20.*cm, 0., 0.);
  
  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, rot2, tr2); 
  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
                   rot1, Hep3Vector(-wSize/4., 0., 2.*m));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, rot2, tr2); 
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                   rot1, Hep3Vector(0., 0., 2.*m));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, rot2, tr2); 
  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                   rot1, Hep3Vector( wSize/4., 0., 2.*m));
  
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids3()
{
// Translation + rotation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, 0, Hep3Vector());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.*cm, 50.*cm, 50.*cm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                         10.*cm, 30.*cm, 20.*cm, 40.*cm, 100.*cm, 0., 360.*deg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV, 
                   0, Hep3Vector(-wSize/8., 0., -2.*m));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                   0, Hep3Vector( wSize/8., 0., -2.*m));


  // Define displacement transformations
  //
 
  // Rotate solid1  
  HepRotation* rot1 = new HepRotation();
  rot1->rotateY(-45.*deg);

  // Rotate + translate solid2
  //
  HepReflectZ3D reflect2 = HepReflectZ3D();
  HepTranslate3D translate2 = HepTranslate3D(20.*cm, 0., 0.);
  HepRotate3D  rotInv1 =  HepRotateY3D(-45.*deg);
         // the same angle as in rot1 as in 3D transform we pass
	 // object rotations and not frame rotations
  HepTransform3D transform2 =  rotInv1 * translate2 * reflect2;
  
  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, transform2); 
  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
                   rot1, Hep3Vector(-wSize/4., 0., 2.*m));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, transform2); 
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                   rot1, Hep3Vector(0., 0., 2.*m));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, transform2); 
  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                   rot1, Hep3Vector( wSize/4., 0., 2.*m));
  
  return (void*) fFactory->Top();
  return 0;
}


