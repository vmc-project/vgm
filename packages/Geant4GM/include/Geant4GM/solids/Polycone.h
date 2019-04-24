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
/// \class Geant4GM::Polycone
///
/// VGM implementation for Geant4 polycone solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_POLYCONE_H
#define GEANT4_GM_POLYCONE_H

#include "BaseVGM/solids/VPolycone.h"

#include <string>

class G4Cons;
class G4Polycone;
class G4Tubs;
class G4ReflectedSolid;

namespace Geant4GM {

class Polycone : public BaseVGM::VPolycone
{
 public:
  Polycone(const std::string& name, double sphi, double dphi, int nofZplanes,
    double* z, double* rin, double* rout);
  Polycone(G4Polycone* polycone, G4ReflectedSolid* reflPolycone = 0);
  Polycone(G4Cons* cons);
  Polycone(G4Tubs* tubs);
  virtual ~Polycone();

  // methods
  virtual std::string Name() const;
  virtual double StartPhi() const;
  virtual double DeltaPhi() const;
  virtual int NofZPlanes() const;
  virtual double* ZValues() const;
  virtual double* InnerRadiusValues() const;
  virtual double* OuterRadiusValues() const;

 protected:
  Polycone();
  Polycone(const Polycone& rhs);

 private:
  void CreateBuffers();

  static const int fgkMaxNofZPlanes;
  static double* fgZBuffer;
  static double* fgRinBuffer;
  static double* fgRoutBuffer;

  bool fIsReflected;
  double* fZValuesRefl;
  G4Polycone* fPolycone;
};

} // namespace Geant4GM

#endif // GEANT4_GM_POLYCONE_H
