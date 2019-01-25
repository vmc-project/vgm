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
/// \class RootGM::DisplacedSolid
///
/// VGM implementation for Root displaced solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef ROOT_GM_DISPLACED_SOLID_H
#define ROOT_GM_DISPLACED_SOLID_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VDisplacedSolid.h"

class TGeoCompositeShape;
class TGeoMatrix;
class TGeoBBox;
class TGeoHalfSpace;

namespace RootGM {

  class DisplacedSolid : public BaseVGM::VDisplacedSolid
  {
    public:
      DisplacedSolid(const std::string& name,
                     VGM::ISolid* solid,
                     TGeoMatrix* displacement);

      DisplacedSolid(TGeoBBox* box);
      DisplacedSolid(TGeoHalfSpace* halfSpace);
      virtual ~DisplacedSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::ISolid*      ConstituentSolid() const;
      virtual VGM::Transform    Displacement() const;
      virtual bool              ToBeReflected() const;

    protected:
      DisplacedSolid();
      DisplacedSolid(const DisplacedSolid& rhs);

    private:
      static const std::string fgkNameExtension;

      TGeoCompositeShape* fCompositeShape;
      VGM::ISolid*  fConstituentSolid;
  };

}

inline bool RootGM::DisplacedSolid::ToBeReflected() const
{ return false; }

#endif //ROOT_GM_BOOLEAN_SOLID_H
