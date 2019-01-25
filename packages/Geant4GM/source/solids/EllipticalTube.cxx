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
// Class EllipticalTube
// --------------------
// VGM implementation for Geant4 elliptical tube solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/EllipticalTube.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4EllipticalTube.hh"
#include "G4ReflectedSolid.hh"

#
//_____________________________________________________________________________
Geant4GM::EllipticalTube::EllipticalTube(const std::string& name,
                                         double dx, double dy, double hz)
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube(),
    fEllipticalTube(new G4EllipticalTube(name,
                    dx / ClhepVGM::Units::Length(),
		    dy / ClhepVGM::Units::Length(),
		    hz / ClhepVGM::Units::Length()))
{
/// Standard constructor to define elliptical tube from parameters
/// \param dx the semi-axis of the ellipse along x in mm
/// \param dy the semi-axis of the ellipse along y in mm
/// \param hz half-length along the z axis in mm

  Geant4GM::SolidMap::Instance()->AddSolid(this, fEllipticalTube);
}


//_____________________________________________________________________________
Geant4GM::EllipticalTube::EllipticalTube(G4EllipticalTube* eltu,
                                         G4ReflectedSolid* reflEltu)
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube(),
    fEllipticalTube(eltu)
{
/// Standard constructor to define elliptical tube from G4 object

  if (reflEltu)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflEltu);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, eltu);
}

//_____________________________________________________________________________
Geant4GM::EllipticalTube::EllipticalTube()
  : VGM::ISolid(),
    VGM::IEllipticalTube(),
    BaseVGM::VEllipticalTube()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::EllipticalTube::EllipticalTube(const EllipticalTube& rhs)
  : VGM::ISolid(rhs),
    VGM::IEllipticalTube(rhs),
    BaseVGM::VEllipticalTube(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::EllipticalTube::~EllipticalTube() {
//
}

//_____________________________________________________________________________
std::string Geant4GM::EllipticalTube::Name() const
{
  return fEllipticalTube->GetName();
}

//_____________________________________________________________________________
double Geant4GM::EllipticalTube::Dx() const
{
  return fEllipticalTube->GetDx() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::EllipticalTube::Dy() const
{
  return fEllipticalTube->GetDy() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::EllipticalTube::ZHalfLength() const
{
  return fEllipticalTube->GetDz() * ClhepVGM::Units::Length();
}
