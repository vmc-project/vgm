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
// Class Ellipsoid
// ---------------
// VGM implementation for Geant4 ellipsoid solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Ellipsoid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4Ellipsoid.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::Ellipsoid::Ellipsoid(const std::string& name,
                   double dx, double dy, double dz,
                   double zBottomCut, double zTopCut)
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid(),
    fEllipsoid( new G4Ellipsoid(name,
                    dx / ClhepVGM::Units::Length(),
		    dy / ClhepVGM::Units::Length(),
		    dz / ClhepVGM::Units::Length(),
		    zBottomCut / ClhepVGM::Units::Length(),
		    zTopCut    / ClhepVGM::Units::Length()) )
{
/// Standard constructor to define ellipsoid from parameters
/// \param dx the semi-axis of the ellipse along x in mm
/// \param dy the semi-axis of the ellipse along y in mm
/// \param dz the semi-axis of the ellipse along z in mm
/// \param zBottomCut bottom cut in z in mm
/// \param zTopCut top cut in z in mm

  Geant4GM::SolidMap::Instance()->AddSolid(this, fEllipsoid);
}


//_____________________________________________________________________________
Geant4GM::Ellipsoid::Ellipsoid(G4Ellipsoid* ellipsoid,
                   G4ReflectedSolid* reflEllipsoid)
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid(),
    fEllipsoid(ellipsoid)
{
/// Standard constructor to define ellipsoid from G4 object

  if (reflEllipsoid)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflEllipsoid);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, ellipsoid);
}

//_____________________________________________________________________________
Geant4GM::Ellipsoid::Ellipsoid()
  : VGM::ISolid(),
    VGM::IEllipsoid(),
    BaseVGM::VEllipsoid()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Ellipsoid::Ellipsoid(const Ellipsoid& rhs)
  : VGM::ISolid(rhs),
    VGM::IEllipsoid(rhs),
    BaseVGM::VEllipsoid(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Ellipsoid::~Ellipsoid() {
//
}

//_____________________________________________________________________________
std::string Geant4GM::Ellipsoid::Name() const
{
  return fEllipsoid->GetName();
}

//_____________________________________________________________________________
double Geant4GM::Ellipsoid::XSemiAxis() const
{
  return fEllipsoid->GetSemiAxisMax(0) * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Ellipsoid::YSemiAxis() const
{
  return fEllipsoid->GetSemiAxisMax(1) * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Ellipsoid::ZSemiAxis() const
{
  return fEllipsoid->GetSemiAxisMax(2) * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Ellipsoid::ZBottomCut() const
{
  return fEllipsoid->GetZBottomCut() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Ellipsoid::ZTopCut() const
{
  return fEllipsoid->GetZTopCut() * ClhepVGM::Units::Length();
}

