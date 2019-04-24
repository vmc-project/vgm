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
/// \class Geant4GM::Cons
///
/// VGM implementation for Geant4 cons solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_CONS_H
#define GEANT4_GM_CONS_H

#include "BaseVGM/solids/VCons.h"

#include <string>

class G4Cons;
class G4ReflectedSolid;

namespace Geant4GM {

class Cons : public BaseVGM::VCons
{
 public:
  Cons(const std::string& name, double rin1, double rout1, double rin2,
    double rout2, double hz, double sphi, double dphi);
  Cons(G4Cons* cons, G4ReflectedSolid* reflCons = 0);
  virtual ~Cons();

  // methods
  virtual std::string Name() const;
  virtual double InnerRadiusMinusZ() const;
  virtual double OuterRadiusMinusZ() const;
  virtual double InnerRadiusPlusZ() const;
  virtual double OuterRadiusPlusZ() const;
  virtual double ZHalfLength() const;
  virtual double StartPhi() const;
  virtual double DeltaPhi() const;

 protected:
  Cons();
  Cons(const Cons& rhs);

 private:
  bool fIsReflected;
  G4Cons* fCons;
};

} // namespace Geant4GM

#endif // GEANT4_GM_CONS_H
