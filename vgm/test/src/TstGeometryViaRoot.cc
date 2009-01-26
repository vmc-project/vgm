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

#include <iomanip>
#include <vector>

#include "Riostream.h"
#include "TMath.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoNode.h"
#include "TGeoMatrix.h"
#include "TGeoCompositeShape.h"
#include "TGeoArb8.h"
#include "TGeoBBox.h"
#include "TGeoCone.h"
#include "TGeoEltu.h"
#include "TGeoPara.h"
#include "TGeoPcon.h"
#include "TGeoPgon.h"
#include "TGeoSphere.h"
#include "TGeoTorus.h"
#include "TGeoTrd2.h"
#include "TGeoTube.h"
#include "TGeoXtru.h"

#include "TstGeometryViaRoot.hh"

//_____________________________________________________________________________
TstGeometryViaRoot::TstGeometryViaRoot()
  : TstVGeometry(),
    fBasicMedium(0)
{
//
  fGeoManager =   new TGeoManager("Test", "Test geometry via Root");
}  

//_____________________________________________________________________________
TstGeometryViaRoot::~TstGeometryViaRoot()
{
  delete fGeoManager;
}

//
// private methods
// 

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateWorld(Double_t x, Double_t y, Double_t z)
{
// Create world volume
// ---
  
  if (!fBasicMedium)
    fBasicMedium =  fGeoManager->GetMedium("Basic"); 

  TGeoShape* worldS
    = new TGeoBBox("worldS", x, y, z);

  TGeoVolume* worldV
    = new TGeoVolume("world", worldS, fBasicMedium);
  
  fGeoManager->SetTopVolume(worldV);
  
  return worldV;
}    

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateNewSolid()
{
  return CreateExtrudedSolid2();
}  


//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateArb8()
{
  TGeoArb8* arb8S = new TGeoArb8("arb8S", 75.0);
  arb8S->SetVertex(0,  45., -15.);
  arb8S->SetVertex(1,   0., -75.);
  arb8S->SetVertex(2, -30., -75.);
  arb8S->SetVertex(3,  15., -15.);
  arb8S->SetVertex(4,  45., -15.);
  arb8S->SetVertex(5,   0., -75.);
  arb8S->SetVertex(6, -30., -75.);
  arb8S->SetVertex(7,  15., -15.);

  std::cout << "Is twisted: " << arb8S->IsTwisted() << std::endl;
  return new TGeoVolume("arb8", arb8S, fBasicMedium);
}  

//_____________________________________________________________________________
void TstGeometryViaRoot::CreateArb8Solids(std::vector<TGeoVolume*>& volumes)
{
  // 1 down vertex: 0=1=2=3
  TGeoArb8* arbS1 = new TGeoArb8("arbS1", 75.0);
  arbS1->SetVertex(0,  45., -15.);
  arbS1->SetVertex(1,  45., -15.);
  arbS1->SetVertex(2,  45., -15.);
  arbS1->SetVertex(3,  45., -15.);
  arbS1->SetVertex(4,  45., -15.);
  arbS1->SetVertex(5,   0., -75.);
  arbS1->SetVertex(6, -30., -75.);
  arbS1->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb1", arbS1, fBasicMedium));

  // 2 down vertices: 0=1 2=3
  TGeoArb8* arbS2 = new TGeoArb8("arbS2", 75.0);
  arbS2->SetVertex(0,   0., -75.);
  arbS2->SetVertex(1,   0., -75.);
  arbS2->SetVertex(2, -30., -75.);
  arbS2->SetVertex(3, -30., -75.);
  arbS2->SetVertex(4,  45., -15.);
  arbS2->SetVertex(5,   0., -75.);
  arbS2->SetVertex(6, -30., -75.);
  arbS2->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb2", arbS2, fBasicMedium));

  // 1 up vertex: 4=5=6=7
  TGeoArb8* arbS3 = new TGeoArb8("arbS3", 75.0);
  arbS3->SetVertex(0,  45., -15.);
  arbS3->SetVertex(1,   0., -75.);
  arbS3->SetVertex(2, -30., -75.);
  arbS3->SetVertex(3,  15., -15.);
  arbS3->SetVertex(4,  45., -15.);
  arbS3->SetVertex(5,  45., -15.);
  arbS3->SetVertex(6,  45., -15.);
  arbS3->SetVertex(7,  45., -15.);
  volumes.push_back(new TGeoVolume("arb3", arbS3, fBasicMedium));
 
  // 2 up vertices: 4=5 6=7
  TGeoArb8* arbS4 = new TGeoArb8("arbS4", 75.0);
  arbS4->SetVertex(0,  45., -15.);
  arbS4->SetVertex(1,   0., -75.);
  arbS4->SetVertex(2, -30., -75.);
  arbS4->SetVertex(3,  15., -15.);
  arbS4->SetVertex(4,   0., -75.);
  arbS4->SetVertex(5,   0., -75.);
  arbS4->SetVertex(6, -30., -75.);
  arbS4->SetVertex(7, -30., -75.);
  volumes.push_back(new TGeoVolume("arb4", arbS4, fBasicMedium));

  // 1 down vertex: 0=1=2=3
  // 3 up vertices: 4=5
  TGeoArb8* arbS5 = new TGeoArb8("arbS5", 75.0);
  arbS5->SetVertex(0,  45., -15.);
  arbS5->SetVertex(1,  45., -15.);
  arbS5->SetVertex(2,  45., -15.);
  arbS5->SetVertex(3,  45., -15.);
  arbS5->SetVertex(4,  45., -15.);
  arbS5->SetVertex(4,   0., -75.);
  arbS5->SetVertex(5,   0., -75.);
  arbS5->SetVertex(6, -30., -75.);
  arbS5->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb5", arbS5, fBasicMedium));

  // 3 down vertices: 0=1 
  // 1 up vertex: 4=5=6=7
  TGeoArb8* arbS6 = new TGeoArb8("arbS6", 75.0);
  arbS6->SetVertex(0,  45., -15.);
  arbS6->SetVertex(1,  45., -15.);
  arbS6->SetVertex(2, -30., -75.);
  arbS6->SetVertex(3,  15., -15.);
  arbS6->SetVertex(4,  45., -15.);
  arbS6->SetVertex(5,  45., -15.);
  arbS6->SetVertex(6,  45., -15.);
  arbS6->SetVertex(7,  45., -15.);
  volumes.push_back(new TGeoVolume("arb6", arbS6, fBasicMedium));

  // all up & down vertices different
  TGeoArb8* arbS7 = new TGeoArb8("arbS7", 75.0);
  arbS7->SetVertex(0,  45., -15.);
  arbS7->SetVertex(1,   0., -75.);
  arbS7->SetVertex(2, -30., -75.);
  arbS7->SetVertex(3,  15., -15.);
  arbS7->SetVertex(4,  45., -15.);
  arbS7->SetVertex(5,   0., -75.);
  arbS7->SetVertex(6, -30., -75.);
  arbS7->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb7", arbS7, fBasicMedium));

/*
  // 3 down vertices: 0=1 (twisted )
  TGeoArb8* arbS3 = new TGeoArb8("arbS3", 75.0);
  arbS3->SetVertex(0,  45., -15.);
  arbS3->SetVertex(1,  45., -15.);
  arbS3->SetVertex(2, -30., -75.);
  arbS3->SetVertex(3,  15., -15.);
  arbS3->SetVertex(4,  45., -15.);
  arbS3->SetVertex(5,   0., -75.);
  arbS3->SetVertex(6, -30., -75.);
  arbS3->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb3", arbS3, fBasicMedium));

  // 3 up vertices: 4=5 (twisted )
  TGeoArb8* arbS6 = new TGeoArb8("arbS6", 75.0);
  arbS6->SetVertex(0,  45., -15.);
  arbS6->SetVertex(1,   0., -75.);
  arbS6->SetVertex(2, -30., -75.);
  arbS6->SetVertex(3,  15., -15.);
  arbS6->SetVertex(4,   0., -75.);
  arbS6->SetVertex(5,   0., -75.);
  arbS6->SetVertex(6, -30., -75.);
  arbS6->SetVertex(7,  15., -15.);
  volumes.push_back(new TGeoVolume("arb3", arbS3, fBasicMedium));
*/
}

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateBox()
{
  TGeoShape* boxS
    = new TGeoBBox("boxS", 20., 60., 50.);
  
  return new TGeoVolume("box", boxS, fBasicMedium);
}  


