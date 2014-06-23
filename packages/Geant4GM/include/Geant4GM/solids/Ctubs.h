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
/// \class Geant4GM::Ctubs
///
/// VGM implementation for cut tubs solid in Geant4.
/// The solid is realized as boolean subtraction of tube and
/// two boxes.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_CTUBS_H
#define GEANT4_GM_CTUBS_H

#include "BaseVGM/solids/VCtubs.h"

#include "globals.hh"
#include "G4ThreeVector.hh"

#include <string>

class G4Tubs;
class G4VSolid;
class G4ReflectedSolid;

namespace Geant4GM {

  class Ctubs : public BaseVGM::VCtubs
  {
    public:
      Ctubs(const std::string& name, 
              double rin, double rout, double hz, 
	      double sphi, double dphi,
	      double nxlow, double nylow, double nzlow,
	      double nxhigh, double nyhigh, double nzhigh);
      virtual ~Ctubs();

      // methods
      virtual std::string Name() const;
      virtual double InnerRadius() const;
      virtual double OuterRadius() const;
      virtual double ZHalfLength() const;
      virtual double StartPhi() const;
      virtual double DeltaPhi() const;
      virtual double NxLow() const;
      virtual double NyLow() const;
      virtual double NzLow() const;
      virtual double NxHigh() const;
      virtual double NyHigh() const;
      virtual double NzHigh() const;

    protected:
      Ctubs();
      Ctubs(const Ctubs& rhs);

    private:
      static const double fgkTolerance;
    
      G4Tubs*   fTubs;
      G4VSolid* fBooleanSolid;
      G4double  fHz;
      G4ThreeVector  fNLow;
      G4ThreeVector  fNHigh;
  };

}

#endif //GEANT4_GM_CTUBS_H
