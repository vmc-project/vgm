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
// Class DisplacedSolid
// ---------------------
// VGM implementation for Geant4 displaced solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/transform.h"

#include "Geant4GM/solids/DisplacedSolid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4DisplacedSolid.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::DisplacedSolid::DisplacedSolid(const std::string& name,
  VGM::ISolid* constituentSolid, CLHEP::HepRotation* rotation,
  const CLHEP::Hep3Vector& translation)
  : VGM::ISolid(),
    VGM::IDisplacedSolid(),
    BaseVGM::VDisplacedSolid(),
    fDisplacedSolid(0),
    fToBeReflected(false)
{
  /// Standard constructor to define displaced solids via constituent
  /// \param constituentSolid constituent solids
  /// \param rotation, translation  the CLHEP rotation and translation of
  ///        the constituent solid

  // Get solid from the volumes map
  G4VSolid* g4Solid =
    Geant4GM::SolidMap::Instance()->GetSolid(constituentSolid);

  // Create displaced solid
  fDisplacedSolid = new G4DisplacedSolid(name, g4Solid, rotation, translation);

  Geant4GM::SolidMap::Instance()->AddSolid(this, fDisplacedSolid);
}

//_____________________________________________________________________________
Geant4GM::DisplacedSolid::DisplacedSolid(
  G4DisplacedSolid* displacedSolid, G4ReflectedSolid* reflectedDisplaced)
  : VGM::ISolid(),
    VGM::IDisplacedSolid(),
    BaseVGM::VDisplacedSolid(),
    fDisplacedSolid(displacedSolid),
    fToBeReflected(false)
{
  /// Standard constructor to define Displaced solid via G4 object

  if (reflectedDisplaced) {
    fToBeReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflectedDisplaced);
  }
  else
    Geant4GM::SolidMap::Instance()->AddSolid(this, fDisplacedSolid);
}

//_____________________________________________________________________________
Geant4GM::DisplacedSolid::DisplacedSolid()
  : VGM::ISolid(), VGM::IDisplacedSolid(), BaseVGM::VDisplacedSolid()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::DisplacedSolid::DisplacedSolid(const DisplacedSolid& rhs)
  : VGM::ISolid(rhs), VGM::IDisplacedSolid(rhs), BaseVGM::VDisplacedSolid(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::DisplacedSolid::~DisplacedSolid()
{
  //
}

//
// public methods
//

//_____________________________________________________________________________
std::string Geant4GM::DisplacedSolid::Name() const
{
  // Returns the Displaced solid name
  // ---

  return fDisplacedSolid->GetName();
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::DisplacedSolid::ConstituentSolid() const
{
  // Returns the constituent solid.
  // ---

  G4VSolid* g4Solid = fDisplacedSolid->GetConstituentMovedSolid();

  VGM::ISolid* solid = Geant4GM::SolidMap::Instance()->GetSolid(g4Solid);

  return solid;
}

//_____________________________________________________________________________
VGM::Transform Geant4GM::DisplacedSolid::Displacement() const
{
  // Returns the first constituent solid.
  // ---

  return ClhepVGM::Transform(fDisplacedSolid->GetObjectRotation(),
    fDisplacedSolid->GetObjectTranslation());
}
