// $Id$
//
// Class Box
// ---------------
// VGM implementation for Geant4 box solid.
//
// Author: Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_BOX_H
#define GEANT4_GM_BOX_H

#include <string>

#include "G4Box.hh"
#include "G4ReflectedSolid.hh"

#include "BaseVGM/solids/VBox.h"

namespace Geant4GM {

  class Box : public BaseVGM::VBox
  {
    public:
      Box(const std::string& name, 
          double hx, double hy, double hz);
      Box(G4Box* box, 
          G4ReflectedSolid* reflBox = 0);
      virtual ~Box();

      // methods
      virtual std::string Name() const;
      virtual double XHalfLength() const;
      virtual double YHalfLength() const;
      virtual double ZHalfLength() const;

    protected:
      Box() : BaseVGM::VBox() {}
      Box(const Box& rhs) : BaseVGM::VBox(rhs) {}

    private:
      G4Box* fBox;
  };

}

#endif //GEANT4_GM_BOX_H
