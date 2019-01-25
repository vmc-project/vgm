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
// Class ScaledSolid
// ---------------------
// VGM implementation for Geant4 Scaled solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/transform.h"

#include "Geant4GM/solids/ScaledSolid.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4ScaledSolid.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::ScaledSolid::ScaledSolid(
                            const std::string& name,
                            VGM::ISolid* solid,
                            const HepGeom::Scale3D& scale3D)
  : VGM::ISolid(),
    VGM::IScaledSolid(),
    BaseVGM::VScaledSolid(),
    fScaledSolid(0),
    fToBeReflected(false)
{
/// Standard constructor to define Scaled solids via constituent
/// and a scale
/// \param solid constituent solids
/// \param scale  the CLHEP scale transformation

  // Get solid from the volumes map
  G4VSolid* g4Solid = Geant4GM::SolidMap::Instance()->GetSolid(solid);

  // Create G4 solid
  fScaledSolid = new G4ScaledSolid(name, g4Solid, scale3D);

  Geant4GM::SolidMap::Instance()->AddSolid(this, fScaledSolid);
}

//_____________________________________________________________________________
Geant4GM::ScaledSolid::ScaledSolid(G4ScaledSolid* scaledSolid,
                                   G4ReflectedSolid* reflectedScaled)
  : VGM::ISolid(),
    VGM::IScaledSolid(),
    BaseVGM::VScaledSolid(),
    fScaledSolid(scaledSolid),
    fToBeReflected(false)
{
/// Standard constructor to define Scaled solid via G4 object

  if ( reflectedScaled ) {
    fToBeReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflectedScaled);
  }
  else {
    Geant4GM::SolidMap::Instance()->AddSolid(this, fScaledSolid);
  }
}

//_____________________________________________________________________________
Geant4GM::ScaledSolid::ScaledSolid()
  : VGM::ISolid(),
    VGM::IScaledSolid(),
    BaseVGM::VScaledSolid()
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::ScaledSolid::ScaledSolid(const ScaledSolid& rhs)
  : VGM::ISolid(rhs),
    VGM::IScaledSolid(rhs),
    BaseVGM::VScaledSolid(rhs)
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::ScaledSolid::~ScaledSolid() {
//
}

//
// public methods
//

//_____________________________________________________________________________
std::string
Geant4GM::ScaledSolid::Name() const
{
// Returns the Scaled solid name
// ---

  return fScaledSolid->GetName();
}

//_____________________________________________________________________________
VGM::ISolid*
Geant4GM::ScaledSolid::ConstituentSolid() const
{
// Returns the constituent (unscaled) solid.
// ---

 G4VSolid* g4Solid =  fScaledSolid->GetUnscaledSolid();
 VGM::ISolid* solid = Geant4GM::SolidMap::Instance()->GetSolid(g4Solid);

 return solid;
}

//_____________________________________________________________________________
VGM::Transform
Geant4GM::ScaledSolid::Scale() const
{
// Returns the solid scale as three vector
// ---

  return ClhepVGM::TransformScale(fScaledSolid->GetScaleTransform());
}
