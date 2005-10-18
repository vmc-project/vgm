// $Id$
//
// Class TstGeometryViaVGM
// ---------------
// The test for solids construction
//
// Author: Ivana Hrivnacova; IPN Orsay


#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/Transform3D.h"

#include "VGM/materials/IMaterialFactory.h"
#include "VGM/volumes/IFactory.h"
#include "VGM/volumes/IVolume.h"

#include "ClhepVGM/transform.h"
#include "ClhepVGM/Units.h"

#include "TstGeometryViaVGM.hh"
#include "TstParameters.hh"

using namespace VGM;

//_____________________________________________________________________________
TstGeometryViaVGM::TstGeometryViaVGM(IFactory* factory)
  : TstVGeometry(),
    fFactory(factory),
    fCm(ClhepVGM::Units::Length(cm)),
    fDeg(ClhepVGM::Units::Angle(deg)),
    fGcm3(ClhepVGM::Units::MassDensity(g/cm3)),
    fGmole(ClhepVGM::Units::AtomicWeight(g/mole))
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
    = fFactory->CreateBox("boxS", 20. * fCm, 60.* fCm, 50.* fCm);
  
  return fFactory->CreateVolume("boxV", boxS, "Basic");
}  


//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateCons(double sphi, double dphi)
{
  ISolid* consS
    = fFactory->CreateCons("consS", 
                           10.* fCm, 40.* fCm, 20.* fCm, 60.* fCm, 50* fCm,
                           sphi, dphi);
  
  return fFactory->CreateVolume("consV", consS, "Basic");
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateEllipticalTube()
{
  ISolid* eltuS
    = fFactory->CreateEllipticalTube("eltuS", 20.* fCm, 50.* fCm, 50* fCm);
  
  return fFactory->CreateVolume("eltuV", eltuS, "Basic");
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreatePara()
{
  ISolid* paraS
    = fFactory->CreatePara("paraS", 40.* fCm, 60.* fCm, 50.* fCm, 
                           30.* fDeg, 30.* fDeg, 30.* fDeg);

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

  z[0] = -50.* fCm;
  rin[0] = 10.* fCm;
  rout[0] = 50.* fCm;
  
  z[1] = 10.* fCm;
  rin[1] = 20.* fCm;
  rout[1] = 30.* fCm;
  
  z[2] = 40.* fCm;
  rin[2] = 30.* fCm;
  rout[2] = 60.* fCm;
  
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

  z[0] = -50.* fCm;
  rin[0] = 10.* fCm;
  rout[0] = 40.* fCm;
  
  z[1] = 10.* fCm;
  rin[1] = 20.* fCm;
  rout[1] = 20.* fCm;
  
  z[2] = 40.* fCm;
  rin[2] = 30.* fCm;
  rout[2] = 50.* fCm;
  

  ISolid* phedraS
    = fFactory->CreatePolyhedra("phedraS", sphi, dphi, 
                           nofSides, nofPlanes, z, rin, rout);

  return fFactory->CreateVolume("phedraV", phedraS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateSphere(double sphi, double dphi)
{
  ISolid* sphereS1
    = fFactory->CreateSphere("sphereS", 20.* fCm, 60.* fCm,
                            sphi, dphi, sphi/2., dphi/2.); 
			    
  return fFactory->CreateVolume("sphereV1", sphereS1, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTorus(double sphi, double dphi)
{
  ISolid* torusS
    = fFactory->CreateTorus("torusS", 20.* fCm, 30.* fCm, 40.* fCm,
                            sphi, dphi);
			    
  return fFactory->CreateVolume("torusV", torusS, "Basic");  
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTrap()
{
  ISolid* trapS
    = fFactory->CreateTrap("trapS", 30.* fCm, 25.* fDeg, 35.* fDeg,
  		          20.* fCm, 10.* fCm, 15.* fCm, 0.* fDeg,
  		          20.* fCm, 10.* fCm, 15.* fCm, 0.* fDeg);

  return fFactory->CreateVolume("trapV", trapS, "Basic");
}

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTrd()
{
  ISolid* trdS
    = fFactory->CreateTrd("trdS", 20.* fCm, 30* fCm, 40.* fCm, 50.* fCm, 50.* fCm);

  return fFactory->CreateVolume("trdV", trdS, "Basic");
}  

//_____________________________________________________________________________
IVolume* TstGeometryViaVGM::CreateTubs(double sphi, double dphi)
{
  ISolid* tubsS
    = fFactory->CreateTubs("tubsS", 20.* fCm, 40* fCm, 50.* fCm, sphi, dphi);

  return fFactory->CreateVolume("tubsV", tubsS, "Basic");
}  
 
//_____________________________________________________________________________
void* TstGeometryViaVGM::PlaceSolids(IVolume* mother,
                                     bool fullPhi, bool reflect, double zpos)
{
  double sphi =   0.* fDeg;
  double dphi = 360.* fDeg;
  if (!fullPhi) {
    sphi = 45.* fDeg;
    dphi = 90.* fDeg;
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
                  ClhepVGM::Transform(
		    HepTranslate3D(-wSize + (counter)*dz,  -dy, zpos))); 
  if (reflect)
    fFactory->CreatePlacement("box", 0, boxV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  -dy, -zpos) * reflect3D)); 

  // Cons 
  //
  IVolume* consV = CreateCons(sphi, dphi);
  fFactory->CreatePlacement("cons", 0, consV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("cons", 0, consV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, dy, -zpos) * reflect3D));

  // Elliptical tube 
  //
  IVolume* eltuV = CreateEllipticalTube();
  fFactory->CreatePlacement("eltu", 0, eltuV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (++counter)*dz, -dy, zpos)));
  if (reflect)
  fFactory->CreatePlacement("cons", 0, eltuV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, -dy, -zpos) * reflect3D));

  // Para
  //
  IVolume* paraV = CreatePara();
  fFactory->CreatePlacement("para", 0, paraV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("para", 0, paraV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, -zpos) * reflect3D));
  
  // Polycone
  //
  IVolume* pconeV = CreatePolycone(sphi, dphi);
  fFactory->CreatePlacement("pcone", 0, pconeV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (++counter)*dz, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("pcone", 0, pconeV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, -dy, -zpos) * reflect3D));

  // Polyhedra
  //
  IVolume* phedraV = CreatePolyhedra(sphi, dphi);
  fFactory->CreatePlacement("phedra", 0, phedraV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("phedra", 0, phedraV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, -zpos) * reflect3D));

  // Sphere 
  //
  IVolume* sphereV = CreateSphere(sphi, dphi);
  fFactory->CreatePlacement("sphere", 0, sphereV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (++counter)*dz, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("sphere", 0, sphereV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, -dy, -zpos) * reflect3D));

  // Torus
  //
  IVolume* torusV = CreateTorus(sphi, dphi);
  fFactory->CreatePlacement("torus", 0, torusV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("torus", 0, torusV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, -zpos) * reflect3D));

  // Trap 
  //
  IVolume* trapV = CreateTrap();
  fFactory->CreatePlacement("trap", 0, trapV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (++counter)*dz, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("trap", 0, trapV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, -dy, -zpos) * reflect3D));

  // Trd
  //
  IVolume* trdV = CreateTrd();
  fFactory->CreatePlacement("trd", 0, trdV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("trd", 0, trdV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz,  dy, -zpos) * reflect3D));
 
  // Trd
  //
  IVolume* tubsV = CreateTubs(sphi, dphi);
  fFactory->CreatePlacement("tubs", 0, tubsV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (++counter)*dz, -dy, zpos)));
  if (reflect)
    fFactory->CreatePlacement("tubs", 0, tubsV, mother, 
                  ClhepVGM::Transform(
                    HepTranslate3D(-wSize + (counter)*dz, -dy, -zpos) * reflect3D));

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
    = materialFactory->CreateElement(" ",  "Vacuum",    z=1.,  a= 1.01 * fGmole);
  IElement* elN
    = materialFactory->CreateElement("N",  "Nitrogen",  z=7.,  a=14.01 * fGmole);
  IElement* elO
    = materialFactory->CreateElement("O",  "Oxygen",    z=8.,  a=16.00 * fGmole);
  IElement* elAl
    = materialFactory->CreateElement("Al", "Aluminium", z=13., a=26.98 * fGmole);


  // simple material (Al)
  //
  IMaterial* basic 
    = materialFactory
      ->CreateMaterial("Basic", density=2.700* fGcm3, elAl, radlen=0., intlen=0.);

  // compound/mixture material
  //
  density = 1.290 * ClhepVGM::Units::MassDensity(mg/cm3);
  ElementVector elements;
  MassFractionVector fractions;
  elements.push_back(elN);
  fractions.push_back(0.7);
  elements.push_back(elO);
  fractions.push_back(0.3);
    
  IMaterial* air 
    = materialFactory
      ->CreateMaterial("Air", density, elements, fractions);

  // vacuum
  //
  density = universe_mean_density / (g/cm3) * fGcm3;
  IMaterial* vacuum
    = materialFactory
      ->CreateMaterial("Vacuum", density, elVacuum, radlen=0., intlen=0.);

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
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
  
  PlaceSolids(worldV, fullPhi, false, 0.);

  return (void*) fFactory->Top();
 }

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestPlacements()
{
  // World
  //
  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
    
  // Big box A
  //
  ISolid * boxA
    = fFactory->CreateBox("boxA", 20.* fCm, 60.* fCm, 50.* fCm);
  IVolume* volA
    = fFactory->CreateVolume("volA", boxA, "Basic");
  
  // Thick layer B (in A)
  //
  ISolid * boxB
    = fFactory->CreateBox("boxB", 20.* fCm, 10.* fCm, 50.* fCm);
  IVolume * volB
    = fFactory->CreateVolume("volB", boxB, "Basic");

  // Thin layer C (in B)
  //
  ISolid * boxC
    = fFactory->CreateBox("boxC", 20.* fCm, 0.2* fCm, 50.* fCm);
  IVolume * volC
    = fFactory->CreateVolume("volC", boxC, "Basic");

  // Place layers B   
  //
  //fFactory->CreateMultiplePlacement("layerB", volB, volA, 
  //                                 VGM::kYAxis, 6, 20.*mm, 0.);
             // division in the whole mother

  fFactory->CreateMultiplePlacement("layerB", volB, volA, 
                                   VGM::kYAxis, 3, 20.* fCm, 60.* fCm);
             // division with offset

	// If layers C placed first, they are not passed
	// in a new TGeo Volume if running with Root.
	// To be improved later.

  // Place layers C
  //
  fFactory->CreatePlacement("layerC", 0, volC, volB,  
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector(0.,  9.8* fCm, 0.)));

  fFactory->CreatePlacement("layerC", 1, volC, volB, 
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector(0., -9.8* fCm, 0.)));


  // Placements of A in a circle
  //
  for (int i=0; i<24; i++) {
   
     double x0 = 5. *m;
     double y0 = 0. *m;
     double dphi = 15.* deg;
         // use directly CLHEP units when using CLHEP rotations

     double phi = dphi*(i+1);
     double x = x0*cos(phi);
     double z = x0*sin(phi);

     HepRotation rot;
     rot.rotateY(-phi);
        // !!! Different meaning of rotation in VGM than in Geant4 
     
     fFactory->CreatePlacement("layerA", i, volA, worldV,
                               ClhepVGM::Transform(rot, Hep3Vector(x, y0, z)));
   }
   
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestReflections(bool fullPhi)
{
  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
  
  PlaceSolids(worldV, fullPhi, true, 100.* fCm);

  return (void*) fFactory->Top();
 }

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestAssemblies()
{
  std::cout << "TestAssemblies: not available via VGM" << std::endl;

  return 0;
 }

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids1()
{
// Only translation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.* fCm, 50.* fCm, 50.* fCm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                          10.* fCm, 30.* fCm, 20.* fCm, 40.* fCm, 100.* fCm, 
			  0., 360.* fDeg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV, 
                   ClhepVGM::Transform( 
		     HepRotation(), Hep3Vector(-wSize/8., 0., -200.* fCm)));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector( wSize/8., 0., -200.* fCm)));


  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, 
		   ClhepVGM::Transform(
		     HepRotation(),Hep3Vector(20.* fCm, 0., 0.))); 

  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
		   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector(-wSize/4., 0., 200.* fCm)));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, 
                   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector(20.* fCm, 0., 0.))); 
				       
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector(0., 0., 200.* fCm)));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, 
                   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector(20.* fCm, 0., 0.))); 
  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                   ClhepVGM::Transform(
		     HepRotation(), Hep3Vector( wSize/4., 0., 200.* fCm)));
  
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids2()
{
// Translation + rotation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.* fCm, 50.* fCm, 50.* fCm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                         10.* fCm, 30.* fCm, 20.* fCm, 40.* fCm, 100.* fCm, 
			 0., 360.* fDeg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV,
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector(-wSize/8., 0., -200.* fCm)));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector( wSize/8., 0., -200.* fCm)));


  // Define displacement transformations
  //
 
  // Rotate solid1  
  HepRotation rot1;
  rot1.rotateY(45.* deg);

  // Rotate + translate solid2
  //
  HepRotation rot2;
  rot2.rotateX( 30.* deg);
  rot2.rotateY(-45.* deg); 
  Hep3Vector tr2 = Hep3Vector(20.* fCm, 0., 0.);
  
  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, 
		  ClhepVGM::Transform(rot2,tr2)); 
  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector(-wSize/4., 0., 200.* fCm)));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, 
		  ClhepVGM::Transform(rot2, tr2)); 
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector(0., 0., 200.* fCm)));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, 
		  ClhepVGM::Transform(rot2, tr2)); 
  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector( wSize/4., 0., 200.* fCm)));
  
  return (void*) fFactory->Top();
}

