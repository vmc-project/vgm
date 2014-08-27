// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2014, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Ctubs
// ---------------
// VGM implementation for cut tubs solid in Geant4.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Ctubs.h"
#include "Geant4GM/solids/SolidMap.h"

#include "geomdefs.hh"
#include "G4CutTubs.hh"
#include "G4ReflectedSolid.hh"

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
    fIsReflected(false),
    fCutTubs(0)
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

  /// Create Geabt4 cut tube 
  fCutTubs = new G4CutTubs(name, 
                           rin  / ClhepVGM::Units::Length(), 
		           rout / ClhepVGM::Units::Length(), 
		           hz   / ClhepVGM::Units::Length(), 
		           sphi / ClhepVGM::Units::Angle(), 
		           dphi / ClhepVGM::Units::Angle(),
                           G4ThreeVector(nxlow / ClhepVGM::Units::Length(), 
                                         nylow / ClhepVGM::Units::Length(),
                                         nzlow / ClhepVGM::Units::Length()),
                           G4ThreeVector(nxhigh / ClhepVGM::Units::Length(), 
                                         nyhigh / ClhepVGM::Units::Length(),
                                         nzhigh / ClhepVGM::Units::Length()));
		     
  Geant4GM::SolidMap::Instance()->AddSolid(this, fCutTubs); 
}


//_____________________________________________________________________________
Geant4GM::Ctubs::Ctubs(G4CutTubs* ctubs, 
                       G4ReflectedSolid* reflCtubs)
  : VGM::ISolid(),
    VGM::ICtubs(),
    BaseVGM::VCtubs(),
    fIsReflected(false),
    fCutTubs(ctubs)
{    
/// Standard constructor to define ctubs from G4 object

  if (reflCtubs) {
    fIsReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflCtubs);
  }
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, ctubs);
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
  return fCutTubs->GetName();
}  
  
//_____________________________________________________________________________
double Geant4GM::Ctubs::InnerRadius() const
{
  return fCutTubs->GetInnerRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::OuterRadius() const
{
  return fCutTubs->GetOuterRadius() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::ZHalfLength() const
{
  return  fCutTubs->GetZHalfLength() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::StartPhi() const
{
  return fCutTubs->GetStartPhiAngle() * ClhepVGM::Units::Angle();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::DeltaPhi() const
{
  return fCutTubs->GetDeltaPhiAngle() * ClhepVGM::Units::Angle();
}  
//_____________________________________________________________________________
double Geant4GM::Ctubs::NxLow() const
{
  if (!fIsReflected)
    return fCutTubs->GetLowNorm().x() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetHighNorm().x() * ClhepVGM::Units::Length();
    
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NyLow() const
{
  if (!fIsReflected)
    return fCutTubs->GetLowNorm().y() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetHighNorm().y() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NzLow() const
{
  if (!fIsReflected)
    return fCutTubs->GetLowNorm().z() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetHighNorm().z() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NxHigh() const
{
  if (!fIsReflected)
    return fCutTubs->GetHighNorm().x() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetLowNorm().x() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NyHigh() const
{
  if (!fIsReflected)
    return fCutTubs->GetHighNorm().y() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetLowNorm().y() * ClhepVGM::Units::Length();
}  

//_____________________________________________________________________________
double Geant4GM::Ctubs::NzHigh() const
{
  if (!fIsReflected)
    return fCutTubs->GetHighNorm().z() * ClhepVGM::Units::Length();
  else
    return fCutTubs->GetLowNorm().z() * ClhepVGM::Units::Length();
}  

