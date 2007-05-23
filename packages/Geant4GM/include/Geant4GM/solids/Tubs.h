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
/// \class Geant4GM::Tubs
///
/// VGM implementation for Geant4 tubs solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TUBS_H
#define GEANT4_GM_TUBS_H

#include <string>

#include "G4Tubs.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VTubs.h"

namespace Geant4GM {

  class Tubs : public BaseVGM::VTubs
  {
    public:
      Tubs(const std::string& name, 
              double rin, double rout, double hz, 
	      double sphi, double dphi);
      Tubs(G4Tubs* tubs, 
              G4ReflectedSolid* reflTubs = 0);
      virtual ~Tubs();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;

    protected:
      Tubs();
      Tubs(const Tubs& rhs);

    private:
      G4Tubs* fTubs;
  };

}

#endif //GEANT4_GM_TUBS_H