//_____________________________________________________________________________
void* TstGeometryViaVGM::TestBooleanSolids3()
{
// Translation + rotation in solid displacement

  double wSize = TstParameters::WorldLength();

  IVolume* worldV = CreateWorld();
  fFactory->CreatePlacement("world", 0, worldV, 0, ClhepVGM::Identity());
  
  // Create solids
  ISolid* solid1 
    = fFactory->CreateBox("boxS", 50.* fCm, 50.* fCm, 50.* fCm);

  ISolid* solid2 
    = fFactory->CreateCons("consS", 
                         10.* fCm, 30.* fCm, 20.* fCm, 40.* fCm, 100.* fCm, 
			 0., 360.* fDeg) ;
    
  // Simple solids placed for a control
  //
  IVolume* volume1
    = fFactory->CreateVolume("volume1", solid1, "Basic");
  fFactory->CreatePlacement("solid1", 0, volume1, worldV, 
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector(-wSize/8., 0., -200.* fCm)));

  IVolume* volume2
    = fFactory->CreateVolume("volume2", solid2, "Basic");
  fFactory->CreatePlacement("solid2", 0, volume2, worldV, 
                            ClhepVGM::Transform(
			      HepRotation(), Hep3Vector( wSize/8., 0., -200.* fCm)));


  // Define displacement transformations
  //
 
  // Rotate solid1  
  HepRotation rot1;
  rot1.rotateY( 45.* deg);

  // Rotate + translate solid2
  //
  HepReflectZ3D reflect2 = HepReflectZ3D();
  HepTranslate3D translate2 = HepTranslate3D(20.* fCm, 0., 0.);
  HepRotate3D  rotInv1 =  HepRotateY3D( -45.* deg);
  HepTransform3D transform2 =  rotInv1 * translate2 * reflect2;
  
  // Intersection
  //
  ISolid* intersectionS
    = fFactory->CreateIntersectionSolid(
                  "solid1Isolid2S", solid1, solid2, 
		  ClhepVGM::Transform(transform2)); 
  IVolume* intersectionV
    = fFactory->CreateVolume("solid1Isolid2V", intersectionS, "Basic");

  fFactory->CreatePlacement("solid1Isolid2", 0, intersectionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector(-wSize/4., 0., 200.* fCm)));
  
  // Subtraction
  //
  ISolid* subtractionS
    = fFactory->CreateSubtractionSolid(
                  "solid1Ssolid2S", solid1, solid2, 
		  ClhepVGM::Transform(transform2)); 
  IVolume* subtractionV
    = fFactory->CreateVolume("solid1Ssolid2V", subtractionS, "Basic");

  fFactory->CreatePlacement("solid1Ssolid2", 0, subtractionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector(0., 0., 200.* fCm)));
  
  // Union
  //
  ISolid* unionS
    = fFactory->CreateUnionSolid(
                  "solid1Usolid2S", solid1, solid2, 
		  ClhepVGM::Transform(transform2)); 

  IVolume* unionV
    = fFactory->CreateVolume("solid1Usolid2V", unionS, "Basic");

  fFactory->CreatePlacement("solid1Usolid2", 0, unionV, worldV, 
                            ClhepVGM::Transform(
			      rot1, Hep3Vector( wSize/4., 0., 200.* fCm)));
  
  return (void*) fFactory->Top();
  return 0;
}


