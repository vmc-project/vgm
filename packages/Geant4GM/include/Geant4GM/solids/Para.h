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
/// \class Geant4GM::Para
///
/// VGM implementation for Geant4 para solid.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PARA_H
#define GEANT4_GM_PARA_H

#include "BaseVGM/solids/VPara.h"

#include <string>

class G4Para;
class G4ReflectedSolid;

namespace Geant4GM {

  class Para : public BaseVGM::VPara
  {
    public:
      Para(const std::string& name,
           double dx, double dy, double dz,
	   double alpha, double theta, double phi);
      Para(G4Para* para,
           G4ReflectedSolid* reflPara = 0);
      virtual ~Para();

      // methods
      virtual std::string Name() const;

      virtual double XHalfLength() const;
      virtual double YHalfLength() const;
      virtual double ZHalfLength() const;
      virtual double Alpha() const;
      virtual double Theta() const;
      virtual double Phi() const;

    protected:
      Para();
      Para(const Para& rhs);

    private:
      bool    fIsReflected;
      G4Para* fPara;
  };

}

#endif //GEANT4_GM_PARA_H
