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
// Class Tubs
// ---------------
// VGM implementation for Geant4 tubs solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Tubs.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4Tubs.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::Tubs::Tubs(const std::string& name,
                     double rin, double rout, double hz,
		     double sphi, double dphi)
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs(),
    fTubs(new G4Tubs(name,
                     rin  / ClhepVGM::Units::Length(),
		     rout / ClhepVGM::Units::Length(),
		     hz   / ClhepVGM::Units::Length(),
		     sphi / ClhepVGM::Units::Angle(),
		     dphi / ClhepVGM::Units::Angle()))
{
/// Standard constructor to define tubs from parameters
/// \param rin inside radius in mm
/// \param rout outside radius in mm
/// \param hz half-length along the z axis in mm
/// \param sphi starting angle of the segment in deg
/// \param dphi opening angle of the segment in deg

  Geant4GM::SolidMap::Instance()->AddSolid(this, fTubs);
}


//_____________________________________________________________________________
Geant4GM::Tubs::Tubs(G4Tubs* tubs,
                     G4ReflectedSolid* reflTubs)
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs(),
    fTubs(tubs)
{
/// Standard constructor to define tubs from G4 object

  if (reflTubs)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflTubs);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, tubs);
}

//_____________________________________________________________________________
Geant4GM::Tubs::Tubs()
  : VGM::ISolid(),
    VGM::ITubs(),
    BaseVGM::VTubs()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Tubs::Tubs(const Tubs& rhs)
  : VGM::ISolid(rhs),
    VGM::ITubs(rhs),
    BaseVGM::VTubs(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Tubs::~Tubs() {
//
}

//_____________________________________________________________________________
std::string Geant4GM::Tubs::Name() const
{
  return fTubs->GetName();
}

//_____________________________________________________________________________
double Geant4GM::Tubs::InnerRadius() const
{
  return fTubs->GetInnerRadius() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Tubs::OuterRadius() const
{
  return fTubs->GetOuterRadius() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Tubs::ZHalfLength() const
{
  return fTubs->GetZHalfLength() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Tubs::StartPhi() const
{
  return fTubs->GetStartPhiAngle() * ClhepVGM::Units::Angle();
}

//_____________________________________________________________________________
double Geant4GM::Tubs::DeltaPhi() const
{
  return fTubs->GetDeltaPhiAngle() * ClhepVGM::Units::Angle();
}
