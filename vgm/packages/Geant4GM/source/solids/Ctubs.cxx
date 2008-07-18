// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Ctubs
// ---------------
// VGM implementation for cut tubs solid in Geant4.
// The solid is realized as boolean subtraction of tube and
// two boxes.
// VGM implementation for Geant4 tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Ctubs.h"
#include "Geant4GM/solids/SolidMap.h"

#include "geomdefs.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"

#include <cmath>

using CLHEP::Hep3Vector;
using CLHEP::HepRotation;

const double Geant4GM::Ctubs::fgkTolerance = 1e-9;
//_____________________________________________________________________________
Geant4GM::Ctubs::Ctubs(const std::string& name, 
                     double rin, double rout, double hz, 
		     double sphi, double dphi,
	             double nxlow, double nylow, double nzlow,
	             double nxhigh, double nyhigh, double nzhigh)
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs(),
    fTubs(0),
    fBooleanSolid(0),
    fHz(hz/ClhepVGM::Units::Length()),
    fNLow( nxlow, nylow, nzlow),
    fNHigh(nxhigh, nyhigh, nzhigh)
    		     
{
/// Standard constructor to define tubs from parameters
/// \param rin inside radius in mm
/// \param rout outside radius in mm
/// \param hz half-length along the z axis in mm
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg
/// \param nxlow X-component of the normal unit vector to the cut plane in -z
/// \param nylow Y-component of the normal unit vector to the cut plane in -z
/// \param nzlow Z-component of the normal unit vector to the cut plane in -z
/// \param nxhigh X-component of the normal unit vector to the cut plane in +z
/// \param nyhigh Y-component of the normal unit vector to the cut plane in +z
/// \param nzhigh Z-component of the normal unit vector to the cut plane in +z

  /// checks for normals
  bool isCutLow  = ( fabs(nxlow)  > fgkTolerance || fabs(nylow)  > fgkTolerance ); 
  bool isCutHigh = ( fabs(nxhigh) > fgkTolerance || fabs(nyhigh) > fgkTolerance ); 

  // Get angles 
  double thetaLow = fNLow.theta();
  double thetaHigh = fNHigh.theta();
  //std::cout << "thetaLow= " << thetaLow*ClhepVGM::Units::Angle() << std::endl;
  //std::cout << "thetaHigh= " << thetaHigh*ClhepVGM::Units::Angle() << std::endl;

  // Calculate new hz
  double dzLow  = fabs(rout * tan(thetaLow));
  double dzHigh = fabs(rout * tan(thetaHigh));
  double dzMax = dzLow >= dzHigh ? dzLow : dzHigh;
  double hzNew = hz + dzMax*1.2;
  //std::cout << "dzLow= " << dzLow << std::endl;
  //std::cout << "dzHigh= " << dzHigh << std::endl;
  //std::cout << "dzMax= " << dzMax << std::endl;
  //std::cout << "hzNew= " << hzNew << std::endl;

  /// Create tube 
  fTubs = new G4Tubs("tubs", 
                      rin   / ClhepVGM::Units::Length(), 
		      rout  / ClhepVGM::Units::Length(), 
		      hzNew / ClhepVGM::Units::Length(), 
		      sphi  / ClhepVGM::Units::Angle(), 
		      dphi  / ClhepVGM::Units::Angle());
		     
		     
  // Define dimensions of boxes
  //
  double hzLow = 1.2 * fabs(rout / cos(thetaLow));		     
  double hzHigh = 1.2 * fabs(rout / cos(thetaHigh));
  //std::cout << "hzLow= " << hzLow << std::endl;
  //std::cout << "hzHigh= " << hzHigh << std::endl;

  double dHz = hzNew-hz;
  double thetaLow2 = thetaLow;
  double thetaHigh2 = thetaHigh;
  if ( thetaLow2 > CLHEP::pi/2. ) thetaLow2 = thetaLow - CLHEP::pi/2.;
  if ( thetaHigh2 > CLHEP::pi/2. ) thetaHigh2 = thetaHigh - CLHEP::pi/2.;
  double rCorner = sqrt(rout*rout + dHz*dHz);
  double thetaPlusLow = atan(dHz/rout) - thetaLow2;
  double thetaPlusHigh = atan(dHz/rout) - thetaHigh2;
  double hxLow = 2.*rCorner*cos(thetaPlusLow);
  double hxHigh = 2.*rCorner*cos(thetaPlusHigh);
  //std::cout << "hxLow= "  << hxLow << std::endl;
  //std::cout << "hxHigh= " << hxHigh << std::endl;
 
  G4VSolid* boxLow = 0;  
  if (isCutLow) {
    boxLow = new G4Box("boxLow", hxLow, hxLow, hzLow); 
    // std::cout << "boxLow: " << *boxLow << std::endl; 
  }  

  G4VSolid* boxHigh = 0;  
  if (isCutHigh) {
    boxHigh = new G4Box("boxHigh", hxHigh, hxHigh, hzHigh);  
    // std::cout << "boxHigh: " << *boxHigh << std::endl;
  }  

  
  // Define rotations of boxes
  //
  // Rotation axis = cross product of normals
  Hep3Vector axisLow = Hep3Vector(0,0,1).cross(fNLow);
  double angleLow = Hep3Vector(0,0,1).angle(fNLow);
  HepRotation rotLow;
  rotLow.set(axisLow, angleLow);
  //std::cout << "AxisLow= " << axisLow << "  " 
  //          << angleLow/deg << "  " << thetaLow/deg << std::endl;
  
  Hep3Vector axisHigh = Hep3Vector(0,0,1).cross(fNHigh);
  double angleHigh = Hep3Vector(0,0,1).angle(fNHigh);
  HepRotation rotHigh;
  rotHigh.set(axisHigh, angleHigh);
  // std::cout << "AxisHigh= " << axisHigh << "  " 
  //           << angleHigh/deg << "  " << thetaHigh/deg << std::endl;
 
  // Define displacement of boxes
  //
  double zposLow  = fabs(hzLow  / cos(thetaLow));
  double zposHigh = fabs(hzHigh / cos(thetaHigh));
  //std::cout << "zposLow="  << zposLow  << std::endl;
  //std::cout << "zposHigh=" << zposHigh << std::endl;


  // Subtract boxes from tube
  G4VSolid* booleanSolid;
  if ( isCutLow )
    booleanSolid = new G4SubtractionSolid("boolean", fTubs, boxLow,
                               new HepRotation(rotLow.inverse()),
                               Hep3Vector(0, 0, - (hz + zposLow)));
  else
    booleanSolid = fTubs;                               			

  if ( isCutHigh)
    fBooleanSolid
       = new G4SubtractionSolid(name, booleanSolid, boxHigh,
                               new HepRotation(rotHigh.inverse()),
                               Hep3Vector(0, 0, hz + zposHigh));
  else
    fBooleanSolid = booleanSolid;
    
  // std::cout << *fBooleanSolid << std::endl;   
		     
  Geant4GM::SolidMap::Instance()->AddSolid(this, fBooleanSolid); 
}


//_____________________________________________________________________________
Geant4GM::Ctubs::Ctubs() 
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Ctubs::Ctubs(const Ctubs& rhs) 
  : VGM::ISolid(rhs),
    VGM::ICtubs(rhs),
    BaseVGM::VCtubs(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Ctubs::~Ctubs() {
//
}    

//_____________________________________________________________________________
std::string Geant4GM::Ctubs::Name() const
{
  return fTubs->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Ctubs::InnerRadius() const
{
  return fTubs->GetInnerRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::OuterRadius() const
{
  return fTubs->GetOuterRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::ZHalfLength() const
{
  return fHz * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::StartPhi() const
{
  return fTubs->GetStartPhiAngle() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::DeltaPhi() const
{
  return fTubs->GetDeltaPhiAngle() * ClhepVGM::Units::Angle();
}  
//_____________________________________________________________________________
double Geant4GM::Ctubs::NxLow() const
{
  return fNLow.x() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NyLow() const
{
  return fNLow.y() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NzLow() const
{
  return fNLow.z() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NxHigh() const
{
  return fNHigh.x() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NyHigh() const
{
  return fNHigh.y() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NzHigh() const
{
  return fNHigh.z() * ClhepVGM::Units::Length();
}  

