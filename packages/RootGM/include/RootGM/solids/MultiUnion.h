// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM::MultiUnion
///
/// VGM implementation for Root Boolean solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_MULTI_UNION_H
#define ROOT_GM_MULTI_UNION_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VMultiUnion.h"

#include "TGeoMatrix.h"

class TGeoShape;
class TGeoCompositeShape;
class TGeoMatrix;

namespace RootGM {

class MultiUnion : public BaseVGM::VMultiUnion
{
 public:
  MultiUnion(const std::string& name, 
    std::vector<VGM::ISolid*> constituents,
    std::vector<TGeoMatrix*> transforms);
  virtual ~MultiUnion();

  // methods
  virtual std::string Name() const;

  virtual int NofSolids() const;
  virtual ISolid* ConstituentSolid(int index) const;
  virtual VGM::Transform Transformation(int index) const;
  virtual bool ToBeReflected() const;

 protected:
  MultiUnion();
  MultiUnion(const MultiUnion& rhs);

 private:
  static const char fgkUnionChar;
  static const char fgkSeparator;

  TGeoCompositeShape* fCompositeShape;
  // keep input data as they cannot be accessed via TGeoCompositeShape
  std::vector<VGM::ISolid*> fConstituents;
  std::vector<TGeoMatrix*> fTransforms;
};

} // namespace RootGM

inline bool RootGM::MultiUnion::ToBeReflected() const { return false; }

#endif // ROOT_GM_MULTI_UNION_H
