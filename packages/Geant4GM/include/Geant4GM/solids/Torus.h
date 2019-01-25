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
/// \class Geant4GM::Torus
///
/// VGM implementation for Geant4 torus solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TORUS_H
#define GEANT4_GM_TORUS_H

#include "BaseVGM/solids/VTorus.h"

#include <string>

class G4Torus;
class G4ReflectedSolid;

namespace Geant4GM {

  class Torus : public BaseVGM::VTorus
  {
    public:
      Torus(const std::string& name,
            double rin, double rout, double rax,
	    double sphi, double dphi);
      Torus(G4Torus* torus,
            G4ReflectedSolid* reflTorus = 0);
      virtual ~Torus();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double AxialRadius() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Torus();
      Torus(const Torus& rhs);

    private:
      G4Torus* fTorus;
  };

}

#endif //GEANT4_GM_TORUS_H
