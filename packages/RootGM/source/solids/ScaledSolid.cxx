// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class ScaledSolid
// ---------------------
// VGM implementation for Root Scaled solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "RootGM/solids/ScaledSolid.h"
#include "RootGM/common/transform.h"
#include "RootGM/solids/SolidMap.h"

#include "TGeoMatrix.h"
#include "TGeoScaledShape.h"

//_____________________________________________________________________________
RootGM::ScaledSolid::ScaledSolid(
  const std::string& name, VGM::ISolid* solid, TGeoScale* scale)
  : VGM::ISolid(), VGM::IScaledSolid(), BaseVGM::VScaledSolid(), fScaledShape(0)
{
  /// Standard constructor to define Scaled solids via constituents
  /// \param solid constituent solids
  /// \param scale  the TGeo scale transformation

  // Get solid from the volumes map
  TGeoShape* rootSolid = RootGM::SolidMap::Instance()->GetSolid(solid);

  // Create new TGeo scaled solid
  fScaledShape = new TGeoScaledShape(name.data(), rootSolid, scale);

  RootGM::SolidMap::Instance()->AddSolid(this, fScaledShape);
}

//_____________________________________________________________________________
RootGM::ScaledSolid::ScaledSolid(TGeoScaledShape* scaledShape)
  : VGM::ISolid(),
    VGM::IScaledSolid(),
    BaseVGM::VScaledSolid(),
    fScaledShape(scaledShape)
{
  /// Standard constructor to define Scaled solid via Root object

  RootGM::SolidMap::Instance()->AddSolid(this, fScaledShape);
}

//_____________________________________________________________________________
RootGM::ScaledSolid::ScaledSolid()
  : VGM::ISolid(), VGM::IScaledSolid(), BaseVGM::VScaledSolid()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::ScaledSolid::ScaledSolid(const ScaledSolid& rhs)
  : VGM::ISolid(rhs), VGM::IScaledSolid(rhs), BaseVGM::VScaledSolid(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::ScaledSolid::~ScaledSolid()
{
  //
}

//
// public methods
//

//_____________________________________________________________________________
std::string RootGM::ScaledSolid::Name() const
{
  // Returns the Scaled solid name
  // ---

  return fScaledShape->GetName();
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::ScaledSolid::ConstituentSolid() const
{
  // Returns the first constituent solid.
  // ---

  TGeoShape* rootSolid = fScaledShape->GetShape();
  VGM::ISolid* solid = RootGM::SolidMap::Instance()->GetSolid(rootSolid);

  return solid;
}

//_____________________________________________________________________________
VGM::Transform RootGM::ScaledSolid::Scale() const
{
  // Returns the solid scale.
  // ---

  return TransformScale(*(fScaledShape->GetScale()));
}
