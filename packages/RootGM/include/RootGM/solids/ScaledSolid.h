// $Id$

// -----------------------------------------------------------------------
// The RootGM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2017, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup RootGM_solids
//
/// \class RootGM::ScaledSolid
///
/// VGM implementation for Root Scaled solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_SCALED_SOLID_H
#define ROOT_GM_SCALED_SOLID_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VScaledSolid.h"

class TGeoShape;
class TGeoScaledShape;
class TGeoScale;

namespace RootGM {

  class ScaledSolid : public BaseVGM::VScaledSolid
  {
    public:
      ScaledSolid(const std::string& name,
                   VGM::ISolid* solid,
                   TGeoScale* scale);
      ScaledSolid(TGeoScaledShape* scaledShape);
      virtual ~ScaledSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::ISolid*    ConstituentSolid() const;
      virtual VGM::Transform  Scale() const;
      virtual bool            ToBeReflected() const;

    protected:
      ScaledSolid();
      ScaledSolid(const ScaledSolid& rhs);

    private:
      TGeoScaledShape* fScaledShape;
  };

}

inline bool RootGM::ScaledSolid::ToBeReflected() const
{ return false; }

#endif //ROOT_GM_SCALED_SOLID_H