//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateCons(Double_t sphi, Double_t dphi)
{
  TGeoShape* consS
    = new TGeoConeSeg("consS", 50., 10., 40., 20., 60., sphi, sphi+dphi);
  
  return new TGeoVolume("cons", consS, fBasicMedium);
}

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateEllipticalTube()
{
  TGeoShape* eltuS
    = new TGeoEltu("eltuS", 20., 30., 50.);
  
  return new TGeoVolume("eltu", eltuS, fBasicMedium);
}  


//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateExtrudedSolid1()
{
  Int_t nz = 4;
  TGeoXtru* xtruS = new TGeoXtru(nz);

  Int_t nv = 8;
  Double_t vx[8] = { -30., -30., 30., 30., 15., 15., -15., -15. };
  Double_t vy[8] = { -30.,  30., 30.,-30.,-30,  15.,  15., -30. };
  xtruS->DefinePolygon(nv, vx, vy);

  Double_t vz[4] = { -40., 10., 15., 40. };
  Double_t xoff[4]  = { -20., 0., 0., 20. };
  Double_t yoff[4]  = {  10., 0., 0., 20. };
  Double_t scale[4] = {  1.5, 0.5, 0.7, 0.9 };

  for (Int_t i=0; i<4; i++)
    xtruS->DefineSection(i, vz[i], xoff[i], yoff[i], scale[i]); 

  return new TGeoVolume("xtru1", xtruS, fBasicMedium);
}  
 
//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateExtrudedSolid2()
{

  Int_t nz = 4;
  TGeoXtru* xtruS = new TGeoXtru(nz);

  Int_t nv = 8;
  Double_t vx[8] = { -30., -30., 30., 30., 15., 15., -15., -15. };
  Double_t vy[8] = { -30.,  30., 30.,-30.,-30,  15.,  15., -30. };
  xtruS->DefinePolygon(nv, vx, vy);

  Double_t vz[4] = { -40., 10., 10., 40. };
  Double_t xoff[4]  = { -20., 0., 0., 20. };
  Double_t yoff[4]  = {  10., 0., 0., 20. };
  Double_t scale[4] = {  1.5, 0.5, 0.7, 0.9 };

  for (Int_t i=0; i<4; i++)
    xtruS->DefineSection(i, vz[i], xoff[i], yoff[i], scale[i]); 

  return new TGeoVolume("xtru2", xtruS, fBasicMedium);

/*
  // Test case with wrong conversion (now ok)

  Int_t nz = 2;
  TGeoXtru* xtruS = new TGeoXtru(nz);

  Int_t nv = 12;
  Double_t vx[12];
  Double_t vy[12];
  vx[0] =    -0.70000;  vy[0] =    -0.30000;
  vx[1] =    -0.70000;  vy[1] =     6.55000;
  vx[2] =     0.10000;  vy[2] =     6.55000;
  vx[3] =     0.10000;  vy[3] =     5.90000;
  vx[4] =     5.40000;  vy[4] =     5.90000;
  vx[5] =     5.40000;  vy[5] =     6.55000;
  vx[6] =     6.20000;  vy[6] =     6.55000;
  vx[7] =     6.20000;  vy[7] =    -0.30000;
  vx[8] =     2.65000;  vy[8] =    -0.30000;
  vx[9] =     2.65000;  vy[9] =    -1.00000;
  vx[10] =     1.85000;  vy[10] =    -1.00000;
  vx[11] =     1.85000;  vy[11] =    -0.30000;
  xtruS->DefinePolygon(nv, vx, vy);

  Double_t vz[2] = { -0.025, 0.025 };
  Double_t xoff[2]  = { 0., 0., };
  Double_t yoff[2]  = { 0., 0., };
  Double_t scale[2] = { 1.0, 1.0 };

  for (Int_t i=0; i<2; i++)
    xtruS->DefineSection(i, vz[i], xoff[i], yoff[i], scale[i]); 

  return new TGeoVolume("xtru2", xtruS, fBasicMedium);

  // Test case with wrong conversion (now ok)

  Int_t nz = 2;
  TGeoXtru* xtruS = new TGeoXtru(nz);

  Int_t nv = 12;
  Double_t vx[12] = { -5, -5, -4, -4, 4, 4, 5, 5, 1, 1, -1, -1 };
  Double_t vy[12] = {  1,  5,  5,  4, 4, 5, 5, 1, 1, 0,  0,  1 };
  xtruS->DefinePolygon(nv, vx, vy);

  Double_t vz[2] = { -1, 1 };
  Double_t xoff[2]  = { 0., 0., };
  Double_t yoff[2]  = { 0., 0., };
  Double_t scale[2] = { 1.0, 1.0 };

  for (Int_t i=0; i<2; i++)
    xtruS->DefineSection(i, vz[i], xoff[i], yoff[i], scale[i]); 

  return new TGeoVolume("xtru2", xtruS, fBasicMedium);


  Int_t nz = 2;
  TGeoXtru* xtruS = new TGeoXtru(nz);

  Int_t nv = 36;
  Double_t vx[36];
  Double_t vy[36];
  vx[0] = 0.1*1.25;       vy[0] = 0.1*0;  
  vx[1] = 0.1*1.25;       vy[1] = -0.1*1.25;  
  vx[2] = -0.1*1.25;      vy[2] = -0.1*1.25;  
  vx[3] = -0.1*1.25;      vy[3] = 0.1*1.25;  
  vx[4] = 0.1*1.25;       vy[4] = 0.1*1.25;  
  vx[5] = 0.1*1.25;       vy[5] = 0.1*0;  
  vx[6] = 0.1*1.22268;    vy[6] = 0.1*0.25989;  
  vx[7] = 0.1*1.14193;    vy[7] = 0.1*0.508421;  
  vx[8] = 0.1*1.01127;    vy[8] = 0.1*0.734732;  
  vx[9] = 0.1*0.836413;   vy[9] = 0.1*0.928931;  
  vx[10] = 0.1*0.625;      vy[10] = 0.1*1.08253;  
  vx[11] = 0.1*0.386271;  vy[11] = 0.1*1.18882; 
  vx[12] = 0.1*0.130661;  vy[12] = 0.1*1.24315;  
  vx[13] = -0.1*0.130661; vy[13] = 0.1*1.24315;  
  vx[14] = -0.1*0.386271; vy[14] = 0.1*1.18882;  
  vx[15] = -0.1*0.625;    vy[15] = 0.1*1.08253; 
  vx[16] = -0.1*0.836413; vy[16] = 0.1*0.928931;  
  vx[17] = -0.1*1.01127;  vy[17] = 0.1*0.734732;  
  vx[18] = -0.1*1.14193;  vy[18] = 0.1*0.508421;  
  vx[19] = -0.1*1.22268;  vy[19] = 0.1*0.25989;  
  vx[20] = -0.1*1.25;     vy[20] = 0.1*1.53076e-16;  
  vx[21] = -0.1*1.22268;  vy[21] = -0.1*0.25989;  
  vx[22] = -0.1*1.14193;  vy[22] = -0.1*0.508421;  
  vx[23] = -0.1*1.01127;  vy[23] = -0.1*0.734732;  
  vx[24] = -0.1*0.836413; vy[24] = -0.1*0.928931;  
  vx[25] = -0.1*0.625;    vy[25] = -0.1*1.08253;  
  vx[26] = -0.1*0.386271; vy[26] = -0.1*1.18882;  
  vx[27] = -0.1*0.130661; vy[27] = -0.1*1.24315;  
  vx[28] = 0.1*0.130661;  vy[28] = -0.1*1.24315;  
  vx[29] = 0.1*0.386271;  vy[29] = -0.1*1.18882;  
  vx[30] = 0.1*0.625;     vy[30] = -0.1*1.08253;  
  vx[31] = 0.1*0.836413;  vy[31] = -0.1*0.928931;  
  vx[32] = 0.1*1.01127;   vy[32] = -0.1*0.734732;  
  vx[33] = 0.1*1.14193;   vy[33] = -0.1*0.508421;  
  vx[34] = 0.1*1.22268;   vy[34] = -0.1*0.25989; 
  vx[35] = 0.1*1.25;      vy[35] = -0.1*3.06152e-16;
  xtruS->DefinePolygon(nv, vx, vy);

  Double_t vz[2] = { -0.025, 0.025 };
  Double_t xoff[2]  = { 0., 0., };
  Double_t yoff[2]  = { 0., 0., };
  Double_t scale[2] = { 1.0, 1.0 };

  for (Int_t i=0; i<2; i++)
    xtruS->DefineSection(i, vz[i], xoff[i], yoff[i], scale[i]); 

  return new TGeoVolume("xtru2", xtruS, fBasicMedium);
*/
}  
 
