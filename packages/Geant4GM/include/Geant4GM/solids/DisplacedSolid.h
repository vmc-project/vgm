// $Id$

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::DisplacedSolid
///
/// VGM implementation for Geant4 displaced solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_DISPLACED_SOLID_H
#define GEANT4_GM_DISPLACED_SOLID_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VDisplacedSolid.h"

#include <iostream>

class G4VSolid;
class G4DisplacedSolid;
class G4ReflectedSolid;

namespace Geant4GM {

class DisplacedSolid : public BaseVGM::VDisplacedSolid
{
 public:
  DisplacedSolid(const std::string& name, VGM::ISolid* constituentSolid,
    CLHEP::HepRotation* rotation, const CLHEP::Hep3Vector& translation);
  DisplacedSolid(
    G4DisplacedSolid* displacedSolid, G4ReflectedSolid* reflectedDisplaced);
  virtual ~DisplacedSolid();

  // methods
  virtual std::string Name() const;

  virtual VGM::ISolid* ConstituentSolid() const;
  virtual VGM::Transform Displacement() const;
  virtual bool ToBeReflected() const;

 protected:
  DisplacedSolid();
  DisplacedSolid(const DisplacedSolid& rhs);

 private:
  G4DisplacedSolid* fDisplacedSolid;
  bool fToBeReflected;
};

} // namespace Geant4GM

inline bool Geant4GM::DisplacedSolid::ToBeReflected() const
{
  return fToBeReflected;
}

#endif // GEANT4_GM_DISPLACED_SOLID_H
