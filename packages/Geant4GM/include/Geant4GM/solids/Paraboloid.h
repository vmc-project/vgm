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
/// \class Geant4GM::Paraboloid
///
/// VGM implementation for Geant4 paraboloid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PARABOLOID_H
#define GEANT4_GM_PARABOLOID_H

#include "BaseVGM/solids/VParaboloid.h"

#include <string>

class G4Paraboloid;
class G4ReflectedSolid;

namespace Geant4GM {

class Paraboloid : public BaseVGM::VParaboloid
{
 public:
  Paraboloid(const std::string& name, double r1, double r2, double hz);
  Paraboloid(G4Paraboloid* paraboloid, G4ReflectedSolid* reflParaboloid = 0);
  virtual ~Paraboloid();

  // methods
  virtual std::string Name() const;
  virtual double RadiusMinusZ() const;
  virtual double RadiusPlusZ() const;
  virtual double ZHalfLength() const;

 protected:
  Paraboloid();
  Paraboloid(const Paraboloid& rhs);

 private:
  bool fIsReflected;
  G4Paraboloid* fParaboloid;
};

} // namespace Geant4GM

#endif // GEANT4_GM_PARABOLOID_H
