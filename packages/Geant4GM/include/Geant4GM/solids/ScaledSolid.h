// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007 - 2017, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::ScaledSolid
///
/// VGM implementation for Geant4 Scaled solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_SCALED_SOLID_H
#define GEANT4_GM_SCALED_SOLID_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VScaledSolid.h"

#include <iostream>

class G4VSolid;
class G4ScaledSolid;
class G4ReflectedSolid;

namespace Geant4GM {

  class ScaledSolid : public BaseVGM::VScaledSolid
  {
    public:
      ScaledSolid(const std::string& name,
                  VGM::ISolid* solid,
                  const HepGeom::Scale3D& scale3D);
      ScaledSolid(G4ScaledSolid* scaledSolid,
                  G4ReflectedSolid* reflectedScaled);
      virtual ~ScaledSolid();

      // methods
      virtual std::string Name() const;

      virtual VGM::ISolid*     ConstituentSolid() const;
      virtual VGM::Transform   Scale() const;
      virtual bool             ToBeReflected() const;

    protected:
      ScaledSolid();
      ScaledSolid(const ScaledSolid& rhs);

    private:
      G4ScaledSolid*  fScaledSolid;
      bool            fToBeReflected;
  };

}

inline bool Geant4GM::ScaledSolid::ToBeReflected() const
{ return fToBeReflected; }

#endif //GEANT4_GM_SCALED_SOLID_H
