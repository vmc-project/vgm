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
/// \class Geant4GM::Polyhedra
///
/// VGM implementation for Geant4 polyhedra solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_POLYHEDRA_H
#define GEANT4_GM_POLYHEDRA_H

#include "BaseVGM/solids/VPolyhedra.h"

#include <string>

class G4Polyhedra;
class G4ReflectedSolid;

namespace Geant4GM {

class Polyhedra : public BaseVGM::VPolyhedra
{
 public:
  Polyhedra(const std::string& name, double sphi, double dphi, int nofSides,
    int nofZplanes, double* z, double* rin, double* rout);
  Polyhedra(G4Polyhedra* polyhedra, G4ReflectedSolid* reflPolyhedra = 0);
  virtual ~Polyhedra();

  // methods
  virtual std::string Name() const;
  virtual double StartPhi() const;
  virtual double DeltaPhi() const;
  virtual int NofSides() const;
  virtual int NofZPlanes() const;
  virtual double* ZValues() const;
  virtual double* InnerRadiusValues() const;
  virtual double* OuterRadiusValues() const;

 protected:
  Polyhedra();
  Polyhedra(const Polyhedra& rhs);

 private:
  void CreateBuffers();

  static const int fgkMaxNofZPlanes;
  static double* fgZBuffer;
  static double* fgRinBuffer;
  static double* fgRoutBuffer;

  bool fIsReflected;
  double* fZValuesRefl;
  G4Polyhedra* fPolyhedra;
};

} // namespace Geant4GM

#endif // GEANT4_GM_POLYHEDRA_H
