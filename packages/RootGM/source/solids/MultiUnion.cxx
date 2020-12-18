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
// Class MultiUnion
// ---------------------
// VGM implementation for Root Boolean solid
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "BaseVGM/common/utilities.h"
#include "VGM/solids/IDisplacedSolid.h"

#include "RootGM/common/transform.h"
#include "RootGM/solids/MultiUnion.h"
#include "RootGM/solids/SolidMap.h"

#include "TGeoBoolNode.h"
#include "TGeoCompositeShape.h"
#include "TString.h"

#include <cstdlib>

const char RootGM::MultiUnion::fgkUnionChar = '+';
const char RootGM::MultiUnion::fgkSeparator = ':';

//_____________________________________________________________________________
RootGM::MultiUnion::MultiUnion(const std::string& name,
  std::vector<VGM::ISolid*> constituents, std::vector<TGeoMatrix*> transforms)
  : VGM::ISolid(),
    VGM::IMultiUnion(),
    BaseVGM::VMultiUnion(),
    fCompositeShape(0),
    fConstituents(constituents),
    fTransforms(transforms)
{
  /// Standard constructor to define Boolean solids via constituents
  /// \param solids constituent solids
  /// \param transforms the constituent solid transformations

  TString formula;

  for (size_t i = 0; i < constituents.size(); ++i) {
    // Get solid displacement, if present, and update transformation
    // which will be used in Root node
    //
    VGM::ISolid* iConstSolid = constituents[i];
    TGeoHMatrix imatrix(*transforms[i]);

    // Get solid displacement, if present, and update transformation
    // which will be used in Root node
    if (iConstSolid->Type() == VGM::kDisplaced) {
      VGM::IDisplacedSolid* displacedSolid =
        dynamic_cast<VGM::IDisplacedSolid*>(iConstSolid);
      TGeoHMatrix displacement(
        *RootGM::CreateTransform(displacedSolid->Displacement()));
      iConstSolid = displacedSolid->ConstituentSolid();
      imatrix = imatrix * displacement;
    }

    // Get Root solid
    TGeoShape* irootSolid = RootGM::SolidMap::Instance()->GetSolid(iConstSolid);
    TString irootSolidName = irootSolid->GetName();
    // CHECK
    // The Root factory should attribute unique name
    if (i > 0) {
      formula += fgkUnionChar;
    }
    formula += irootSolidName;

    TGeoMatrix* inewMatrix = 0;
    if (!imatrix.IsIdentity()) {
      inewMatrix = new TGeoCombiTrans(imatrix);
      // set matrix name
      TString tname = "t";
      tname += i;
      inewMatrix->SetName(tname);
      inewMatrix->RegisterYourself();
      // add transformation to formula
      formula += fgkSeparator;
      formula += tname;
    }
  }

  // std::cout << "RootGM::MultiUnion::MultiUnion formula: " << formula <<
  // std::endl;
  fCompositeShape = new TGeoCompositeShape(name.data(), formula.Data());
  RootGM::SolidMap::Instance()->AddSolid(this, fCompositeShape);
}

//_____________________________________________________________________________
RootGM::MultiUnion::MultiUnion()
  : VGM::ISolid(), VGM::IMultiUnion(), BaseVGM::VMultiUnion()
{
  /// Protected default constructor
}

//_____________________________________________________________________________
RootGM::MultiUnion::MultiUnion(const MultiUnion& rhs)
  : VGM::ISolid(rhs), VGM::IMultiUnion(rhs), BaseVGM::VMultiUnion(rhs)
{
  /// Protected copy constructor
}

//_____________________________________________________________________________
RootGM::MultiUnion::~MultiUnion()
{
  //
}

//
// public methods
//

//_____________________________________________________________________________
std::string RootGM::MultiUnion::Name() const
{
  // Returns the Boolean solid name
  // ---

  return fCompositeShape->GetName();
}

//_____________________________________________________________________________
int RootGM::MultiUnion::NofSolids() const
{
  // Returns the Boolean solid name
  // ---

  return int(fConstituents.size());
}

//_____________________________________________________________________________
VGM::ISolid* RootGM::MultiUnion::ConstituentSolid(int index) const
{
  // Returns the index-th constituent solid.
  // ---

  return fConstituents[index];
}

//_____________________________________________________________________________
VGM::Transform RootGM::MultiUnion::Transformation(int index) const
{
  // Returns the displacement of the index-th constituent solid
  // ---

  return Transform(*fTransforms[index]);
}