//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreatePara()
{
  TGeoShape* paraS
    = new TGeoPara("paraS", 40., 60., 50., 30., 30., 30.);

  return new TGeoVolume("para", paraS, fBasicMedium);
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreatePolycone(Double_t sphi, Double_t dphi)
{
  // Define parameters

  Int_t nofZPlanes = 3;
  Double_t z[3];
  Double_t rin[3];
  Double_t rout[3];

  z[0] = -50.;
  rin[0] = 10.;
  rout[0] = 50.;
  
  z[1] = 10.;
  rin[1] = 20.;
  rout[1] = 30.;
  
  z[2] = 40.;
  rin[2] = 30.;
  rout[2] = 60.;
  
  // Redefine parameters in one array
  //
  Double_t* param = new Double_t[3+3*nofZPlanes]; 
          // number of parameters: sphi, dphi, nz + 3*nofZPlanes
 
  param[0] = sphi;
  param[1] = dphi;
  param[2] = nofZPlanes;
  
  for (int i=0; i<nofZPlanes; i++) {
    int j = 3 + 3*i; 
    param[j] = z[i]; param[j+1] = rin[i]; param[j+2] = rout[i];
  }

  TGeoShape* pconeS = new TGeoPcon(param);
  pconeS->SetName("pconeS");
  
  delete [] param; 
  
  return new TGeoVolume("pcone", pconeS, fBasicMedium);
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreatePolyhedra(Double_t sphi, Double_t dphi)
{
  // Define parameters

  Int_t nofSides = 4;
  Int_t nofZPlanes = 3;
  Double_t z[3];
  Double_t rin[3];
  Double_t rout[3];

  z[0] = -50.;
  rin[0] = 10.;
  rout[0] = 40.;
  
  z[1] = 10.;
  rin[1] = 20.;
  rout[1] = 20.;
  
  z[2] = 40.;
  rin[2] = 30.;
  rout[2] = 50.;
  
  // Redefine parameters in one array
  //
  Double_t* param = new Double_t[4+3*nofZPlanes]; 
          // number of parameters: sphi, dphi, nz + 3*nofZPlanes
 
  param[0] = sphi;
  param[1] = dphi;
  param[2] = nofSides;
  param[3] = nofZPlanes;
  
  for (int i=0; i<nofZPlanes; i++) {
    int j = 4 + 3*i; 
    param[j] = z[i]; param[j+1] = rin[i]; param[j+2] = rout[i];
  }

  TGeoShape* phedraS = new TGeoPgon(param); 
  phedraS->SetName("phedraS");

  delete [] param;

  return new TGeoVolume("phedra", phedraS, fBasicMedium);
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateSphere(Double_t sphi, Double_t dphi)
{
  TGeoShape* sphereS
    = new TGeoSphere("sphereS", 20., 60., 
                      sphi/2., sphi/2.+ dphi/2., sphi, sphi + dphi); 
			    
  return new TGeoVolume("sphere", sphereS, fBasicMedium);
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateTorus(Double_t sphi, Double_t dphi)
{
  TGeoShape* torusS
    = new TGeoTorus("torusS", 40., 20., 30., sphi, dphi);
			    
  return new TGeoVolume("torus", torusS, fBasicMedium);  
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateTrap()
{
  TGeoShape* trapS
    = new TGeoTrap("trapS", 30., 25., 35.,
		    20., 10., 15., 0.,
		    20., 10., 15., 0.);
  return new TGeoVolume("trap", trapS, fBasicMedium);
}

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateTrd()
{
  TGeoShape* trdS
    = new TGeoTrd2("trdS", 20., 30, 40., 50., 50.);

  return new TGeoVolume("trd", trdS, fBasicMedium);
}  

//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateTubs(Double_t sphi, Double_t dphi)
{
  TGeoShape* tubsS
    = new TGeoTubeSeg("tubsS", 20., 40, 50., sphi, sphi + dphi);

  return new TGeoVolume("tubs", tubsS, fBasicMedium);
}  
 
//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::CreateCtubs(Double_t /*sphi*/, Double_t /*dphi*/)
{
  //TGeoShape* tubsS
  //  = new TGeoCtub("ctubsS", 20., 30, 60.49, sphi, sphi + dphi,
  //                 0.00, 0.64, -0.77, 0.00, 0.09, 0.87);
  TGeoShape* tubsS
    = new TGeoCtub("ctubsS", 20., 30, 60.49, 330., 610.,
                   0.00, 0.64, -0.77, 0.00, 0.09, 0.87);

  return new TGeoVolume("ctubs", tubsS, fBasicMedium);
}  
 
//_____________________________________________________________________________
TGeoVolume* TstGeometryViaRoot::PlaceSolids(TGeoVolume* mother,
                                     Bool_t fullPhi, Bool_t reflect, Double_t zpos)
{
  Double_t sphi =   0.;
  Double_t dphi = 360.;
  if (!fullPhi) {
    sphi = 45.;
    dphi = 90.;
  }  
 
  int counter = 0;
  Double_t x0 = -450.;
  Double_t dx =  150.;
  Double_t dy =  150.;
  
  TGeoRotation* reflect3D = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* matrix = new Double_t[9];
  matrix[0] = 1; matrix[1] = 0; matrix[2] = 0;
  matrix[3] = 0; matrix[4] = 1; matrix[5] = 0;
  matrix[6] = 0; matrix[7] = 0; matrix[8] = -1;
  reflect3D->SetMatrix(matrix);
 
  // Box
  //
  TGeoVolume* boxV = CreateBox();
  mother->AddNode(boxV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx,  -dy, zpos)); 
  if (reflect)
    mother->AddNode(boxV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx,  -dy, -zpos, reflect3D)); 

  // Cons 
  //
  TGeoVolume* consV = CreateCons(sphi, dphi);
  mother->AddNode(consV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx, dy, zpos));
  if (reflect)
    mother->AddNode(consV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, dy, -zpos, reflect3D));

  // Elliptical tube 
  //
  TGeoVolume* eltuV = CreateEllipticalTube();
  mother->AddNode(eltuV, 0, 
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(eltuV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

  // Para
  //
  TGeoVolume* paraV = CreatePara();
  mother->AddNode(paraV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx,  dy, zpos));
  if (reflect)
    mother->AddNode(paraV, 1, 
                  new TGeoCombiTrans(x0 + (counter)*dx,  dy, -zpos, reflect3D));

  // Polycone
  //
  TGeoVolume* pconeV = CreatePolycone(sphi, dphi);
  mother->AddNode(pconeV, 0,
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(pconeV, 1, 
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

  // Polyhedra
  //
  TGeoVolume* phedraV = CreatePolyhedra(sphi, dphi);
  mother->AddNode(phedraV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx,  dy, zpos));
  if (reflect)
    mother->AddNode(phedraV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx,  dy, -zpos, reflect3D));

  // Sphere 
  //
  TGeoVolume* sphereV = CreateSphere(sphi, dphi);
  mother->AddNode(sphereV, 0, 
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(sphereV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

  // Torus
  //
  TGeoVolume* torusV = CreateTorus(sphi, dphi);
  mother->AddNode(torusV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx,  dy, zpos));
  if (reflect)
    mother->AddNode(torusV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx,  dy, -zpos, reflect3D));

  // Trap 
  //
  TGeoVolume* trapV = CreateTrap();
  mother->AddNode(trapV, 0, 
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(trapV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

  // Trd
  //
  TGeoVolume* trdV = CreateTrd();
  mother->AddNode(trdV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx,  dy, zpos));
  if (reflect)
    mother->AddNode(trdV, 1, 
                  new TGeoCombiTrans(x0 + (counter)*dx,  dy, -zpos, reflect3D));
 
  // Tube
  //
  TGeoVolume* tubsV = CreateTubs(sphi, dphi);
  mother->AddNode(tubsV, 0, 
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(tubsV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

   // Ctubs
  //
  TGeoVolume* ctubsV = CreateCtubs(sphi, dphi);
  mother->AddNode(ctubsV, 0, 
                  new TGeoTranslation(x0 + (counter)*dx, dy, zpos));
  if (reflect)
    mother->AddNode(ctubsV, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, dy, -zpos, reflect3D));

  // Xtru1
  //
  TGeoVolume* xtru1V = CreateExtrudedSolid1();
  mother->AddNode(xtru1V, 0, 
                  new TGeoTranslation(x0 + (++counter)*dx, -dy, zpos));
  if (reflect)
    mother->AddNode(xtru1V, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, -dy, -zpos, reflect3D));

   // Xtru2
  //
  TGeoVolume* xtru2V = CreateExtrudedSolid2();
  mother->AddNode(xtru2V, 0, 
                  new TGeoTranslation(x0 + (counter)*dx, dy, zpos));
  if (reflect)
    mother->AddNode(xtru2V, 1,
                  new TGeoCombiTrans(x0 + (counter)*dx, dy, -zpos, reflect3D));

  return mother;   		  
}

//_____________________________________________________________________________
void TstGeometryViaRoot::PlaceExtraSolid(VGM::SolidType solidType,
                                         TGeoVolume* mother)
{
  Double_t zpos = 100.;
  
  TGeoRotation* reflect3D = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* matrix = new Double_t[9];
  matrix[0] = 1; matrix[1] = 0; matrix[2] = 0;
  matrix[3] = 0; matrix[4] = 1; matrix[5] = 0;
  matrix[6] = 0; matrix[7] = 0; matrix[8] = -1;
  reflect3D->SetMatrix(matrix);
 
  // Arb8 
  //
  TGeoVolume* vol = 0;
  //TString volName;
 
  if ( solidType == VGM::kArb8 ) {
    vol = CreateArb8();
    //volName = "arb8";
  }    
    
  if ( ! vol )  return;

  mother->AddNode(vol, 0, 
                  new TGeoTranslation(0, 0, zpos)); 

  mother->AddNode(vol, 1,
                  new TGeoCombiTrans(0, 0, -zpos, reflect3D)); 

}

//_____________________________________________________________________________
void TstGeometryViaRoot::PlaceSolids(const std::vector<TGeoVolume*>& volumes,
                                     TGeoVolume* mother)
{
  // Place volumes defined in the vector 

  Double_t x0 = -450.;
  Double_t dx =  150.;
  Double_t zpos = 100.;
  
  
  TGeoRotation* reflect3D = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* matrix = new Double_t[9];
  matrix[0] = 1; matrix[1] = 0; matrix[2] = 0;
  matrix[3] = 0; matrix[4] = 1; matrix[5] = 0;
  matrix[6] = 0; matrix[7] = 0; matrix[8] = -1;
  reflect3D->SetMatrix(matrix);
 
  for ( UInt_t i=0; i<volumes.size(); ++i) {
    mother->AddNode(volumes[i], 0, 
                    new TGeoTranslation(x0 + i*dx, 0, zpos)); 
    mother->AddNode(volumes[i], 1,
                    new TGeoCombiTrans(x0 + i*dx, 0, -zpos, reflect3D)); 
  }                  
}


//
// public methods
// 

//_____________________________________________________________________________
void  TstGeometryViaRoot::DefineMaterials()
{
  // simple material (Al)
  //
  Double_t z, a, w, density; 
  TGeoMaterial* material1
    = new TGeoMaterial("Basic", a=26.98, z=13., density=2.700);

  // compound/mixture material
  //
  TGeoMixture* material2
    = new TGeoMixture("Air", 2, density= 1.290*1e-03);
  material2->DefineElement(0, a=14.01, z=7.0, w=0.7); 
  material2->DefineElement(1, a=16.00, z=8.0, w=0.3); 

  // material from predefined elements
  //
  TGeoElementTable* elemTable = gGeoManager->GetElementTable();
  TGeoElement* H = elemTable->GetElement(1);
  TGeoElement* C = elemTable->GetElement(6);

  Int_t natoms; 
  TGeoMixture* material3
    = new TGeoMixture("Scintillator", 2, density=1.032);  
  material3->AddElement(C, natoms= 9);
  material3->AddElement(H, natoms=10);

  // material using isotopes 
  // not supported in Root - using simple material definition
  //
  TGeoMaterial* material4
    = new TGeoMaterial("Uranium", a=235.31, z=92., density=13.61);

  // vacuum
  //
  TGeoMaterial* material5
    = new TGeoMaterial("Vacuum", 0, 0, 0,
                       TGeoMaterial::kMatStateGas, 
                       2.73 /* kelvin*/ , 
                       3.e-18/*pascal*/ * 6.24150e+3 /* MeV/mm3 */); 

  // Tracking medias
  new TGeoMedium("Basic",        1, material1);
  new TGeoMedium("Air",          2, material2);
  new TGeoMedium("Scintillator", 3, material3);
  new TGeoMedium("Uranium",      4, material4);
  new TGeoMedium("Vacuum",       5, material5);
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestSolids(Bool_t fullPhi)
{
  TGeoVolume* worldV = CreateWorld(600., 300., 200.);
  
  PlaceSolids(worldV, fullPhi, false, 0.);
  
  return (void*) gGeoManager->GetTopNode();
 }

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestExtraSolid(VGM::SolidType solidType)
{
  TGeoVolume* worldV = CreateWorld(600., 300., 200.);
  
  PlaceExtraSolid(solidType, worldV);
  
  return (void*) gGeoManager->GetTopNode();
 }

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestNewSolid()
{
  TGeoVolume* worldV = CreateWorld(200., 200., 200.);
 
  TGeoVolume* newSolidV = CreateNewSolid();
  if ( newSolidV ) {
    worldV->AddNode(newSolidV, 0, new TGeoTranslation()); 
  }  

/*  
  TGeoShape* boxS
    = new TGeoBBox("boxS", 1., 1., 1.);

  TGeoVolume* boxV = new TGeoVolume("boxV", boxS, fBasicMedium);
  worldV->AddNode(boxV, 0, new TGeoTranslation(-3.92, 1.26, 39.7));
  worldV->AddNode(boxV, 0, new TGeoTranslation(-0.999, 4.75, 26.8));
  worldV->AddNode(boxV, 0, new TGeoTranslation( 2.8, 9.28, 10.0));
  worldV->AddNode(boxV, 0, new TGeoTranslation(4.56, 11.4, 2.23));
  worldV->AddNode(boxV, 0, new TGeoTranslation(6.06, 13.2, -4.38));
  worldV->AddNode(boxV, 0, new TGeoTranslation(14.1, 22.8, -40.0));
*/  
  return (void*) gGeoManager->GetTopNode();
 }

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestNewSolid2()
{
  TGeoVolume* worldV = CreateWorld(600., 300., 200.);
  
  std::vector<TGeoVolume*> volumes;
  CreateArb8Solids(volumes);
  PlaceSolids(volumes, worldV);
  
  return (void*) gGeoManager->GetTopNode();
 }

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestPlacements()
{

  // World
  //
  TGeoVolume* worldV = CreateWorld(600., 100., 600.);
    
  // Get materials via names
  TGeoMedium* air = gGeoManager->GetMedium("Air");
  TGeoMedium* scintillator = gGeoManager->GetMedium("Scintillator");
  TGeoMedium* uranium = gGeoManager->GetMedium("Uranium");
  TGeoMedium* vacuum = gGeoManager->GetMedium("Vacuum");
  
  // Reset world material to vacuum
  worldV->SetMedium(vacuum);

  // Big box A
  //
  TGeoShape* boxA
    = new TGeoBBox("boxA", 20., 60., 50.);
  TGeoVolume* volA
    = new TGeoVolume("layerA", boxA, air);
  
  // Thick layer B (in A)
  // Place layers B  (division) 
  //
  //TGeoVolume* volB = volA->Divide("layerB", 2, 6, -6., 2.); 
  //           // division in the whole mother
        
  TGeoVolume* volB = volA->Divide("layerB", 2, 3, 0., 20.); 
  volB->SetMedium(uranium); 
             // division with offset

  // Thin layer C (in B)
  //
  TGeoShape* boxC
    = new TGeoBBox("boxC", 20., 0.2, 50.);
  TGeoVolume* volC
    = new TGeoVolume("layerC", boxC, scintillator);

  // Place layers C
  //
  volB->AddNode(volC, 1, new TGeoTranslation(0.,  9.8, 0.));
  volB->AddNode(volC, 2, new TGeoTranslation(0., -9.8, 0.));
    
  // Placements of A in a circle
  //
  for (Int_t i=0; i<24; i++) {
   
     Double_t x0 = 500.;
     Double_t y0 = 0.;
     Double_t dphi = 15.;

     Double_t phi = dphi*(i+1);
     Double_t x = x0*cos(phi*TMath::DegToRad());
     Double_t z = x0*sin(phi*TMath::DegToRad());

     TGeoRotation* rot = new TGeoRotation();
     rot->RotateY(-phi);
        // !!! Different meaning of rotation in Root than in Geant4
     
     TGeoCombiTrans* combi= new TGeoCombiTrans( x, y0, z, rot);
     worldV->AddNode(volA, i+1, combi);
   }

  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestReflections(Bool_t fullPhi)
{

  TGeoVolume* worldV = CreateWorld(600., 300., 300.);
  
  PlaceSolids(worldV, fullPhi, true, 100.);

  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestAssemblies()
{
// Example for assemblies from Root tutorial

  // World
  //
  TGeoVolume* top = CreateWorld(1000., 1000., 100.);
   
  // Make the elementary assembly of the whole structure
  TGeoVolume *tplate = new TGeoVolumeAssembly("TOOTHPLATE");

  Int_t ntooth = 5;
  Double_t xplate = 25;
  Double_t yplate = 50;
  Double_t xtooth = 10;
  Double_t ytooth = 0.5*yplate/ntooth;
  Double_t dshift = 2.*xplate + xtooth;
  Double_t xt,yt;
   
  TGeoVolume *plate 
    = fGeoManager->MakeBox("PLATE", fBasicMedium, xplate,yplate,1);
  TGeoVolume *tooth 
    = fGeoManager->MakeBox("TOOTH", fBasicMedium, xtooth,ytooth,1);
  tplate->AddNode(plate,1);
  for (Int_t i=0; i<ntooth; i++) {
    xt = xplate+xtooth;
    yt = -yplate + (4*i+1)*ytooth;
    tplate->AddNode(tooth, i+1, new TGeoTranslation(xt,yt,0));
    xt = -xplate-xtooth;
    yt = -yplate + (4*i+3)*ytooth;
    tplate->AddNode(tooth, ntooth+i+1, new TGeoTranslation(xt,yt,0));
  }   

  TGeoRotation *rot1 = new TGeoRotation();
  rot1->RotateX(90);
  TGeoRotation *rot;
  // Make a hexagone cell out of 6 toothplates. These can zip togeather
  // without generating overlaps (they are self-contained)
  TGeoVolume *cell = new TGeoVolumeAssembly("CELL");
  for (Int_t i2=0; i2<6; i2++) {
    Double_t phi =  60.*i2;
    Double_t phirad = phi*TMath::DegToRad();
    Double_t xp = dshift*TMath::Sin(phirad);
    Double_t yp = -dshift*TMath::Cos(phirad);
    rot = new TGeoRotation(*rot1);
    rot->RotateZ(phi);   
    cell->AddNode(tplate,i2+1,new TGeoCombiTrans(xp,yp,0,rot));
  }   
  //top->AddNode(cell, 1, new TGeoTranslation());
    
  // Make a row as an assembly of cells, then combine rows in a honeycomb
  // structure. This again works without any need to define rows as "overlapping"
  TGeoVolume *row = new TGeoVolumeAssembly("ROW");
  Int_t ncells = 5;
  for (Int_t i3=0; i3<ncells; i3++) {
    Double_t ycell = (2*i3+1)*(dshift+10);
    row->AddNode(cell, ncells+i3+1, new TGeoTranslation(0,ycell,0));
    row->AddNode(cell,ncells-i3,new TGeoTranslation(0,-ycell,0));
  }
  //top->AddNode(row, 1, new TGeoTranslation());
 
  Double_t dxrow = 3.*(dshift+10.)*TMath::Tan(30.*TMath::DegToRad());
  Double_t dyrow = dshift+10.;
  Int_t nrows = 5;
  for (Int_t i4=0; i4<nrows; i4++) {
    Double_t xrow = 0.5*(2*i4+1)*dxrow;
    Double_t yrow = 0.5*dyrow;
    if ((i4%2)==0) yrow = -yrow;
    top->AddNode(row, nrows+i4+1, new TGeoTranslation(xrow,yrow,0));
    top->AddNode(row, nrows-i4, new TGeoTranslation(-xrow,-yrow,0));
  }        
  
  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestAssemblies2()
{
// Example for assemblies with reflections

  // World
  //
  TGeoVolume* top = CreateWorld(200., 200., 100.);
   
  // Assembly
  //
  TGeoVolume* assembly = new TGeoVolumeAssembly("Assembly");

  // Cons volume
  Double_t rmin1 = 10.;
  Double_t rmax1 = 40;
  Double_t rmin2 = 20.;
  Double_t rmax2 = 60;
  Double_t hz = 50.;
  Double_t phi1 = 0.; 
  Double_t phi2 = 360.;
  TGeoVolume* consV 
    = fGeoManager->MakeCons("CONS", fBasicMedium, 
                            hz, rmin1, rmax1, rmin2, rmax2, phi1, phi2);

  // Transformations
  //
  
  TGeoRotation* rot1 = new TGeoRotation();
  rot1->RotateY( 90.);
  TGeoCombiTrans* combi1 = new TGeoCombiTrans( 110., 0., 0., rot1);

  TGeoRotation* reflectX3D = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* mX = new Double_t[9];
  mX[0] = -1; mX[1] = 0; mX[2] = 0;
  mX[3] =  0; mX[4] = 1; mX[5] = 0;
  mX[6] =  0; mX[7] = 0; mX[8] = 1;
  reflectX3D->SetMatrix(mX);
  TGeoCombiTrans* combi2 = new TGeoCombiTrans( (*reflectX3D) * (*combi1));
  
  TGeoRotation* rot3 = new TGeoRotation();
  rot3->RotateX(-90.);
  TGeoCombiTrans* combi3 = new TGeoCombiTrans( 0., 110., 0., rot3);

  TGeoRotation* reflectY3D = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* mY = new Double_t[9];
  mY[0] = 1; mY[1] =  0; mY[2] = 0;
  mY[3] = 0; mY[4] = -1; mY[5] = 0;
  mY[6] = 0; mY[7] =  0; mY[8] = 1;
  reflectY3D->SetMatrix(mY);
  TGeoCombiTrans* combi4 = new TGeoCombiTrans( (*reflectY3D) * (*combi3));

/* 
  // Simple placement
  top->AddNode(consV, 1, combi1);
  top->AddNode(consV, 2, combi2);
  top->AddNode(consV, 3, combi3);
  top->AddNode(consV, 4, combi4);
*/  

  // Place via assembly
  assembly->AddNode(consV, 1, combi1);
  assembly->AddNode(consV, 2, combi2);
  assembly->AddNode(consV, 3, combi3);
  assembly->AddNode(consV, 4, combi4);
  top->AddNode(assembly, 1);

  return (void*) gGeoManager->GetTopNode();
 }

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestBooleanSolids1()
{
// Only translation in solid displacement

  TGeoVolume* worldV = CreateWorld(400., 100., 400.);

  // Create solids
  TGeoShape* solid1 
    = new TGeoBBox("boxS", 50., 50., 50.);

  TGeoShape* solid2 
    = new TGeoConeSeg("tubsS", 100., 10., 30., 20., 40., 0., 360.) ;
 
  // Simple solids placed for a control
  //
  TGeoVolume* volume1
    = new TGeoVolume("solid1", solid1, fBasicMedium);
  worldV->AddNode(volume1, 1, 
                  new TGeoTranslation(-125., 0., -200.));

  TGeoVolume* volume2
    = new TGeoVolume("solid2", solid2, fBasicMedium);
  worldV->AddNode(volume2, 1, 
                  new TGeoTranslation( 125., 0., -200.));


  // Define displacement transformations
  //
  
  // Translate solid2  
  //
  TGeoTranslation* tr2 = new TGeoTranslation(20., 0., 0.);
  tr2->SetName("tr2");
  tr2->RegisterYourself();
  
  // Intersection
  //
  TGeoShape* intersectionS
    = new TGeoCompositeShape("intersection_solid1_solid2_S", "boxS*tubsS:tr2"); 
  TGeoVolume* intersectionV
    = new TGeoVolume("intersection_solid1_solid2", intersectionS, fBasicMedium);
  worldV->AddNode(intersectionV, 1, 
                  new TGeoTranslation(-250., 0., 200.));
  
  // Subtraction
  //
  TGeoShape* subtractionS
    = new TGeoCompositeShape("subtraction_solid1_solid2_S", "boxS-tubsS:tr2"); 
  TGeoVolume* subtractionV
    = new TGeoVolume("subtraction_solid1_solid2", subtractionS, fBasicMedium);
  worldV->AddNode(subtractionV, 1, 
                  new TGeoTranslation(0., 0., 200.));
  
  // Union
  //
  TGeoShape* unionS
    = new TGeoCompositeShape("union_solid1_solid2_S", "boxS+tubsS:tr2"); 
  TGeoVolume* unionV
    = new TGeoVolume("union_solid1_solid2", unionS, fBasicMedium);
  worldV->AddNode(unionV, 1, 
                  new TGeoTranslation(250., 0., 200.));
  
  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestBooleanSolids2()
{
// Translation + rotation in solid displacement

  TGeoVolume* worldV = CreateWorld(400., 100., 400.);

  // Create solids
  TGeoShape* solid1 
    = new TGeoBBox("boxS", 50., 50., 50.);

  TGeoShape* solid2 
    = new TGeoConeSeg("tubsS", 100., 10., 30., 20., 40., 0., 360.) ;
 
  // Simple solids placed for a control
  //
  TGeoVolume* volume1
    = new TGeoVolume("solid1", solid1, fBasicMedium);
  worldV->AddNode(volume1, 1, 
                  new TGeoTranslation(-125., 0., -200.));

  TGeoVolume* volume2
    = new TGeoVolume("solid2", solid2, fBasicMedium);
  worldV->AddNode(volume2, 1, 
                  new TGeoTranslation( 125., 0., -200.));

  // Define displacement transformations
  //
  
  // Rotate solid1  
  //
  TGeoRotation* rot1 = new TGeoRotation();
  rot1->RotateY(45.);
  TGeoCombiTrans* tr1 = new TGeoCombiTrans(0., 0., 0., rot1);
  tr1->SetName("tr1");
  tr1->RegisterYourself();
 
  // Translate + Rotate solid2  
  //
/*
  TGeoRotation* rot2 = new TGeoRotation();
  rot2->RotateX(30.);
  TGeoCombiTrans* tr2 = new TGeoCombiTrans(20., 0., 0., rot2);
  tr2->SetName("tr2");
  tr2->RegisterYourself();
*/  
  TGeoRotation* rot2 = new TGeoRotation();
  rot2->RotateX(30.);
  
  TGeoTranslation* trans = new TGeoTranslation(20., 0., 0.);
  TGeoHMatrix mrot1(*rot1);
  TGeoHMatrix mtrans(*trans);
  TGeoHMatrix mtransT = mrot1 * mtrans * mrot1.Inverse();
  const Double_t* transT = mtransT.GetTranslation();
  TGeoCombiTrans* tr2 = new TGeoCombiTrans(transT[0], transT[1], transT[2], rot2);
  tr2->SetName("tr2");
  tr2->RegisterYourself();
  //tr2->Print();

  // Intersection
  //
  TGeoShape* intersectionS
    = new TGeoCompositeShape("intersection_solid1_solid2_S", "boxS:tr1*tubsS:tr2"); 
  TGeoVolume* intersectionV
    = new TGeoVolume("intersection_solid1_solid2", intersectionS, fBasicMedium);
  worldV->AddNode(intersectionV, 1, 
                  new TGeoTranslation(-250., 0., 200.));

  // Subtraction
  //
  TGeoShape* subtractionS
    = new TGeoCompositeShape("subtraction_solid1_solid2_S", "boxS:tr1-tubsS:tr2"); 
  TGeoVolume* subtractionV
    = new TGeoVolume("subtraction_solid1_solid2", subtractionS, fBasicMedium);
  worldV->AddNode(subtractionV, 1, 
                  new TGeoTranslation(0., 0., 200.));
  
  // Union
  //
  TGeoShape* unionS
    = new TGeoCompositeShape("union_solid1_solid2_S", "boxS:tr1+tubsS:tr2"); 
  TGeoVolume* unionV
    = new TGeoVolume("union_solid1_solid2", unionS, fBasicMedium);
  worldV->AddNode(unionV, 1, 
                  new TGeoTranslation(250., 0., 200.));
  
  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestBooleanSolids3()
{
// Translation + reflection in solid displacement

  TGeoVolume* worldV = CreateWorld(400., 100., 400.);
  
  // Create solids
  TGeoShape* solid1 
    = new TGeoBBox("boxS", 50., 50., 50.);

  TGeoShape* solid2 
    = new TGeoConeSeg("tubsS", 100., 10., 30., 20., 50., 0., 360.) ;
 
  // Simple solids placed for a control
  //
  TGeoVolume* volume1
    = new TGeoVolume("solid1", solid1, fBasicMedium);
  worldV->AddNode(volume1, 1, 
                  new TGeoTranslation(-125., 0., -200.));

  TGeoVolume* volume2
    = new TGeoVolume("solid2", solid2, fBasicMedium);
  worldV->AddNode(volume2, 1, 
                  new TGeoTranslation( 125., 0., -200.));


  // Define displacement transformations
  //
  
  // Rotate solid1  
  //
  TGeoRotation* rot1 = new TGeoRotation();
  rot1->RotateY(45.);
  TGeoCombiTrans* tr1 = new TGeoCombiTrans(0., 0., 0., rot1);
  tr1->SetName("tr1");
  tr1->RegisterYourself();
 
  // Translate + Reflect solid2  
  //
  TGeoRotation* rot2 = new TGeoRotation();
  // how to simply apply reflection ???
  Double_t* matrix = new Double_t[9];
  matrix[0] = 1; matrix[1] = 0; matrix[2] = 0;
  matrix[3] = 0; matrix[4] = 1; matrix[5] = 0;
  matrix[6] = 0; matrix[7] = 0; matrix[8] = -1;
  rot2->SetMatrix(matrix);

  TGeoCombiTrans* tr2 = new TGeoCombiTrans(20., 0., 0., rot2);
  tr2->SetName("tr2");
  tr2->RegisterYourself();
  
  // Intersection
  //
  TGeoShape* intersectionS
    = new TGeoCompositeShape("intersection_solid1_solid2_S", "boxS:tr1*tubsS:tr2"); 
  TGeoVolume* intersectionV
    = new TGeoVolume("intersection_solid1_solid2", intersectionS, fBasicMedium);
  worldV->AddNode(intersectionV, 1, 
                  new TGeoTranslation(-250., 0., 200.));
  
  // Subtraction
  //
  TGeoShape* subtractionS
    = new TGeoCompositeShape("subtraction_solid1_solid2S", "boxS:tr1-tubsS:tr2"); 
  TGeoVolume* subtractionV
    = new TGeoVolume("subtraction_solid1_solid2", subtractionS, fBasicMedium);
  worldV->AddNode(subtractionV, 1, 
                  new TGeoTranslation(0., 0., 200.));
  
  // Union
  //
  TGeoShape* unionS
    = new TGeoCompositeShape("subtraction_solid1_solid2S", "boxS:tr1+tubsS:tr2"); 
  TGeoVolume* unionV
    = new TGeoVolume("union_solid1_solid2", unionS, fBasicMedium);
  worldV->AddNode(unionV, 1, 
                  new TGeoTranslation(250., 0., 200.));
  
  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestBooleanSolids4()
{
// Example for composite shape from Root User's guide

  TGeoVolume* top = CreateWorld(100., 250., 250.);
  const Double_t sq2 = TMath::Sqrt(2.);
  
  // Make shape components
  //
  new TGeoBBox("B", 100., 125.*sq2, 125.*sq2);
  new TGeoTube("T", 0., 100., 250) ;
  TGeoPgon* spgon = new TGeoPgon("P", 0., 360., 6, 2);
  spgon->DefineSection(0, -250,0, 80); 
  spgon->DefineSection(1, 250,0, 80); 
 
  // Define rotations
  //
  //TGeoRotation* r1 = new TGeoRotation("r1", 90, 0, 0, 180, 90, 90);
  //TGeoRotation* r2 = new TGeoRotation("r2", 90, 0, 45, 90, 45, 270);
        // includes reflection - let's better define a pure rotations
	// so that we can export this geometry in Geant4

  TGeoRotation* r1 = new TGeoRotation();
  r1->RotateX(90.);
  r1->SetName("r1");
  r1->RegisterYourself();
  
  TGeoRotation* r2 = new TGeoRotation();
  r2->RotateX(45.);
  r2->SetName("r2");
  r2->RegisterYourself();
 
  // Create composite shape
  //
  TGeoCompositeShape* cs
    = new TGeoCompositeShape("cs", "((T+T:r1)-(P+P:r1))*B:r2"); 
  //TGeoCompositeShape* cs
  //  = new TGeoCompositeShape("cs", "((T:r1+T)-(P:r1+P)):r2*B"); 

  TGeoVolume* comp = new TGeoVolume("COMP", cs, fBasicMedium);
  comp->SetLineColor(5);  

  top->AddNode(comp, 1); 

  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestBooleanSolids5()
{
// Example for a complex composite shape with transformations
// performed on the left constituent solids.
// ---

  TGeoVolume* top = CreateWorld(500., 500., 500.);
  gGeoManager->SetTopVolume(top);  

  // Add a small box in the middle
  //
  TGeoShape* solid
    = new TGeoBBox("SB", 10., 10, 10);
  TGeoVolume* volume1
    = new TGeoVolume("volume1", solid,fBasicMedium);
  top->AddNode(volume1, 1, new TGeoTranslation(0., 0., 0.));
  volume1->SetLineColor(4);  


  // Make shape componenets
  //
  new TGeoBBox("B", 100., 100, 100);
  new TGeoTube("T", 0., 20., 120.) ;
 
  // Define rotations
  //
  TGeoTranslation* t1 = new TGeoTranslation("t1", 0., 50., 0);
  t1->RegisterYourself();
  TGeoTranslation* t2 = new TGeoTranslation("t2", 0., -50., 0);
  t2->RegisterYourself();
  TGeoTranslation* t3 = new TGeoTranslation("t3", 300., 0., 0);
  t3->RegisterYourself();
  
  TGeoRotation* r1 = new TGeoRotation();
  r1->RotateZ(45.);
  r1->SetName("r1");
  r1->RegisterYourself();

  TGeoRotation* r2 = new TGeoRotation();
  r2->RotateZ(90.);
  r2->SetName("r2");
  r2->RegisterYourself();
  
  TGeoCombiTrans* tc1 = new TGeoCombiTrans("tc1", -300., 0., 0, r1);
  tc1->RegisterYourself();
  TGeoCombiTrans* tc2 = new TGeoCombiTrans("tc2",  0., -50., 0., r2);
  tc2->RegisterYourself();
 
  // Create composite shape
  //
  //TGeoCompositeShape* cs1
  //  = new TGeoCompositeShape("cs", "B:t1-T:r2"); 

  //TGeoCompositeShape* cs2
  //  = new TGeoCompositeShape("cs", "(B:t1-T:r2):r1+SB"); 

  //TGeoCompositeShape* cs3
  //  = new TGeoCompositeShape("cs", "B:t2-T:r2"); 

  TGeoCompositeShape* cs
    = new TGeoCompositeShape("cs", "(B:t1-T:r2):tc1+(B:t2-T:r2):t3"); 

  TGeoVolume* comp = new TGeoVolume("COMP", cs, fBasicMedium);
  comp->SetLineColor(5);  

  top->AddNode(comp, 1, new TGeoTranslation(0, 0, 150.)); 

  return (void*) gGeoManager->GetTopNode();
}

//_____________________________________________________________________________
void* TstGeometryViaRoot::TestSpecial()
{
// Special test, geometry is loaded from geometry.root file.
// ---

  gGeoManager->Import("geometry.root");

/*
  TGeoVolume* worldV = gGeoManager->GetTopVolume();
  TGeoShape* boxS
    = new TGeoBBox("boxS", 1., 1., 1.);

  TGeoVolume* boxV = new TGeoVolume("boxV", boxS, fBasicMedium);
  worldV->AddNode(boxV, 0, new TGeoTranslation(6.22, 1.57e+02, 2.51e+02));
  worldV->AddNode(boxV, 0, new TGeoTranslation(6.60, 1.57e+02, 2.51e+02));
  worldV->AddNode(boxV, 0, new TGeoTranslation(6.98, 1.58e+02, 2.52e+02));
  worldV->AddNode(boxV, 0, new TGeoTranslation(11.9, 1.59e+02, 2.6e+02));
*/
  return (void*) gGeoManager->GetTopNode();
}
  

