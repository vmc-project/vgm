// $Id$
//
// Class Para
// ---------------
// VGM implementation for Geant4 para solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_PARA_H
#define GEANT4_GM_PARA_H

#include <string>

#include "G4Para.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VPara.h"

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
      Para() : BaseVGM::VPara() {}
      Para(const Para& rhs) : BaseVGM::VPara(rhs) {}

    private:
      bool    fIsReflected;
      G4Para* fPara;
  };

}

#endif //GEANT4_GM_PARA_H
