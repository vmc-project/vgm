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
// Class Box
// ---------------
// VGM implementation for Geant4 box solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/Units.h"

#include "Geant4GM/solids/Box.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4Box.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::Box::Box(const std::string& name,
                   double hx, double hy, double hz)
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox(),
    fBox( new G4Box(name,
                    hx / ClhepVGM::Units::Length(),
		    hy / ClhepVGM::Units::Length(),
		    hz / ClhepVGM::Units::Length()) )
{
/// Standard constructor to define box from parameters
/// \param hx half-length along the x axis in mm
/// \param hy half-length along the y axis in mm
/// \param hz half-length along the z axis in mm

  Geant4GM::SolidMap::Instance()->AddSolid(this, fBox);
}


//_____________________________________________________________________________
Geant4GM::Box::Box(G4Box* box,
                   G4ReflectedSolid* reflBox)
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox(),
    fBox(box)
{
/// Standard constructor to define box from G4 object

  if (reflBox)
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflBox);
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, box);
}

//_____________________________________________________________________________
Geant4GM::Box::Box()
  : VGM::ISolid(),
    VGM::IBox(),
    BaseVGM::VBox()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Box::Box(const Box& rhs)
  : VGM::ISolid(rhs),
    VGM::IBox(rhs),
    BaseVGM::VBox(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Box::~Box() {
//
}

//_____________________________________________________________________________
std::string Geant4GM::Box::Name() const
{
  return fBox->GetName();
}

//_____________________________________________________________________________
double Geant4GM::Box::XHalfLength() const
{
  return fBox->GetXHalfLength() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Box::YHalfLength() const
{
  return fBox->GetYHalfLength() * ClhepVGM::Units::Length();
}

//_____________________________________________________________________________
double Geant4GM::Box::ZHalfLength() const
{
  return fBox->GetZHalfLength() * ClhepVGM::Units::Length();
}


