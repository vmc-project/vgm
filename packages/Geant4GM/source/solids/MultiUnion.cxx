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
// Class MultiUnion
// ---------------------
// VGM implementation for Geant4 multi union solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "ClhepVGM/transform.h"

#include "Geant4GM/solids/MultiUnion.h"
#include "Geant4GM/solids/SolidMap.h"

#include "G4MultiUnion.hh"
#include "G4ReflectedSolid.hh"

//_____________________________________________________________________________
Geant4GM::MultiUnion::MultiUnion(const std::string& name,
  std::vector<VGM::ISolid*> constituents, std::vector<G4Transform3D> transforms)
  : VGM::ISolid(),
    VGM::IMultiUnion(),
    BaseVGM::VMultiUnion(),
    fMultiUnion(0),
    fToBeReflected(false)
{
  /// Standard constructor to define Boolean solids via constituents
  /// \param solids constituent solids
  /// \param transforms the constituent solid transformations

  fMultiUnion = new G4MultiUnion(name);

  for (size_t i = 0; i < constituents.size(); ++i) {
    // Get solid from the volumes map
    G4VSolid* g4Solid =
      Geant4GM::SolidMap::Instance()->GetSolid(constituents[i]);
    // Add constituent
    fMultiUnion->AddNode(*g4Solid, transforms[i]);
  }
  // Finally close the structure
  fMultiUnion->Voxelize();

  Geant4GM::SolidMap::Instance()->AddSolid(this, fMultiUnion);
}

//_____________________________________________________________________________
Geant4GM::MultiUnion::MultiUnion(
  G4MultiUnion* multiUnion, G4ReflectedSolid* reflected)
  : VGM::ISolid(),
    VGM::IMultiUnion(),
    BaseVGM::VMultiUnion(),
    fMultiUnion(multiUnion),
    fToBeReflected(false)
{
  /// Standard constructor to define Boolean solid via G4 object

  if (reflected) {
    fToBeReflected = true;
    Geant4GM::SolidMap::Instance()->AddSolid(this, reflected);
  }
  else {
    Geant4GM::SolidMap::Instance()->AddSolid(this, fMultiUnion);
  }
}

//_____________________________________________________________________________
Geant4GM::MultiUnion::MultiUnion()
  : VGM::ISolid(), VGM::IMultiUnion(), BaseVGM::VMultiUnion()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::MultiUnion::MultiUnion(const MultiUnion& rhs)
  : VGM::ISolid(rhs), VGM::IMultiUnion(rhs), BaseVGM::VMultiUnion(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::MultiUnion::~MultiUnion()
{
  //
}

//
// public methods
//

//_____________________________________________________________________________
std::string Geant4GM::MultiUnion::Name() const
{
  // Returns the Boolean solid name
  // ---

  return fMultiUnion->GetName();
}

//_____________________________________________________________________________
G4int Geant4GM::MultiUnion::NofSolids() const
{
  // Returns the number of constituent solids.
  // ---

  return fMultiUnion->GetNumberOfSolids();
}

//_____________________________________________________________________________
VGM::ISolid* Geant4GM::MultiUnion::ConstituentSolid(G4int index) const
{
  // Returns the index-th constituent solid.
  // ---

  G4VSolid* g4Solid = fMultiUnion->GetSolid(index);

  return Geant4GM::SolidMap::Instance()->GetSolid(g4Solid);
}

//_____________________________________________________________________________
VGM::Transform Geant4GM::MultiUnion::Transformation(G4int index) const
{
  // Returns the displacement of the index-th constituent solid
  // ---

  return ClhepVGM::Transform(fMultiUnion->GetTransformation(index));
}
