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
/// \class Geant4GM::Hype
///
/// VGM implementation for Geant4 hyperboloid solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_HYPE_H
#define GEANT4_GM_HYPE_H

#include "BaseVGM/solids/VHype.h"

#include <string>

class G4Hype;
class G4ReflectedSolid;

namespace Geant4GM {

class Hype : public BaseVGM::VHype
{
 public:
  Hype(const std::string& name, double r1, double r2, double stereo1,
    double stereo2, double hz);
  Hype(G4Hype* hype, G4ReflectedSolid* reflHype = 0);
  virtual ~Hype();

  // methods
  virtual std::string Name() const;
  virtual double InnerRadius() const;
  virtual double InnerStereoAngle() const;
  virtual double OuterRadius() const;
  virtual double OuterStereoAngle() const;
  virtual double ZHalfLength() const;

 protected:
  Hype();
  Hype(const Hype& rhs);

 private:
  G4Hype* fHype;
};

} // namespace Geant4GM

#endif // GEANT4_GM_HYPE_H
