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
/// \class Geant4GM::Trd
///
/// VGM implementation for Geant4 trd solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_TRD_H
#define GEANT4_GM_TRD_H

#include "BaseVGM/solids/VTrd.h"

#include <string>

class G4Trd;
class G4ReflectedSolid;

namespace Geant4GM {

  class Trd : public BaseVGM::VTrd
  {
    public:
      Trd(const std::string& name, 
          double hx1, double hx2, double hy1, double hy2, double hz);
      Trd(G4Trd* trd, 
          G4ReflectedSolid* reflTrd = 0);
      virtual ~Trd();

      // methods
      virtual std::string Name() const;
      virtual double XHalfLengthMinusZ() const;
      virtual double XHalfLengthPlusZ() const;
      virtual double YHalfLengthMinusZ() const;
      virtual double YHalfLengthPlusZ() const;
      virtual double ZHalfLength() const;

    protected:
      Trd();
      Trd(const Trd& rhs);

    private:
      bool    fIsReflected;
      G4Trd*  fTrd;
  };

}

#endif //GEANT4_GM_TRD_H
