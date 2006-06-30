// $Id$
/// \ingroup Geant4GM_solids
//
/// \class Geant4GM::Ctubs
///
/// VGM implementation for cut tubs solid in Geant4.
/// The solid is realized as boolean subtraction of tube and
/// two boxes.
///
/// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_CTUBS_H
#define GEANT4_GM_CTUBS_H

#include <string>

#include "G4Tubs.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VCtubs.h"

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
      G4Tubs*   fTubs;
      G4VSolid* fBooleanSolid;
      G4double  fHz;
      G4ThreeVector  fNLow;
      G4ThreeVector  fNHigh;
  };

}

#endif //GEANT4_GM_CTUBS_H
