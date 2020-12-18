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
/// \class Geant4GM::MultiUnion
///
/// VGM implementation for Geant4 Boolean solid
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MULTI_UNION_H
#define GEANT4_GM_MULTI_UNION_H

#include "VGM/common/Transform.h"

#include "BaseVGM/solids/VMultiUnion.h"

#include "G4Transform3D.hh"

#include <iostream>
#include <vector>

class G4VSolid;
class G4MultiUnion;
class G4ReflectedSolid;

namespace Geant4GM {

class MultiUnion : public BaseVGM::VMultiUnion
{
 public:
  MultiUnion(const std::string& name, 
    std::vector<VGM::ISolid*> constituents,
    std::vector<G4Transform3D> transforms);
  MultiUnion(
    G4MultiUnion* MultiUnion, G4ReflectedSolid* reflected);
  virtual ~MultiUnion();

  // methods
  virtual std::string Name() const;

  virtual int NofSolids() const;
  virtual ISolid* ConstituentSolid(G4int index) const;
  virtual VGM::Transform Transformation(G4int index) const;
  virtual bool ToBeReflected() const;

 protected:
  MultiUnion();
  MultiUnion(const MultiUnion& rhs);

 private:
  G4MultiUnion* fMultiUnion;
  bool fToBeReflected;
};

} // namespace Geant4GM

inline bool Geant4GM::MultiUnion::ToBeReflected() const
{
  return fToBeReflected;
}

#endif // GEANT4_GM_MULTI_UNION_H
