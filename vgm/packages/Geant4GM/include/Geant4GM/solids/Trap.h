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
/// \class Geant4GM::Trap
///
/// VGM implementation for Geant4 trap solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TRAP_H
#define GEANT4_GM_TRAP_H

#include <string>

#include "G4Trap.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VTrap.h"

namespace Geant4GM {

  class Trap : public BaseVGM::VTrap
  {
    public:
      Trap(const std::string& name, 
           double hz, double theta, double phi,
           double dy1, double dx1, double dx2, double alpha1, 
           double dy2, double dx3, double dx4, double alpha2);
      Trap(G4Trap* trap, 
           G4ReflectedSolid* reflTrap = 0);
      virtual ~Trap();

      // methods
      virtual std::string Name() const;
      virtual double ZHalfLength() const;
      virtual double Theta() const;
      virtual double Phi() const;
      virtual double YHalfLengthMinusZ() const;
      virtual double XHalfLengthMinusZMinusY() const;
      virtual double XHalfLengthMinusZPlusY() const;
      virtual double AlphaMinusZ() const;
      virtual double YHalfLengthPlusZ() const;
      virtual double XHalfLengthPlusZMinusY() const;
      virtual double XHalfLengthPlusZPlusY() const;
      virtual double AlphaPlusZ() const;

    protected:
      Trap();
      Trap(const Trap& rhs);

    private:
      bool    fIsReflected;
      G4Trap* fTrap;
  };

}

#endif //GEANT4_GM_TRAP_H
